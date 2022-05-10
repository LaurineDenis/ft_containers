#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
// #include <limits>
// #include <vector>
// #include <cstddef>
#include <sstream>


namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public :

		//----------------DEFINE----------------

			typedef		Alloc	allocator_type;
			typedef		T		value_type;

		private :

		//---------------VALUES----------------

			T				*_array;		//tableau
			size_t			_size_alloc;	//taille allouée
			size_t			_size_filled;	//taille remplie (index)
			allocator_type	_alloc;			//malloc

		public :

		//-------------CONSTRUCTORS-------------

			//contructors by default
			explicit vector (const Alloc& alloc = Alloc()): _size_alloc(0), _size_filled(0), _alloc(alloc)
			{
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * 2));
			};

			//contructors fill one (remplir)
			explicit vector (size_t n, const value_type& val = value_type(), const Alloc& alloc = Alloc());

			//Constructor fill list (remplir)
			template <class InputIte>
			vector(InputIte first, InputIte last, const Alloc& alloc = Alloc());

			//Constructor by copy
			vector (const vector& x);

	};
}

#endif