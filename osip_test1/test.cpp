#ifndef OSIP_MT
#define OSIP_MT
#endif

#include <osip2/osip_mt.h>
#include <osip2/osip_condv.h>
#include <osip2/osip.h>

void* print ( void *arg )
{ 
   for ( int i = 0 ; i < 10  ; i++ )
   printf ("this is only a test \n") ;
	
   return (void*)  0  ;
}

int main ( int argc ,char **argv )
{
  void * thread_obj = NULL ; 
  
  typedef void*(*func_ptr_t )(void*)  ;
  
   func_ptr_t func_ptr ;

   func_ptr = print  ;

 // (*func_ptr) () ;

  thread_obj = (void *)osip_thread_create ( 20000 ,func_ptr , NULL ) ; 
	
  if ( thread_obj == NULL )
  {
	perror ("failed to create thread obj by osip_thread_create method ") ;
	return -1 ;
  }

 printf ("here we go to run the thread \n") ;
	
 if (  osip_thread_join ( (struct osip_thread*) thread_obj ) != 0 )
 {
	perror ("failed to execute osip_thread_join method") ;
	return -1 ;		
 }

  return 0 ;
}
