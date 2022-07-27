#ifndef MAP_HPP
# define MAP_HPP

# include <map>
# include <limits>
# include <memory>
# include <utility>
# include <cstddef>
# include <iostream>
# include "node.hpp"
# include "utils.hpp"
# include "iterator_map.hpp"
# include "iterator.hpp"
# include "pair.hpp"

# include <stdio.h>

namespace ft
{
	template <	class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<Key, T> > >
	class map
	{
		public:

			typedef Key 										key_type;
			typedef T 											mapped_type;
			typedef ft::pair<const key_type,mapped_type> 		value_type;
			typedef Compare 									key_compare;
			typedef Alloc 										allocator_type;
			typedef Node<value_type>							m_node;
			// typedef std::allocator<m_node>						m_node_alloc;
			typedef std::ptrdiff_t 								difference_type;
			typedef size_t 										size_type;
			typedef typename allocator_type::reference 				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer 				pointer;
			typedef typename allocator_type::const_pointer 			const_pointer;
			typedef typename Alloc::template rebind<m_node>::other						node_allocator_type;
			typedef ft::iterator_map<m_node, value_type>								iterator;
			typedef ft::const_iterator_map<m_node, const value_type, iterator>			const_iterator;
			typedef ft::reverse_iterator<iterator>										reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;

		private:

			key_compare			_compare;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;
			m_node			*_root;
			m_node			*_end;
			m_node			*_begin;
			size_type		_size;

		public :

			class value_compare
			{
				friend class map;

				protected:

					Compare comp;
					value_compare(Compare c): comp(c)
					{}

				public:

					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					bool operator()(const value_type &x, const value_type &y) const
					{
						return (comp(x.first, y.first));
					}
			};


			//contructor and destructor

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
			 _compare(comp), _alloc(alloc), _node_alloc(std::allocator<m_node>()), _root(NULL), _end(NULL), _begin(NULL), _size(0)
			{
				// std::cout << "Constructor 1 " << std::endl;
				_begin = _node_alloc.allocate(1);
				_node_alloc.construct(_begin, m_node());
				_end = _node_alloc.allocate(1);
				_node_alloc.construct(_end, m_node());
				_begin->top = _end;
			};
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			 _compare(comp), _alloc(alloc), _node_alloc(std::allocator<m_node>()), _root(NULL), _end(NULL), _begin(NULL), _size(0)
			{
				// std::cout << "Constructor 2 " << std::endl;
				_begin = _node_alloc.allocate(1);
				_node_alloc.construct(_begin, m_node());
				_end = _node_alloc.allocate(1);
				_node_alloc.construct(_end, m_node());
				_begin->top = _end;
				insert(first, last);
			};

			map (const map& x) : 
			_compare(x._compare), _alloc(x._alloc), _node_alloc(x._node_alloc), _root(NULL), _size(0)
			{
				// std::cout << "Constructor 3 " << std::endl;
				_begin = _node_alloc.allocate(1);
				_node_alloc.construct(_begin, m_node());
				_end = _node_alloc.allocate(1);
				_node_alloc.construct(_end, m_node());
				_begin->top = _end;
				this->insert(x.begin(), x.end());
			};

			~map()
			{
				clear();
				_node_alloc.destroy(_begin);
				_node_alloc.deallocate(_begin, 1);
				_node_alloc.destroy(_end);
				_node_alloc.deallocate(_end, 1);
			};

			//operator

			map& operator=(const map& x)
			{
				clear();
				_compare = x._compare;
				_size = 0;
				_alloc = x._alloc;
				_node_alloc = x._node_alloc;
				insert(x.begin(), x.end());
				return (*this);
			};

			//iterators

			iterator begin()
			{
				return (iterator(_begin->top));
			};

			const_iterator begin() const
			{
				return (const_iterator(_begin->top));
			};

