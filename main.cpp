#include "common.hpp"
#include <vector>
#include <iostream>
#include <list>



#define TESTED_TYPE int

void print(std::vector<int> const &input)
{
	for (size_t i =0; i < input.size() ; i++)
	{
		std::cout << input.at(i)<< ' '<< std::endl;

	}
}

template <class T, class Alloc>
void	cmp(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
//	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		main(void)
{
	ft::vector<TESTED_TYPE> vct(4);
	ft::vector<TESTED_TYPE> vct2(4);

	//cmp(vct, vct);  // 0
//	cmp(vct, vct2); // 1

	vct2.resize(10);
	//cmp(vct, vct2); // 2
	// cmp(vct2, vct); // 3

	 vct[2] = 42;
	printSize(vct);

	 cmp(vct, vct2); // 4
	// cmp(vct2, vct); // 5

	// swap(vct, vct2);

	// cmp(vct, vct2); // 6
	// cmp(vct2, vct); // 7

	return (0);
}