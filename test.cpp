#include <cstdio>
#include <iostream>

using namespace std ;

int main ( int c , char *v[] )
{
	char list[64] ;
	
	int x = 32167 ;

	sprintf (list , "%dinuyasha" , x) ;
	
	printf ("here is the list :%s " , list ) ;
	return 0 ;
}
