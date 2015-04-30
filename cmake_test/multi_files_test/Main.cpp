#include <cstdio>
#include <iostream>
#include <cstring>

#include "dir/hello.h"

using namespace std ;


int main ( int argc , char ** argv )
{
   string name ;
   cout << "input to who say hello " << endl ;
   cin >> name ;

   sayHello say_hello ( name ) ;
   say_hello.hello () ;
	
   return 0 ;
} 
