#ifndef PROCESS_H_
#define PROCESS_H_

#include <cstdio>
#include <cstring>
#include <iostream>

#include "IPC.h"

class Process
{
  public :
	Process ( std::string &_name , std::string &_shared_mem_name, bool isMain) ;	
	~Process ( ) ;
	int runProc ( std::string & file_name ) ;
	int getSharedFileNum ()
	{
		if ( isMain ) return ipc->get_file_num () ;
		else return 0 ;
	}	

  private :
	IPC *ipc ;
	std::string name ;
	std::string shared_mem_name ;
	
	bool isMain ; 
} ;






#endif 


