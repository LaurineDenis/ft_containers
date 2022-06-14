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

	template <typename T1, typename T2>
    pair<T1, T2>	make_pair(T1 x, T2 y) {

        return (pair<T1, T2>(x, y));
    }

	template <class T>
	struct less : std::binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const { return x < y; }
	};
}

#endif