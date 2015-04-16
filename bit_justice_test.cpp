#include <cstdio>


int main ( int c , char **argv )
{

unsigned char test_char = 0x8 ; // 	 0000 1000
				//  loc  0------>7
// i want to visit the index = 3 's value , you know it must 1

// what i do is as follows

int pos = 3 ;
 
unsigned char v ;

for ( int i = 0 ; i < 7 ; i++  )
{
	
	if ( (test_char>>i)&1 )
	{
		printf ("1 value loc in test_char is %d \n" , i) ;
	}
}
 

 return 0 ;

}
