#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <cstdio>
#include <errno.h>
#include <time.h>

#include "my_pipe.h"

/**
  in class myPipe 

  pipes[0] ---- > is equal to the server's readin socket descriptor 
  		 and server's accept method return socket descriptor 

  pipes[1] ---- > is just like the client's write in socket descriptor
  
  socket_fd ---> is like the server's listen socket descriptor   

*/


myPipe::myPipe ()
{
  int sock_fd = 0 ; 
  int ret = 0 ;

  struct timeval timeout = {0,0} ;  // 0 s

  static int port_num = 1027 ;
  struct sockaddr_in  sock_addr ;
  
  sock_fd = (int) socket( AF_INET , SOCK_STREAM , IPPROTO_TCP ) ;
 
  if ( 0 > sock_fd )
  {
      perror (" socket error ") ;
      return ;
  }

  pipes[1] = (int) socket (AF_INET , SOCK_STREAM , IPPROTO_TCP ) ;
 
  if ( 0 > pipes[1] )
  {
       // if we apply for client's socket fd failed , do not forget 
      // close sock_fd 
	close ( sock_fd ) ;
        return ;
  }

  /* here we initialize the address */
  sock_addr.sin_addr.s_addr = inet_addr ("127.0.0.1") ; // we use the loop address
  sock_addr.sin_family      = AF_INET ;

  int try_times = 25 ; // we would like try 25 times until we get a appropriate ip port
  
  // you may wonder what's the definition of an appropriate port ?
  // here it is : set the appropriate port to the sock_addr 
  // and then bind the sock_addr to the sock_fd correctly 
 //  the port is the so-called appropriate 


  while ( port_num++ && try_times-- > 0 )
  {
	sock_addr.sin_port = htons ( (short) port_num ) ;
	
	if ( bind ( sock_fd , (struct sockaddr *)&sock_addr , sizeof(sock_addr)) < 0 )
	{
		// on ,port_num is not good , we have to increase it by 1 
		perror ("failed bind the socke_addr to sock_fd ") ;
        }
	
	else 
		// this branch we get the appropriate port we want 
		break ;
  }
//-------------while end -------------------
 
 if ( try_times == 0 ) // this means we tried try_times and we didn't get the port num we want
 {
	perror ("failed to get correct port which can bind to sock_fd") ;
	
	// do not forget close the two socket descriptor
	close ( sock_fd ) ;
	close ( pipes[1] ) ;
	
	return ;
 }

// ---------- if we get here , that means we got correct port num and finish binding----------------
 
 ret = listen ( sock_fd , 1 ) ; // 1 means listen-back queue length is limited to 1
 
 if ( ret != 0 )
 {
	perror ( "failed to execute listen ") ;

	// this branch means listen method failed 
	close ( sock_fd ) ;
	close ( pipes[1] ) ;
	return ;
 }
 
// method following is used to set receiving buffer size

ret = setsockopt ( pipes[1] , SOL_SOCKET , SO_RCVTIMEO ,  &timeout ,sizeof(timeout) ); 
 
if ( ret != 0 ) // this means setsockopt met error
{
	perror ("failed to execute setsocket method ") ;
	printf ("ret  %d  errno : %d \n" , ret , errno  ) ;
	close ( sock_fd ) ;
	close ( pipes[1] ) ;
	return ;
}

// here we use the write myPipe connect to local loop address

ret = connect ( pipes[1] , (struct sockaddr *)&sock_addr , sizeof ( sock_addr )) ;

if ( ret != 0 ) // something wrong
{
	perror ("failed to execute connect method ") ;
	close ( pipes[1] ) ;
	close ( sock_fd ) ;
	
	return ;
} 

// here we use the accept method to accept 
// connection requests send to sock_fd 

pipes[0] = accept ( sock_fd , NULL , NULL ) ;

if ( pipes[0] <= 0 ) // something wrong with accept 
{
	perror ("failed to execute accept method ") ;
        close ( pipes[1] ) ;
	close ( sock_fd ) ;
	
	return ;
}


       printf ("you create a pipe successfully \n") ;

}

myPipe::~myPipe ()
{
	close ( pipes[0] ) ;
	close ( pipes[1] ) ;
}

/**
  method write contents into myPipe 
  use myPipes[1] as descriptor
  const is used to let the method caller could not change 
  the value of the pointer , cause the content space is read-only 

  buf -> pointer points to the to be written space 
  len -> length of to be written content space

**/
int  myPipe::write_in_pipe ( const void *buf , int len )
{
    return send ( pipes[1] , ( const char *) buf , len , 0 ) ;
}

/**
  both send and recv method 's 0 here means :
  if no one receives ( sends ) data from ( to ) me 
  i will not blocked waitting 
*/

int myPipe::read_from_pipe ( void *buf , int len )
{
    return recv ( pipes[0] , (char *)buf , len , 0 ) ;
}

int myPipe::get_read_descr ()
{
    return pipes[0] ; 
}
