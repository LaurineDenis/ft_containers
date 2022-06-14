#ifndef MAP_HPP
# define MAP_HPP

# include <map>
# include <limits>
# include <memory>
# include <utility>
# include <cstddef>
# include <iostream>
# include "utils.hpp"

# include <stdio.h>

namespace ft
{

	template <class Key, class T>
	class Node
	{
		public :

		typedef ft::pair<Tkey, Tvalue>	pair;

		protected:

			bool				is_end;
			pair				node;
			Node				*left;
			Node				*right;
			Node				*top;

		public:

			Node();
			~Node();

			//getter setter
			pair	*getPair()	{ return &node; };
			Node	*getRight()	{ return right; };
			Node	*getLeft()	{ return left; };
			Node	*getTop()	{ return top; };
			bool	getIsEnd()	{ return is_end; };


			void	setPair(const pair &pair)		{ *node = pair; };
			void	setRight(Node *node){
				right = node;
				if (node->getTop())
					node->getTop()->setIsEnd(false);
				right->setIsEnd(true);
			};
			void	setLeft(Node *node){
				left = node;
				if (node->getTop())
					node->getTop()->setIsEnd(false);
				left->setIsEnd(true);
			};
			void	setTop(Node *node)				{ top = node; };
			void	setIsEnd(bool end)				{ is_end = end; };
			void	set_key(const Tkey &key)		{ node.first = key; };
			void	set_val(const Tvalue &val)		{ node.second = val; };

	};


	template <	class Key, 
				class T, 
				class Compare = less<Key>, 
				class Alloc = std::allocator<ft::Node<Key, T> > >
	class Map
	{
		public:

			typedef Key									key_type;
			typedef T									mapped_type;
			typedef ft::pair<key_type, mapped_type>		value_type;
			typedef Compare								key_compare;
			typedef std::allocator<value_type>			allocator_type;
			typedef size_t								size_type;
			typedef ptrdiff_t							difference_type;

		private :

			Node<Key, T>	*_tree;
			allocator_type	_alloc;
			key_compare		_comp;
			size_t			_size;

			
	};
}

#endif