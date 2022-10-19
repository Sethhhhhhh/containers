#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

#include <algorithm>
#include "red_black_tree_node.hpp"
#include "red_black_tree_iterator.hpp"
#include "../reverse_iterator.hpp"

#include <iostream>

namespace ft {

	template <typename T, typename Cmp, typename Alloc>
	class rbtree {

		private:

			/*
			** Typedef
			*/

			typedef	size_t														size_type;
			typedef ptrdiff_t													difference_type;
			typedef T															value_type;
			typedef red_black_tree_node<T>										node_type;
			typedef red_black_tree_node<T>*										node_pointer;

			typedef typename Alloc::template rebind<Node<value_type> >::other	size_allocator;
        	typedef typename Alloc::template rebind<value_type>::other  		data_allocator;
       		typedef typename Alloc::template rebind<red_black_tree_node<value_type> >::other  node_allocator;

			/*
			** Variable
			*/

			data_allocator	_data_alloc;
			node_allocator	_node_alloc;
			Cmp				_key_compare;
			size_type		_size;

			node_type*		_root;
			node_type*		_nil;

			/*
			** Util
			*/

			node_pointer	minimum(node_pointer node) const {
				if (node == _nil)
					return node;
				
				node_pointer	tmp = node;
				while(tmp->left != _nil)
					tmp = tmp->left;
				return (tmp);
			}

			node_pointer	maximum(node_pointer node) const {
				if (node == _nil)
					return (node);
				
				node_pointer	tmp = node;
				while (tmp->right != _nil)
					tmp = tmp->right;
				return (tmp);
			}

			bool			is_equal(const value_type &x, const value_type &y) const {
				return !_key_compare(x, y) && !_key_compare(y, x);
			}

			node_pointer	find(const value_type &x) const {
				node_pointer y = _root;
		
				while (y != _nil && !is_equal(x, *y->data)) {
					if (_key_compare(x, *y->data))
						y = y->left;
					else
						y = y->right;
				}
				return (y);
			}

			node_pointer	create(const value_type &x) {
				node_pointer	node = _node_alloc.allocate(1);

				node->p = _nil;
				node->nil = _nil;
				node->data = _data_alloc.allocate(1);
				_data_alloc.construct(node->data, x);

				return node;
			}

			/*
			**	Remove
			*/

			void	_clean_node(node_pointer node) {
				if (node != _nil) {
					_data_alloc.destroy(node->data);
					_data_alloc.deallocate(node->data, 1);    
					_node_alloc.deallocate(node, 1);
				}
			}

			void	transplant(node_pointer u, node_pointer v) {
				if (u->p == _nil)
					_root = v;
				else if (u == u->p->left)
					u->p->left = v;
				else
					u->p->right = v;
				v->p = u->p;
			}

			void	remove_fix(node_pointer x) {
				while (x != _root && !x->color) {
					if (x == x->p->left) {
						node_pointer w = x->p->right;

						if (w->color == true) {
							w->color = false;
							x->p->color = true;

							left_rotate(x->p);
							
							w = x->p->right;
						}
						if (!w->left->color && !w->right->color) {
							w->color = true;
							x = x->p;
						}
						else {   
							if (!w->right->color) {
								w->left->color = false;
								w->color = true;

								right_rotate(w);
								
								w = x->p->right;
							}
							w->color = x->p->color;
							x->p->color = false;
							w->right->color = false;

							left_rotate(x->p);
							
							x = _root;
						}
					}
					else {
						node_pointer w = x->p->left;
						if (w->color) {
							w->color = false;
							x->p->color = true;
							
							right_rotate(x->p);
							
							w = x->p->left;
						}
						if (!w->right->color && !w->left->color) {
							w->color = true;
							x = x->p;
						}
						else {
							if (!w->left->color) {
								w->right->color = false;
								w->color = true;
								
								left_rotate(w);
								
								w = x->p->left;
							}
							w->color = x->p->color;
							x->p->color = false;
							w->left->color = false;
							
							right_rotate(x->p);
							
							x = _root;
						}
							}
				}
				x->color = false;
			}

			/*
			** Rotate
			*/

