#ifndef MESSAGE_H
#define MESSAGE_H

typedef struct  msg_header
{
  int len ;
  
  msg_header() : len (0)
  {}

} header_t;

typedef struct msg
{
  header_t header ;
  char data[0] ;

} message_t;


#endif // message.h
