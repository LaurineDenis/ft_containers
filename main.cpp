#include "common.hpp"
#include <vector>
#include <iostream>

#define TESTED_TYPE std::string

void print(std::vector<std::string> const &input)
{
	for (size_t i =0; i < input.size() ; i++)
	{
		std::cout << input.at(i)<< ' '<< std::endl;

	}
}

void	checkErase_std(std::vector<TESTED_TYPE> const &vct,
					std::vector<TESTED_TYPE>::const_iterator const &it)
{
	
	static int i = 0;
	std::cout << "it_std = " << *it << " vct.begin_std= " << *vct.begin() << std::endl;

	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	print(vct);
}
void	checkErase(ft::vector<TESTED_TYPE> const &vct,
					ft::vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "it = " << *it << " vct.begin= " << *vct.begin() << std::endl;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
//	printSize(vct);
}

int		main(void)
{
	ft::vector<TESTED_TYPE> vct(10);

	std::vector<TESTED_TYPE> vct_std(10);
	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);

	for (unsigned long int i = 0; i < vct_std.size(); ++i)
	
		vct_std[i] = std::string((vct_std.size() - i), i + 65);

	printSize(vct);
	print(vct_std);

	//checkErase(vct, vct.erase(vct.begin() + 2));
	//checkErase_std(vct_std, vct_std.erase(vct_std.begin() + 2));
	


	//checkErase(vct, vct.erase(vct.begin()));
	//checkErase(vct, vct.erase(vct.end() - 1));



	checkErase_std(vct_std, vct_std.erase(vct_std.begin(), vct_std.begin() +3 ));
	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));

	return (0);
}