			void	left_rotate(node_pointer x) {
				node_pointer   y = x->right;

				x->right = y->left;
				if (y->left != _nil)
					y->left->p = x;
				y->p = x->p;
				if (x->p == _nil)
					_root = y;
				else if (x == x->p->left)
					x->p->left = y;
				else
					x->p->right = y;
				y->left = x;
   				x->p = y;
			}
			void	right_rotate(node_pointer x) {
				node_pointer   y = x->left;

				x->left = y->right;
				if (y->right != _nil)
					y->right->p = x;
				y->p = x->p;
				if (x->p == _nil)
					_root = y;
				else if (x == x->p->right)
					x->p->right = y;
				else
					x->p->left = y;
				y->right = x;
				x->p = y;
			}

			void	_clean_tree(node_pointer node) {
				if (node != _nil) {
					_clean_tree(node->left);
					_clean_tree(node->right);
					_clean_node(node);
				}
			}
		
		public:

			/*
			** Typedef
			*/

			typedef ft::red_black_tree_iterator<value_type, node_type>				iterator;
			typedef	ft::red_black_tree_iterator<const value_type, const node_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef ft::pair<iterator, bool>                                		pair_type;
       		typedef ft::pair<iterator, iterator>                            		pair_range; 
        	typedef ft::pair<const_iterator, const_iterator>                		const_pair_range; 

			/*
			** Constructor
			*/
			
			rbtree();
			explicit rbtree(const Cmp compare, const Alloc allocator) : _data_alloc(allocator), _key_compare(compare), _size(0) {
				_size = 0;

				_nil = _node_alloc.allocate(1);
				_nil->color = false;
				_nil->data = NULL;
				_nil->right = _nil;
				_nil->left = _nil;
				_nil->p = _nil;
				_nil->nil = _nil;
				_nil->max = _nil;
				_nil->min = _nil;

				_root = _nil;
			};
			rbtree(const rbtree &x) {
				clean();
				for (const_iterator i = x.begin(); i != x.end(); i++) {
					insert(*i);
				}
				return *this;
			};
			rbtree & operator=(const rbtree &x) {
				clean();

				for (const_iterator i = x.begin(); i != x.end(); i++) {
					insert(*i);
				}
				return *this;
			};

			/*
			** Destructor
			*/

			~rbtree() {
				if (_root != _nil)
					clean();
				_node_alloc.deallocate(_nil, 1);
			};

			void	clean() {
				_clean_tree(_root);
				_root = _nil;
				_root->right = _nil;
    			_root->left = _nil;
				_size = 0;				
			}

			void	remove(node_pointer node) {
				node_pointer tmp_x;
				node_pointer tmp_y;
				tmp_y = node;
				bool node_isred = node->color;
				if (node->left == _nil)
				{
					tmp_x = node->right;
					transplant(node, node->right);
				}
				else if (node->right == _nil)
				{
					tmp_x = node->left;
					transplant(node, node->left);
				}
				else
				{
					tmp_y = minimum(node->right);
					node_isred = tmp_y->color;
					tmp_x = tmp_y->right;
					if (tmp_y->p == node)
						tmp_x->p = tmp_y;
					else
					{
						transplant(tmp_y, tmp_y->right);
						tmp_y->right = node->right;
						tmp_y->right->p = tmp_y;
					}
					transplant(node, tmp_y);
					tmp_y->left = node->left;
					tmp_y->left->p = tmp_y;
					tmp_y->color = node->color;
				}
				_clean_node(node);
				if (node_isred == false)
					remove_fix(tmp_x);
				_nil->max = maximum(_root);
				_nil->min = minimum(_root);
				_nil->p = _nil;
				_size--;
			}

			node_pointer	search(const value_type &v) const {
				node_pointer	x = _root;

				while (x != _nil && !is_equal(v, *x->data)) {
					if (_key_compare(v, *(x->data)))
						x = x->left;
					else
						x = x->right;
				}
				return x;
			}


			/*
			** Insert	
			*/

			pair_type	insert(const value_type &v) {
				node_pointer y = _nil;
				node_pointer x = _root;

				while (x != _nil) {
					y = x;
					if (is_equal(v, *x->data)) {
            			return pair_type(iterator(x), false);
					}
					else if (_key_compare(v, *x->data)) {
						x = x->left;	
					}
					else {
						x = x->right;
					}
				}

				node_pointer z = create(v);
				z->p = y;

				if (y == _nil)
					_root = z;
				else if (_key_compare(v, *y->data)) {
					y->left = z;
				}
				else {
					y->right = z;
				}

				z->left = _nil;
				z->right = _nil;
				z->color = true;
				insert_fix(z);
				_size++;

				return pair_type(iterator(z), true);
			}

