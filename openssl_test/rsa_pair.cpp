#include <stdio.h>

#include "rsa_pair.h"

using namespace std ;

rsaPair::rsaPair( string  pub_k_path , string pri_k_path , string  psword)
{
   pub_key = NULL ;
   pri_key = NULL ;


   if ( pub_k_path.empty () || pri_k_path.empty() )
   {
	perror ("file stores key values empty") ;
        return ;
   }
   
   if ( psword.empty ())
   {
	perror ("password empty , use default") ;
	password = "inuyasha" ;
  	return ; 
  }

   printf ("here ") ;
  
   pub_key_path = pub_k_path ;
   pri_key_path = pri_k_path ;
    
   password = psword ;

}

rsaPair::~rsaPair ()
{
    if ( pub_key )
       RSA_free ( pub_key ) ;
  
    if ( pri_key )
	RSA_free ( pri_key ) ; 
}


int create_key_pair ()
{
  RSA *rsa ;
  int modulelen = 1024 ;
  int ret ;
  unsigned int len ;
  unsigned long e = RSA_3 ;
 
  BIGNUM *bn ;
  
  bn = BN_new () ; 
  ret = BN_set_word ( bn , e ) ;
   
  if ( ret != 1 )
  {
	perror ("BN_set_word method goes wrong ") ;
	return -1 ;
  }
  
  rsa = RSA_new () ;

  if ( RSA_generate_key_ex ( rsa , modulelen , bn , NULL ) != 1 )
  {
	perror ("RSA_generate_key_ex method goes wrong") ;
	return -1 ;
  }



  return 0 ;
}

