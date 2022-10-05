#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

namespace ft {

	template <typename T, typename Cmp, typename Alloc>
	class rbtree {

		private:
			typedef	size_t					size_type;
			typedef ptrdiff_t				difference_type;
			typedef T						value_type;
			typedef red_black_tree_node<T>	node_type;
			typedef red_black_tree_node<T>*	node_pointer;

			Cmp	_key_compare;

			/*
			** Constructor
			*/
			
			rbtree() {};
			rbtree(const rbtree &x) {};
			rbtree & operator=(const rbtree &x) {};

			/*
			** Destructor
			*/

			~rbtree() {};

			/*
			** Util
			*/

			node_pointer	mininum(node_pointer node) const {
				if (node == nullptr)
					return node;
				
				node_pointer	tmp = node;
				while(node->left != nullptr)
					tmp = tmp->left;
				return (tmp);
			}

			node_pointer	maximum(node_pointer node) const {
				if (node == nullptr)
					return (node);
				
				node_pointer	tmp = node;
				while (tmp->right != nullptr)
					tmp = tmp->right;
				return (tmp);
			}

			/*
			** Insert
			*/

			void	insert(const value_type &z) {
				node_pointer y = nullptr;
				node_pointer x = _root;

				while (x != nullptr) {
					y = x;
					if (_key_compare(z, y))
						x = x->left;	
					else
						x = x->right;

					z->p = y;
					if (y == nullptr)
						_root = z;
					else if (_key_compare(z, y))
						y->left = z;
					else
						y->right = z;
					z->left = nullptr;
					z->right = nullptr;
					z->color = true;
					insert_fix(z);
				}
			}
			void	insert_fix(node_pointer z) {
				while (z->p->color) {
					if (z->p == z->p->p->left) {
						y = z->p->right;
						if (y->color) {
							z->p->color = false;
							y->color = false;
							z->p->p->color = true;
						} else {
							if (z == z->p->right) {
								z = z->p;
								left_rotate(z);
							}
							z->p->color = false;
							z->p->color = true;
							right_rotate(z->p->p);
						}
					} else {
						y = z->p->left;
						if (y->color) {
							z->p->color = false;
							y->color = false;
							z->p->p->color = true;
						} else {
							if (z == z->p->left) {
								z = z->p;
								right_rotate(z);
							}
							z->p->color = false;
							z->p->color = true;
							left_rotate(z->p->p);
						}
					}
				}
			}

			/*
			**	Remove
			*/

			void	transplant(node_pointer u, node_pointer v) {
				if (u->p == nullptr)
					_root = v;
				else if (u == u->p->left)
					u->p->left = v;
				else
					u->p->right = v;
				v->p = u->p;
			}
			
			void	remove(node_pointer z) {
				node_pointer	x;
				node_pointer	y;

				y = z;
				bool original_color = y->color;

				if (z->left == nullptr) {
					x = z->right;
					transplant(z, z->right);
				} else if (z->right == nullptr) {
					x = z-left;
					transplant(z, z->left)
				} else {
					y = mininum(z->right)
					x = y->right;
					if (y->p == z)
						x->p = y;
					else {
						transplant(y, y->right);
						y->right = z->right;
						y->right->p = y;
					}
					transplant(z, y->right);
					y->left = z->left;
					y->left->p = y;
					y->color = z->color;
				}
				if (!color)
					remove_fix(x);
			}
			void	remove_fix(node_pointer x) {
				node_pointer	w;

				while (x != _root && !x->color) {
					if (x == x->p->left) {
						w = x->p->left;
						if (w->color) {
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
					} else {
						w = x->p->right;
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
				node_pointer y = x->right;

				x->right = y->left;
				if (y->left != nullptr)
					y->left->p = x;
				y->p = x->p;
				if (x->p == nullptr)
					x->p->left = y;
				else
					x->p->right = y;
				y->left = x;
				x->p = y;
			}
			void	right_rotate(node_pointer x) {
				node_pointer y = x->left;

				x->left = y->right;
				if (y->right != nullptr)
					y->right->p = x;
				y->p = x->p;
				if (x->p == nullptr)
					x->p->right = y;
				else
					x->p->left = y;
				y->right = x;
				x->p = y;
			}
	};
};

#endif