#ifndef __EQUAL_HPP__
#define __EQUAL_HPP__

namespace ft {
	
	template <class InputIterator1, class InputIterator2>
  	bool equal(InputIterator1 lhs_begin, InputIterator1 lhs_end, InputIterator2 rhs_begin)
	{
		while (lhs_begin != lhs_end) {
			if (!(*lhs_begin == *rhs_begin))
				return false;
			++lhs_begin; ++rhs_begin;
		}

		return true;
	}
};

#endif