#include <iostream>
#include <cstdio>
#include <cstring>
#include <bson.h>

using namespace std ;
using namespace bson ;

enum MSG_TYPE
{
  request = 0 ,
  response 
} ;

typedef struct msg_header
{
  int type ;
  int len ;
}msg_header_t ;


typedef struct msg
{
  msg_header_t msg_header ;
  char data[0] ;
} msg_t ;

int main ( int argc , char ** argv )
{
// first we test how to parse message into the BSONObj object
// data message from string -> char data[0] -> BSONObjBuilder -> BSONObj

	string line ;
	char *pBuffer = NULL ;
	msg_t *message = NULL  ;
	int len = (int)sizeof(msg_t);	
	
	BSONObjBuilder bsonBuilder ;
	BSONObj        bsonObj ;
cout << "extract message data(content) from char * to BSONObj " << endl ;


	cout << "input message content "<< endl ;
	cin >> line ;
	len += line.size ()+1 ;

        pBuffer = (char*)malloc(len * sizeof(char)) ;
	message = (msg_t*)(pBuffer) ;

	message->msg_header.type = 0;
	message->msg_header.len  = len ;
	
	memcpy( &message->data[0] , line.c_str () , line.size( ) ) ;
	message->data[line.size()] = '\0' ;
	
	cout << &message->data[0] << endl ;

	bsonBuilder.append("request message data", &message->data[0] ) ;
	
	bsonObj = bsonBuilder.obj () ;

	cout << bsonObj.objsize() << endl ;

// this can not be parsed by std::cout  , only out put '%'
//	cout << bsonObj.objdata() << endl ;

	cout << bsonObj.toString() << endl ;	
		
// second we test how to build message by message length and message data
// message data is stored in BSONObj 
// data from BSONObj -> char data[0]

cout << "build a message , message data from BSONObj" << endl ;
	msg_t *message2 = NULL ;
	int msg_len = sizeof(msg_t) ;
		
	if ( bsonObj.objsize() != 0 )
		msg_len += bsonObj.objsize ()+1 ;
	
	pBuffer = (char*)malloc(msg_len * sizeof(char)) ;
	
	message2 = (msg_t*)pBuffer ;
	
	message2->msg_header.len = msg_len ;
	message2->msg_header.type = 0 ;
	
	if ( bsonObj.objsize() != 0 )
	   memcpy ( &message2->data[0] , bsonObj.objdata () , bsonObj.objsize() ) ;
	
	message2->data[bsonObj.objsize()] = '\0' ;	

	
	BSONObj obj2 = BSONObj (&message2->data[0]);
	
	cout << obj2.objsize () << endl ;
	cout << obj2.toString() << endl ;
	
	return 0 ;
}



