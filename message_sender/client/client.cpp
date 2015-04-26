#include <cstdio>    // perror 
#include <cstring>   // string
#include <strings.h>  // memset
#include <iostream> 
#include <sys/types.h> // AF_INET, SOCK_STREAM
#include <sys/socket.h> // socket , connect
#include <arpa/inet.h> // inet_aton 
#include <netinet/in.h>
#include <unistd.h>


#define SERVER_PORT  1027
#define SERVER_IP   "10.0.2.15"
#define MAXLINE      1024*2

using namespace std ;


int main ( int argc , char **argv )
{
   char buf [MAXLINE] ;
   ssize_t n ;  // message content length
   struct sockaddr_in server_addr ;
   int connfd ;
   int ret ;
   string msg ;
	
   connfd = socket (AF_INET , SOCK_STREAM , 0 ) ;
   bzero (&server_addr , sizeof(struct sockaddr_in)) ;
  
   server_addr.sin_family = AF_INET ;
   server_addr.sin_port   = htons (SERVER_PORT) ;
   inet_aton (SERVER_IP , &server_addr.sin_addr ) ;
   
   ret = connect ( connfd , (struct sockaddr*)&server_addr , sizeof(struct sockaddr_in) ) ;	
  

 if ( ret  < 0 )
  {
	perror ("failed connect") ;
	return -1;
  }
  
  cout << "input message "<< endl ;
  cin >> msg ;
  
  write (connfd , msg.c_str() , msg.size() ) ;
	

 return 0 ;
}
