#ifndef RSA_PAIR_H_
#define RSA_PAIR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bn.h> // this is for the BN_new


class rsaPair
{
  public :
        rsaPair () 
        {
           pub_key = NULL ;
           pri_key = NULL ;
	}
	rsaPair ( std::string  pub_k_path , std::string  pri_key_path, std::string  psword ) ;
	~rsaPair () ;
	
	int create_key_pair () ;

  private :
	std::string pub_key_path ;
	std::string pri_key_path ;
	std::string password ;
	RSA *pub_key ;
	RSA *pri_key ;
} ;

#endif
