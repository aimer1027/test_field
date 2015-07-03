#include <cstdio>
#include <cstring>
#include <iostream>

#include "Processor.h"

using namespace std ;


Process::Process ( std::string&  _name , std::string&  _shared_mem_name , bool _isMain ):name(_name ) 
		,shared_mem_name(_shared_mem_name ), isMain(_isMain)
{
	ipc = new IPC( shared_mem_name  ) ; // here we create a ipc instance
}


Process::~Process ()
{
	// if this is the Main process , release the shared memory
	if ( isMain) 
	{
		ipc->remove_shared_mem () ; 
		cout << "now we remove shared memory by main process" << endl ;
	}
	else
	  cout << "sub process exit" << endl ;
	
}

int Process::runProc ( std::string &file_name )
{
	// here we gonna to run the process
	if ( isMain )
	{
		ipc->create_shared_mem() ;
		ipc->init_shared_memory() ;
	}
	return ipc->reader (file_name ) ;
	
}



