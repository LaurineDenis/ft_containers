#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>
# include <vector>
# include <cstddef>
# include <sstream>
# include <iostream>
# include "iterator_traits.hpp"
# include "iterator.hpp"
# include "utils.hpp"


namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public :

		//----------------DEFINE----------------

			typedef				Alloc							allocator_type;
			typedef				T								value_type;
			typedef				size_t							size_type;
			typedef typename    std::ptrdiff_t					difference_type;
			typedef typename	Alloc::reference				reference;
			typedef typename	Alloc::const_reference			const_reference;
			typedef typename	Alloc::pointer					pointer;
			typedef typename	Alloc::const_pointer			const_pointer;



		// 	typedef				ft::Iterator<T>					iterator;
		// 	typedef				ft::Const_iterator<T>			const_iterator;
		// 	typedef				ft::reverse_iterator<T>			reverse_iterator;
		// 	typedef				ft::reverse_iterator<T>			const_reverse_iterator;
		// //	typedef typename 	ft::iterator_traits<iterator>::difference_type	difference_type;
			
			
			
			
			typedef				iterator_vector<pointer>			iterator;
			typedef				iterator_vector<const_pointer>			const_iterator;
			typedef				ft::reverse_iterator<iterator>		reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			
		private :

		//---------------VALUES----------------

			T				*_array;		//tableau
			size_type		_size_alloc;	//taille allouée
			size_type		_size_filled;	//taille remplie (index)
			allocator_type	_alloc;			//malloc

		public :

		//-------------CONSTRUCTORS-------------

			//contructors by default
			explicit vector (const Alloc& alloc = Alloc()): _size_alloc(0), _size_filled(0), _alloc(alloc)
			{
			};

			//contructors fill one (remplir)
			explicit vector (size_type n, const value_type& val = value_type(), const Alloc& alloc = Alloc()) : _size_alloc(n +1), _size_filled(n), _alloc(alloc)
			{
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
				for ( size_t i = 0; i < n; i++)
					_array[i] = val;
			};
		
			//Constructor fill list (remplir)
			//Constructor fill list (remplir)
            template <class InputIte>
            vector(InputIte first, InputIte last, const Alloc& alloc = Alloc(),
            typename ft::enable_if<!std::is_integral<InputIte>::value, InputIte>::type* = NULL)
            : _size_alloc(0), _size_filled(0), _alloc(alloc)
			{
				
				InputIte count = first;
				while (count++ != last)
						_size_alloc++;
				_size_alloc += 1;
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));	
				 while (first != last)
				 	_array[_size_filled++]= *first++;
				
			};

			//Constructor by copy
			//_alloc(allocator_type())
			
			vector (const vector& x) :_size_alloc(x._size_alloc), _size_filled(0), _alloc(x._alloc)
			{
				if (*this == x)
					return;
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));	
				insert(begin(), x.begin(), x.end()); 

			};

			// operator =
			vector& operator= (const vector& x)
			{

				if (*this == x)
					return *this;
				_size_alloc = x._size_alloc;
				_size_filled = x._size_filled;
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));	
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = x._array[i];
				return (*this);
			};

			//destructeur
			~vector()
			{
				this->clear();
				if (_size_alloc > 0)
				{
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
					_size_alloc = 0;
				}
			};

			

		//-------------FONCTION-------------

			//print
			void			print_vector()
			{
				for (size_type i = 0; i < _size_filled; i++)
				{
					std::cout << "_array["<< i <<"] = " << _array[i] << std::endl;
				}
			};

			void			print_vector_const() const
			{
				for (size_type i = 0; i < _size_filled; i++)
				{
					std::cout << "_array["<< i <<"] = " << _array[i] << std::endl;
				}
			};

			//print
			void			print_element()
			{
				std::cout << "Size alloc : " << _size_alloc << std::endl;
				std::cout << "Size filled : " << _size_filled << std::endl;
			};

		//-------------ITERATORS-------------

			// begin Renvoie un itérateur pointant vers le premier élément du vecteur.
			iterator begin()
			{
				//std::cout << "coucou: "<< *_array << std::endl;
				return (iterator(_array));
			};

			// begin const
			const_iterator begin() const
			{

				return (const_iterator(_array));
			};

			// end Renvoie un itérateur faisant référence à l'élément après la fin dans le conteneur vectoriel.
			iterator end()
			{
				return (iterator(_array + _size_filled));
			};

			// end const
			const_iterator end() const
			{

				return (const_iterator(_array + _size_filled));
			};

			// rbegin pointe vers l'élément juste avant celui qui serait pointé par member end.
			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->_array + (this->_size_filled)));
			};

			// rbegin const
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->_array + (this->_size_filled)));
			};


			// rend Renvoie un itérateur inverse pointant vers l'élément théorique précédant le premier élément du vecteur
			reverse_iterator rend()
			{
				return (reverse_iterator((this->begin())));
			};
			// rend const
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator((rend())));
			};
		//-------------CAPACITY-------------
			//size
			size_type	size()	const
			{
				

				return ( _size_filled);
			};
			
			//max_size
			size_type		max_size() const
			{
				return std::numeric_limits<size_type>::max() / sizeof(*_array);
			};

			//resize
			void resize (size_type n, value_type val = value_type())
			{
				if (n <= _size_filled)
				{
					size_type i = _size_filled;
					while (n < i)
					{
						pop_back();
						n++;
					}
				}

				if (_size_alloc > n)
				{
					
					// alloc = 10 et n =  5 alloc trop grande

					T tmp[_size_filled + 1];
					size_type tmp_size = _size_filled;
					for (size_type i = 0; i < _size_filled; i++)
						tmp[i] = _array[i];
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
					_size_alloc = _size_filled + 1;
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
					for (size_type i = 0; i < tmp_size; i++)
						_array[i] = tmp[i];
				}
				else if (_size_alloc < n)
				{   // size_alloc = 4 et n= 10
					T tmp[_size_alloc + n]; // on fait un vecto temp avec la bonne taille
					for (size_type i = 0; i < _size_alloc; i++)
						tmp[i] = _array[i]; // on copie ce qu'il y avait dans array
				//	size_type tmp_size = _size_alloc; // on copie l'alloc de base
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);// on desalloue
					_size_alloc = n + 1;// on change l'alloc de base et o rajoute 1
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc)); // on alloue a la bonne taille
					for (size_type i = 0; i < _size_filled; i++)
						_array[i] = tmp[i]; // on remet dans array ce qu'on avait copié
					for (size_type i = _size_filled; i < n; i++)
						_array[i] = val; // et on lui rajoute la valeur
					_size_filled = n; // ne pas oublié de mettre a jour filled
				}
			};

			//capacity
			size_type		capacity() const
			{
				return _size_alloc;
			};

			//empty
			bool empty() const
			{
				return ( _size_filled == 0);
			};

			//reserve => Réaloue plus grand si besoin donc change seulement le size_alloc
			//n => la taille demandé du futur array
			void			reserve (size_type n)
			{
				if (n > max_size() || (n * 2) + _size_alloc > max_size())
					throw std::length_error::exception();
				// [1,2,3,4,5] n = 5 alloc = 6
				if (_size_alloc == 0)
				{
					_size_alloc = n + 1;
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
				}
				else
				{
					//realoue plus grand
					T			tmp[_size_alloc];	
					for (size_type i = 0; i < _size_filled ; i++)
						tmp[i] = _array[i];
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
					
					_size_alloc = (n * 2) + _size_alloc;
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
					for (size_type i = 0; i < _size_filled; i++)
						_array[i] = tmp[i];
				}
			};

		//-------------ELEMENT ACCESS-------------
			// operator [] Élément d'accès Renvoie une référence à l'élément à la position n dans le vecteur
			reference operator[] (size_type n)
			{
				return (_array[n]);
			};

			// const operator []
			const_reference operator[] (size_type n) const
			{
				return (_array[n]);
			};

			// at Élément d'accès Renvoie une référence à l'élément à la position n dans le vecteur a la diff de operator [] la on verifie les limits 
			reference at (size_type n)
			{
				if (n >= _size_filled || n < 0)
					throw std::out_of_range("vector");
				return (_array[n]);
			};

			// at const	
			const_reference at (size_type n) const
			{
				if (n >= _size_filled || n < 0)
					throw std::out_of_range("vector");
				return (_array[n]);
			};

			// front Renvoie une référence au premier élément du vecteur. // comportement indefini si le vecteur est vide
			reference front()
			{
				return (_array[0]);
			};

			// front const 
			const_reference front() const
			{

				return (_array[0]);
			};
		
			// back Renvoie une référence au dernier élément du vecteur.  // comportement indefini si le vecteur est vide
			reference back()
			{
				return (_array[_size_filled - 1]);
			};

			// back const 	
			const_reference back() const
			{
				return (_array[_size_filled - 1]);
			};
			
		//-------------MODIFIERS-------------

		//ATTENTION ENLEVER LE STD EN FT
		// assign Affecte un nouveau contenu au vecteur, en remplaçant son contenu actuel et en modifiant sa taille en conséquence.
		// assign (1) les nouveaux contenus sont des éléments construits à partir de chacun des éléments de la gamme entre premier et dernier, dans le même ordre
		template <class InputIterator>
  			void assign (InputIterator first, InputIterator last, 
			typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				InputIterator start = first;
				InputIterator end = last;
				size_t save = _size_filled;
				while (start != end)
					push_back(*start++);
				for (size_t i = 0; i < save; i++)
					erase(begin());
			};
		// assign (2) le nouveau contenu est constitué de n éléments, chacun initialisé à une copie de val.
			void assign (size_type n, const value_type& val)
			{
				if (_size_alloc != 0)
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * n)); 
				_size_alloc = n;
				for (size_type i = 0; i < n; i++)
					_array[i] = val;
				_size_filled = n;
			};
		
		//push_back Ajoute un nouvel élément à la fin du vecteur, après son dernier élément actuel. Le contenu de val est copié (ou déplacé) vers le nouvel élément.
			void push_back (const value_type& val)
			{

				if (_size_alloc == 0)
				{
					_size_alloc += 2;
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
				}
				else if (_size_alloc - 1 <= _size_filled) 
					reserve(_size_alloc - 1);
				_array[_size_filled] = val;
				_size_filled++;
				
			};

		//pop_back Supprime le dernier élément du vecteur, réduisant ainsi la taille du conteneur d'une unité
			void pop_back()
			{
				_size_filled--;
			};
		
		// insert insertion de new element dans le vecteur 
			iterator insert (iterator position, const value_type& val)
			{

				if (position < begin())
				{
						reserve(1);
						int tmp = _size_filled +1;
						while (tmp-- > 0)
						{
							_array[tmp] = _array[tmp - 1];
						}
						_array[0] = 0;
						_size_filled++;
						return (position);
				}

				iterator begin_index = begin();
				size_t position_size = 0;
				size_t end_size = 1;
				if (position == end())
				{
					push_back(val);
					return (position);
				}
				reserve(1);
				while (begin_index != position)
				{
					position_size++;
					begin_index++;
				}
				begin_index = begin();
				while (begin_index != end())
				{
					end_size++;
					begin_index++;
				}
				T tmp[_size_filled + 1];
				for (size_t i = 0; i != position_size; i++)
						tmp[i] = _array[i];
				tmp[position_size] = val;
				for (size_t i = position_size + 1; i != end_size; i++)
						tmp[i] = _array[i - 1];
				_size_filled++;
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
				position = _array + position_size;
				return(position);
			};

    		void insert (iterator position, size_type n, const value_type& val)
			{
				//print_element();
			 	// std::cout << "position= " << *position << std::endl;
				// if (position < begin())
				// {
				// 		reserve(n);
				// 		size_t tmp = (_size_filled + n);
				// 		int i = _size_filled;
				// 		_array[0] = 0;
				// 		while (i-- >= 0)
				// 		{
				// 			_array[tmp--] = _array[i];
				// 		}
				// 		print_vector();
				// 		print_element();
				// 		return ;

			
				// }
		//		COMPORTEMENT INDE


				iterator it = position;
				iterator begin_index = begin();
				size_t		end_size = n;
				size_t position_size = 0;

				if (it == end())
				{
					for (size_type i = 0; i != n; i++)
						push_back(val);
					return ;
				}
				reserve(n);
				while (begin_index != position)
				{
					position_size++;
					begin_index++;
				}
				begin_index = begin();
				while (begin_index != end())
				{
					end_size++;
					begin_index++;
				}
				T tmp[n + _size_alloc];
				for (size_type i = 0; i != position_size; i++)
					tmp[i] = _array[i];
				for (size_type y = position_size; y != n + position_size; y++)
						tmp[y] = val;
				for (size_type y = position_size + n; y != end_size; y++)
				{
					tmp[y] = _array[position_size];
					position_size++;
				}
				_size_filled += n;
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
			};

		//ATTENTION METTRE STD EN FT
		template <class InputIterator>
   			void insert (iterator position, InputIterator first, InputIterator last,
			 typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_t		count = 0;
				InputIterator save = first;

				while (save != last)
				{
					save++;
					count++;
				}
				iterator begin_index = begin();
				size_t		end_size = 0;
				size_t position_size = 0;


				// cas 2 on ajoute a la fin
				if (position == end() || _size_filled == 0)
				{
					while (first != last)
					{
						push_back(*first);
						first++;
					}
				}
				// cas 2 : rajouter en plein milieux 
				else 
				{
					T tmp[_size_filled + count];
					T tmp2[_size_filled + count];
					size_type y = 0;
					size_type k = 0;
					
					save = first;
					while(save != last)
						tmp2[k++] = *save++;
					k = 0;

					reserve(count);// enelever +size
					_size_filled += count;


					while (begin_index != position)
					{
						position_size++;
						begin_index++;
					}
					begin_index = begin();
					while (begin_index != end())
					{
						end_size++;
						begin_index++;
					}
					for (size_t i = 0; i != position_size; i++)
						tmp[y++] = _array[i];
					while (first != last)
					{
						tmp[y] = tmp2[k];
						*first++;
						y++;
						k++;
					}
					for (size_t i = y; i != end_size; i++)
						tmp[i] = _array[position_size++];
					for (size_type i = 0; i < _size_filled; i++)
						_array[i] = tmp[i];
				}
			};
		
		// swap 
			void swap (vector& x)
			{
				T		*tmp_array = x._array;
				size_type	tmp_size_filled = x._size_filled;
				size_type	tmp_size_alloc = x._size_alloc;
				x._array = _array;
				x._size_filled = _size_filled;
				x._size_alloc = _size_alloc;
				_array = tmp_array;
				_size_filled = tmp_size_filled;
				_size_alloc = tmp_size_alloc;
			};

		//-------------ALLOCATOR-------------

			allocator_type get_allocator() const
			{
				return (this->_alloc); // Renvoie une copie de l'objet d'allocation associé au vecteur.
			};


			//erase only one element
			iterator erase (iterator position)
			{
				T		tmp[_size_filled - 1];
				iterator save = begin();
			//	iterator endz = end()-1;

				int			j;
				j = 0;
				//print_vector();
				//std::cout << "it = " << *save << " end = "<< *endz << std::endl;
				for (iterator it = begin(); it < end(); it++)
				{
				//	std::cout << "tmp = "  << std::endl;
					if (it != position)
					{
						tmp[j] = *it;
						j++;
					}
				}
				_size_filled--;
				_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];


			//	print_vector();
				return (position);
			};

			//erase an range de first(inclu) a last(non inclu) 
			iterator erase (iterator first, iterator last)
			{
				T		tmp[_size_filled];
				iterator	it = begin();
				iterator	save = begin();
				iterator	_end = end();
				int			j;
				j = 0;
				while (it != first)
				{
					tmp[j++] = *it;
					it++;
				}
				while (it != last)
					it++;
				while (it != _end)
				{
					tmp[j++] = *it;
					it++;
				}
				_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
				_size_filled = j;
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
				return (first);
			};

			//clear suprimme tous les elements du tab
			void clear()
			{
				while(_size_filled > 0)
				{
					pop_back();
				}
				if (_size_alloc > 0)
				{
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * 2));
				_size_alloc = 2;
				}
			};
			
	};

		//-------------NON-MEMBER FUNCTION OVERLOADS-------------

		// relational operators ==
		template <class T, class Alloc>
			bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			};
		// relational operators !=
		template <class T, class Alloc>
			bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return (!(lhs == rhs));
			};
		
		// relational operators < // Renvoie true si la plage [first1,last1)(donc lhs) est lexicographiquement inférieure à la plage [first2,last2) (donc rhs).
		template <class T, class Alloc>
			bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{

				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));

			};
		
		// relational operators <=
		template <class T, class Alloc>
			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs == rhs)
					return (true);
				return (!(lhs > rhs));
			};
		
		// relational operators >
		template <class T, class Alloc>
			bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs == rhs)
					return (false);
				return (!(lhs < rhs));
			};
		
		// relational operators >=
		template <class T, class Alloc>
			bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs == rhs)
					return (true);
				return (!(lhs < rhs));
			};
		
		// swap <vector>
		template <class T, class Alloc>
  			void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) // il se comporte comme si x.swap(y) a été appelé.
			{
				return(x.swap(y));
			};


		template < class T >		
		std::ostream& operator <<(std::ostream& s, ft::vector<T>& v) 
			{
				if (v.empty() == true)
					return (s);
				s << "{";
				for (typename vector<T>::iterator it = v.begin(); it + 1 != v.end(); ++it)
				{
					s << *it << ", ";
				}
				s << v[v.size() - 1] << "}";
				return s;
			}
}

#endif
