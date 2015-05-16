/**
  in this file i would like create a pair of pipe 
  pipe[0] is used to read from pipe's contents 
  pipe[1] is used to write into pipe's contents

  and the sock_fd is the socket descriptor used to 
  listen to the target port 

  I would like create a class , write all the method (initialize connect and other thing)
  into the class's constructor 
  and packed write , read pipe's contents into the class too 
  
  by Aimer 2015/5/16
***/

#ifndef PIPE_H__
#define PIPE_H__



class pipe
{
  public :
	pipe () ;
	~piep () ;
        void write_in_pipe 	( const void *buf , int len ) ;
    	void read_from_pipe 	( void *buf , int len ) ;
	int  get_read_descr 	() ;
	
 private :
	int pipe[2]  ;

} ;


#endif // pipe.h
