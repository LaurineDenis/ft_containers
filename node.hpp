#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"

namespace ft
{
	template<class Pair>
	struct Node
	{
		Node*	top;
		Node*	left;
		Node*	right;
		Pair	value;
		int		height;

		Node(): top(NULL), left(NULL), right(NULL), value(), height(0)
		{};

		Node(const Pair &data): top(NULL), left(NULL), right(NULL), value(data), height(0)
		{};

		Node(const Node &x): top(x.top), left(x.left), right(x.right), value(x.value), height(x.height)
		{};

		~Node()
		{};

		Node &operator=(const Node &x)
		{
			if (this != &x)
			{
				top = x.top;
				left = x.left;
				right = x.right;
				value = x.value;
			}
			return (*this);
		};

		Node *find_min(Node *node)
		{
			if (!node)
				return NULL;
			while (node->left)
				node = node->left;
			return (node);
		};

		Node *find_max(Node *node)
		{
			if (!node)
				return NULL;
			while (node->right)
				node = node->right;
			return (node);
		};

		Node *next_node()
		{
			Node* tmp = this;
			if (tmp->right)
				return (find_min(tmp->right));
			Node* pa = tmp->top;
			while (pa && tmp == pa->right)
			{
                tmp = pa;
                pa = tmp->top;
            }
            return (pa);
		};

		Node *previous_node()
		{
			Node* tmp = this;
			if (tmp->left)
				return find_max(tmp->left);
			Node* pa = tmp->top;
			while (pa && tmp == pa->left){
                tmp = pa;
                pa = tmp->top;
            }
            return (pa);
		};
	};
}

#endif