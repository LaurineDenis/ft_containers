#include "common.hpp"
#include <vector>
#include <iostream>

#define TESTED_TYPE int

void print(std::vector<int> const &input)
{
	for (size_t i =0; i < input.size() ; i++)
	{
		std::cout << input.at(i)<< ' '<< std::endl;
	//	std::endl;

	}
}

int main(void)
{
	ft::vector<TESTED_TYPE> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	printSize(vct);

	ft::vector<TESTED_TYPE> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	for (unsigned long int i = 0; i < vct_c.size(); ++i)
		std::cout << "vct_c.at(): " << vct_c.at(i) << std::endl;
	try {
		std::cout << vct_c.at(10) << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception1!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception1: " << e.what() << std::endl;
	}
	printSize(vct_c);
	return 0;
}



// int		main(void)
// {
// 	ft::vector<TESTED_TYPE> vct(5);
// 	std::vector<TESTED_TYPE> vct_std(5);

// 	vct.print_vector();
// 	ft::vector<TESTED_TYPE>::iterator it = vct.begin(), ite = vct.end();
// 	std::vector<TESTED_TYPE>::iterator il = vct_std.begin(), ile = vct_std.end();

// 	std::cout << "len: " << (ite - it) << std::endl;
// 	for (; it != ite; ++it)
// 		*it = (ite - it);

// 	for (; il != ile; ++il)
// 		*il = (ile - il);
// 	vct.print_vector();
// 	print(vct_std);

// 	 it = vct.begin();
// 	 il = vct_std.begin();

// std::cout << "being_0= " << *it << std::endl;
// 	std::cout << "end_0= " << *ite << std::endl;

// 	std::cout << "being_std_0= " << *il << std::endl;
// 	std::cout << "end_std_0= " << *ile << std::endl;
	
// 	std::cout << "------------------------------"<< std::endl;

// 	ft::vector<TESTED_TYPE> vct_range(it, --(--ite));
// 	std::vector<TESTED_TYPE> vct_range_std(il, --(--ile));
	
// 	std::cout << "------------------------------"<< std::endl;

// 	std::cout << "being= " << *it << std::endl;
// 	std::cout << "end= " << *ite << std::endl;
// 	// --(--ite);
// 	// std::cout << "endekekkeke= " << *ite << std::endl;

// 	std::cout << "being_std= " << *il << std::endl;
// 	std::cout << "end_std=  " << *ile << std::endl;

	
// 	//  vct_range.print_vector();

// 	for (int i = 0; it != ite; ++it)
// 		*it = ++i * 5;

// for (int i = 0; il != ile; ++il)
// 		*il = ++i * 5;
	
// 	it = vct.begin();
// 	il = vct_std.begin();

// 	vct.print_vector();
// 	print(vct_std);
	 

// 	ft::vector<TESTED_TYPE> vct_copy(vct);
// 	std::vector<TESTED_TYPE> vct_copy_std(vct_std);

// 	for (int i = 0; it != ite; ++it)
// 		*it = ++i * 7;

// 	for (int i = 0; il != ile; ++il)
// 		*il = ++i * 7;

// 	vct_copy.print_vector();
// 	print(vct_copy_std);



// 	// vct_copy.push_back(42);
// 	// vct_copy.push_back(21);

// 	// std::cout << "\t-- PART ONE --" << std::endl;
// 	// printSize(vct);
// 	// printSize(vct_range);
// 	// printSize(vct_copy);

// 	// vct = vct_copy;
// 	// vct_copy = vct_range;
// 	// vct_range.clear();

// 	// std::cout << "\t-- PART TWO --" << std::endl;
// 	// printSize(vct);
// 	// printSize(vct_range);
// 	// printSize(vct_copy);
// 	return (0);
// }
