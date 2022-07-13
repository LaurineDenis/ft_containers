#include "common.hpp"
#include <vector>
#include <iostream>

#define TESTED_TYPE int

void	is_empty(ft::vector<TESTED_TYPE> const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

void	iss_empty(std::vector<TESTED_TYPE> const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

void print(std::vector<int> const &input)
{
	for (size_t i =0; i < input.size() ; i++)
	{
		std::cout << input.at(i)<< ' '<< std::endl;
	//	std::endl;

	}
}

int		main(void)
{
//	const int start_size = 7;
	ft::vector<TESTED_TYPE> vct(5,1);
	ft::vector<TESTED_TYPE> vct2(vct);

	std::vector<TESTED_TYPE> vct1(5,1);
	std::vector<TESTED_TYPE> vct3(vct1);


//	 print(vct1);
//	 printSize(vct);
	 vct.print_element();

	print(vct3);
	printSize(vct2);
	vct2.print_element();




	vct3.insert(vct3.begin() + 3, 4,5);
	print(vct3);
	vct2.insert(vct2.begin() + 3, 4,5);
	printSize(vct2);


	//  vct1.push_back(6);
	//  vct.push_back(6);
	//  vct1.push_back(7);
	//  vct.push_back(7);
	//  print(vct1);
	//  printSize(vct);



//	std::vector<TESTED_TYPE> vct3;
//	std::vector<TESTED_TYPE>::iterator il = vct1.begin();

	// for (int i = 2; i < start_size; ++i)
	// 	it[i] = (start_size - i) * 3;

	// for (int i = 2; i < start_size; ++i)
	// 	il[i] = (start_size - i) * 3;
	//  print(vct1);
	//  printSize(vct, true);

	//   vct.resize(10, 42);
	//  vct1.resize(10, 42);
	//  print(vct1);
	//   printSize(vct, true);

	//  vct.resize(18, 43);
	//  vct1.resize(18, 43);
	//  print(vct1);
	// printSize(vct, true);
	
	//  vct.resize(10);
	//  vct1.resize(10);
	//  print(vct1);
	// printSize(vct, true);

	//  vct.resize(23, 44);
	//   vct1.resize(23, 44);
	//  print(vct1);
	//  printSize(vct, true);

	//  vct.resize(5);
	//  vct1.resize(5);
	//  print(vct1);
	// printSize(vct, true);
	
	
	// vct.reserve(5);
	// vct1.reserve(5);
	//  print(vct1);
	//  printSize(vct, true);

	//  vct.resize(87);
	//  vct1.resize(87);
	// print(vct1);
	// printSize(vct, true);

	// vct.resize(5);
	//  vct1.resize(5);
	// print(vct1);
	// printSize(vct, true);

	//  is_empty(vct2);
	//   iss_empty(vct3);

	//  vct2 = vct;
	//  vct3 = vct1;
	//  print(vct3);
	//  printSize(vct2, true);

	// is_empty(vct2);
	// vct.reserve(vct.capacity() + 1);
	// printSize(vct, true);
	// printSize(vct2, true);

	// vct2.resize(0);
	// is_empty(vct2);
	// printSize(vct2, true);
	return (0);
}
