
#include <iostream>
#include <map>
#include <string>
#include "./containers/map.hpp"

int	main(void) {
	// std::map<int, char>	x;

	// x.insert(std::pair<int, char>(5, 'a'));

	// std::cout << (x[5]) << std::endl;

	std::list<T3> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(lst_size - i, i));

	std::cout << "ok" << std::endl;
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());

	return 0;
}