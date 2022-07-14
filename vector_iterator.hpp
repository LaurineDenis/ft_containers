#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template<typename Iterator>
	class VectorIterator
	{	
		public:

			typedef Iterator                                                    iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type         value_type;
			typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
			typedef typename iterator_traits<iterator_type>::pointer            pointer;
			typedef typename iterator_traits<iterator_type>::reference          reference;
		
		private:

			iterator_type _p;
		
		public:

			VectorIterator(): _p(NULL) {};
			VectorIterator(iterator_type x): _p(x) {};
			template <class Iter>
			VectorIterator(VectorIterator<Iter> const &other): _p(other.base()) {};
			virtual ~VectorIterator() {};

			VectorIterator &operator=(VectorIterator const &other)
			{
				this->_p = other.base();
				return (*this);
			}

			reference operator*() const
			{
				return (*_p);
			}

			pointer operator->() const
			{
				return (_p);
			}

			VectorIterator &operator++()
			{
				++this->_p;
				return (*this);
			}

			VectorIterator operator++(int)
			{
				VectorIterator tmp(*this);
				++this->_p;
				return (tmp);
			}

			VectorIterator operator--(int)
			{
				VectorIterator tmp(*this);
				--this->_p;
				return (tmp);
			}

			VectorIterator &operator--()
			{
				--this->_p;
				return (*this);
			}

			template <class T>
			friend VectorIterator<T> operator+(const int & lhs, const VectorIterator<T>& rhs);

			VectorIterator	operator+(difference_type n) const
			{
				VectorIterator	tmp(*this);
				tmp += n;
				return (tmp);
			}

			VectorIterator	operator+=(difference_type n)
			{
				_p += n;
				return (*this);
			}

			VectorIterator	operator-(difference_type n) const
			{
				VectorIterator	tmp(*this);
				tmp -= n;
				return (tmp);
			}

			VectorIterator&	operator-=(difference_type n)
			{
				_p -= n;
				return (*this);
			}

			reference	operator[](difference_type n) const
			{
				return (_p[n]);
			}

			iterator_type	base() const
			{
				return (_p);
			}

	};
			template <class Iter1, class Iter2>
			bool	operator==(const VectorIterator<Iter1>& x, const VectorIterator<Iter2>& y)
			{
				return (x.base() == y.base());
			}

			template <class Iter1, class Iter2>
			bool	operator<(const VectorIterator<Iter1>& x, const VectorIterator<Iter2>& y)
			{
				return (x.base() < y.base());
			}

			template <class Iter1, class Iter2>
			bool	operator!=(const VectorIterator<Iter1>& x, const VectorIterator<Iter2>& y)
			{
				return (x.base() != y.base());
			}

			template <class Iter1, class Iter2>
			bool	operator>(const VectorIterator<Iter1>& x, const VectorIterator<Iter2>& y)
			{
				return (y.base() < x.base());
			}

			template <class Iter1, class Iter2>
			bool	operator>=(const VectorIterator<Iter1>& x, const VectorIterator<Iter2>& y)
			{
				return (!(x.base() < y.base()));
			}

			template <class Iter1, class Iter2>
			bool	operator<=(const VectorIterator<Iter1>& x, const VectorIterator<Iter2>& y)
			{
				return (!(y.base() < x.base()));
			}

			template <class T>
			VectorIterator<T> operator+(const int & lhs, const VectorIterator<T> & rhs) {
				VectorIterator<T> ret(rhs);
				ret += lhs;
				return (ret);
			}

			template <class Iter1, class Iter2>
			typename VectorIterator<Iter1>::difference_type operator-(const VectorIterator<Iter1>& x, const VectorIterator<Iter2>& y)
			{
				return (x.base() - y.base());
			}

}

#endif
