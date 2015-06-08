#include <cstdio>
#include <cstring>
#include <isotream>

#include "IPC.h"

using namespace std ;

int main( int argc , char *argc [] )
{
	string shared_memory_name = "Aimer" ;
	
	IPC ipc ( shared_memory_name  ) ;
	
	return 0 ;
}
