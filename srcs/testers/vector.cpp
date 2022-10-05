#include <iostream>
#include <vector>
#include <string>

#include "../containers/vector.hpp"

const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

using namespace ft;

void	check(std::string str, bool checked) {
	if (checked)
		std::cout << GREEN << str << " ✓" << RESET << std::endl;
	else
		std::cout << RED << str << " ✗" << RESET << std::endl;
}

void	iterators() {
	std::cout << "-------- ITERATORS --------\n" << std::endl;

	ft::vector<int>	vector(5);

	int	i = 0;
	ft::vector<int>::iterator it = vector.begin();
	for (; it != vector.end(); it++) {
		*it = ++i;
	}

	check("begin", *vector.begin() == 1);
	check("end", *vector.end() == 0);
}

void	capacity() {
	std::cout << "\n-------- CAPACITY --------\n" << std::endl;

	ft::vector<int>	vector(10);

	int	i = 0;
	ft::vector<int>::iterator it = vector.begin();
	for (; it != vector.end(); it++) {
		*it = ++i;
	}

	check("size", vector.size() == 10);
	check("max_size", vector.max_size() == 4611686018427387903);

	vector.resize(50);
	check("resize", vector.size() == 50);

	check("capacity", vector.capacity() == 50);

	check("empty", vector.empty() == false);

	vector.reserve(100);
	check("reserve", vector.capacity() == 100);
}

void	element_access() {
	std::cout << "\n-------- ELEMENT ACCESS --------\n" << std::endl;

	ft::vector<int>	vector(5);

	int	i = 0;
	ft::vector<int>::iterator it = vector.begin();
	for (; it != vector.end(); it++) {
		*it = ++i;
	}
	check("operator[]", vector[2] == 3);

	check("at", vector.at(2) == 3);

	check("front", vector.front() == 1);

	check("back", vector.back() == 5);
}

void	modifiers() {
	std::cout << "\n-------- MODIFIERS --------\n" << std::endl;

	ft::vector<int>	vector;

	vector.assign(5, 100);
	bool checked = true;
	ft::vector<int>::iterator it = vector.begin();
	for (; it != vector.end(); it++) {
		if (*it != 100)
			checked = false;
	}
	check("assign", checked);

	vector.pop_back();
	check("pop_back", *(vector.end() - 1) == 100);

	it = vector.insert(--it, 2, 300);
	checked = true;
	for (; it != vector.end(); it++) {
		if (*it != 300)
			checked = false;
	}
	check("insert", checked);

	vector.erase((vector.end() - 1));
	check("erase", *(vector.end() - 1) == 300);

	ft::vector<int>	x(10);
	int	i = 10;
	it = x.begin();
	for (; it != x.end(); it++) {
		*it = --i;
	}
	vector.swap(x);
	checked = true;
	it = vector.begin();
	i = 10;
	for (; it != vector.end(); it++) {
		if (*it != --i)
			checked = false;
	}
	check("swap", checked);

	vector.clear();
	check("clear", vector.empty());
}

int	main() {
	iterators();
	capacity();
	element_access();
	modifiers();

	return (0);
}