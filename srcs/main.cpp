
#include <iostream>
#include <map>
#include <string>
#include "./containers/map.hpp"
#include <list>

#define T1 int
#define T2 int
typedef ft::pair<const T1, T2> T3;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int	main(void) {
	std::list<ft::pair<const T1, T2> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::pair<const T1, T2>(lst_size - i, i));

	ft::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	// std::cout << ((++mp.begin())->second) << std::endl;

	mp.erase(++mp.begin());
	// std::cout << ((mp.begin())->second) << std::endl;

	// mp.erase(mp.begin());

	printSize(mp);



	return 0;
}