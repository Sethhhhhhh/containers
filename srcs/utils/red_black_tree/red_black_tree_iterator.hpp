#ifndef __RED_BLACK_TREE_ITERATOR_HPP__
#define __RED_BLACK_TREE_ITERATOR_HPP__

#include <iterator>

namespace ft {

	template <typename T, typename Node>
	class red_black_tree_iterator {

		public:
			typedef T								value_type;
			typedef T&								reference;
			typedef T*								pointer;
			typedef const T&						const_reference;
			typedef const T*						const_pointer;

			typedef std::bidirectional_iterator_tag	iterator_category;
       		typedef ptrdiff_t                       difference_type;
        	typedef Node*                     		node_pointer;

			node_pointer	node;

			/*
			** Constructor
			*/

			red_black_tree_iterator() {};
			red_black_tree_iterator(const red_black_tree_iterator &x) {};
			red_black_tree_iterator& operator=(const red_black_tree_iterator &x) {
				if (this != &x)
					node = x.node;
				return *this;
			}

			reference operator*() { return *node->data; }
			pointer operator->() { return node->data; }
			const_reference operator*() const { return *node->data; }
			const_pointer operator->() const { return node->data; }

			red_black_tree_iterator operator++() {}

			red_black_tree_iterator operator++(int) {}

			red_black_tree_iterator operator--() {}

			red_black_tree_iterator operator--(int) {}

			bool	operator==(const red_black_tree_iterator &x) const { return node == x.node; }
			bool	operator!=(const red_black_tree_iterator &x) const { return node != x.node; }
		
		protected:
			void	increment() {
				if (node == nullptr)
					return ;
				if (node->right != nullptr) {
					node = node->right;
					while (node->left != nullptr)
						node = node->left;
				} else {
					node_pointer	tmp = node->p;

					while (tmp != nullptr && node == tmp->right) {
						node = tmp;
						tmp = tmp->p;
					}
					node = tmp;
				}
			}

			void	decrement() {
				if (node != nullptr) {
					node = nullptr;
					return ;
				}
				if (node->left != nullptr) {
					node = node->left;
					while (node->right != nullptr)
						node = node->right;
				} else {
					node_pointer tmp = node->parent;

					while (tmp != nullptr && node == tmp->left) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
			}
	};
};

#endif
