#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include <vector>
#include <cstddef>
#include <sstream>
#include <iostream>


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
			explicit vector (size_t n, const value_type& val = value_type(), const Alloc& alloc = Alloc()) : _size_alloc(n), _size_filled(0), _alloc(alloc)
			{
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * n));
				for (_size_filled = 0; _size_filled < n; _size_filled++)
				{
					_array[_size_filled] = val;
				}
			};

			//Constructor fill list (remplir)
			template <class InputIte>
			vector(InputIte first, InputIte last, const Alloc& alloc = Alloc());

			//Constructor by copy
			vector (const vector& x);

		//-------------FONCTION-------------
			//print
			void print_vector()
			{
				for (int i = 0; i < _size_filled; i++)
				{
					std::cout << "_array["<< i <<"] = " << _array[i] << std::endl;
				}
			};

			//size
			size_t	size()
			{
				return (_size_filled);
			}

			//resize
			void resize (size_type n, value_type val = value_type())
			{
				if (n <= _size_filled)
				{
					for(n; n <_size_filled; n++)
						pop_back();
				}
				else if (_size_alloc > n)
				{
					T tmp[n];
					for (size_type i = 0; i < n; i++)
						tmp[i] = _array[i];
					_alloc.deallocate(_array, sizeof(T *) * _size);
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * n));
					for (size_type i = 0; i < n; i++)
						_array[i] = tmp[i];
				}
				else
				{               
					reserve(n);
					for(_size_filled; _size_filled < n; _size_filled++)
						_array[_size_filled]= val;
				}

				//empty
				bool empty() const
				{
					return (_size_filled == 0);
				}
			}



	};
}
#endif