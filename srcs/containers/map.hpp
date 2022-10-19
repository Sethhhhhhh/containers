#ifndef __FT_MAP__
#define __FT_MAP__

#include <functional>
#include "../utils/pair.hpp"
#include "../utils/red_black_tree/red_black_tree.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/lexicographical_compare.hpp"
#include "../utils/equal.hpp"


#include <algorithm>

namespace ft {

	template <
		typename Key,
		typename T,
		typename Compare = std::less<Key>,
		typename Alloc = std::allocator<pair<const Key, T> >
	>
	class map {

		public:
			typedef Key											key_type;
			typedef	T											mapped_type;
			typedef pair<const key_type, mapped_type>			value_type;
			typedef	Compare										key_compare;
			typedef	Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map<Key, T, Compare, Alloc>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}

				public:
					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};

		private:
			/*
			**	Typedef
			*/

			typedef	rbtree<value_type, value_compare, Alloc>	tree_type;
			typedef typename tree_type::pair_type				pair_type;
			typedef typename tree_type::pair_range				pair_range;
			typedef typename tree_type::const_pair_range		const_pair_range;

			key_compare key_cmp;
        	tree_type  	tree;

		public:
			typedef typename tree_type::iterator               iterator;
			typedef typename tree_type::const_iterator         const_iterator;
			typedef typename tree_type::reverse_iterator       reverse_iterator;
			typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

			/*
			**	Constructor
			*/

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(comp, alloc) {}

			template <typename InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(comp, alloc) {
				while (first != last) {
        			tree.insert(*first++);
				}
			}

			map(const map& x) : tree(x.key_comp(), x.get_allocator()) {
				const_iterator pos = x.begin();

				while (pos != x.end()) {
					tree.insert(*pos++);
				}
			}

			map& operator=(const map& x) {
				tree = x.tree;
				key_cmp = x.key_cmp;

				return *this;
			}

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

			bool empty() const { return !tree.get_size(); }
			size_type size() const { return tree.get_size(); }
			size_type max_size() const { return tree.get_max_size(); }

			/*
			** Element access
			*/

			mapped_type& operator[](const key_type& k) {
				value_type v = ft::make_pair(k, mapped_type());
    			return (((tree.insert(v)).first)->second);
			}
			/*
			** Modifiers
			*/

			pair<iterator, bool> insert(const value_type& x) {
				return tree.insert(x);
			}
			iterator insert(iterator position, const value_type& x) {
				return tree.insert(x, position);
			}
			
			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last) {
				while (first != last) {
					tree.insert(*first++);
				}
			}

			void erase(iterator position) {
				if (position == end())
					return ;

				key_type key = position->first;
				value_type x = ft::make_pair(key, mapped_type());
				tree.remove(tree.search(x));
			}
			size_type erase(const key_type& k) {
				value_type x = ft::make_pair(k, mapped_type());
				iterator pos(tree.search(x));

				if (pos != end())
					tree.remove(tree.search(x));
				return pos == end() ? 0 : 1;
			}
			void erase(iterator first, iterator last) {
				if (first != end())
					while (first != last)
						tree.remove(tree.search(*first++));
			}

			void swap(map& x) { tree.swap(x.tree); }

			void clear() { tree.clean(); }

			/*
			** Observers
			*/

			key_compare key_comp() const { return key_cmp; }
			value_compare value_comp() const { return value_compare(tree.get_key_compare()); }

			/*
			** Operations
			*/

			iterator find(const key_type& k) {
				value_type	x = ft::make_pair(k, mapped_type());
				return iterator(tree.search(x));
			}
			const_iterator find(const key_type& k) const {
				value_type	x = ft::make_pair(k, mapped_type());
				return const_iterator(tree.search(x));
			}

			size_type count(const key_type& k) const {
				value_type x = ft::make_pair(k, mapped_type());
				const_iterator pos(tree.search(x));

				return (pos == end() ? 0 : 1);
			}

			iterator lower_bound(const key_type& k) {
				value_type x = ft::make_pair(k, mapped_type());
    			return tree.lower_bound(x);
			}
			const_iterator lower_bound(const key_type& k) const {
				value_type x = ft::make_pair(k, mapped_type());
    			return tree.lower_bound(x);
			}

			iterator upper_bound(const key_type& k) {
				value_type x = ft::make_pair(k, mapped_type());
    			return tree.upper_bound(x);
			}
			const_iterator upper_bound(const key_type& k) const {
				value_type x = ft::make_pair(k, mapped_type());
    			return tree.upper_bound(x);
			}

			pair_range equal_range(const key_type& k) {
				value_type x = ft::make_pair(k, mapped_type());
				
    			return tree.equal_range(x);
			}

			const_pair_range equal_range(const key_type& k) const {
				value_type x = ft::make_pair(k, mapped_type());

    			return tree.equal_range(x);
			}

			allocator_type	get_allocator() const { return tree.get_data_allocator(); }
	};

	/*
	** Non-member functions
	*/

	template <typename Key, typename T, typename _Cmp, typename _Alloc>
	bool
	operator==(map<Key, T, _Cmp, _Alloc> const &lhs,	map<Key, T, _Cmp, _Alloc> const &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename Key, typename T, typename Cmp, typename Alloc>
	bool
	operator<(map<Key, T, Cmp, Alloc> const &lhs, map<Key, T, Cmp, Alloc> const &rhs)
	{
		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename Key, typename T, typename Cmp, typename Alloc>
	bool
	operator!=(map<Key, T, Cmp, Alloc> const &lhs, map<Key, T, Cmp, Alloc> const &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename Key, typename T, typename Cmp, typename Alloc>
	bool
	operator>(map<Key, T, Cmp, Alloc> const &lhs, map<Key, T, Cmp, Alloc> const &rhs)
	{
		return (rhs < lhs);
	}

	template <typename Key, typename T, typename Cmp, typename Alloc>
	bool
	operator<=(map<Key, T, Cmp, Alloc> const &lhs, map<Key, T, Cmp, Alloc> const &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename Key, typename T, typename Cmp, typename Alloc>
	bool
	operator>=(map<Key, T, Cmp, Alloc> const &lhs, map<Key, T, Cmp, Alloc> const &rhs)
	{
		return (!(lhs < rhs));
	}
};


#endif