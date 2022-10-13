
#include <iostream>
#include <map>
#include <string>
#include "./containers/map.hpp"

int	main(void) {
	// std::map<int, char>	x;

	// x.insert(std::pair<int, char>(5, 'a'));

	// std::cout << (x[5]) << std::endl;

	ft::map<int, char>	y;

	y.insert(ft::pair<int, char>(0, 'a'));
	y.insert(ft::pair<int, char>(1, 'b'));

	ft::map<int, char>::iterator it = y.begin(), ite = y.end();
	for (; it != ite; ++it) {
		std::cout << "- " << it->first << it->second << std::endl;
	}

	return 0;
}