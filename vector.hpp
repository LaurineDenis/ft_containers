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
			typedef		size_t	size_type;

		private :

		//---------------VALUES----------------

			T				*_array;		//tableau
			size_t			_size_alloc;	//taille allouée
			size_t			 _size_filled;	//taille remplie (index)
			allocator_type	_alloc;			//malloc

		public :

		//-------------CONSTRUCTORS-------------

			//contructors by default
			explicit vector (const Alloc& alloc = Alloc()): _size_alloc(0),  (0), _alloc(alloc)
			{
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * 2));
			};

			//contructors fill one (remplir)
			explicit vector (size_t n, const value_type& val = value_type(), const Alloc& alloc = Alloc()) : _size_alloc(n),  (0), _alloc(alloc)
			{
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * n));
				for (  = 0;   < n;  ++)
				{
					_array[ ] = val;
				}
			};

			//Constructor fill list (remplir)
			template <class InputIte>
			vector(InputIte first, InputIte last, const Alloc& alloc = Alloc())
			{

			};

			//Constructor by copy
			vector (const vector& x)
			{

			};

		//-------------FONCTION-------------

			//print
			void			print_vector()
			{
				for (int i = 0; i <  ; i++)
				{
					std::cout << "_array["<< i <<"] = " << _array[i] << std::endl;
				}
			};


		//-------------ITERATORS-------------

			// begin Renvoie un itérateur pointant vers le premier élément du vecteur.
			iterator begin()
			{
				return (iterator(_array));
			};

			// begin const
			const_iterator begin() const
			{
				return (iterator(_array));
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
				return (reverse_iterator(_array[_size_filled - 1]))
			};

			// rbegin const
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(_array[_size_filled - 1]));
			};


			// rend Renvoie un itérateur inverse pointant vers l'élément théorique précédant le premier élément du vecteur
			reverse_iterator rend()
			{
				return (reverse_iterator(_array[0 - 1]));
			};
			// rend const
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(_array[0 - 1]));
			};
		//-------------CAPACITY-------------
			//size
			size_t	size()
			{
				return ( );
			};
			
			//max_size
			size_type		max_size() const
			{
				return std::numeric_limits<size_t>::max() / sizeof(*_array);
			};

			//resize
			void resize (size_type n, value_type val = value_type())
			{
				if (n <=  )
				{
					for(n; n < ; n++)
						pop_back();
				}
				else if (_size_alloc > n)
				{
					T tmp[n];
					for (size_type i = 0; i < n; i++)
						tmp[i] = _array[i];
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * n));
					for (size_type i = 0; i < n; i++)
						_array[i] = tmp[i];
				}
				else
				{               
					reserve(n);
					for( size_t i = 0; i < n;  i++)
						_array[i]= val;
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
				return (  == 0);
			};

			//reserve => Réaloue plus grand si besoin donc change seulement le size_alloc
			//n => la taille demandé du futur array
			void			reserve (size_type n)
			{
				if (n > max_size())
					throw exception;
				if (_size_alloc < n)
				{
					//realoue plus grand
					T			tmp[_size_alloc + n];
					size_type	tmp_size;
					for (int i = 0; i <  ; i++)
						tmp[i] = _array[i];
					_array.deallocate(_array, sizeof(T *) * _size_alloc);
					tmp_size = _size_alloc;
					_size_alloc = tmp_size + n;
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
					for (size_t i = 0; i < tmp_size; i++)
						_array[i] = tmp[i];
				}
			};

		//-------------ELEMENT ACCESS-------------
			// operator [] Élément d'accès Renvoie une référence à l'élément à la position n dans le vecteur
			reference operator[] (size_type n)
			{
				// if (n > _size_filled || n < 0)
				// 	throw exception; // out of range  
			// ON NE DOIT PAS FAIRE LES VERIFICATION --> CHELOU
				return (_array[n]);
			};

			// const operator []
			const_reference operator[] (size_type n) const
			{
				// if (n >= _size_filled || n < 0)
				// 	throw exception; // out of range 
				return (_array[n]);
			};

			// at Élément d'accès Renvoie une référence à l'élément à la position n dans le vecteur a la diff de operator [] la on verifie les limits 
			reference at (size_type n)
			{
				if (n >= _size_filled || n < 0)
					throw exception; // out of range 
				return (_array[n]);
			};

			// at const	
			const_reference at (size_type n) const
			{
				if (n >= _size_filled || n < 0)
					throw exception; // out of range 
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
  			void assign (InputIterator first, InputIterator last)
			{
				T tmp[_size_filled];
					for (size_type i = 0; i < _size_filled; i++)
						tmp[i] = _array[i];
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * n));
					iterator i; // doit dire que c un iterator pour le mettre a first 
					for (i = first; i != last; i++)
						_array[i] = i;
			};
		// assign (2) le nouveau contenu est constitué de n éléments, chacun initialisé à une copie de val.
			void assign (size_type n, const value_type& val)
			{
				T tmp[_size_filled];
					for (size_type i = 0; i < _size_filled; i++)
						tmp[i] = _array[i];
					_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
					_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * n));
					for (size_type i = 0; i < n; i++)
						_array[i] = val;
			};
		
		//push_back Ajoute un nouvel élément à la fin du vecteur, après son dernier élément actuel. Le contenu de val est copié (ou déplacé) vers le nouvel élément.
			void push_back (const value_type& val)
			{
				if (_size_alloc + 1 >= _size_filled) //Cela augmente effectivement la taille du conteneur de un, ce qui provoque une réallocation automatique de l'espace de stockage alloué si - et seulement si - la nouvelle taille de vecteur dépasse la capacité de vecteur actuelle.
					reserve(_size_filled + 1);
				_array[_size_filled + 1] = val;
				_size_filled++;
			};

		//pop_back Supprime le dernier élément du vecteur, réduisant ainsi la taille du conteneur d'une unité
			void pop_back()
			{
				T tmp[_size_filled];
				for (size_type i = 0; i < _size_filled; i++)
					tmp[i] = _array[i];
				_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_size_filled--;
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_filled));
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
			};
		
		// insert insertion de new element dans le vecteur 
			iterator insert (iterator position, const value_type& val)
			{
				iterator it = position;
				T tmp[_size_filled + 1];
				for (size_t i = 0; i != it.; i++)
						tmp[i] = _array[i];
				_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_size_filled++;
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_filled));
				for (size_type i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];

			};

    		void insert (iterator position, size_type n, const value_type& val)
			{

			};
	
		template <class InputIterator>
   			void insert (iterator position, InputIterator first, InputIterator last)
			{

			};

			//erase only one element
			iterator erase (iterator position)
			{
				T		tmp[_size_filled - 1];
				iterator	it = begin();
				int			j;
				j = 0;
				for (it = 0; it < end(); it++)
				{
					if (it != position)
						tmp[j] = it;
					j++;
				}
				_size_filled--;
				_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * _size_alloc));
				for (size_t i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
			};

			//erase an range de first(inclu) a last(non inclu) 
			iterator erase (iterator first, iterator last)
			{
				T		tmp[_size_filled - 1];
				iterator	it = begin();
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
				for (size_t i = 0; i < _size_filled; i++)
					_array[i] = tmp[i];
			};

			//clear suprimme tous les elements du tab
			void clear()
			{
				for (_size_filled; _size_filled >= 0; _size_filled--)
				{
					pop_back();
				}
				_alloc.deallocate(_array, sizeof(T *) * _size_alloc);
				_array = reinterpret_cast<T *>(_alloc.allocate(sizeof(T *) * 2));
			};
			
			//get_allocator retourne l'allocateur utilisé
			allocator_type get_allocator() const
			{

			};
	};
}
#endif