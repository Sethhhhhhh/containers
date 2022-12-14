#ifndef __ITERATORS_HPP__
#define __ITERATORS_HPP__

#include <cstddef>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	> struct iterator {
		typedef Category    iterator_category;
		typedef T           value_type;
		typedef Distance    difference_type;
		typedef Pointer     pointer;
		typedef Reference   reference;
	};

	template <class Iterator>
	class iterator_traits {
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <class T>
	class iterator_traits<T*> {
		typedef std:ptrdiff_t		        difference_type;
		typedef T 							value_type;
		typedef T*							pointer;
		typedef T&			                reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator_traits<const T*> {
		typedef std:ptrdiff_t		        difference_type;
		typedef T 							value_type;
		typedef const T*					pointer;
		typedef const T&			        reference;
		typedef random_access_iterator_tag	iterator_category;
	};
}

#endif