#ifndef ITERATOR_VECTOR_HPP
#define ITERATOR_VECTOR_HPP

#include "iterator_traits.hpp"



namespace ft
{
	template<typename Iterator>
	class iterator_vector
	{	
		public:

			typedef Iterator                                                    iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type         value_type;
			typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
			typedef typename iterator_traits<iterator_type>::pointer            pointer;
			typedef typename iterator_traits<iterator_type>::reference          reference;

        private:
			    iterator_type _ptr;

        public :


            // ----------------CONSTRUCTEURS----------------------------
			iterator_vector(){};
			iterator_vector(iterator_type x): _ptr(x){};
			template <class Iter>
			iterator_vector(iterator_vector<Iter> const &copy): _ptr(copy.base()) {};
			virtual ~iterator_vector() {};

			iterator_vector &operator=(iterator_vector const &copy)
			{
				_ptr = copy.base();
				return (*this);
			};

			
            //-------------FONCTION INCREMENT DECREMENT-----------
			iterator_vector &operator++()
			{
				++this->_ptr;
				return (*this);
			};

			iterator_vector operator++(int)
			{
				iterator_vector tmp(*this);
				++this->_ptr;
				return (tmp);
			};

			iterator_vector operator--(int)
			{
				iterator_vector tmp(*this);
				--this->_ptr;
				return (tmp);
			};

			iterator_vector &operator--()
			{
				--this->_ptr;
				return (*this);
			};

			// template <class T>
			// friend iterator_vector<T> operator+(const int & lhs, const iterator_vector<T>& rhs);


            //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
			iterator_vector	operator+(difference_type n) const
			{
				iterator_vector	tmp(*this);
				tmp += n;
				return (tmp);
			};

			iterator_vector	operator-(difference_type n) const
			{
				iterator_vector	tmp(*this);
				tmp -= n;
				return (tmp);
			};


            //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
			iterator_vector	operator+=(difference_type n)
			{
				_ptr += n;
				return (*this);
			};


			iterator_vector&	operator-=(difference_type n)
			{
                if (_ptr != 0)
				    _ptr -= n;
				return (*this);
			};


            //-------------REFERENCE & POINTEUR -----------
			reference	operator[](difference_type n) const
			{
				return (_ptr[n]);
			};

            reference operator*() const
			{
				return (*_ptr);
			};

			pointer operator->() const
			{
				return (_ptr);
			};

			iterator_type	base() const
			{
				return (_ptr);
			};
	};
            
            
     //-------------BOOLEANS NON MEMBER -----------

    template <class Iter1, class Iter2>
    bool	operator==(const iterator_vector<Iter1>& lhs, const iterator_vector<Iter2>& rhs)
    {
        return (lhs.base() == rhs.base());
    };

    template <class Iter1, class Iter2>
    bool	operator<(const iterator_vector<Iter1>& lhs, const iterator_vector<Iter2>& rhs)
    {
        return (lhs.base() < rhs.base());
    };

    template <class Iter1, class Iter2>
    bool	operator!=(const iterator_vector<Iter1>& lhs, const iterator_vector<Iter2>& rhs)
    {
        return (lhs.base() != rhs.base());
    };

    template <class Iter1, class Iter2>
    bool	operator>(const iterator_vector<Iter1>& lhs, const iterator_vector<Iter2>& rhs)
    {
        return (lhs.base() > rhs.base());
    };

    template <class Iter1, class Iter2>
    bool	operator>=(const iterator_vector<Iter1>& lhs, const iterator_vector<Iter2>& rhs)
    {
        return (lhs.base() >= rhs.base());
    };

    template <class Iter1, class Iter2>
    bool	operator<=(const iterator_vector<Iter1>& lhs, const iterator_vector<Iter2>& rhs)
    {
        return (lhs.base() <= rhs.base());
    };

    template <class T>
    iterator_vector<T> operator+(const int & lhs, const iterator_vector<T> & rhs) {
        iterator_vector<T> ret(rhs);
        ret += lhs;
        return (ret);
    };

    template <class Iter1, class Iter2>
    typename iterator_vector<Iter1>::difference_type operator-(const iterator_vector<Iter1>& x, const iterator_vector<Iter2>& y)
    {
        return (x.base() - y.base());
    };

}

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

			iterator_type _ptr;

		public:
            
            // ----------------CONSTRUCTEURS----------------------------
            reverse_iterator(){};
			reverse_iterator(iterator_type it): _ptr(it){};
			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it): _ptr(rev_it.base()){};
			virtual ~reverse_iterator(){};

			template <class Iter>
			reverse_iterator&	operator=(const reverse_iterator<Iter>& rev_it) 
            {
				_ptr = rev_it.base();
				return *this;
			};

           
            //-------------FONCTION INCREMENT DECREMENT-----------
			reverse_iterator& operator++()
			{
				--this->_ptr;
				return (*this);
			};

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--this->_ptr;
				return (tmp);
			};

            reverse_iterator& operator--()
			{
				++this->_ptr;
				return (*this);
			};

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++this->_ptr;
				return (tmp);
			};

            //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
            reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(this->_ptr - n));
			};

			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(this->_ptr + n));
			};

            //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
			
			reverse_iterator& operator+=(difference_type n)
			{
				this->_ptr = this->_ptr - n;
				return (*this);
			};

			reverse_iterator& operator-=(difference_type n)
			{
                // std::cout << "_pts = " << *_ptr+n << std::endl;
          
				this->_ptr +=  n;
				return (*this);

			};


            //-------------REFERENCE & POINTEUR -----------

			pointer operator->() const
			{
				return (&(operator*()));
			};

			reference	operator[](difference_type _n) const 
			{
				return *(*this + _n);
			};

            iterator_type base() const
			{
				return (this->_ptr);
			};

			reference operator*() const
			{
				iterator_type tmp = _ptr;
				--tmp;
				return (*tmp);
			};

			// template <class Iter>
			// friend reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it);
    };

    //-------------BOOLEANS NON MEMBER -----------
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() == rhs.base());
	};

    template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() != rhs.base());
	};

    template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() > rhs.base());
	};

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	};

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() < rhs.base());
	};

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	};

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (rhs.base() - lhs.base());
	};

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
	{
		return (it.base() - n);
	};
}

#endif