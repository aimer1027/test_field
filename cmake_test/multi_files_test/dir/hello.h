#ifndef HELLO_H_
#define HELLO_H_

#include <string>

class sayHello
{
 private :
	std::string toWho ;
  public :
	sayHello ( std::string who )
	{
		toWho = who ;
	}
	void hello () ;
} ;


#endif // hello.h
