#ifndef MAP_UTILS_HPP
# define MAP_UTILS_HPP

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

			pair				node;
			Node				*left;
			Node				*right;
			Node				*top;
			int					height;

		public:

			Node() : left(NULL), right(NULL), top(nullptr), height(1) 
			{};

			Node(Node<T> const &src) : pair(src.node)
			{
				left = src.left;
				right = src.right;
				height = src.height;
				top = src.top;
			};

			Node(T const &pair) : pair(pair)
			{
				left = NULL;
				right = NULL;
				top = NULL;
				height = 1;
			};

			~Node();

			Node<T> &operator=(Node<T> const &rhs)
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

			bool operator==(Node<T> const &rhs)
			{
				if (left == rhs.left && right == rhs.right && top == rhs.top && height == rhs.height)
					return true;
				return false;
			};

			bool operator!=(Node<T> const &rhs)
			{
				if (left == rhs.left && right == rhs.right && top == rhs.top && height == rhs.height)
					return false;
				return true;
			};
	};

	template <class T, class Comp, typename Alloc = std::allocator<T> >
	class BST_base
	{
		public:

			typedef typename	Alloc::template	rebind<Node<T> >::other		allocator_type;

			Node<T>				*ptr;
			Comp				comp;
			allocator_type		allocate;

			BST_base(const allocator_type &alloc = allocator_type()) : ptr(nullptr), allocate(alloc)
			{};

			BST_base(Comp &p, const allocator_type &alloc = allocator_type()) : ptr(nullptr), comp(p), allocate(alloc)
			{};

			BST_base(Node<T> &p) : ptr(p)
			{};

			size_t		size(Node<T> *root)
			{
				size_t		len;
				if (root == NULL)
					return (0);
				len = 1;
				while (root->left)
					len += size(root->left);
				while (root->right)
					len += size(root->right);
				return (len);
			};

			Node<T>		*clear(Node<T> *root)
			{
				if (root == NULL)
					return (NULL);
				if (root->right)
				{
					clear(root->right);
					allocate.deallocate(root->right, 1);
					root->top = NULL;
					root->right = NULL;
				}
				if (root->left)
				{
					clear(root->left);
					allocate.deallocate(root->left, 1);
					root->top = NULL;
					root->left = NULL;
				}
				return (NULL);
			};

			T			&get_data()
			{
				return (ptr->node);
			};

			Node<T>		*most_left(Node<T> *node) const
			{
				// Node<T>		*tmp = node;
				while (node && node->left)
					node = node->left;
				// return (tmp);
				return (node);
			};

			Node<T>		*most_right(Node<T> *node) const
			{
				// Node<T>		*tmp = node;
				while (node && node->right)
					node = node->right;
				// return (tmp);
				return (node);
			};

			Node<T>		*newNode(T const &pair)
			{
				Node<T> *new_node = allocate.allocate(1);
				new_node = Node(pair);
				return (new_node);
			};

			int			max(int a, int b) const
			{
				return ( a > b ? a : b );
			};

			int			height(Node<T> *root) const
			{
				if (root == NULL)
					return (NULL);
				return (root->height);
			};

			Node<T>		*right_rotate(Node<T> *root)
			{
				if (root == NULL)
					return (NULL);
				Node<T>		*tmp;
				if (root->right != NULL)
					tmp = root->right;
				if (tmp->left != NULL)
					root->right = tmp->left;
				tmp->left = root;
				tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
				root->height = max(height(root->left), height(root->right)) + 1;
				return (tmp);
			};

			Node<T>		*left_rotate(Node<T> *x)
			{
				if (root == NULL)
					return (NULL);
				Node<T>		*tmp;
				if (root->left != NULL)
					tmp = root->left;
				if (tmp->right != NULL)
					root->left = tmp->right;
				tmp->right = root;
				tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
				root->height = max(height(root->left), height(root->right)) + 1;
				return (tmp);
			};

			int			getBalanceFactor(Node<T> *root)
			{
				if (root == NULL)
					return (0);
				return (height(root->left) - height(root->right));
			};

			Node<T>		*insertNode(Node<T> *root, T pair)
			{
				if (root == NULL)
					return (newNode(pair));
				if (comp(root->pair, pair))
				{
					Node<T> *new_node = insertNode(root->left, pair);
					new_node->top = root;
					root->left = new_node;
				}
				else if (comp(pair, root->pair))
				{
					Node<T> *new_node = insertNode(root->right, pair);
					new_node->top = root;
					root->right = new_node;
				}
				else
					return (root);
				root = balance_tree(root, pair);
				return (root);
			};

			Node<T>		*balance_tree(Node<T> *root, T pair)
			{
				if (root == NULL)
					return (NULL);
				root->height = max(height(root->left), height(root->right)) + 1;
				int balance = getBalanceFactor(root);
				if (balance > 1)
				{
					if (comp(pair, root->left->pair))
					{
						return (right_rotate(root));
					}
					else if (comp(root->left->pair, pair))
					{
						root->left = left_rotate(root->left);
						return (right_rotate(root));
					}
				}
				if (balance < -1)
				{

					if (comp(root->right->pair, pair))
					{
						return (left_rotate(root));
					}
					else if (comp(pair, root->right->pair))
					{
						root->right = right_rotate(root->right);
						return (left_rotate(root));
					}
				}
				return (root);
			};

			Node<T>		*nodeWithMimumValue(Node<T> *node)
			{
				Node<T>		*current = node;

				while (current->left != NULL)
					current = current->left;
				return (current);
			};

			bool		count(Node<T> *root, T pair) const
			{
				Node<T>		*tmp;
				
				tmp = root;
				if (root == NULL)
					return (false);
				while (tmp)
				{
					if (tmp->pair.first == pair.first)
						return (true);
					if (comp(tmp->pair, pair))
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				return (false);
			};

			Node<T>		*deleteNode(Node<T> *root, T key)
			{
				if (root == NULL)
					return (NULL);
				if (comp(key, root->pair))
					root->left = deleteNode(root->left, key);
				else if (comp(root->pair, key))
					root->right = deleteNode(root->right, key);
				else
				{
					if ((root->right == NULL) && (root->left == NULL))
					{
						// allocate.destroy(root);
						allocate.deallocate(root, 1);
					}
					else if ((root->right == NULL) || (root->left == NULL))
					{
						Node<T>		*temp = root->left ? root->left : root->right;
						Node<T>		*save_top = root->top;
						// m_allocate.construct(root, temp->pair);
						root = newNode(pair);
						root->left = temp->left;
						root->right = temp->right;
						root->height = temp->height;
						root->top = save_top;
						// allocate.destroy(temp);
						allocate.deallocate(temp, 1);
					}
					else
					{
						Node<T>		*temp = nodeWithMimumValue(root->right);
						Node<T>		*new_node = newNode(temp->pair);
						// Node<T>		*new_node = m_allocate.allocate(1);
						// m_allocate.construct(new_node, temp->pair);
						new_node->top = root->top;
						new_node->left = root->left;
						new_node->right = root->right;
						new_node->height = root->height;

						if (root->left)
							root->left->top = new_node;
						if (root->right)
							root->right->top = new_node;

						if (root == root->top->left)
							root->top->left = new_node;
						else if (root == root->top->right)
							root->top->right = new_node;

						root->left = nullptr;
						root->right = nullptr;
						root->top = nullptr;
						root = new_node;
						root->right = deleteNode(root->right, temp->pair);
					}
					root = balance_tree(root, pair);
					return (root);
				}
			};

	};
	
}

#endif