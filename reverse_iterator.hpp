#ifndef MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

# include <memory>
// # include "RBT.hpp"
#include "iterator_traits.hpp"

namespace ft
{
template <class Iterator>
class reverse_iterator
    {
		public:

			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

		private:

			iterator_type _p;

		public:

			reverse_iterator(): _p()
			{

			}

			reverse_iterator(iterator_type it): _p(it)
			{

			}

			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it): _p(rev_it.base())
			{

			}

			virtual ~reverse_iterator()
			{

			}

			template <class Iter>
			reverse_iterator&	operator=(const reverse_iterator<Iter>& rev_it) {
				_p = rev_it.base();
				return *this;
			}

            iterator_type base() const
			{
				return (this->_p);
			}

			reference operator*() const
			{
				iterator_type tmp = _p;
				--tmp;
				return (*tmp);
			}

			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(this->_p - n));
			}

			reverse_iterator& operator++()
			{
				--this->_p;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--this->_p;
				return (tmp);
			}

			reverse_iterator& operator+=(difference_type n)
			{
				this->_p = this->_p - n;
				return (*this);
			}

			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(this->_p + n));
			}

			reverse_iterator& operator--()
			{
				++this->_p;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++this->_p;
				return (tmp);
			}

			reverse_iterator& operator-=(difference_type n)
			{
				this->_p = this->_p + n;
				return (*this);
			}

			pointer operator->() const
			{
				return (&(operator*()));
			}

			reference	operator[](difference_type _n) const 
			{
				return *(*this + _n);
			}

			template <class Iter>
			friend reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it);
    };

	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

    template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

    template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
	{
		return (it.base() - n);
	}
}

#endif
