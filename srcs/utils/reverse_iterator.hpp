#ifndef __REVERSE_ITERATOR_HPP__
#define __REVERSE_ITERATOR_HPP__

#include "iterators.hpp"

namespace ft {

	template <typename Iterator>
	class reverse_iterator {

	protected:
		Iterator								current;
		typedef iterator_traits<Iterator>		traits_type;

	public:

		typedef Iterator									iterator_type;
		typedef typename traits_type::difference_type		difference_type;
		typedef typename traits_type::pointer				pointer;
		typedef typename traits_type::reference				reference;
		typedef typename traits_type::value_type			value_type;

		/*
		**	Constructor
		*/

		reverse_iterator() : current() {}
		
		explicit reverse_iterator(iterator_type x) : current(x) {}
		
		reverse_iterator(reverse_iterator const & x) : current(x.current) {}
		
		reverse_iterator	&operator=(const reverse_iterator &x) {
			if (this != &x)
				current = x.current;
			return (*this);
		}

		template<typename InputIterator>
		reverse_iterator(reverse_iterator<InputIterator> const & x) : current(x.base()) {}

		iterator_type	base() const {
			return (current);
		}

		/*
		** Operator *
		*/

		reference	operator*() const {
			Iterator it = current;
			return *--it;
		}

		/*
		** Operator ->
		*/

		pointer	operator->() const { return &(operator*()); }

		/*
		** Operator []
		*/

		reference	operator[](difference_type n) const { return *(*this + n); }

		/*
		** Operator +
		*/

		reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(current - n)); }

		/*
		** Operator ++
		*/

		reverse_iterator&	operator++() {
			--current;
			return *this;
		}

		reverse_iterator		operator++(int) {
			reverse_iterator rit = *this;
			--current;
			return rit;
		}

		/*
		** Operator -
		*/

		reverse_iterator	operator-(difference_type n) { return reverse_iterator(current + n); }
		
		/*
		** Operator --
		*/

		reverse_iterator&	operator--() {
			++current;
			return *this;
		}

		reverse_iterator		operator--(int) {
			reverse_iterator rit = (*this);

			++current;
			return rit;
		}

		/*
		**	Operator +=
		*/

		reverse_iterator&	operator+=(difference_type n) {
			current -= n;
			return *this;
		}

		/*
		**	Operator -=
		*/

		reverse_iterator&	operator-=(difference_type n) {
			current += n;
			return *this;
		}
};


	template<class InputIterator1, class InputIterator2>
	bool	operator==(const reverse_iterator<InputIterator1>& lhs, const reverse_iterator<InputIterator2>& rhs) {

		return (lhs.base() == rhs.base());
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator!=(const reverse_iterator<InputIterator1>& lhs, const reverse_iterator<InputIterator2>& rhs) {

		return !(lhs == rhs);
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator<(const reverse_iterator<InputIterator1>& lhs, const reverse_iterator<InputIterator2>& rhs) {

		return (rhs.base() < lhs.base());
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator<=(const reverse_iterator<InputIterator1>& lhs, const reverse_iterator<InputIterator2>& rhs) {

		return (!(rhs < lhs));
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator>(const reverse_iterator<InputIterator1>& lhs, const reverse_iterator<InputIterator2>& rhs) {

		return (rhs < lhs);
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator>=(const reverse_iterator<InputIterator1>& lhs, const reverse_iterator<InputIterator2>& rhs) {

		return (!(lhs < rhs));
	}

	template<class InputIterator1, class InputIterator2>
	typename reverse_iterator<InputIterator1>::difference_type	operator-(const reverse_iterator<InputIterator1>& lhs,
		const reverse_iterator<InputIterator2>& rhs) {

		return (rhs.base() - lhs.base());
	}

	template<class Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it) {

		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

};

#endif