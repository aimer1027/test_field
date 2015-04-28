// test how to push and extract vector object
// into and from a BSONObj 

// first test a int type vector
// second test char type vector 
// then test a struct node type vector

// 


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <bson.h>

using namespace std ;
using namespace bson ;

int main ( int argc , char ** argv )
{
  vector <int> list1, list2 ; // list2 stored content extract from obj1  
  BSONObjBuilder builder ;
  BSONObj obj1  ;  // push in obj1
  
  // insert contents into list
  for ( int i = 0 ; i < 30 ; i++ )
      list1.push_back (i) ;
  
   builder.append ("Integer_List", list1) ;
  
   obj1 = builder.obj () ;

   cout << "here is the bson obj content "<< endl ;
   cout << obj1.toString () << endl ;  

   // extract from obj1 
  
   BSONObjIterator iter (obj1["Integer_List"].embeddedObjectUserCheck()) ;
   
   while ( iter.more() )
      list2.push_back (iter.next().number()) ;  

   for ( int i = 0 ; i < list2.size () ; i++ )
      cout << list2[i] << endl ;

  
  cout <<"-----------test bson vector<char>------------------------"<< endl ;
  vector<char> charList1, charList2 ;
  BSONObj cObj1 ;
  BSONObjBuilder cBuilder ;
 
  for ( int i = 0 ; i < 100 ; i++  )
  {
	char c = 0x01 ;
	charList1.push_back(c) ;
  }

  for ( int i = 0 ; i < charList1.size() ; i++ ) 
     cout << charList1[i] << endl ;
 cBuilder.append ("bit_field",charList1) ;
  
 cObj1 = cBuilder.obj () ;
  
 cout << "here is cObj1 " << cObj1.toString () << endl ;
 
 // extract info from BSONObj stroed it  into charList2
 
 BSONObjIterator cIter (cObj1["bit_field"].embeddedObjectUserCheck()) ;
 
 while (cIter.more () )
 {
	charList2.push_back ((char)cIter.next().number()) ;
 } 

 cout << "output contents in charList2 " << endl ;

 for ( int i = 0 ; i < charList2.size () ; i++ )
   cout << charList2[i] << endl ;


   return 0 ;
}









