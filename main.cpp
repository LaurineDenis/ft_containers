//#include "common.hpp"

#include <list>
# include "vector.hpp"


void print(std::vector<int> const &input)
{
	std::cout << "---------STD--------" << std::endl;
	for (size_t i =0; i < input.size() ; i++)
	{
		std::cout << input.at(i)<< ' '<< std::endl;

	}
}

int		main(void)
{	
	const int size = 7;
	std::cout << "---------FT--------" << std::endl;
	ft::vector<int> vct(size);
	ft::vector<int> vct_two(4);
	
	std::vector<int> vct_std(size);
	std::vector<int> vct_two_std(4);


	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;

	
	for (unsigned long int i = 0; i < vct_std.size(); ++i)
		vct_std[i] = (vct_std.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two_std.size(); ++i)
		vct_two_std[i] = (vct_two_std.size() - i) * 5;
	
	vct.print_vector();
	print(vct_std);

	vct_two.print_vector();
	print(vct_two_std);

	std::cout << "---------ASSIGN-01-------" << std::endl;

	vct_two.assign(vct.begin(), vct.end());
	vct_two_std.assign(vct_std.begin(), vct_std.end());
	vct_two.print_vector();
	print(vct_two_std);

	ft::vector<int>::iterator it(vct.begin());
	ft::vector<int>::const_iterator ite(vct.end());

	
	return (0);
}
