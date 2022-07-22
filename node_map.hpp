#ifndef NODE_MAP_HPP
# define NODE_MAP_HPP

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

	template <class T>
	class Node
	{
		public:

			T					node;
			Node				*left;
			Node				*right;
			Node				*top;
			int					height;

			Node() : left(NULL), right(NULL), top(nullptr), height(1) 
			{};

			Node(Node<T> const &src) : node(src.node)
			{
				left = src.left;
				right = src.right;
				height = src.height;
				top = src.top;
			};

			Node(T const &pair) : node(pair)
			{
				left = NULL;
				right = NULL;
				top = NULL;
				height = 1;
			};

			~Node();

			Node<T>	&operator=(Node<T> const &rhs)
			{
				if (this != &rhs)
				{
					left = rhs.left;
					right = rhs.right;
					top = rhs.top;
					height = rhs.height;
				}
				return *this;
			};

			bool	operator==(Node<T> const &rhs)
			{
				if (left == rhs.left && right == rhs.right && top == rhs.top && height == rhs.height)
					return true;
				return false;
			};

			bool	operator!=(Node<T> const &rhs)
			{
				if (left == rhs.left && right == rhs.right && top == rhs.top && height == rhs.height)
					return false;
				return true;
			};

			Node	*find_min(Node *node)
			{
				if (!node)
					return (NULL);
				while (node->left)
					node = node->left;
				return (node);
			};

			Node	*find_max(Node *node)
			{
				if (!node)
					return (NULL);
				while (node->right)
					node = node->right;
				return (node);
			};

			Node	*next_node()
			{
				Node* tmp = this;
				if (tmp->right)
					return (find_min(tmp->right));
				Node* parent = tmp->top;
				while (parent && tmp == parent->right)
				{
					tmp = parent;
					parent = tmp->top;
				}
				return (parent);
			};

			Node	*previous_node()
			{
				Node* tmp = this;
				if (tmp->left)
					return find_max(tmp->left);
				Node* parent = tmp->top;
				while (parent && tmp == parent->left)
				{
					tmp = parent;
					parent = tmp->top;
				}
				return (parent);
			};
	};
	
}

#endif