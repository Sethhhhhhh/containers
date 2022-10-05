#ifndef __FT_MAP__
#define __FT_MAP__

#include <functional>
#include "../utils/pair.hpp"

namespace ft {

	template <
		typename Key,
		typename T,
		typename Compare = std::less<Key>,
		typename Alloc = std::allocator<pair<const Key, T>>
	>
	class map {

		public:
			typedef Key										key_type;
			typedef	T										mapped_type;
			typedef pair<const key_type, mapped_type>		value_type;
			typedef	Compare									key_compare;
			typedef	Alloc									allocator_type;
			typedef allocator_type::reference				reference;
			typedef	allocator_type::const_reference			const_reference;
			typedef	allocator_type::pointer					pointer;
			typedef	allocator_type::const_pointer			const_pointer;
			typedef ptrdiff_t								difference_type;
			typedef size_t									size_type;

			/*
			**	Constructor
			*/

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}

			template <typename InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}

			map(const map& x) {}

			map& operator=(const map& x) {}

			/*
			**	Destructor
			*/

			~map() {};

			/*
			** Iterators
			*/

			iterator begin() {}
			const_iterator begin() const {}

			iterator end() {}
			const_iterator end() const {}

			reverse_iterator rbegin() {}
			const_reverse_iterator rbegin() const {}

			reverse_iterator rend() {}
			const_reverse_iterator rend() const {}

			/*
			** Capacity
			*/

			bool empty() const {}
			size_type size() const {}
			size_type max_size() const {}

			/*
			** Element access
			*/

			mapped_type& operator[](const key_type& k) {}
			mapped_type& at(const key_type& k);const mapped_type& at (const key_type& k) const {}

			/*
			** Modifiers
			*/

			pair<iterator, bool> insert(const value_type& val) {}
			iterator insert(iterator position, const value_type& val) {}
			
			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last) {}

			void erase(iterator position) {}
			size_type erase(const key_type& k) {}
			void erase(iterator first, iterator last) {}

			void swap(map& x) {}

			void clear() {}

			/*
			** Observers
			*/

			key_compare key_comp() const {}
			value_compare value_comp() const {}

			/*
			** Operations
			*/

			iterator find(const key_type& k) {}
			const_iterator find(const key_type& k) const {}

			size_type count(const key_type& k) const {}

			iterator lower_bound(const key_type& k) {}
			const_iterator lower_bound(const key_type& k) const {}

			iterator upper_bound(const key_type& k) {}
			const_iterator upper_bound(const key_type& k) const {}

			pair<const_iterator, const_iterator> equal_range(const key_type& k) const {}
			pair<iterator, iterator> equal_range(const key_type& k) {}
	};
};


#endif