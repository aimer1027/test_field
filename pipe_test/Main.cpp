/**
  in this file used to test pipe class ' s method
**/
 
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <iostream>

#include "my_pipe.h"

using namespace std ;

int main ( int argc , char ** argv )
{
  char *strPtr ;
  string line_in ;
 
  cout << "input a line " << endl ;

  cin >> line_in ;
   
  strPtr = (char *)malloc (1024*sizeof(char)) ;
 
cout <<"----- ok here we test pipe write and read ---------" <<endl ;


  myPipe p  ; 
  
  p.write_in_pipe ( line_in.c_str() , line_in.size() ) ;

  p.read_from_pipe ( strPtr , 1024  ) ;

  cout << "here is what read from pipe " << endl ;
  cout << strPtr << endl ;

  return 0 ;
}
