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

			red_black_tree_iterator() : node() {}
			red_black_tree_iterator(node_pointer x) : node(x) {}
			red_black_tree_iterator(const red_black_tree_iterator &x) : node(x.node) {}

			red_black_tree_iterator& operator=(const red_black_tree_iterator &x) {
				if (this != &x)
					node = x.node;
				return *this;
			}

			operator    red_black_tree_iterator<value_type const, Node const>() const
			{
				return red_black_tree_iterator<value_type const, Node const>(node);
			}

			reference operator*() { return *node->data; }
			pointer operator->() { return node->data; }
			const_reference operator*() const { return *node->data; }
			const_pointer operator->() const { return node->data; }

			red_black_tree_iterator operator++() {
				increment();
				return *this;
			}

			red_black_tree_iterator operator++(int) {
				red_black_tree_iterator	x(*this);
				
				increment();
				
				return x;
			}

			red_black_tree_iterator operator--() {
				decrement();
				return *this;
			}

			red_black_tree_iterator operator--(int) {
				red_black_tree_iterator	x(*this);

				decrement();
				
				return *this;
			}

			bool	operator==(const red_black_tree_iterator &x) const {
				return node == x.node;
			}
			bool	operator!=(const red_black_tree_iterator &x) const {
				return node != x.node;
			}
		
		protected:
			void	increment() {
				if (node == node->nil)
					return ;
				if (node->right != node->nil) {
					node = node->right;
					while (node->left != node->nil)
						node = node->left;
				} else {
					node_pointer	tmp = node->p;

					while (tmp != node->nil && node == tmp->right) {
						node = tmp;
						tmp = tmp->p;
					}
					node = tmp;
				}
			}

			void	decrement() {
				if (node != node->nil) {
					node = node->nil;
					return ;
				}
				if (node->left != node->nil) {
					node = node->left;
					while (node->right != node->nil)
						node = node->right;
				} else {
					node_pointer tmp = node->p;

					while (tmp != node->nil && node == tmp->left) {
						node = tmp;
						tmp = tmp->p;
					}
					node = tmp;
				}
			}
	};
};

#endif
