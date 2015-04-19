#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>


using namespace std ;

class node
{
  public:
  char *test_line ;
  int id ; 

  node ( int i )
  {
   test_line = (char*)malloc ( 64 ) ;
    cout << "you create a node "<< endl ;

    id = i ;
  }
	
  ~node ()
  {

	cout << "when delete node , this line will be shown " << endl ;
	release_test_line () ;

  }

  void release_test_line()
  {
	delete test_line  ;
	cout << "what i want to test is that : if ~node will call this method"<<endl ;
	cout << "when i use delete "<< endl ; 
  }

} ;

int main ( int argc , char **argv )
{
 vector<node*>pNode_queue ;
 
 for ( int i = 0 ; i < 10 ; i++ )
 {
   pNode_queue.push_back ( new node (i) ) ;
 }



for ( vector<node*>::iterator it = pNode_queue.begin () ;
		it != pNode_queue.end() ; it++  )
 {
	if ( (*it)->id == 8 )
        {
		vector<node*>::iterator it2 = it ;
		it = pNode_queue.erase( it  ) ;
        	
		delete *it2 ;
	}
 }

/*
for ( int i = 0 ; i < 10 ; i++ )
{
  if ( pNode_queue[i]->id == 8  )
   printf (" find 8 th d\n ") ;
}
*/

cout <<"show the queue " << endl ;

for ( vector<node*>::iterator it = pNode_queue.begin () ;
		it != pNode_queue.end () ; it++ )
{
	cout << "node id = " << (*it)->id << endl ;
}

 return 0 ;
}
