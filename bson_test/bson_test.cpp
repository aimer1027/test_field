#include <cstdio>
#include <bson.h>
#include <iostream>
#include <vector>

using namespace std ;
using namespace bson ;

typedef struct msg
{
  int len ;
  char data[0] ;
} msg_t ;


int main ( int argc , char ** argv )
{
  string line ;  
  BSONObjBuilder builder ;

  cout << "input message "<<endl ;
  cin >> line ;

  builder.append ("line size", (int)line.size()) ;  
  builder.append ("file content", line.c_str()) ;

  BSONObj key = builder.obj() ;
  cout << key.toString() << endl ;  
  return 0 ;
}
