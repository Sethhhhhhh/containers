#ifndef __REVERSE_ITERATOR__
#define __REVERSE_ITERATOR__

#include "iterators.hpp"

namespace ft
{
    template< class Iterator >
    class reverse_iterator {

        protected:
            Iterator                                current;
            typedef iterator_traits<Iterator>		traits_type;

        public:
            typedef Iterator									iterator_type;
            typedef typename traits_type::difference_type		difference_type;
            typedef typename traits_type::pointer				pointer;
            typedef typename traits_type::reference				reference;
            typedef typename traits_type::value_type			value_type;

            reverse_iterator() : current() {}
            reverse_iterator(const reverse_iterator &_x) : current(_x.current) {}
            template<typename input_iterator>
		    reverse_iterator(reverse_iterator<input_iterator> const &_x) : current(_x.base()) {}

            iterator_type base() const {
                return (current);
            }

            reference	operator*() const {
                Iterator tmp = current;

                return (*(--tmp));
            }

            reverse_iterator operator+(difference_type n) const {
                return (reverse_iterator(current - n));
            }

            reverse_iterator& operator++() {
                --current;
                return (*this);
            }

            reverse_iterator operator++(int) {
                reverse_iterator tmp = (*this);

                --current;
                return (tmp);
            }

            reverse_iterator& operator+=(difference_type n) {
                current -= n;
                return (*this);
            }

            reverse_iterator operator-(difference_type n) const {
                return reverse_iterator(current + n);
            }

            reverse_iterator& operator--() {
                ++current;
                return (*this);
            }

            reverse_iterator operator--(int) {
                reverse_iterator tmp = (*this);

                ++current;
                return (tmp);
            }

            reverse_iterator& operator-=(difference_type n) {
                current += n;
                return (*this);
            }

            pointer operator->() const {
                return (&(operator*()));
            }

            reference operator[](difference_type n) const {
                return (*(*this + n));
            }

            template<class lhs_itarator, class rhs_iterator>
            bool	operator==(const reverse_iterator<lhs_itarator>& lhs, const reverse_iterator<rhs_iterator>& rhs) {

                return (lhs.base() == rhs.base());
            }

            template<class lhs_itarator, class rhs_iterator>
            bool	operator!=(const reverse_iterator<lhs_itarator>& lhs, const reverse_iterator<rhs_iterator>& rhs) {

                return !(lhs == rhs);
            }

            template<class lhs_itarator, class rhs_iterator>
            bool	operator<(const reverse_iterator<lhs_itarator>& lhs, const reverse_iterator<rhs_iterator>& rhs) {

                return (rhs.base() < lhs.base());
            }

            template<class lhs_itarator, class rhs_iterator>
            bool	operator<=(const reverse_iterator<lhs_itarator>& lhs, const reverse_iterator<rhs_iterator>& rhs) {

                return (!(rhs < lhs));
            }

            template<class lhs_itarator, class rhs_iterator>
            bool	operator>(const reverse_iterator<lhs_itarator>& lhs, const reverse_iterator<rhs_iterator>& rhs) {

                return (rhs < lhs);
            }

            template<class lhs_itarator, class rhs_iterator>
            bool	operator>=(const reverse_iterator<lhs_itarator>& lhs, const reverse_iterator<rhs_iterator>& rhs) {

                return (!(lhs < rhs));
            }

            template<class lhs_itarator, class rhs_iterator>
            typename reverse_iterator<lhs_itarator>::difference_type	operator-(const reverse_iterator<lhs_itarator>& lhs,
                const reverse_iterator<rhs_iterator>& rhs) {

                return (rhs.base() - lhs.base());
            }

            template<class Iterator>
            reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n,
                const reverse_iterator<Iterator>& rev_it) {

                return (reverse_iterator<Iterator>(rev_it.base() - n));
            }

    };     
}

#endif
