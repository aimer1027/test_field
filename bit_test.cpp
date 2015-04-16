#include <cstdio>

/*
  this test method is used to set bit value 
  to each vector<char>
  and testify whether the unsigned char 
  occupies 8 bits in this platform
*/

#define set_value_one(value,pos) value|=(1<<pos)

#define set_value_zero(value,pos) value&=!(1<<pos)


unsigned char test_bit  ;

int setbit (  int index ,int value  )
{
   if ( value == 0)
   {
	// call bit set 0 method 
	set_value_zero(test_bit,index) ;
   }
  
  else if ( value == 1 )
  {
	// call bit set 1 method 
	set_value_one (test_bit,index) ;
  }

  else
  {
	printf ("illegal value input \n neither 1 nor 0 \n") ;
  }
   
}



int main ( int c , char ** v)
{
 // first initialize the test_bit all 0 each bit
  
 test_bit = 0x00 ; // i plan to use memeset , but i forget test_bit is only a char 

 // testify how may bits on unsigned char occupy in this platform
 printf ( " usigned char occupy %d bits \n " , 8*sizeof(test_bit) ) ;

 printf (" test_bit before set bit operation %x \n", test_bit) ;
 
 setbit (3, 1 ) ;
 
 printf (" test_bit :  %x \n" , test_bit) ;


 setbit (3, 0) ;
 
 printf (" test_bit : %x \n", test_bit) ;

 return 0 ;
}
