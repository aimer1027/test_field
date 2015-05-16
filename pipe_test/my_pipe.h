/**
  in this file i would like create a pair of myPipe 
  myPipe[0] is used to read from myPipe's contents 
  myPipe[1] is used to write into myPipe's contents

  and the sock_fd is the socket descriptor used to 
  listen to the target port 

  I would like create a class , write all the method (initialize connect and other thing)
  into the class's constructor 
  and packed write , read myPipe's contents into the class too 
  
  by Aimer 2015/5/16
***/

#ifndef PIPE_H__
#define PIPE_H__



class myPipe
{
  public :
	myPipe () ;
	~myPipe () ;
        int  write_in_pipe 	( const void *buf , int len ) ;
    	int  read_from_pipe 	( void *buf , int len ) ;
	int  get_read_descr 	() ;
	
 private :
	int pipes[2]  ;

} ;


#endif // myPipe.h