			iterator	insert(const value_type &v, iterator pos) {
				node_pointer x = pos.node;

				if (x == _nil || pos == end() || !_key_compare(v, *(x->data)) || x->p == _nil || !_key_compare(*(x->p->data), v))
					return insert(v).first;
					
				node_pointer y = _nil;

				while (x != _nil) {
					y = x;
					if (_key_compare(v, *x->data))
						x = x->left;
					else
						x = x->right;
				}

				node_pointer z = create(v);
				z->p = y;

				if (y == _nil)
					_root = z;
				else if (_key_compare(v, *y->data))
					y->left = z;
				else
					y->right = z;

				z->left = _nil;
				z->right = _nil;
				z->color = true;

				insert_fix(z);
				_size++;

				return iterator(z);
			}

			void	insert_fix(node_pointer z) {	
				while (z->p->color) {
					if (z->p == z->p->p->left) {
						node_pointer y = z->p->p->right;
						
						if (y->color) {
							z->p->color = false;
							y->color = false;
							z->p->p->color = true;

							z = z->p->p;
						}
						else {
							if (z == z->p->right) {
								z = z->p;
								left_rotate(z);
							}
							z->p->color = false;
							z->p->p->color = true;
							right_rotate(z->p->p);
						}
					}
					else {
						node_pointer y = z->p->p->left;
						
						if (y->color) {
							z->p->color = false;
							y->color = false;
							z->p->p->color = true;

							z = z->p->p;
						} else {
							if (z == z->p->left) {
								z = z->p;
								right_rotate(z);
							}
							z->p->color = false;
							z->p->p->color = true;
							left_rotate(z->p->p);
						}
					}
				}
				_root->color = false;
				_nil->max = maximum(_root);
    			_nil->min = minimum(_root);
			}

			void	swap(rbtree &tree) {
				std::swap(_root, tree._root);
				std::swap(_size, tree._size);
				std::swap(_nil, tree._nil);
			}

			size_type	get_size() const { return _size; }
			data_allocator	get_data_allocator() const { return _data_alloc; }

			/*
			** Iterators
			*/

			iterator		begin() { return iterator(minimum(_root)); }
			const_iterator	begin() const { return const_iterator(minimum(_root)); }

			iterator		end() { return iterator(_nil); }
			const_iterator	end() const { return const_iterator(_nil); }

			reverse_iterator	rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }

			reverse_iterator	rend() { return reverse_iterator(begin()); }
			const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

			/*
			** Bounds
			*/

			iterator	lower_bound(const value_type &x) {
				iterator	it = begin();
				iterator	ite = end();

				while(it != ite) {
					if (!_key_compare(*it, x))
						return it;
					it++;
				}
				return it;
			}

			const_iterator	lower_bound(const value_type &x) const {
				const_iterator	it = begin();
				const_iterator	ite = end();

				while(it != ite) {
					if (!_key_compare(*it, x))
						return it;
					it++;
				}
				return it;
			}

			iterator	upper_bound(const value_type &x) {
				iterator	it = begin();
				iterator	ite = end();

				while(it != ite) {
					if (_key_compare(x, *it))
						return it;
					it++;
				}
				return it;
			}

			const_iterator	upper_bound(const value_type &x) const {
				const_iterator	it = begin();
				const_iterator	ite = end();

				while(it != ite) {
					if (_key_compare(x, *it))
						return it;
					it++;
				}
				return it;
			}

			pair_range	equal_range(const value_type &v) {
				iterator it = upper_bound(v);
				iterator ite = lower_bound(v);

				return pair_range(ite, it);
			}

			const_pair_range	equal_range(const value_type &v) const {
				const_iterator it = upper_bound(v);
				const_iterator ite = lower_bound(v);

				return const_pair_range(ite, it);
			}


			size_type	get_max_size() const {
				size_allocator	x;

				return x.max_size();
			}

			Cmp	get_key_compare() const { return _key_compare; }

	};
};

#endif