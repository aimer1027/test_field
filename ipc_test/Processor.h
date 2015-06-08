#ifndef PROCESS_H_
#define PROCESS_H_

#include <cstdio>
#include <cstring>
#include <iostream>

#include "IPC.h"

class Process
{
  public :
	Process ( std::string &_name , std::string &_shared_mem_name) ;	
	~Process ( ) ;
	
	int runAsMainProc() ;
	int runAsSubProc ( std::string & file_name ) ;
	

  private :
	IPC *ipc ;
	std::string name ;
	std::string shared_mem_name ;
	
} ;






#endif 


