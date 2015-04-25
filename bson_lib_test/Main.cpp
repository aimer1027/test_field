#include <cstdio>
#include <bson.h>
#include <util/json.h>
#include <util/time_support.h>
#include <lib/nonce.h>

using namespace bson ;

int main ( int argc ,char **argv )
{
  BufBuilder bson(1) ;
  bson.appendStr("hello Aimer") ;

  std::cout<<bson.buf() << std::endl ;  
  std::cout<< bson.len() << std::endl;  


  printf ("hello Aimer \n") ;
  return 0;
}
