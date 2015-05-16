#ifndef OSIP_MT
#define OSIP_MT
#endif

#include <osip2/osip_mt.h>
#include <osip2/osip_condv.h>
#include <osip2/osip.h>

#include <cstdio>


#include "thread_base.h"

//----------------------------
_thread::_thread ()
{
   thread = NULL ;
}

//----------------------------
_thread::~_thread ()
{
  
}

//------------release method ------------
int _thread::_release ()
{
   char ch [5] = "exit" ;
   int ret ;
	
   if ( thread == NULL )
 	return 0 ; // thread obj already released 
	
   ret = osip_thread_join ( (struct osip_thread*)thread) ;
 
   if ( ret != 0 )
   {
	perror ("could not shutdown thread \n") ;
	return -1 ;
   }	
   
  osip_free ( thread ) ;
 
  thread = NULL ;

  return 0 ;
}

//---------------------------------------
int _thread::_start ( void*(*func_loader)(void*) , void *func_args )
{
   // treate the thread-instance as the loader which 
  // loads the input method pointer to run
    
     if ( fun_loader == NULL )
     {
	perror ("[error] you input empty function pointer") ;
	return -1 ;
     }
	
     thread = (void*)osip_thread_create ( 20000 , func_loader, func_args) ;
	
     if ( thread == NULL )
     {
	perror ("[error] osip_thread_create meets error ") ;
	return -1 ;
     }
	
     return 0 ;
}

//----------------------------------------

int _thread::_wakeUp ()
{
   int ret ;
   char ch [6] = "wake" ;
	
   return 0 ;
}
