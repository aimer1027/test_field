#include <cstdio>
#include <cstring>
#include <iostream>

#include "IPC.h"
#include "Processor.h"

using namespace std ;

int main( int argc , char *argv [] )
{
	std::string shared_memory_name = "Aimer" ;
	std::string file_name = "/tmp/rsa_key" ;	

	/*
   		// tests for class IPC
	
	IPC ipc ( shared_memory_name  ) ;

	
	if (ipc.create_shared_mem () )
	{
		perror ("create_shared_mem failed ") ;
		return -1 ;
	}
	
	if (ipc.init_shared_memory () )
	{	
		perror ("init_shared_memory failed ") ;
		return -1 ;
	} 
	
	if ( ipc.reader( file_name ) )
	{
		perror ("reader method failed ") ;
		return -1 ;
	}

	cout << endl ;
	cout <<"------------------ here we gonna test another IPC node visit shared memory's content-----------------" << endl ;
	IPC ipc2 (shared_memory_name ) ;
	ipc2.reader(file_name) ;
	
   */	
	// test for class Process 
	
	std::string proc_name = "main " ;
	
	
       
	Process mainProc (proc_name , shared_memory_name, true  ) ;

	
	string new_file_name = file_name +"0.txt" ;	

	cout <<"-------------------------- main process running ------------------------" << endl ;

	mainProc.runProc (new_file_name) ;	

	
	cout <<" ------------------ sub process running ----------------------------" << endl ;

	for ( int i = 1 ; i < mainProc.getSharedFileNum() ; i++ )
	{
		proc_name = "sub_proc " ;
		Process subProc (proc_name, shared_memory_name , false ) ;
		
		char no = i +'0' ;
		new_file_name = file_name+no+".txt" ;

		cout << endl ;
		
		cout <<"---------------- sub process run "<< i << "------------------------"<< endl ;
		subProc.runProc(new_file_name) ;
	
		cout <<"---------------- sub process " << i << "end---------------------------" <<endl ;
	}



	cout << "end of main "<< endl ;
	return 0 ;
}
