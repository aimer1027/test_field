#include <cstdio>
#include <cstring>
#include <iostream>

#include "rsa_pair.h"

using namespace std ;

int main ( int argc , char **argv )
{

  string pub_key_path , pri_key_path ;
  string password ;
  
  cout << "public key path " << endl;
  cin >> pub_key_path ;
  cout << pub_key_path << endl ;  


  cout << "private key path " << endl ;
  cin >> pri_key_path ;
  cout << pri_key_path <<endl ;
  

  cout << "password " << endl ;
  cin >> password ;
  cout << password  <<endl;

  
 // rsaPair key_pair ;
  rsaPair key_pair ( pub_key_path , pri_key_path , password) ; 
  
   key_pair.create_key_pair () ;  
  
  
  return 0 ;
}
