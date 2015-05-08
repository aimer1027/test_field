#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "NodeManager.hpp"

using namespace std ;

// here is the defination of node 

struct NodeManager::node 
{
  node ():node_name ( NULL )
  {}
	
  node ( string & name ) : node_name ( name )
  {}

  ~node ()
  {
	cout << "node relasesd " << endl ;
  }

  string node_name ;
} ;

NodeManager::NodeManager ( string &name  ):nodePtr(new node (name))
{
  cout << "create node \n node name :" << endl ;
  cout << nodePtr->node_name << endl ;
}

NodeManager::~NodeManager ()
{
  cout <<"release NodeManager space " <<endl ;
}
