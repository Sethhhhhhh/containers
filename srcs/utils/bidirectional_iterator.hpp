#ifndef __BIDIRECTIONAL_ITERATOR_HPP__
#define __BIDIRECTIONAL_ITERATOR_HPP__

#include <cstddef>

namespace ft {

	template <
		typename Category,
		typename T,
		typename Distance = std::ptrdiff_t,
		typename Pointer = T*,
		typename Reference = T&
	>
	class bidirectional_iterator {

		public:
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;

			bidirectional_iterator();

			bidirectional_iterator(bidirectional_iterator const &x);

	};
};

#endif