/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:47:50 by vintran           #+#    #+#             */
/*   Updated: 2022/04/11 01:22:21 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP
# include "iterators.hpp"

namespace ft {

	template < typename Iterator >
	class reverseIterator: public iterator< typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference > {

//=================================VARIABLES====================================//

	protected:

		Iterator								current;
		typedef iterator_traits<Iterator>		traits_type;


//=================================TYPEDEF======================================//

	public:

		typedef Iterator									iterator_type;
		typedef typename traits_type::difference_type		difference_type;
		typedef typename traits_type::pointer				pointer;
		typedef typename traits_type::reference				reference;
		typedef typename traits_type::value_type			value_type;


//================================CONSTRUCTOR===================================//

		//default
		reverseIterator() : current() {}

		//initialization
		explicit reverseIterator(iterator_type x) : current(x) {}

		//copy
		reverseIterator(reverseIterator const & x) : current(x.current) {}

		//copy from InputIterator
		template<typename InputIterator>
		reverseIterator(reverseIterator<InputIterator> const & x) : current(x.base()) {}


//=================================MEMBER FUNCTIONS================================//

		iterator_type	base() const {

			return (current);
		}

		reference	operator*() const {

			Iterator tmp = current;

			return (*(--tmp));
		}

		reverseIterator		operator+(difference_type n) const {

			return (reverseIterator(current - n));
		}

		reverseIterator&	operator++() {

			--current;
			return (*this);
		}

		reverseIterator		operator++(int) {

			reverseIterator tmp = (*this);

			--current;
			return (tmp);
		}

		reverseIterator&	operator+=(difference_type n) {

			current -= n;
			return (*this);
		}

		reverseIterator		operator-(difference_type n) const {

			return reverseIterator(current + n);
		}

		reverseIterator&	operator--() {

			++current;
			return (*this);
		}

		reverseIterator		operator--(int) {

			reverseIterator tmp = (*this);

			++current;
			return (tmp);
		}

		reverseIterator&	operator-=(difference_type n) {

			current += n;
			return (*this);
		}

		pointer		operator->() const {

			return (&(operator*()));
		}

		reference	operator[](difference_type n) const {

			return (*(*this + n));
		}
};

//================================NON-MEMBER FUNCTIONS OVERLOADS===========================//

	template<class InputIterator1, class InputIterator2>
	bool	operator==(const reverseIterator<InputIterator1>& lhs, const reverseIterator<InputIterator2>& rhs) {

		return (lhs.base() == rhs.base());
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator!=(const reverseIterator<InputIterator1>& lhs, const reverseIterator<InputIterator2>& rhs) {

		return !(lhs == rhs);
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator<(const reverseIterator<InputIterator1>& lhs, const reverseIterator<InputIterator2>& rhs) {

		return (rhs.base() < lhs.base());
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator<=(const reverseIterator<InputIterator1>& lhs, const reverseIterator<InputIterator2>& rhs) {

		return (!(rhs < lhs));
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator>(const reverseIterator<InputIterator1>& lhs, const reverseIterator<InputIterator2>& rhs) {

		return (rhs < lhs);
	}

	template<class InputIterator1, class InputIterator2>
	bool	operator>=(const reverseIterator<InputIterator1>& lhs, const reverseIterator<InputIterator2>& rhs) {

		return (!(lhs < rhs));
	}

	template<class InputIterator1, class InputIterator2>
	typename reverseIterator<InputIterator1>::difference_type	operator-(const reverseIterator<InputIterator1>& lhs,
		const reverseIterator<InputIterator2>& rhs) {

		return (rhs.base() - lhs.base());
	}

	template<class Iterator>
	reverseIterator<Iterator>	operator+(typename reverseIterator<Iterator>::difference_type n,
		const reverseIterator<Iterator>& rev_it) {

		return (reverseIterator<Iterator>(rev_it.base() - n));
	}

};

#endif