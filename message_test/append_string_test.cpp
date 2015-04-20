#include <cstdio>
#include <iostream>
#include <cstring>

/**
 string& append( const string &str ) ;
 string& append ( const string &str , size_t subpos , size_t sublen ) ;
 string& append ( const char *s ) ;
 string& append ( const char *s , size_t n ) ;
 string& append( size_t n , char c ) ;
*/



using namespace std ;


int main ( int argc , char **argv )
{
 char c  = '9' ;
 string msg_out = "origin message" ;
 string keyword = "BitTorrent";
 
 msg_out.append ( 1 , c  ) ;

 msg_out.append ( keyword, 0 , keyword.size() ) ;


 cout << msg_out << endl ;
 return 0 ;
}
