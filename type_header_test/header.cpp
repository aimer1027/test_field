#include <cstdio>
#include <iostream>
#include <string.h>
#include <cstring>
#include <cstdlib>

using namespace std ;

enum MSG_TYPE
{
  NONE = 0 ,
  HAND_SHAKE,
  KEEP_ALIVE
} ;


typedef struct msg_head
{
  int len ;  // data length
  int type ; // message type 

  msg_head() :len (0) , type (NONE)
  {}
} head_t ;

typedef struct hand_shake_msg 
{
  head_t header ;
  char data[0] ;
}hand_shake_msg_t ;

typedef struct keep_alive_msg
{
  head_t header ;
  char data[0]  ;
}keep_alive_msg_t  ;


int getMessageType ( char *msg )
{
   head_t *pHeader = (head_t*)(msg) ;
   
   switch ( pHeader->type)
   {
	case HAND_SHAKE :
	{
	    cout << "message type : hand shake message" << endl ;
	    break ;
        }
	case KEEP_ALIVE :
	{
	     cout << "message type : keep alive message" << endl ;
	     break ;
	}
	case NONE:
	default :
	     cout << "unknown type  message " << endl ;
   }
	
	return 0 ;
}

int main ( int argc , char **argv )
{
// build hand shake message and test getMessageType method 
  char *pMsg = NULL ;
  hand_shake_msg *pHandShakeMsg = NULL ;
  string line ;
  int size = 0 ;

  size  += sizeof(hand_shake_msg_t);
  

  cout << "input hand shake message " << endl ;
  
  cin >> line ;
  
  size += line.size () ;

  pMsg = (char *)malloc(size*sizeof(char));
 
  pHandShakeMsg = (hand_shake_msg_t*)pMsg ;
  
  pHandShakeMsg->header.len = line.size() ;
  pHandShakeMsg->header.type = HAND_SHAKE ;
  
  memcpy ( &pHandShakeMsg->data[0] , line.c_str() , line.size() ) ;
  
  pMsg = (char*)(pHandShakeMsg) ;
  
  getMessageType ( pMsg ) ;


  return 0  ;
}
