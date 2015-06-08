#include <cstdio>
#include <cstring>
#include <iostream>

#include "IPC.h"

using namespace std ;

int main( int argc , char *argv [] )
{
	string shared_memory_name = "Aimer" ;
	string file_name = "/tmp/rsa_key0.txt" ;	

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
	
	
	return 0 ;
}
