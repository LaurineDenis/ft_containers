//#include "common.hpp"

#include <list>
# include "vector.hpp"
# include <vector>



void print(std::vector<int> const &input)
{
	std::cout << "---------STD--------" << std::endl;
	for (size_t i =0; i < input.size() ; i++)
	{
		std::cout << input.at(i)<< ' '<< std::endl;

	}
}


void print_string(std::vector<std::string> const &input)
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
	
	std::cout << "---------vct 1-------" << std::endl;

	vct.print_vector();
	print(vct_std);

	std::cout << "---------vct 2-------" << std::endl;

	vct_two.print_vector();
	print(vct_two_std);

	std::cout << "---------ASSIGN-01-------" << std::endl;

	std::cout << "on met dans le vct 2 le vecteur 1" << std::endl;

	vct_two.assign(vct.begin(), vct.end());
	vct_two_std.assign(vct_std.begin(), vct_std.end());
	vct_two.print_vector();
	print(vct_two_std);

	std::cout << "---------ASSIGN-02-------" << std::endl;

	std::cout << "on remplace vct 1 par 2 42" << std::endl;

	vct.assign(2, 42);
	vct_std.assign(2, 42);
	vct.print_vector();
	print(vct_std);


	std::cout << "---------AT-01-------" << std::endl;
	
	std::cout << "on essaie d'avoir l'index 10 dans le vct 1" << std::endl;
	
	vct.print_vector();	
	try {
		std::cout << "vct.at(10) = " << vct.at(10) << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}

	std::cout << "---------AT-02-------" << std::endl;

	std::cout << "on essaie d'avoir l'index 5 dans le vct 2" << std::endl;
	
	vct_two.print_vector();	
	try {
		std::cout << "vct_two.at(5) = " << vct_two.at(5) << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}


	std::cout << "---------AT CONST-------" << std::endl;

	ft::vector<int> const vct_tree(vct_two);
	std::vector<int> const vct_tree_std(vct_two_std);

	vct_tree.print_vector_const();
	print(vct_tree_std);

	try {
		std::cout << "vct_two.at(5) = " << vct_tree.at(0) << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}


	std::cout << "---------BIDIREC-------" << std::endl;

	vct.print_vector_const();
	print(vct_std);


	vct_two.insert(vct_two.end(), vct.begin(), vct.end());
	vct_two_std.insert(vct_two_std.end(), vct_std.begin(), vct_std.end());

	vct_two.print_vector_const();
	print(vct_two_std);

	std::cout << "---------COPY CONSTRUC-------" << std::endl;

	ft::vector<int> vct_four(vct);
	std::vector<int> vct_four_std(vct_std);
	
	vct_four.push_back(1000);
	vct_four.push_back(200);

	vct_four_std.push_back(1000);
	vct_four_std.push_back(200);

	vct_four.print_vector_const();
	print(vct_four_std);


	vct = vct_two;
	vct_std = vct_two_std;

	vct.print_vector_const();
	print(vct_std);

	std::cout << "---------ERASE-on suprimme 1 element------" << std::endl;

	vct.erase(vct.begin() + 4);
	vct_std.erase(vct_std.begin() + 4);
	vct.print_vector_const();
	print(vct_std);


	std::cout << "---------ERASE-on suprimme une plage------" << std::endl;


	vct.erase(vct.begin() + 4, vct.end());
	vct_std.erase(vct_std.begin() + 4, vct_std.end());
	vct.print_vector_const();
	print(vct_std);

	std::cout << "---------INSERT 1 element------" << std::endl;
	
	vct_two.print_vector();
	print(vct_two_std);


	vct_two.insert(vct_two.end()-3, 10000);
	vct_two_std.insert(vct_two_std.end()-3, 10000);
	vct_two.print_vector();
	print(vct_two_std);


