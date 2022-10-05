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
			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map<Key, T, Compare, Alloc>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}

				public:
					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			}

		private:
			/*
			**	Typedef
			*/

			typedef	red_black_tree<T, value_compare, Alloc>	_tree_type;
			typedef typename _tree_type::pair_type			pair_type;
			typedef typename _tree_type::pair_range			pair_range;
			typedef typename _tree_type::const_pair_range	const_pair_range;

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

			_tree_type	tree;

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

			iterator begin() { return tree.begin(); }
			const_iterator begin() const { return tree.begin(); }

			iterator end() { return tree.end(); }
			const_iterator end() const { return tree.end(); }

			reverse_iterator rbegin() { return tree.rbegin(); }
			const_reverse_iterator rbegin() const { return tree.rbegin(); }

			reverse_iterator rend() { return tree.rend(); }
			const_reverse_iterator rend() const { return tree.rend(); }

			/*
			** Capacity
			*/

			bool empty() const {}
			size_type size() const { return tree.get_size(); }
			size_type max_size() const {}

			/*
			** Element access
			*/

			mapped_type& operator[](const key_type& k) {}
			mapped_type& at(const key_type& k);const mapped_type& at (const key_type& k) const {}

			/*
			** Modifiers
			*/

			pair<iterator, bool> insert(const value_type& val) { return tree.insert(val); }
			iterator insert(iterator position, const value_type& val) {
				return tree.insert(val, position);
			}
			
			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last) {
				while (first != last)
					tree.insert(*first++);
			}

			void erase(iterator position) {}
			size_type erase(const key_type& k) {}
			void erase(iterator first, iterator last) {}

			void swap(map& x) { tree.swap(x.tree); }

			void clear() { tree.clean(); }

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