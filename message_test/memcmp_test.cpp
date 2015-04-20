#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std ;

int main ( )
{
   string test1 = "3216731267inuyasha3216732167" ;
   string hash_info = "inuyasha" ;
   string sub_str = test1.substr (10, 8) ;
   
   cout << sub_str<< endl ;
   cout << hash_info << endl ; 


   if ( memcmp(sub_str.c_str(), hash_info.c_str() , 8) == 0 )
	cout << "equal " << endl ;
  return 0 ;
}
