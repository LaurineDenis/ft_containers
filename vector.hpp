#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>
# include <vector>
# include <cstddef>
# include <sstream>
# include <iostream>
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
			typedef typename	Alloc::reference				reference;
			typedef typename	Alloc::const_reference			const_reference;
			typedef typename	Alloc::pointer					pointer;
			typedef typename	Alloc::const_pointer			const_pointer;
			typedef				iterator<T>						iterator;
			typedef				const_iterator<T>				const_iterator;
			typedef				reverse_iterator<iterator>		reverse_iterator;
			typedef				const_reverse_iterator<iterator>	const_reverse_iterator;
			class				OutOfRange : public std::exception
			{ 
				virtual const char *what() const throw()
				{
					return "ft::Vector error : Out of range!\n";
				}
			};
			class				length_error : public std::exception
			{ virtual const char *what() const throw()
				{
					return "ft::Vector error : Length error!\n";
				}
			};

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
				// std::cout << "constructor by default 0" <<std::endl;
				// _array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * 2));
			};

			//contructors fill one (remplir)
			explicit vector (size_type n, const value_type& val = value_type(), const Alloc& alloc = Alloc()) : _size_alloc(n), _size_filled(0), _alloc(alloc)
			{
				// std::cout << "constructor by value 0" <<std::endl;
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * n));
				for ( _size_filled= 0; _size_filled < n; _size_filled++)
				{
					_array[_size_filled] = val;
				}


			};
			//Constructor fill list (remplir)
			template <class InputIte>
			vector(InputIte first, InputIte last, const Alloc& alloc = Alloc(),
			typename ft::enable_if<InputIte::input_iterator, InputIte>::type = NULL) : _size_alloc(0), _size_filled(0), _alloc(alloc)
			{
				// std::cout << "constructor by list 0" <<std::endl;
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
			};
			//Constructor by copy
			//_alloc(allocator_type())
			vector (const vector& x) :_size_alloc(0), _size_filled(0), _alloc(x._alloc)
			{
				//*this = x;
				 //std::cout << "constructor COPY 0" <<std::endl;

				if (*this == x)
					return;
				insert(begin(), x.begin(), x.end()); 
				//POURQUOI FAIRE CA ?

			};

			// operator =
			vector& operator= (const vector& x)
			{

			//    std::cout << "operator = 0" << std::endl;
				if (*this == x)
					return *this;
				_array = x._array;
				_size_alloc = x._size_alloc;
				_size_filled = x._size_filled;
		//		print_vector();
				return (*this);
			};

			//destructeur
			~vector()
			{
			//    std::cout << "destructor 0" << std::endl;
				this->clear();
			//    std::cout << "destructor 1" << std::endl;
			//	print_element();
				if (_size_alloc > 0)
				{
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
			   		// std::cout << "destructor 2" << std::endl;
					_size_alloc = 0;
				}
			   //  std::cout << "destructor 3" << std::endl;
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

			//print
			void			print_element()
			{
				std::cout << "Size alloc : " << _size_alloc << std::endl;
				std::cout << "Size filled : " << _size_filled << std::endl;
			};

		//-------------EXCEPTIONS------------

			// const char		*vector<T, Alloc>::OutOfRange::what() const throw()
			// {
			// 	return "ft::Vector error : Out of range!\n";
			// }

			// const char		*vector<T, Alloc>::length_error::what() const throw()
			// {
			// 	return "ft::Vector error : Length error!\n";
			// }

		//-------------ITERATORS-------------

			// begin Renvoie un itérateur pointant vers le premier élément du vecteur.
			iterator begin()
			{
				// print_element();
				// std::cout << "begin = " << _array[12] << std::endl;

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
				return (reverse_iterator(--(this->end())));
			};

			// rbegin const
			const_reverse_iterator rbegin() const
			{
				return (rbegin());
			};


			// rend Renvoie un itérateur inverse pointant vers l'élément théorique précédant le premier élément du vecteur
			reverse_iterator rend()
			{
				return (reverse_iterator(--(this->begin())));
			};
			// rend const
			const_reverse_iterator rend() const
			{
				return (rend());
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
				// std::cout << "size_filled = " << _size_filled << std::endl;
				// std::cout << "n = " << n << std::endl;
				// std::cout << "_size_alloc = " << _size_alloc << std::endl;


				if (n <= _size_filled)
				{
					size_type i = _size_filled;
					while (n < i)
					{
						pop_back();
						n++;
					}
				}
				else if (_size_alloc > n)
				{
					// alloc = 10 et n =  5 alloc trop grande

					T tmp[_size_alloc];
					size_type tmp_size = _size_alloc;
					for (size_type i = 0; i < _size_alloc - 1; i++)
						tmp[i] = _array[i];
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
					_size_alloc = n + 1;
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
					for (size_type i = 0; i < tmp_size; i++)
						_array[i] = tmp[i];
					for (size_type i = tmp_size ; i < _size_alloc - 1; i++)
						_array[i] = tmp[i];
					_size_filled = n;
				}
				else
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
				// std::cout << "reserve 0" <<std::endl;
				if (n > max_size())
					throw vector::length_error();
				
				if (_size_alloc < n)
				{
					//realoue plus grand
					T			tmp[_size_filled + n + 1];
					size_type	tmp_size;
					for (size_type i = 0; i < _size_filled ; i++)
						tmp[i] = _array[i];
					tmp_size = _size_filled + n;
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
					_size_alloc = tmp_size + 1;
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
					for (size_type i = 0; i < tmp_size; i++)
						_array[i] = tmp[i];
				}
			};

		//-------------ELEMENT ACCESS-------------
			// operator [] Élément d'accès Renvoie une référence à l'élément à la position n dans le vecteur
			reference operator[] (size_type n)
			{
				if (n > _size_filled || n < 0)
					throw vector::OutOfRange(); // out of range  
			// ON NE DOIT PAS FAIRE LES VERIFICATION --> CHELOU
				return (_array[n]);
			};

			// const operator []
			const_reference operator[] (size_type n) const
			{
				if (n >= _size_filled || n < 0)
					throw vector::OutOfRange(); // out of range 
				return (_array[n]);
			};

			// at Élément d'accès Renvoie une référence à l'élément à la position n dans le vecteur a la diff de operator [] la on verifie les limits 
			reference at (size_type n)
			{
				if (n >= _size_filled || n < 0)
					throw vector::OutOfRange(); // out of range
				return (_array[n]);
			};

			// at const	
			const_reference at (size_type n) const
			{
				if (n >= _size_filled || n < 0)
					throw vector::OutOfRange(); // out of range 
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

		// assign Affecte un nouveau contenu au vecteur, en remplaçant son contenu actuel et en modifiant sa taille en conséquence.
		// assign (1) les nouveaux contenus sont des éléments construits à partir de chacun des éléments de la gamme entre premier et dernier, dans le même ordre
		template <class InputIterator>
  			void assign (InputIterator first, InputIterator last, 
			typename ft::enable_if<InputIterator::input_iterator, InputIterator>::type = NULL)
			{
				iterator start = first;
				iterator end = last;
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
				// std::cout << "push back 0" <<std::endl;
				// print_element();
				if (_size_alloc == 0)
				{
					_size_alloc++;
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc + 1));
				}
				else if (_size_alloc + 1 >= _size_filled) //Cela augmente effectivement la taille du conteneur de un, ce qui provoque une réallocation automatique de l'espace de stockage alloué si - et seulement si - la nouvelle taille de vecteur dépasse la capacité de vecteur actuelle.
					reserve(_size_filled + 1);
				// print_element();
				// std::cout << "push back 1" <<std::endl;
				_array[_size_filled] = val;
				// std::cout << "push back 2" <<std::endl;
				_size_filled++;
				// print_element();
				// print_vector();
				// std::cout << "push back 3" <<std::endl;
			};

		//pop_back Supprime le dernier élément du vecteur, réduisant ainsi la taille du conteneur d'une unité
			void pop_back()
			{
				//std::cout << "pop back 0" <<std::endl;
				_size_filled--;
			};
		
		// insert insertion de new element dans le vecteur 
			iterator insert (iterator position, const value_type& val)
			{
				iterator it = position;
				reserve(_size_filled + 1);
				if (it == end())
				{
					push_back(val);
					return (position);
				}
				T tmp[_size_filled + 1];
				for (iterator i = begin(); i != position; i++)
						tmp[i] = _array[i];
				tmp[position] = val;
				for (iterator i = position; i != end(); i++)
						tmp[i] = _array[i];
				_size_filled++;
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
				return(position);
			};

    		void insert (iterator position, size_type n, const value_type& val)
			{
				iterator it = position;
				reserve(n);
				if (it == end())
				{
					for (size_type i = 0; i != n; i++)
						push_back(val);
				}
				T tmp[n];
				for (iterator i = begin(); i != position; i++)
						tmp[i] = _array[i];
				for (size_type y = 0; y != n; y++)
						tmp[y++] = val;
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
			};
	
		template <class InputIterator>
   			void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<InputIterator::input_iterator, InputIterator>::type = NULL)
			{

				size_type	count = 0;
				iterator it = position;

				while (first != last)
				{
					first++;
					count++;
				}
				first -= count;

				// cas 1 : vecteur vide mais deja alloue et bonne taille donc juste a remplir 
				if (_size_filled == count)
				{

					while (first != last)
					{
						push_back(*first);
						first++;
						_size_filled--; // obligé car on realloue 
					}
				}
				// // cas 2 : vecteur plein mais on doit rajouter que a la fin : donc realloc plus push
				else if (position == end())
				{
					
					while (first != last)
					{
						push_back(*first);
						first++;
					}
				}
				// cas 3 : rajouter en plein milieux 
				else 
				{
					T tmp[_size_filled + count];
					size_type y = 0;
					reserve(count);
					_size_filled += count;
					for (iterator i = begin(); i != it; i++)
							tmp[y] = _array[y];
					while (first != last)
							tmp[y] = *first++;
					for (size_type i = 0; i < _size_filled; i++)
						_array[i] = tmp[i];
				}
			};
		
		// swap 
			void swap (vector& x)
			{
			    // std::cout << "swap 0" << std::endl;
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
				int			j;
				j = 0;
				for (iterator it = begin(); it < end(); it++)
				{
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
				return (save);
			};

			//erase an range de first(inclu) a last(non inclu) 
			iterator erase (iterator first, iterator last)
			{
				T		tmp[_size_filled - 1];
				iterator	it = begin();
				iterator	save = begin();
				int			j;
				j = 0;
				for (it = 0; it < end(); it++)
				{
					if (it == first)
					{
						while (first != last && it != end())
						{
							first++;
							it++;
							_size_filled--;
						}
					}
					tmp[j] = it;
					j++;
				}
				_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
				return (save);
			};

			//clear suprimme tous les elements du tab
			void clear()
			{
			//	print_element();
			//	print_vector();

				while(_size_filled > 0)
				{
					pop_back();
				}
				if (_size_alloc > 0)
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * 2));
				_size_alloc = 2;
			};
			
	};

		//-------------NON-MEMBER FUNCTION OVERLOADS-------------

		// relational operators ==
		template <class T, class Alloc>
			bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return (false);
				typename ft::vector<T>::const_iterator first_lhs = lhs.begin();
				typename ft::vector<T>::const_iterator first_rhs = rhs.begin();
				while (first_lhs != lhs.end() && first_rhs != rhs.end())
				{
					if (first_lhs != first_rhs)
						return (false);
					first_lhs++;
					first_rhs++;
				}
				return (true);
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
				if (lhs == rhs)
					return (false);
				typename ft::vector<T>::const_iterator first_lhs = lhs.begin(); // on doit faire un template d'iterator
				typename ft::vector<T>::const_iterator  first_rhs = rhs.begin();
				while (first_lhs != lhs.end() && first_rhs != rhs.end())
				{
					first_lhs++;
					first_rhs++;
				}
				if (first_lhs != lhs.end) // on regarde si on a reussi a aller a la fin du vecteur 
					return (true); // si c'est pas le cas ca veut dire que rhs a terminé la boucle mais que lhs nn; donc elle est plus petite
				return (false);
			};
		
		// relational operators <=
		template <class T, class Alloc>
			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs == rhs)
					return (true);
				return (!(lhs < rhs));
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