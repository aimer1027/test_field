#include <cstdio>    // perror 
#include <cstring>   // string
#include <strings.h>  // memset
#include <iostream> 
#include <sys/types.h> // AF_INET, SOCK_STREAM
#include <sys/socket.h> // socket , connect
#include <arpa/inet.h> // inet_aton 
#include <netinet/in.h>
#include <unistd.h>

#include <bson.h>      // BSONObj , BSONObjBuilder

#include "../utils/message.h"  // struct message_t

#define SERVER_PORT  1027
#define SERVER_IP   "10.0.2.15"
#define MAXLINE      1024*2

using namespace std ;
using namespace bson ;

// add method buildMessage  here
/**
method  :
 int buildMessage ( char **ppBuffer[out], int *pBufferSize[out], BSONObj *obj[in] )
 return :
        0 if success building a message
        -1 if failed building a message 
*/

int buildMessage ( char **ppBuffer , int *pBufferSize , BSONObj *obj )
{
   message_t *pMessage = NULL ;
   int size = sizeof(message_t) ;

   if ( obj != NULL )
       size += obj->objsize() ;
   
   if ( size > *pBufferSize )
   {
	*ppBuffer = (char*)realloc(*ppBuffer , size*sizeof(char)) ;
         *pBufferSize = size ;
		
         if ( *ppBuffer == NULL )
	 {
		perror ("failed to realloc space for ppBuffer") ;
		return -1 ;
         }
   }
  
  pMessage = (message_t*)(*ppBuffer) ;
  pMessage->header.len = size ;
 
  if ( obj != NULL )
  {
    memcpy (&pMessage->data[0] , obj->objdata() , obj->objsize() ) ;
  }
 
  return 0 ;
}


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
 
  BSONObjBuilder builder ;
  
  builder.append ("message data", msg.c_str ()) ;  

  BSONObj obj = builder.obj() ;
  
  char *pBuffer = NULL ;
  int pBufferSize = 0 ;
  
  cout << obj.toString() << endl ;

  cout << "-------- /test build message/ ------------"<<endl ;
  
  buildMessage (&pBuffer , &pBufferSize , &obj) ;

// pBuffer content can not be seen on console
//  cout << " here is the pBuffer content \n "<< pBuffer << endl ;
  cout <<"message size " << pBufferSize << endl ;
  cout << "message data size " << obj.objsize() << endl ;
  cout << "message header size " << pBufferSize - obj.objsize() << endl ;
  
  write (connfd , pBuffer , pBufferSize ) ;
	

 return 0 ;
}
