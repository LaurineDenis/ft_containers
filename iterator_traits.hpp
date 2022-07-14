#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>

namespace ft {
    template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef	ptrdiff_t								difference_type;
		typedef	T										value_type;
		typedef	T*										pointer;
		typedef	T&										reference;
		typedef	std::random_access_iterator_tag			iterator_category;
	};
	
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef	ptrdiff_t										difference_type;
		typedef	T												value_type;
		typedef	const	T*										pointer;
		typedef	const	T&										reference;
		typedef	std::random_access_iterator_tag					iterator_category;
	};
}

// template <class Category, class T>
// struct iterator
// {
// 	typedef	T			value_type;
// 	typedef	ptrdiff_t	difference_type;
// 	typedef	T*		pointer;
// 	typedef	T&	reference;
// 	typedef	Category	iterator_category;
// };

// template< class Iterator >
// class iterator_traits {

// public:
// 	typedef typename Iterator::difference_type       difference_type;
// 	typedef typename Iterator::value_type            value_type;
// 	typedef typename Iterator::pointer               pointer;
// 	typedef typename Iterator::reference             reference;
// 	typedef typename Iterator::iterator_category     iterator_category;
// };

// template <class T>
// class iterator_traits<T*>
// {
// public:
// 	typedef std::ptrdiff_t							difference_type;
// 	typedef T										value_type;
// 	typedef T*										pointer;
// 	typedef T&										reference;
// 	typedef std::random_access_iterator_tag			iterator_category;
// };

// template <class T>
// class iterator_traits<const T*>
// {
// 	typedef std::ptrdiff_t							difference_type;
// 	typedef T										value_type;
// 	typedef const T*								pointer;
// 	typedef const T&								reference;
// 	typedef std::random_access_iterator_tag			iterator_category;
// };

#endif