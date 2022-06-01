#ifndef UTILS_TESTER_HPP
# define UTILS_TESTER_HPP

# include <vector>
# include <iostream>
# include <memory>
#include <list>
#include <stack>
// # include "../map/map.hpp"


# define COLOR_RESET "\033[0m"
# define COLOR_RED "\033[1;31m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_WHITE "\033[1;37m"
# define COLOR_YELLOW "\033[1;93m"

# define COLOR_RED_(str) COLOR_RED << str << COLOR_RESET
# define COLOR_BLUE_(str) COLOR_BLUE << str << COLOR_RESET
# define COLOR_GREEN_(str) COLOR_GREEN << str << COLOR_RESET
# define COLOR_WHITE_(str) COLOR_WHITE << str << COLOR_RESET
# define COLOR_YELLOW_(str) COLOR_YELLOW << str << COLOR_RESET

# define FT_TEST false
# define STD_TEST true


static void clearscreen() { std::cout << std::string( 100, '\n' ); }

static int to_int(char const *s)
{
	if ( s == NULL || *s == '\0' )
		throw std::invalid_argument("null or empty string argument");

	bool negate = (s[0] == '-');
	if ( *s == '+' || *s == '-' )
		++s;

	if ( *s == '\0')
		throw std::invalid_argument("sign character only.");

	int result = 0;
	while(*s)
	{
		if ( *s < '0' || *s > '9' )
			throw std::invalid_argument("invalid input string");
		result = result * 10 - (*s - '0');  //assume negative number
		++s;
	}
	return negate ? result : -result; //-result is positive!
}

void	print_header(std::string content)
{
	std::cout << COLOR_WHITE_(content) << std::endl;
}

template <typename T>
static void	print_vector(std::vector<T> lst)
{
	for (typename std::vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << std::endl;
}

void	menu(std::vector<void(*)()> lst_funs, std::vector<std::string> lst_messages, std::string title)
{
	std::string		input_line;

	// INPUT CHECK
	if (lst_funs.size() != lst_messages.size())
	{
		std::cerr << "ERROR : There isn't a message for each function test." << std::endl;
		return ;
	}

	// WELCOME MESSAGE
	std::cout << "Welcome in " << title << " test." << std::endl;

	// INTERACTIVE LOOP
	while (1)
	{
		std::cout << "Select a tester in this list to run and compare the code :" << std::endl;
		std::cout << "([exit|quit] to leave)" << std::endl << std::endl;
		print_vector(lst_messages);

		// GET
		std::cout << "> ";
		std::getline(std::cin, input_line);
		if (input_line == "exit" || input_line == "quit" || input_line == "e" || input_line == "q")
			return;
		clearscreen();

		try
		{
			// EVAL
			unsigned int input_num = to_int(input_line.c_str());
			if (input_num >= lst_funs.size())
				throw std::invalid_argument(" ");

			// EXEC
			(*(lst_funs[input_num]))();
		}
		catch (std::invalid_argument &e)
		{
			std::cerr << \
			"🔴 Input error, you can enter only a number existing" \
			<< std::endl << std::endl;
		}
		catch (std::exception &e) {	std::cerr << e.what() << std::endl; }

		// ENDING LOOP WAIT
		if (title != "TESTER")
		{
			std::cout << std::endl <<"Press enter to select another test" << std::endl;
			std::getline(std::cin, input_line);
		}
		else
			clearscreen();
	}
}

template <typename Tkey, typename Tvalue>
std::ostream	&operator<<(std::ostream &o, std::pair<Tkey, Tvalue> const &i)
{
	std::cout << \
	"key = " << i.first << ", value = " << i.second << " ";
	return (o);
};

// template <class Tkey, class Tvalue, class Compare>
// std::ostream	&operator<<(std::ostream &o, ft::map<Tkey, Tvalue, Compare> &i)
// {
// 	if (i.size() == 0)
// 	{
// 		o << "{}";
// 		return (o);
// 	}
// 	for (typename ft::map<Tkey, Tvalue, Compare>::const_iterator it = i.begin();
// 		 it != i.end();
// 		 it++)
// 		o << *it << std::endl;
// 	return (o);
// };

// template <typename Tkey, typename Tvalue>
// std::ostream	&operator<<(std::ostream &o, std::map<Tkey, Tvalue> &i)
// {
// 	if (i.size() == 0)
// 	{
// 		o << "{}";
// 		return (o);
// 	}
// 	for (typename std::map<Tkey, Tvalue>::const_iterator it = i.begin();
// 		 it != i.end();
// 		 it++)
// 		o << *it << std::endl;
// 	return (o);
// };

// template <typename Tkey, typename Tvalue, class Compare>
// std::ostream	&operator<<(std::ostream &o, std::map<Tkey, Tvalue, Compare> &i)
// {
// 	if (i.size() == 0)
// 	{
// 		o << "{}";
// 		return (o);
// 	}
// 	for (typename std::map<Tkey, Tvalue, Compare>::const_iterator it = i.begin();
// 		 it != i.end();
// 		 it++)
// 		o << *it << std::endl;
// 	return (o);
// };

void	print_header(std::string content);
void	menu(std::vector<void (*)()> lst_funs, std::vector<std::string> lst_messages, std::string title);

#endif