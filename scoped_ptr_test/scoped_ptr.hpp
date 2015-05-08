#ifndef SCOPED_PTR_HPP__
#define SCOPED_PTR_HPP__

#include <boost/scoped_ptr.hpp>

template <typename T>
class Scoped_Ptr
{
	public :
		typedef boost::scoped_ptr<T> Type ;
} ;


#endif
