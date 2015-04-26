#include <cstdio>
#include <limits.h>
#include <sys/types.h>  	// socket , bind , accept   
#include <sys/socket.h> 	// socket , bind , socklen_t , accept
#include <poll.h>       	// poll, struct pollfd
#include <netdb.h>      	// socklen_t
#include <netinet/in.h> 	// struct sockaddr_in , sockaddr
#include <errno.h> 		// errno
#include <unistd.h>             // read, write
#include <strings.h>		// bzero
#include <iostream>             // cout , endl , cin

#include <bson.h>               // BSONObj 
#include "../utils/message.h"   // struct message_t

#define MAXLINE 	1024*2
#define OPEN_MAX 	1024
#define SERVER_PORT 	1027
#define INFTIM		1024

using namespace std ;
using namespace bson ;

//add method parseMessage
/**
method :
    this method is used to extract message's data 
    from char *pBuffer , into BSONObj this object

    int parseMessage( char *pBuffer [in], BSONObj &msgData [out])
    return:
	0 : success extracting  message data into BSONObj
        -1: failed extracting   message data into BSONObj 
    
   [in] : means this parameter is pass-in-value parameter
   [out] : means this parameter is value-result which can 
	   also be recognized as the return value of the method 
*/ 

int parseMessage ( char *pBuffer, BSONObj &msgData )
{
  if ( pBuffer == NULL )
  {
	perror ("message is invalid ") ;
	return -1 ;
  }

  message_t *pMessage = (message_t*)(pBuffer) ;
 
  if ( pMessage->header.len < sizeof(message_t) )
  {
	perror ("message content is invalid ") ;
	return -1 ;
  }

 // cout << pMessage->header.len << endl ;
//  cout << &pMessage->data[0] << endl ;

//  BSONObjBuilder builder ;
//  builder.append ("", &(pMessage->data[0])) ; 

  msgData = BSONObj(&pMessage->data[0]) ;

  
  return 0 ;
}


int main ( int argc , char ** argv )
{
	int i , maxi , listenfd , connfd , sockfd ;
	int nready ;
	ssize_t n ;
	char buf[MAXLINE] ;
	socklen_t client_len  ;	
	struct pollfd client[OPEN_MAX] ;
	struct sockaddr_in client_addr , server_addr ;
	
	listenfd = socket ( AF_INET , SOCK_STREAM , 0 ) ;
	bzero ( &server_addr , sizeof(struct sockaddr_in)) ;
	
	server_addr.sin_family = AF_INET ;
	server_addr.sin_addr.s_addr = htonl (INADDR_ANY) ;
	server_addr.sin_port = htons (  SERVER_PORT  ) ;
	
	bind (listenfd , (struct sockaddr*)&server_addr ,
			sizeof(struct sockaddr_in) ) ;
	
	listen ( listenfd , 10 ) ;
	
	client[0].fd = listenfd ;
	client[0].events = POLLRDNORM ; // poll read normal
	
	for ( i = 1 ; i < OPEN_MAX ; i++ )
	{
	  client[i].fd = -1;
	}
	
	maxi = 0 ;
	
	for ( ;  ; )
	{
		nready = poll (client , maxi+1 , INFTIM) ;
	
	       if ( client[0].revents & POLLRDNORM )
	       {
		   // this means new client connection request come
		   client_len = sizeof( struct sockaddr_in ) ;
		   connfd = accept ( listenfd , (struct sockaddr*)&client_addr , 
			&client_len  ) ;
		   
		   // updates maxi, and check if i out of limition of OPEN_MAX
		   for ( i = 1 ; i < OPEN_MAX ; i++ )
		   {
			if ( client[i].fd < 0  )
			{
			   client[i].fd = connfd ;
			   break ;
			}	
		   } // for 
		
		  if ( i == OPEN_MAX )
		  {
			perror ("too many client requests ") ;
			return -1 ;
		  }
		
		  client[i].events = POLLRDNORM ;
		  
                  if ( i > maxi )
		     maxi = i ;
			
		  if ( --nready <= 0 )
			continue ;
	       }  // if
		
		for ( i = 1 ; i <= maxi ; i++ )
		{
		     if ( ( sockfd = client[i].fd ) < 0 )
			continue ; // continue the sub for cycle
			
		    if ( client[i].revents & (POLLRDNORM | POLLERR) )
		   {
         	  	   if ( ( n = read(sockfd , buf , MAXLINE)) < 0 )
		     	{
				// read n < 0 , it must some error happen
		  		// if client reset connection , release client[i].fd
				// else return error code 
		        	if ( errno == ECONNRESET )
			        {
					// this means client reset connection
					close (sockfd) ;
					client[i].fd = -1 ;
				}
				else
				{
					perror ("error when server read from client") ;
					return -1 ;
				}  

		     	}
		     	else if ( n == 0 )
		     	{
				// this means client close connection 
				close (sockfd) ;
				client[i].fd = -1 ;
		     	}
		     	else
		     	{
		
				//cout << "n = " << n << endl ;
				
	                        BSONObj msgData ;
				
				parseMessage (buf , msgData) ;
 				cout << msgData.toString() << endl ;

				// n > 0 , server read something from client
	                       // cout << "receive message len " << msgData.objsize() <<endl ; 
			}

		  } // if POLLRDNORM | POLLERROR
	
		}// for
		
	} // main cycle 
	
	return 0 ;
}
