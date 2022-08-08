#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include "utils/reverse_iterator.hpp"

namespace ft
{
    template <typename T, typename Alloc = std::allocator<T> >
    class vector
    {
        
        public:
            typedef T                                               value_type;
            typedef Alloc                                           allocator_type;
            typedef size_t                                          size_type;
            typedef ptdrdiff_t                                      difference_type;
            typedef T*                                              iterator;
            typedef const T*                                        const_iterator;

            typedef typename Alloc::pointer                         pointer;
            typedef typename Alloc::reference                       reference;
            typedef typename Alloc::const_reference                 const_reference;

            typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
    }
}