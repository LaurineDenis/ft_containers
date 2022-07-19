#ifndef MAP_HPP
# define MAP_HPP

# include <map>
# include <limits>
# include <memory>
# include <utility>
# include <cstddef>
# include <iostream>
# include "utils.hpp"
# include "map_utils.hpp"

# include <stdio.h>

namespace ft
{
	template <	class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::Node<Key, T> > >
	class Map
	{
		public:

			typedef Key									key_type;
			typedef T									mapped_type;
			typedef ft::pair<key_type, mapped_type>		value_type;
			typedef Compare								key_compare;
			typedef Alloc								allocator_type;
			typedef size_t								size_type;
			typedef ptrdiff_t							difference_type;

			template <class Key, class T, class Compare, class Alloc>
			class map<Key,T,Compare,Alloc>::value_compare
			{
				friend class map;
				protected:

					Compare						comp;
					value_compare (Compare c) :	comp(c) {};

				public:
				
					typedef bool		result_type;
					typedef	value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					};
			}

		protected :

			Node<Key, T>	*_tree;
			allocator_type	_alloc;
			key_compare		_key_compare;
			value_compare	_value_compare;
			size_t			_size;

		private :

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
			_alloc(alloc), _key_compare(comp), _value_compare(value_compare()), _tree(_alloc) {}
			{};
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

			map (const map& x);
	};
}

#endif