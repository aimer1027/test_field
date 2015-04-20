#include <cstdio>
#include <cstring>

int int_to_char ( int i , unsigned char c[] )
{
	c[3] = i %256 ;
	c[2] = (i-c[3])/256%256 ;
	c[1] = ( i - c[3] - c[2]*256 )/256/256%256 ;
	c[0] = (i-c[3] -c[2]*256  - c[1]*256*256 )/256/256/256%256 ;
	
	printf ("here is the result :\n") ;
	printf ("c[2] = %x \n", c[2]) ;

	return 0 ;
}


int main ( int argc , char ** argv )
{
  int i = 123456789;
  unsigned char c[5] ;

  int_to_char ( i , c ) ;
 
  return 0 ;
}
