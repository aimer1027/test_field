#ifndef RSA_PAIR_H_
#define RSA_PAIR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

class rsaPair
{
  public :
	rsaPair ( std::string & pub_k_path , std::string & pri_key_path ) ;
	~rsaPair () ;
	
	int create_key_pair ( const std::string &password) ;

  private :
	std::string pub_key_path ;
	std::string pri_key_path ;
	std::string password ;
	RSA *pub_key ;
	RSA *pri_key ;
} ;

#endif
