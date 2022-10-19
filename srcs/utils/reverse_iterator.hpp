#ifndef __REVERSE_ITERATOR_HPP__
#define __REVERSE_ITERATOR_HPP__

#include "iterators.hpp"

namespace ft {

template < typename Iterator >
	class reverse_iterator: public iterator< typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference >
	{
		protected:
			Iterator											current;
			typedef iterator_traits<Iterator>					traits_type;

		public:
			typedef Iterator									iterator_type;
			typedef typename traits_type::difference_type		difference_type;
			typedef typename traits_type::pointer				pointer;
			typedef typename traits_type::reference				reference;
			typedef typename traits_type::value_type			value_type;

			/* ------------------------------------------------------------------ */
			/* CONSTRUCTORS & DESTRUCTORS                                         */
			/* ------------------------------------------------------------------ */

			//default
			reverse_iterator() : current() {}

			//initialization : on construit un itérateur inverse à partir d'un itérateur normal
			explicit reverse_iterator(iterator_type it) : current(it) {}

			//copy : Construit un itérateur inverse à partir d'un autre itérateur inverse
			reverse_iterator(reverse_iterator const & rev_it) : current(rev_it.current) {}

			//copy form InputIterator : on construit un itérateur inverse à partir d'un autre itérateur inverse
			template<typename InputIterator>
			reverse_iterator(reverse_iterator<InputIterator> const & rev_it) : current(rev_it.base()) {}

			/* ------------------------------------------------------------------ */
			/* MEMBER FUNCTIONS                                                   */
			/* ------------------------------------------------------------------ */

			iterator_type		base() const { return (current); }

			pointer				operator->() const { return (&(operator*())); }

			reference			operator*() const
			{
				Iterator tmp = current;
				return (*(--tmp));
			}

			reverse_iterator		operator+(difference_type n) const
			{
				return reverse_iterator(current - n);
			}

			reverse_iterator		operator-(difference_type n) const
			{
				return reverse_iterator(current + n);
			}

			// pre-incrementation
			reverse_iterator&	operator++()
			{
				--current;
				return *this;
			}

			// post-incrementation
			reverse_iterator		operator++(int)
			{
				reverse_iterator tmp = (*this);
				--current;
				// ++(*this);
				return tmp;
			}

			reverse_iterator&	operator--()
			{
				++current;
				return *this;
			}

			reverse_iterator		operator--(int)
			{
				reverse_iterator tmp = (*this);
				++current;
				// --(*this);
				return tmp;
			}

			reverse_iterator&	operator+=(difference_type n)
			{
				current -= n;
				return *this;
			}

			reverse_iterator&	operator-=(difference_type n)
			{
				current += n;
				return *this;
			}

			reference			operator[](difference_type n) const
			{
				return *(*this + n);
			}
	};

	/* -------------------------------------------------------------------------- */
	/* NON-MEMBER FUNCTION OVERLOADS                                              */
	/* -------------------------------------------------------------------------- */

	template <class InputIterator1, class InputIterator2>
	bool	operator==(const reverse_iterator<InputIterator1>& lhs,
						const reverse_iterator<InputIterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator!=(const reverse_iterator<InputIterator1>& lhs,
						const reverse_iterator<InputIterator2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator<(const reverse_iterator<InputIterator1>& lhs,
						const reverse_iterator<InputIterator2>& rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator<=(const reverse_iterator<InputIterator1>& lhs,
						const reverse_iterator<InputIterator2>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator>(const reverse_iterator<InputIterator1>& lhs,
						const reverse_iterator<InputIterator2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator>=(const reverse_iterator<InputIterator1>& lhs,
						const reverse_iterator<InputIterator2>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class InputIterator1, class InputIterator2>
	typename reverse_iterator<InputIterator1>::difference_type	operator-(
			const reverse_iterator<InputIterator1>& lhs,
			const reverse_iterator<InputIterator2>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator>	operator+(
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it)
	{
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

};

#endif