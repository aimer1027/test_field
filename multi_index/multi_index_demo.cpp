#if !defined(NDEBUG)
#define BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING
#define BOOST_MULTI_INDEX_ENABLE_SAFE_MODE
#endif

#include <cstdio>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/shared_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using boost::multi_index_container ;
using namespace boost::multi_index ;

struct file_node
{
	int id ;
	std::string path_name ;
	long  length ;
	std::string creator ;
	 

	file_node( int id , std::string path_name , std::string creator ):
		id(id) , path_name(path_name) , length(0), creator(creator)
	{
	 	
			 
	}

	friend std::ostream & operator<<(std::ostream &os , const file_node & f ) ;
} ;

std::ostream &operator<< ( std::ostream &os , const  file_node &f )
{
	 char file_buffer[1024] ;
	 std::string file_content ;
	 bool isOpen = false ;

	 FILE *fp = fopen(f.path_name.c_str() , "r") ;
		if ( fp != NULL )
			  isOpen = true ;

	 if ( isOpen )
	 {
	      int ret =  fread((void*)file_buffer , sizeof(char) , sizeof(file_buffer)-1 , fp );
		  file_buffer[ret] = '\0' ;
		  
		  file_content+= file_buffer ;

		 fclose (fp) ;
	 }


	 else
	 {
		 file_content = "failed open file "+ f.path_name ;
	 }
	

	os<<"[file path]	 " << f.path_name << std::endl 
		<< "[file index]	 " << f.id << std::endl 
		<<"[file  creator] " << f.creator << std::endl 
		<<"[file contents] " << file_content << std::endl << std::endl ; ;
	return os ;
}

/**
 here we tags for accessing the corresponding indices of file_node_table
*/

struct path_name {} ;
struct creator {} ;

/**
  here we define a multi_index_container of file_node, with 
  following indices:
  - a unique index sorted by file_node::path_name
  - a non-unique index sorted by file_node::length 
  - a non-unique index sorted by file_node::creator

*/

typedef multi_index_container
<
  file_node , // table element
  indexed_by <

		  ordered_unique
		  <
			tag<path_name> , BOOST_MULTI_INDEX_MEMBER(file_node, std::string , path_name)
		  > , // this is for  file's path_name , like primary-key in database table
		   
		  ordered_non_unique
		  <
			tag<creator> ,  BOOST_MULTI_INDEX_MEMBER(file_node, std::string , creator)
		  > // second index file node's creator
  > // end indexed by
> file_node_table ;

typedef boost::shared_ptr<file_node_table> ftPtr ;


int main ()
{
	// try create obj by shared_ptr
	ftPtr file_table_ptr( new file_node_table ) ;

	std::string file_path , author  ;
	file_path = "/tmp/rsa_key" ;
	author = "kokia" ;

	// add additional node with creator/author name as 'Aimer'

	file_table_ptr->insert( file_node (1200 , "/tmp/rsa_key.pub" , "Aimer")) ;

	for ( int i = 0 ; i < 5 ; i++ )
	{
		char no = i+'0' ;	
		file_table_ptr->insert(file_node(i , file_path+no+".txt" , author)) ;
	}

	std::cout << "+++++++++++++++++++++ print files by author ++++++++++++++++++++ "<< std::endl ;
   
	file_node_table::index<creator>::type & index_by_author = file_table_ptr->get<creator>() ;

	file_node_table::index<creator>::type::iterator creator_it = index_by_author.begin() ;

	while ( creator_it != index_by_author.end())
	{
		std::cout << *creator_it << std::endl ;
		creator_it++ ;
	}
 

	std::cout << "+++++++++++ print files by path name +++++++++++++++++++++" << std::endl ;

	file_node_table::index<path_name>::type & file_table_view_index_by_path_name =
			file_table_ptr->get<path_name>() ;

	// path_it points to the first element in the VIEW which sorted by path_name
	file_node_table::index<path_name>::type::iterator 
			 path_it = file_table_view_index_by_path_name.begin () ;

	for ( ; path_it != file_table_view_index_by_path_name.end() ; path_it++ )
	{
		// call operator<< method of each object which pointed by iterator of path name
		std::cout << *path_it << std::endl ;
	}

	std::cout << "----------------------- test find method --------------------------------------" << std::endl ;

	file_node_table::index<creator>::type::iterator 
				 itr(file_table_ptr->get<creator>().find("Aimer")) ;

	if ( itr != file_table_ptr->get<creator>().end() )
	{
		std::cout<< " find file node " << std::endl ;
		std::cout << *itr << std::endl ;
	}

	else
	{
		std::cout << " file node not find" << std::endl ;
	}

	return 0 ;
}


