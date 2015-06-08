#include "IPC.h"

#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std ;

IPC::IPC( std::string &shared_mem_name )
{

  shm_name_ = shared_mem_name ;

}

//---------------------------------------------

/**
  in create_shared_mem we create a shared memory
  
  from official online documents
  we  create a shared memory as two basic steps:
  
  1. create a managed_shared_memory 
  
  2. create a special type of allocator 
     if we want to shared memory organized like a STL
     constructor and allocates the space from the shared-memory
     dynamically
 
  however , here , we just create shared memory ,
  until method init_shared_memory we write file's contents into 
  the shared memory , so we do not need step2 here 
*/


int IPC::create_shared_mem ()
{
  // before we create a shared memory , we should call the remove first in case of
 // it already exist , this will cause an error happend during running time
	remove_shared_mem () ; 

  boost::interprocess::managed_shared_memory 
		shm ( boost::interprocess::create_only ,
			shm_name_.c_str() , 65536/2 ) ;
  return 0 ;
}

//-----------------------------------------------------

int IPC::init_shared_memory ()
{
    /*
     here we gonna to initialize the shared_memory 
     we would like create the shared memory like this
 	
    | file-name | file-contents |
    |  .....    |  .....        |

   */	

  int num ;
  string name ;

  cout << "input how many files and their names which you want to shared them into shared memory"<< endl ;
  cout << "how many" << endl ;
  cin >> num ;

  for ( int i = 0 ; i < num ; i++ )
  {
        cout << "file name " << endl ;
        cin >> name ;

        file_name_list_.push_back ( name ) ;
  }	
   

   // here we create a shared_memory_manager 
   boost::interprocess::managed_shared_memory shm (boost::interprocess::open_only ,
		shm_name_.c_str() ) ;
	
    // here is basic step 2 , create an allocator instance
    // CharAllocator is user defined char's allocator 
   // allocates space from shared memory object

    CharAllocator charallocator( shm.get_segment_manager() ) ;
 
   
 // in the following cycle , we open each file ,
// and output the file's content into shared memory

    for ( size_t i(0)  ; i < file_name_list_.size() ; i++)	
    {
	fstream i_file ;
	i_file.open ( file_name_list_[i].c_str(),ios::in | ios::binary ) ;
       
        if ( !i_file.is_open())
        {
	 	perror ("[error] open file failed") ;
		return -1 ;	
	} 
	
	string file_content ;
	char file_buffer [256] ;	

	while ( !i_file.eof()) 
	{
		memset ( file_buffer, '\0' , sizeof(file_buffer))  ;
		i_file.getline(file_buffer, 256 ) ;
		file_content += file_buffer  ;
	}
	
	// here we finish reading a whole file's content 
	// next , we transfer the string type into 
	// boost::interprocess::basic_string type	
 
	i_file.close() ;
 
	bi_string bi_file_conent (charallocator) ;
	bi_file_conent = file_content.c_str()  ;
	shm.construct<bi_string>(file_name_list_[i].c_str())(bi_file_conent) ;
    
   } // for cycle    

   return 0 ;
}

//-------------------------------------------------------
int IPC::reader( string &file_name )
{
	// fist we need to open the shared memory object by target name
	boost::interprocess::managed_shared_memory shm 
		( boost::interprocess::open_only ,shm_name_.c_str()) ;
	
	// then we use the opened memory manager to create 
	// a user-defined allocator type's instance

	CharAllocator charallocator( shm.get_segment_manager()) ;
	
	// then we use the user-defined allocator instance create 
       // user-defined type 
	bi_string str(charallocator) ;
	
	string file_content ;
	

	std::pair<bi_string*,boost::interprocess::managed_shared_memory::size_type>res 
		= shm.find<bi_string>( file_name.c_str()  ) ;
		
	if ( res.first == NULL )
	{
		perror ("[error] failed find target file in shared memory") ;
		return -1 ;
	}
	
	file_content = string(res.first->c_str() , res.first->size() ) ;
 	
	
	cout << "here is the file's content " << endl ;
 	cout <<  file_content << endl ;	

	return 0 ;
}

//--------------------------------------------------------
int IPC::remove_shared_mem ()
{

  boost::interprocess::shared_memory_object::remove(shm_name_.c_str() ) ;
	
  return 0;
}

//-------------------------------------------------------------
IPC::~IPC()
{
	remove_shared_mem () ;
}