			reverse_iterator rbegin()
			{
				return (reverse_iterator(_end));
			};

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(_end));
			};

			reverse_iterator rend()
			{
				return (reverse_iterator(_begin->top));
			};

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(_begin->top));
			};

			iterator end()
			{
				return (iterator(_end));
			};

			const_iterator end() const
			{
				return (const_iterator(_end));
			};

			//observeurs

			key_compare key_comp() const
			{
				return (_compare);
			};

			value_compare value_comp() const
			{
				return (value_compare(_compare));
			};

			//capacity

			bool empty() const
			{
				if (_size != 0)
					return (false);
				return (true);
			};

			size_type size() const
			{
				return (_size);
			};

			size_type max_size() const
			{
				return (std::numeric_limits<size_type>::max() / sizeof(m_node));
			};

			//element accessor

			mapped_type& operator[](const key_type& k)
			{
				//return (*(insert(pair(k, mapped_type())).first)).second;
				// std::cout << "To insert with [ ] K : " << k << std::endl;
				return (*(this->insert(value_type(k, mapped_type())).first)).second;
				// return (*(insert(ft::make_pair(k, mapped_type())).first)).second;
			};

			//Modifiers

			pair<iterator, bool> insert(const value_type &val)
			{
				// std::cout << "Insert normal " << std::endl;
				//Si arbre vide on créer le 1er maillon
				if (!_root)
				{
					_root = _node_alloc.allocate(1);
					_node_alloc.construct(_root, m_node(val));
					_root->left = _begin;
					_root->right = _end;
					_end->top = _root;
					_begin->top = _root;
					_size = 1;
					return (ft::make_pair(iterator(_root), true));
				}
				iterator it = this->find(val.first);
				if (it != this->end())
					return (ft::make_pair(it, false));
				m_node *node;
				m_node *new_n = _node_alloc.allocate(1);
				_node_alloc.construct(new_n, m_node(val));
				if (_compare(_end->top->value.first, val.first))
					node = _end->top;
				else if (!_compare(_begin->top->value.first, val.first))
					node = _begin->top;
				else
					node = _root;			
				while (node->right || node->left)
				{
					if (_compare(node->value.first, val.first))
					{
						if (node->right && node->right != _end)
							node = node->right;
						else
							break ;
					}
					else
					{
						if (node->left && node->left != _begin)
							node = node->left;
						else
							break ;
					}
				}
				new_n->top = node;
				if (_compare(node->value.first, val.first))
				{
					new_n->right = node->right;
					if (new_n->right)
						new_n->right->top = new_n;
					new_n->left = NULL;
					node->right = new_n;
				}
				else
				{
					new_n->left = node->left;
					if (new_n->left)
						new_n->left->top = new_n;
					new_n->right = NULL;
					node->left = new_n;
				}
				_size++;
				if (_size >= 3)
					rebalance(new_n);
				return ft::make_pair(new_n, true);
			};

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				// std::cout << "Insert position " << std::endl;
				return (insert(val).first);
			};

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				// std::cout << "Insert iterator " << std::endl;
				while (first != last)
				{
					insert(*first);
					first++;
				}
			};

			// void	print_node(m_node *node)
			// {
			// 	if (node == NULL)
			// 		return;
			// 	// std::cout << "Print Node " << std::endl;
			// 	// std::cout << "Key : " << node->value.first << std::endl;
			// 	// std::cout << "Value : " << node->value.second << std::endl;
			// }

			// void	print_tree(void)
			// {
			// 	// std::cout << "Print Tree " << std::endl;
			// 	// std::cout << "Size : " << _size << std::endl;
			// 	// std::cout << "Root" << std::endl;
			// 	// std::cout << "Key : " << _root->value.first << std::endl;
			// 	// std::cout << "Value : " << _root->value.second << std::endl;
			// 	// std::cout << "_end " << std::endl;
			// 	// std::cout << "Key : " << _end->value.first << std::endl;
			// 	// std::cout << "Value : " << _end->value.second << std::endl;
			// 	// std::cout << "_begin" << std::endl;
			// 	// std::cout << "Key : " << _begin->value.first << std::endl;
			// 	// std::cout << "Value : " << _begin->value.second << std::endl;
			// }

			void erase(iterator position)
			{
				// std::cout << "Erase" <<std::endl;
				m_node	*p = position.get_internal_pointer();
				m_node	*tmp;
				m_node	*toBalance;

				if (p == _root)
				{
					if (p->right && !p->left)
					{
						p->right->top = NULL;
						_root = p->right;
					}
					else if (!p->right && p->left)
					{
						p->left->top = NULL;
						_root = p->left;
					}
					else if (p->right && p->left)
					{
						if (p->right != _end)
						{
							tmp = p->find_min(p->right);
							if (tmp->top != p)
								toBalance = tmp->top;
							else
								toBalance = tmp;
							tmp->left = p->left;
							p->left->top = tmp;
							if (tmp != p->right)
							{
								tmp->right = p->right;
								p->right->top = tmp;
							}
							if (tmp->top)
							{
								if (tmp->top->left == tmp)
									tmp->top->left = NULL;
								else
									tmp->top->right = NULL;
							}
							tmp->top = NULL;
							_root = tmp;
						}
						else if (p->left != _begin)
						{
							p->left->top = NULL;
							tmp = p->find_max(p->left);
							if (tmp->top != p)
								toBalance = tmp->top;
							else
								toBalance = tmp;
							tmp->left = p->left;
							if (p->right->top)
								p->right->top = tmp;
							tmp->right = p->right;
							if (p->left)
								p->left->top = tmp;
							if (tmp->top)
							{
								if (tmp->top->left == tmp)
									tmp->top->left = NULL;
								else
									tmp->top->right = NULL;
							}
							tmp->top = NULL;
							_root = tmp;
						}
						else
						{
							_begin->top = _end;
							_end->left = _begin;
							_root = NULL;
						}
					}
					else
					{
						_begin->top = _end;
						_root = NULL;
					}
				}
				else if (!p->right && !p->left)
				{
					if (p->top->right == p)
						p->top->right = NULL;
					else
						p->top->left = NULL;
					toBalance = p->top;
				}
				else if (!p->right && p->left)
				{
					if (p->top->right == p)
						p->top->right = p->left;
					else
						p->top->left = p->left;
					p->left->top = p->top;
					toBalance = p->top;
				}
				else if (p->right && !p->left)
				{
					if (p->top->right == p)
						p->top->right = p->right;
					else
						p->top->left = p->right;
					p->right->top = p->top;
					toBalance = p->top;
				}
				else
				{
					if (p->left == _begin)
					{
						p->top->left = p->right;
						p->right->top = p->top;
						m_node *tmp = p->find_min(p->right);
						tmp->left = p->left;
						p->left->top = tmp;
						toBalance = p->top;
					}
					else
					{
						m_node *max_left = p->find_max(p->left);
						if (!max_left->left && !max_left->right)
						{
							if (max_left == max_left->top->left)
								max_left->top->left = NULL;
							else
								max_left->top->right = NULL;
							max_left->top = NULL;
						}
						else if (max_left->left && !max_left->right)
						{
							if (max_left == max_left->top->left)
								max_left->top->left = max_left->left;
							else
								max_left->top->right = max_left->left;
							max_left->left->top = max_left->top;
						}
						else if (!max_left->left && max_left->right)
						{
							if (max_left == max_left->top->left)
								max_left->top->left = max_left->right;
							else
								max_left->top->right = max_left->right;
							max_left->right->top = max_left->top;
						}
						max_left->top = p->top;
						if (p->top->left == p)
							p->top->left = max_left;
						else
							p->top->right = max_left;
						max_left->left = p->left;
						if (p->left)
							p->left->top = max_left;
						max_left->right = p->right;
						if (p->right)
							p->right->top = max_left;
						toBalance = max_left;
					}
				}
				_node_alloc.destroy(p);
				_node_alloc.deallocate(p, 1);
				_size--;
				if (_size == 0)
				{
					_root = NULL;
					_begin->right = NULL;
					_begin->left = NULL;
					_end->right = NULL;
					_end->left = NULL;
					_begin->top = _end;
				}
				else if (_size >= 3)
					rebalance(toBalance);
			};

			size_type erase (const key_type &key)
			{
				iterator pos = find(key);
				if (pos == end())
					return (0);
				erase(pos);
				return (1);
			};

			void erase(iterator first, iterator last)
			{
				iterator tmp;

				if (first == last)
					return ;
				tmp = first;
				erase(++first, last);
				erase(tmp);
			};

			void swap(map &x)
			{
				m_node		*tmp_node;
				size_type	size_tmp;
				
				if (x == *this)
					return ;
				tmp_node = x._root;
				x._root = _root;
				_root = tmp_node;
				tmp_node = x._end;
				x._end = _end;
				_end = tmp_node;
				tmp_node = x._begin;
				x._begin = _begin;
				_begin = tmp_node;
				size_tmp = x._size;
				x._size = _size;
				_size = size_tmp;
			};

			void clear()
			{
				this->erase(this->begin(), this->end());
				// erase(begin(), end());
			};

			iterator find (const key_type& k)
			{
				m_node *node;

				node = _root;
				while (node && node != _end && node != _begin && (_compare(node->value.first, k) || _compare(k, node->value.first)))
				{
					if (_compare(node->value.first, k))
						node = node->right;
					else
						node = node->left;
				}
				if (node && node != _end && node != _begin && !_compare(node->value.first, k) && !_compare(k, node->value.first))
					return (iterator(node));
				else
					return (iterator(_end));
			};

			const_iterator find (const key_type& k) const
			{
				m_node *node;

				node = _root;
				while (node && node != _end && node != _begin && (_compare(node->value.first, k) || _compare(k, node->value.first)))
				{
					if (_compare(node->value.first, k))
						node = node->right;
					else
						node = node->left;
				}
				if (node && node != _end && node != _begin && !_compare(node->value.first, k) && !_compare(k, node->value.first))
					return (const_iterator(node));
				else
					return (const_iterator(_end));
			};


			size_type count (const key_type& k) const
			{
				if (find(k) == end())
					return (0);
				return (1);
			};

			iterator lower_bound (const key_type& k)
			{
				for (iterator iter = begin(); iter != end(); iter++)
				{
					if (!_compare(iter->first, k))
						return (iter);
				}
				return (end());
			};

			const_iterator lower_bound (const key_type& k) const
			{
				for (const_iterator iter = begin(); iter != end(); iter++)
				{
					if (!_compare(iter->first, k))
						return (iter);
				}
				return (end());
			};

			iterator upper_bound (const key_type& k)
			{
				for (iterator iter = begin(); iter != end(); iter++)
				{
					if (_compare(k, iter->first))
						return (iter);
				}
				return (end());
			};

			const_iterator upper_bound (const key_type& k) const
			{
				for (const_iterator iter = begin(); iter != end(); iter++)
				{
					if (_compare(k, iter->first))
						return (iter);
				}
				return (end());
			};

			pair<iterator, iterator> equal_range(const key_type &k)
			{
				return (make_pair(lower_bound(k), upper_bound(k)));
			};

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (make_pair(lower_bound(k), upper_bound(k)));
			};

			allocator_type get_allocator(void) const
			{
				return (Alloc());
			};

			private :

			m_node		*right_rotate(m_node *node)
			{
				// std::cout << "right rotate" <<std::endl;
				m_node *tmp = node->left;
				if (tmp != NULL)
				{
					if (tmp->right)
					{
						node->left = tmp->right;
						tmp->right->top = node;
					}
					else
						node->left = NULL;
					tmp->right = node;
					if (node->top)
					{
						if (node->top->left == node)
							node->top->left = tmp;
						else
							node->top->right = tmp;
					}
					else
						tmp->top = NULL;
					tmp->top = node->top;
					node->top = tmp;
					if (_root == node)
						_root = tmp;
				}
				else
					node->left = NULL;
				set_height(node);
				set_height(tmp);
				return (tmp);
			};

			m_node		*left_rotate(m_node *node)
			{
				// std::cout << "left rotate" <<std::endl;
				m_node *tmp = node->right;
				if (tmp != NULL)
				{
					if (tmp->left)
					{
						node->right = tmp->left;
						tmp->left->top = node;
					}
					else
						node->right = NULL;
					tmp->left = node;
					if (node->top)
					{
						if (node->top->left == node)
							node->top->left = tmp;
						else
							node->top->right = tmp;
					}
					else
						tmp->top = NULL;
					tmp->top = node->top;
					node->top = tmp;
					if (_root == node)
						_root = tmp;
				}
				else
					node->right = NULL;
				set_height(node);
				set_height(tmp);
				return (tmp);
			};

			void set_height(m_node *node)
			{
				int		size_right, size_left;

				if (node->left != NULL && node->left != _begin && node->left != _end)
					size_left = node->left->height;
				else
					size_left = -1;
				if (node->right != NULL && node->right != _begin && node->right != _end)
					size_right = node->right->height;
				else
					size_right = -1;
				node->height = std::max(size_left, size_right) + 1;
			}

			int			getBalanceFactor(m_node *node)
			{
				// std::cout << "balance factor" <<std::endl;
				return (retHeight(node->right) - retHeight(node->left));
			};

			int retHeight(m_node *node)
			{
				if (node != NULL && node != _begin && node != _end)
					return (node->height);
				return (-1);
			};

			void rebalance(m_node *node)
			{
				if (node == NULL)
					return ;
				// std::cout << "Rebalance" <<std::endl;
				while (node->top)
				{
					set_height(node);
					balance_tree(node);
					node = node->top;
				}
				set_height(node);
				balance_tree(node);
			}

			m_node		*balance_tree(m_node *node)
			{
				// std::cout << "balance tree" <<std::endl;
				m_node		*ret;
				int bf = getBalanceFactor(node);
				if (bf < -1)
				{
					if (getBalanceFactor(node->left) <= 0)
						ret = right_rotate(node);
					else
					{
						ret = left_rotate(node->left);
						ret = right_rotate(node);
					}	
				}
				if (bf > 1)
				{
					if (getBalanceFactor(node->right) >= 0)
						ret = left_rotate(node);
					else
					{
						ret = right_rotate(node->right);
						ret = left_rotate(node);
					}
				}
				return (ret);
			};

	};

	//Non members operators
	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		typename ft::map<Key, T>::const_iterator rit = rhs.begin();
		typename ft::map<Key, T>::const_iterator lit = lhs.begin();
		if (lhs.size() != rhs.size())
			return false;
		while (rit != rhs.end() && lit != lhs.end())
		{
			if (*rit != *lit)
				return false;
			rit++;
			lit++;
		}
		return true;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(rhs == lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator< (const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs > rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator> (const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key,T,Compare,Alloc> &lhs, ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return lhs.swap(rhs);
	}
}

#endif