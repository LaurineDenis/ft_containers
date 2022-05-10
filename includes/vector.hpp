#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
// #include <limits>
// #include <vector>
// #include <cstddef>
// #include <sstream>


namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public :
		//define
			typedef Alloc allocator_type;
		//contructors
			explicit vector (const Alloc& alloc = Alloc()); //by default
			explicit vector (size_type n, const value_type& val = value_type(), const Alloc& alloc = Alloc()); //remplir value
			template <class InputIte>
			vector(InputIte first, InputIte last, const Alloc& alloc = Alloc()); //remplir list
			vector (const vector& x); //by copy
	}
}

#endif