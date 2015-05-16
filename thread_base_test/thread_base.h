/**
   this class is used to create a thread base class 
   each class wants to adds multi-thread functions in it 
   can inherit this class , and adds its own functions 
   on base of the this class 
*/

class _thread
{
 public :
	void *thread ;
        
 public :
	_thread() ;
	~_thread () ;  // will call _release method 
	
	int _release () ;	// this will release the space occupied by current thread 
	int _start ( void *(*func_loader)(void*) , void *func_args ) ;
	int _wakeUp () ;
	
} ;


#ifndef 
