#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	template<bool, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <typename Tkey, typename Tvalue>
	class pair
	{
		public:

			pair(void) {};

			template<class U, class V>
			pair (const pair<U,V>& pr)
			{
				this->first = pr.first;
				this->second = pr.second;
			};

			pair (const Tkey& a, const Tvalue& b)
			: first(a), second(b)
			{};

			~pair()
			{};

			pair	&operator=(pair const &src)
			{
				this->first = src.first;
				this->second = src.second;

				return (*this);
			};

			Tkey	first;
			Tvalue	second;
	};

	// template <class T>
	// struct less : std::binary_function<T, T, bool>
	// {
	// 	bool operator()(const T &x, const T &y) const { return x < y; }
	// };

	template <typename T1, typename T2>
    pair<T1, T2>	make_pair(T1 x, T2 y) 
	{
        return (pair<T1, T2>(x, y));
    }

	template<class T1, class T2>
	bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return (lhs.first == rhs.first);
	}

	template<class T1, class T2>
	bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(lhs == rhs);
	}

	template<class T1, class T2>
	bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return (lhs.first != rhs.first ? lhs.first < rhs.first : lhs.second < rhs.second);
	}

	template<class T1, class T2>
	bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return (rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(lhs < rhs);
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
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
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