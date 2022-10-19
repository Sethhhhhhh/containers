#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <memory>
#include <stdexcept>
#include "../utils/reverse_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/equal.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace ft
{
    template <typename T, typename Alloc = std::allocator<T> >
    class vector
    {
        public:

			/*
			** Typedef
			*/

            typedef T                                               value_type;
            typedef Alloc                                           allocator_type;
            typedef size_t                                          size_type;
            typedef ptrdiff_t                                      	difference_type;
            typedef T*                                              iterator;
            typedef const T*                                        const_iterator;

            typedef typename Alloc::pointer                         pointer;
            typedef typename Alloc::reference                       reference;
            typedef typename Alloc::const_reference                 const_reference;

            typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			/*
			** Constructor
			*/

			explicit	vector(const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_size = 0;
				_capacity = 0;
				_start = NULL;
			}

			explicit	vector(
				size_type n,
				const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()
			) {
				_alloc = alloc;
				_start = NULL;

				_check_range(n);
				
				if (n) {
					_start = _alloc.allocate(n);
					_capacity = n;
				}
				else
					_capacity = 0;
				_size = n;

				iterator	it = _start;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(it++, val);
			}

			template <typename InputIterator>
			vector(
				InputIterator first,
				InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL
			) {
					difference_type dist = std::distance(first, last);
					_alloc = alloc;
					_size = static_cast<size_type>(dist);
					_capacity = static_cast<size_type>(dist);
					
					if (dist) {    
						_check_range(_capacity);
						_start = _alloc.allocate(_capacity);
						std::uninitialized_copy(first, last, _start);
					}
			}

			vector(const vector& src) {
				_start = NULL;
				_size = src._size;
				_capacity = src._capacity;

				if (src._capacity)
					_start = _alloc.allocate(_capacity);
				if (src._capacity)
					std::uninitialized_copy(src._start, src._start + src._size, _start);
			}

			vector& operator=(const vector& x) {
				if (*this == x)
					return *this;

				_dealloc();
				if (x.empty())
					return *this;

				_size = x.size();
				_capacity = x.capacity();

				if (_capacity > _alloc.max_size())
					throw std::out_of_range("vector::_check_range");

				_start = _alloc.allocate(_capacity);

				std::uninitialized_copy(x.begin(), x.end(), _start);
				return *this;
			}

			/*
			** Destructor
			*/

			virtual ~vector() {
				clear();
				if (_capacity)
					_alloc.deallocate(_start, _capacity);
			}

			/*
			** Iterators
			*/

			iterator				begin() {
				return _start;
			}

			const_iterator			begin() const {
				return _start;
			}

			iterator				end() {
				return _start + _size;
			}

			const_iterator			end() const {
				return _start + _size;
			}
		
			reverse_iterator		rbegin() {
				return reverse_iterator(end());
			}

			const_reverse_iterator	rbegin() const {
				return const_reverse_iterator(end());
			}

			reverse_iterator		rend() {
				return reverse_iterator(begin());
			}

			const_reverse_iterator	rend() const {
				return const_reverse_iterator(begin());
			}

			/*
			** Capacity
			*/

			size_type	size() const {
				return _size;
			}

			size_type	max_size() const {
				return _alloc.max_size();
			}

			void	resize(
				size_type n,
				value_type val = value_type()
			) {
				_check_range(n);
				
				if (n == _size)
					return;
				
				if (n == 0) {
					clear();
					return;
				}
				
				if (n < _size) {
					iterator it = end();
					size_type diff = _size - n;

					while (diff--) {
						_alloc.destroy(--it);
						_size--;
					}
					return ;
				}
				
				if (n > _size)
					_realloc(n, val);
			}

			size_type	capacity() const {
				return _capacity;
			}

			bool	empty() const {
				return _size == 0;
			}

			void	reserve(size_type n) {
				if (_capacity > n)
					return ;
				if (n > max_size())
					throw std::out_of_range("vector::reserve");
				else
					_realloc(n);
			}

			/*
			** Element access
			*/

			reference			operator[](size_type n) {
				return _start[n];
			}

			const_reference		operator[](size_type n) const {
				return _start[n];
			}

			reference			at(size_type n) {
				if (n > _size)
					throw std::out_of_range("vector::_check_range");

				return _start[n];
			}

			const_reference		at(size_type n) const {
				if (n > _size)
					throw std::out_of_range("vector::_check_range");

				return _start[n];
			}

			reference			front() {
				return *begin();
			}

			const_reference		front() const {
				return *begin();
			}

			reference			back() {
				return *(end() - 1);
			}

			const_reference		back() const {
				return *(end() - 1);
			}

			/*
			** Modifiers
			*/

			template <class InputIterator>
  			void assign(
				InputIterator first,
				InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL
			) {
				size_type dist = std::distance(first, last);

				_dealloc();
				if (dist) {
					if (dist > _alloc.max_size())
						throw std::out_of_range("vector::_check_range");
					_start = _alloc.allocate(dist);
					_capacity = dist;
				}
				
				for (iterator i = begin(); i < begin() + dist; i++)
					_alloc.construct(i, *first++);
				
				_size = dist;
			}

			void assign(
				size_type n,
				const value_type& val
			) {
				_dealloc();

				if (n)
					reserve(n);

				for (iterator i = begin(); i < begin() + n; i++)
					_alloc.construct(i, val);

				_size = n;
			}

			void	push_back(const value_type& val) {
				if (!_capacity) {
					_start = _alloc.allocate(1);
					_alloc.construct(_start, val);
					_capacity = 1;
					_size++;

					return;
				}
				if (_size + 1 <= this->_capacity) {
					_alloc.construct(_start + _size, val);
					_size++;
					return;
				}

				size_type	new_size;
				size_type	prev_size = _size;
				_check_range(_size + 1);
				if (_size * 2 < _alloc.max_size())
					new_size = _size * 2;
				else
					new_size = _size + 1;
				
				iterator	it = _alloc.allocate(new_size);
				std::uninitialized_copy(_start, _start + _size, it);
				_alloc.construct(it + prev_size, val);    
				_dealloc();
				_capacity = new_size;
				_start = it;
				_size = prev_size + 1;
			}

			void	pop_back() {
				if (!_size)
					return;

				_alloc.destroy(end() - 1);
				_size--;
			}

			iterator insert(
				iterator position,
				const value_type& val
			) {
				difference_type	new_size = std::distance(begin(), position);

				insert(position, 1, val);
				return (begin() + new_size);
			}

			void insert(
				iterator position,
				size_type n,
				const value_type& val
			) {
				difference_type	beginToPos = std::distance(begin(), position);
				difference_type prev_size = _size;
				
				resize(_size + n);

				iterator old_end = begin() + prev_size;
				position = begin() + beginToPos;
				iterator new_end = _start + _size;

				while (old_end != position) {
					new_end--;
					old_end--;
					*new_end = *old_end;
				}

				while (n) {
					*position = val;
					n--;
					position++;
				}
			}
			
			template <class InputIterator>
    		void insert(
				iterator position,
				InputIterator first,
				InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL
			) {
				difference_type	beginToPos = std::distance(begin(), position);
				difference_type	prev_size = _size;
				difference_type	n = std::distance(first, last);

				resize(_size + n);

				iterator old_end = begin() + prev_size;
				position = begin() + beginToPos;
				iterator new_end = end();
				
				while (old_end != position) {
					new_end--;
					old_end--;
					*new_end = *old_end;
				}
				
				while (first != last) {
					*position = *first;
					position++;
					first++;
				}
			}

			iterator erase(iterator position) {
				if (position == end())
					return position;
				return (erase(position, position + 1));
			}

			iterator erase(
				iterator first,
				iterator last
			) {
				if (first == last)
					return (first);
				
				if (last == end()) {
					for (iterator i = first; i != last; i++) {
						_alloc.destroy(i);
						_size--;
					}
					return (first);
				}
				
				iterator it = first;
				difference_type size = std::distance(first, last);
				
				while (it != last) {
					_alloc.destroy(it);
					it++;
				}
				
				it = first;
				while (it + size != end()) {
					_alloc.construct(it, *(it + size));
					_alloc.destroy(it + size);
					it++;
				}
				
				_size -= static_cast<size_type>(size);
				
				return (first);
			}

			void swap(vector& x) {
				std::swap(_alloc, x._alloc);
				std::swap(_start, x._start);
				std::swap(_size, x._size);
				std::swap(_capacity, x._capacity);
			}

			void clear() {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				_size = 0;
			}

			protected:
				allocator_type	_alloc;
				iterator		_start;
				size_type		_size;
				size_type		_capacity;

			private:
				void	_dealloc() {
					if (_capacity) {
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(_start + i);
						_alloc.deallocate(_start, _capacity);
					}

					_capacity = 0;
					_size = 0;
				}

				void	_realloc(size_type n) {
					size_type	prevSize = _size;
					iterator	it = _alloc.allocate(n);
					std::uninitialized_copy(_start, _start + _size, it);
					_dealloc();
					
					_size = prevSize;
					_start = it;
					_capacity = n;
				}

				void	_realloc(size_type n, value_type const & val) {
					size_type	prev_size = _size;
					iterator	it = _alloc.allocate(n);

					std::uninitialized_copy(_start, _start + _size, it);
					_dealloc();
					
					_start = it;
					std::uninitialized_fill(_start + prev_size, _start + n, val);
					_size = n;
					_capacity = n;
				}

				void	_check_range(size_type n) const {
					if (n > _alloc.max_size())
						throw std::out_of_range("vector::_check_range");
				}
    };

	/*
	** Non-member relational operators
	*/

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs != rhs)
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		return (false);
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs == rhs)
			return (true);
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs == rhs)
			return (false);
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs == rhs)
			return (true);
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
};

#endif