#ifndef UTILS_HPP
#define	UTILS_HPP

#include "iterator_traits.hpp"
#include <algorithm>
#include <iostream>

namespace ft {

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T> struct is_integral : public std::false_type {};
	template <> struct is_integral<bool> : public std::true_type {};
	template <> struct is_integral<char> : public std::true_type {};
	template <> struct is_integral<signed char> : public std::true_type {};
	template <> struct is_integral<unsigned char> : public std::true_type {};
	template <> struct is_integral<wchar_t> : public std::true_type {};
	template <> struct is_integral<char16_t> : public std::true_type {};
	template <> struct is_integral<char32_t> : public std::true_type {};
	template <> struct is_integral<short> : public std::true_type {};
	template <> struct is_integral<unsigned short> : public std::true_type {};
	template <> struct is_integral<int> : public std::true_type {};
	template <> struct is_integral<unsigned int> : public std::true_type {};
	template <> struct is_integral<long> : public std::true_type {};
	template <> struct is_integral<unsigned long> : public std::true_type {};
	template <> struct is_integral<long long> : public std::true_type {};
	template <> struct is_integral<unsigned long long> : public std::true_type {};
	template <> struct is_integral<__int128_t> : public std::true_type {};
	template <> struct is_integral<__uint128_t> : public std::true_type {};

	template <class Iter>
	typename ft::iterator_traits<Iter>::difference_type	distance(Iter first, Iter last) {
		typename ft::iterator_traits<Iter>::difference_type ret = 0;
		while (first != last) {
			ret++;
			first++;
		}
		return ret;
	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1 )
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}


#endif
