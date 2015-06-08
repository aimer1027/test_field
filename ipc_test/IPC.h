#ifndef IPC_H_
#define IPC_H_

#include <string>
#include <vector>
#include <memory>

#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/containers/string.hpp"

namespace bi = boost::interprocess ;

typedef bi::allocator<char ,bi::managed_shared_memory::segment_manager> CharAllocator;
typedef bi::basic_string<char , std::char_traits<char> , CharAllocator> bi_string ;


class IPC
{
public :

  // in this file reads in file name 
  IPC (std::string &shm_name ) ;
  ~IPC () ;

 /*
	open each file by name (path) which stored in file_name_list_
	and reads file's content one after another writes it into the shared-memory 
 */
	
  int init_shared_memory() ;	


  /**
	this method is used to write into the file with name of file_name stored inside  shared memory 
	with the name of shm_name_
  */
  int writter (std::string &file_name  ) ;
	
  /**
	and this method is read the file 's contents from the shared memory 
	prints it onto the screen 
  */
  int reader  ( std::string &file_name ) ;
 
  int remove_shared_mem () ;
  int create_shared_mem  () ;

private :
  std::string shm_name_ ;
  std::vector<std::string> file_name_list_ ;
	
} ;




#endif
