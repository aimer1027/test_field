#ifndef IPC_H_
#define IPC_H_

#include <string>
#include <vector>
#include <memory>

#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/containers/string.hpp"

namespace bi = boost::interprocess ;

typedef bi::allocator<char ,bi::managed_shared_memory::segment_manager> ;
typedef bi::basic_string<char , std::char_traits<char> , CharAllocator> bi_string ;


class IPC
{
public :

  IPC ( std::string shm_name) ;
  ~IPC () ;

  int writter ( std::string &file_name ) ;
  int reader  ( std::string &file_name ) ;
 
  int remove_shared_mem () ;
  int create_shared_mem  () ;

private :
  std::string shm_name_ ;
 	
} ;




#endif
