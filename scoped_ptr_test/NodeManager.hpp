#ifndef NODE_MANAGER_HPP__
#define NODE_MANAGER_HPP__

#include "scoped_ptr.hpp"
#include <boost/scoped_ptr.hpp>
#include <cstring>

class NodeManager
{
  public :
	NodeManager( std::string& name ) ;
	~NodeManager () ;
  private :

	struct node ; // only declearation
	Scoped_Ptr<node>::Type nodePtr ;        
} ;


#endif
