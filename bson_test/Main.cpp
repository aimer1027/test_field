#include <cstdio>
#include <bson.h>
#include <iostream>
#include <vector>

using namespace std ;
using namespace bson ;

void iter ( bo o )
{
  // iterator example 
  cout << "\niter()\n";

  for ( bo::iterator i(o) ; i.more() ;)
  {
	cout << '  '<< i.next().toString() << endl ;
  }
}

int main ( int argc ,char **argv )
{
  BufBuilder bson(1) ;
  bson.appendStr("hello Aimer") ;

  cout<<bson.buf() << endl ;  
  cout<< bson.len() << endl;  
  printf ("hello Aimer \n") ;

  cout <<"------bson tests----------"<<endl ;
 
  cout << "build bits : " << 8*sizeof(char *) << endl ;
  
  // a bson object defaults on construction to {}
  
  bo empty ;
  
  cout << "empty:   " << empty << endl ;
  
   // make a simple {name :'joe', age: 33.7} object
   {
	bob b ;
	b.append("name","joe") ;
	b.append("age", 33.7) ;
        b.obj () ;
   }
 	
  // make {name : 'joe' , age: 33.7 } with a more compact notation 
  bo x = bob().append("name","joe").append("age",33.7).obj() ;
  
  // convert from bson to json
  string json = x.toString () ;
  cout << "json for x :"<< json << endl ;
  
 // access some fields of bson object x
  cout << "Some x things : " << x["name"]<< ' ' << x["age"].Number() <<'  '<<endl;
  cout << " is x empty : " << x.isEmpty () << endl ;
 

// test BSONObj 
  string line ;
  char data[0] ;
  

  cout << "-------test BSONObj ---------"<<endl ;
  cout << "input message "<< endl ;
  cin >> line ;
  
  cout <<  "line.size = "<< line.size() << endl ; 
  memcpy (&data[0] , line.c_str() , line.size()) ;
  bson::BSONObj bsonData = bson::BSONObj( &data[0]  ) ;   
  
    cout << &(data[0]) << endl ; 

  return 0;
}