std::cout << "---------INSERT une plage------" << std::endl;


	vct.print_vector();
	print(vct_std);

	vct.insert(vct.end()-1, 5, 66);
	vct_std.insert(vct_std.end()-1, 5, 66);
	vct.print_vector();
	print(vct_std);
	
	vct.print_element();

	std::cout << "---------INSERT avec iterator------" << std::endl;
	
	vct.insert(vct.begin() + 2, vct.begin(), vct.end());
	vct_std.insert(vct_std.begin() + 2, vct_std.begin(), vct_std.end());
	vct.print_vector();
	print(vct_std);
	vct.print_element();

	std::cout << "---------ITE ARROW------" << std::endl;


	ft::vector<int>::iterator it(vct_two.begin());
	ft::vector<int>::const_iterator ite(vct_two.end());

	std::vector<int>::iterator it_std(vct_two_std.begin());
	std::vector<int>::const_iterator ite_std(vct_two_std.end());
	
	std::cout << "            it ++           " << std::endl;

	std::cout << "it = " << *(++it) << std::endl;
	std::cout << "it = " << *(it++) << std::endl;
	std::cout << "it = " << *it++ << std::endl;
	std::cout << "it = " << *++it << std::endl;

	std::cout << "it_std = " << *(++it_std) << std::endl;
	std::cout << "it_std = " << *(it_std++) << std::endl;
	std::cout << "it_std = " << *it_std++ << std::endl;
	std::cout << "it_std = " << *++it_std << std::endl;	

	std::cout << "            ite ++           " << std::endl;

	std::cout << "ite = " << *(++ite) << std::endl;
	std::cout << "ite = " << *(ite++) << std::endl;
	std::cout << "ite = " << *ite++ << std::endl;
	std::cout << "ite = " << *++ite << std::endl;
	
	std::cout << "ite_std = " << *(++ite_std) << std::endl;
	std::cout << "ite_std = " << *(ite_std++) << std::endl;
	std::cout << "ite_std = " << *ite_std++ << std::endl;
	std::cout << "ite_std = " << *++ite_std << std::endl;


	std::cout << "            it --          " << std::endl;

	std::cout << "it = " << *(--it) << std::endl;
	std::cout << "it = " << *(it--) << std::endl;
	std::cout << "it = " << *it-- << std::endl;
	std::cout << "it = " << *--it << std::endl;

	std::cout << "it_std = " << *(--it_std) << std::endl;
	std::cout << "it_std = " << *(it_std--) << std::endl;
	std::cout << "it_std = " << *it_std-- << std::endl;
	std::cout << "it_std = " << *--it_std << std::endl;

	std::cout << "            ite --          " << std::endl;

	std::cout << "ite = " << *(--ite) << std::endl;
	std::cout << "ite = " << *(ite--) << std::endl;
	std::cout << "ite = " << *--ite << std::endl;
	std::cout << "ite = " << *ite-- << std::endl;

	std::cout << " ite_std = " << *(--ite_std) << std::endl;
	std::cout << " ite_std = " << *(ite_std--) << std::endl;
	std::cout << " ite_std = " << *--ite_std << std::endl;
	std::cout << " ite_std = " << *ite_std-- << std::endl;
 

	std::cout << "---------ITE------" << std::endl;


	std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
	std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	std::cout << "           std       " << std::endl;


	std::cout << "const_ite_std +=: " << *(ite_std += 2) << std::endl;
	std::cout << "const_ite_std -=: " << *(ite_std -= 2) << std::endl;

	std::cout << "(it_std == const_it_std): " << (ite_std == it_std) << std::endl;
	std::cout << "(const_ite_std - it_std): " << (ite_std - it_std) << std::endl;
	std::cout << "(ite_std + 3 == it_std): " << (ite_std + 3 == it_std) << std::endl;

	std::cout << "---------POP------" << std::endl;


	ft::vector<std::string> src(2, "test");
	ft::vector<std::string> src_two(4);
	
	std::vector<std::string> src_std(2, "test");
	std::vector<std::string> src_two_std(4);

	src.push_back("c'est long les tests");
	src.push_back("j'espère que le projet sera validé");

	src_std.push_back("c'est long les tests");
	src_std.push_back("j'espère que le projet sera validé");
	
	src.print_vector();
	print_string(src_std);

	src.pop_back();
	src_std.pop_back();

	std::cout << "					" << std::endl;
	
	src.print_vector();
	print_string(src_std);



	std::cout << "---------RELATIONAL OPE------" << std::endl;

	std::cout << "			vct4		" << std::endl;

	vct_four.print_vector();
	print(vct_four_std);

	std::cout << "			vct2 		" << std::endl;

	vct_two.print_vector();
	print(vct_two_std);


	std::cout << "			operation 		" << std::endl;

	std::cout << "eq: " << (vct_four == vct_two) << " | ne: " << (vct_four != vct_two) << std::endl;
	std::cout << "lt: " << (vct_four <  vct_two) << " | le: " << (vct_four <= vct_two) << std::endl;
	std::cout << "gt: " << (vct_four >  vct_two) << " | ge: " << (vct_four >= vct_two) << std::endl;


	std::cout << "			std		" << std::endl;

	std::cout << "eq: " << (vct_four_std == vct_two_std) << " | ne: " << (vct_four_std != vct_two_std) << std::endl;
	std::cout << "lt: " << (vct_four_std <  vct_two_std) << " | le: " << (vct_four_std <= vct_two_std) << std::endl;
	std::cout << "gt: " << (vct_four_std >  vct_two_std) << " | ge: " << (vct_four_std >= vct_two_std) << std::endl;




	std::cout << "---------RITE ARROW------" << std::endl;

	ft::vector<int>::reverse_iterator irr(vct_two.rbegin());
	ft::vector<int>::const_reverse_iterator irre(vct_two.rend());

	std::vector<int>::reverse_iterator irr_std(vct_two_std.rbegin());
	std::vector<int>::const_reverse_iterator irre_std(vct_two_std.rend());
	
	std::cout << "            irr++           " << std::endl;

	std::cout << "irr = " << *(++irr) << std::endl;
	std::cout << "irr = " << *(irr++) << std::endl;
	std::cout << "irr = " << *irr++ << std::endl;
	std::cout << "irr = " << *++irr << std::endl;

	std::cout << "irr_std = " << *(++irr_std) << std::endl;
	std::cout << "irr_std = " << *(irr_std++) << std::endl;
	std::cout << "irr_std = " << *irr_std++ << std::endl;
	std::cout << "irr_std = " << *++irr_std << std::endl;	

	std::cout << "            ite ++           " << std::endl;

	std::cout << "irre = " << *(++irre) << std::endl;
	std::cout << "irre = " << *(irre++) << std::endl;
	std::cout << "irre = " << *irre++ << std::endl;
	std::cout << "irre = " << *++irre << std::endl;
	
	std::cout << "irre_std = " << *(++irre_std) << std::endl;
	std::cout << "irre_std = " << *(irre_std++) << std::endl;
	std::cout << "irre_std = " << *irre_std++ << std::endl;
	std::cout << "irre_std = " << *++irre_std << std::endl;


	std::cout << "            it --          " << std::endl;

	std::cout << "irr = " << *(--irr) << std::endl;
	std::cout << "irr = " << *(irr--) << std::endl;
	std::cout << "irr = " << *irr-- << std::endl;
	std::cout << "irr = " << *--irr << std::endl;

	std::cout << "irr_std = " << *(--irr_std) << std::endl;
	std::cout << "irr_std = " << *(irr_std--) << std::endl;
	std::cout << "irr_std = " << *irr_std-- << std::endl;
	std::cout << "irr_std = " << *--irr_std << std::endl;

	std::cout << "            irre --          " << std::endl;

	std::cout << "irre = " << *(--irre) << std::endl;
	std::cout << "irre = " << *(irre--) << std::endl;
	std::cout << "irre = " << *--irre << std::endl;
	std::cout << "irre = " << *irre-- << std::endl;

	std::cout << " irre_std = " << *(--irre_std) << std::endl;
	std::cout << " irre_std = " << *(irre_std--) << std::endl;
	std::cout << " irre_std = " << *--irre_std << std::endl;
	std::cout << " irre_std = " << *irre_std-- << std::endl;

	std::cout << "---------RITE-----" << std::endl;

	std::cout << "const_irre +=: " << *(irre += 2) << std::endl;
	std::cout << "const_irre -=: " << *(irre -= 2) << std::endl;

	std::cout << "(irr == const_irr): " << (irre == irr) << std::endl;
	std::cout << "(const_irre - irr): " << (irre - irr) << std::endl;
	std::cout << "(irre + 3 == irr): " << (irre + 3 == irr) << std::endl;

	std::cout << "           std       " << std::endl;


	std::cout << "const_irre_std +=: " << *(irre_std += 2) << std::endl;
	std::cout << "const_irre_std -=: " << *(irre_std -= 2) << std::endl;

	std::cout << "(irr_std == const_irr_std): " << (irre_std == irr_std) << std::endl;
	std::cout << "(const_irre_std - irr_std): " << (irre_std - irr_std) << std::endl;
	std::cout << "(irre_std + 3 == irr_std): " << (irre_std + 3 == irr_std) << std::endl;

	std::cout << "---------SIZE-----" << std::endl;

	vct_two.resize(18, 43);
	vct_two_std.resize(18, 43);
	vct_two.print_vector();
	print(vct_two_std);
	vct_two.print_element();
	std::cout << "size std = " << vct_two_std.size() << std::endl;

	vct_two.resize(10);
	vct_two_std.resize(10);
	vct_two.print_vector();
	print(vct_two_std);
	vct_two.print_element();
	std::cout << "size std = " << vct_two_std.size() << std::endl;

	vct_two.resize(3);
	vct_two_std.resize(3);
	vct_two.print_vector();
	print(vct_two_std);
	vct_two.print_element();
	std::cout << "size std = " << vct_two_std.size() << std::endl;

	std::cout << "---------SWAP-----" << std::endl;

	std::cout << "avant swap " << std::endl;

	vct_two.print_vector();
	print(vct_two_std);

	vct_four.print_vector();
	print(vct_four_std);

	vct_two.swap(vct_four);
	vct_two_std.swap(vct_four_std);

	std::cout << "apres swap " << std::endl;

	vct_two.print_vector();
	print(vct_two_std);

	vct_four.print_vector();
	print(vct_four_std);

	return (0);
}
