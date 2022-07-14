#ifndef BSTNODE_HPP
#define BSTNODE_HPP

#include "pair.hpp"

namespace ft
{
	template<class Pair>
	struct BSTNode
	{
		BSTNode* parent;
		BSTNode* left;
		BSTNode* right;
		Pair value;
		int height;

		BSTNode(): parent(NULL), left(NULL), right(NULL), value(), height(0)
		{

		}

		BSTNode(const Pair &data): parent(NULL), left(NULL), right(NULL), value(data), height(0)
		{

		}

		// BSTNode(BSTNode *parent, BSTNode *left, BSTNode *right): parent(parent), left(left), right(right), value(), height(0)
		// {

		// }

		BSTNode(const BSTNode &x): parent(x.parent), left(x.left), right(x.right), value(x.value), height(x.height)
		{

		}

		~BSTNode()
		{

		}

		BSTNode &operator=(const BSTNode &x)
		{
			if (this != &x)
			{
				parent = x.parent;
				left = x.left;
				right = x.right;
				value = x.value;
			}
			return (*this);
		}

		BSTNode *findMin(BSTNode *node)
		{
			if (!node)
				return NULL;
			while (node->left)
			{
				//std::cout << "findMin node = " << node->value.first << std::endl;
				node = node->left;
			}
			return (node);
		}

		BSTNode *findMax(BSTNode *node)
		{
			//std::cout << "node = " << node->value.first << std::endl;
			if (!node)
				return NULL;
			while (node->right)
				node = node->right;
			//std::cout << "node = " << node->value.first << std::endl;
			return (node);
		}

		BSTNode *next()
		{
			BSTNode* tmp = this;
			//std::cout << "next() tmp = " << tmp->value.first << std::endl;
			// if (tmp->right)
			// 	std::cout << "->right = " << tmp->right->value.first << std::endl;
			if (tmp->right)
			{
				//std::cout << "ff" << std::endl;
				//std::cout << "findMin = " << findMin(tmp->right)->value.first << std::endl;
				return (findMin(tmp->right));
			}
			BSTNode* pa = tmp->parent;
			while (pa && tmp == pa->right)
			{
                tmp = pa;
                pa = tmp->parent;
            }
			//std::cout << "return pa = " << pa->value.first << std::endl;
            return pa;
		}

		BSTNode *prev()
		{
			BSTNode* tmp = this;
			if (tmp->left)
				return findMax(tmp->left);
			BSTNode* pa = tmp->parent;
			while (pa && tmp == pa->left){
                tmp = pa;
                pa = tmp->parent;
            }
            return pa;
		}
	};
}

#endif
