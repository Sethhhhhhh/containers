#ifndef __RED_BLACK_TREE_NODE__
#define __RED_BLACK_TREE_NODE__

namespace ft {

	template <typename T>
	class red_black_tree_node {
		
		public:

			/*
			**	Typedef
			*/

			typedef red_black_tree_node		node;
			typedef red_black_tree_node*	pointer;
			typedef T*						data;

			/*
			**	Variable
			*/

			bool	color = true;
			pointer	p;
			pointer	left;
			pointer	right;

			pointer	min;
			pointer	max;

			/*
			**	Constructor
			*/

			red_black_tree_node() : color(false), p(), left(), right(), min(), max() {};
			
			red_black_tree_node(const red_black_tree_node& x) {
				*this = x;
			};

			red_black_tree_node & operator=(const red_black_tree_node& x) {
				color = x.color;
				p = x.p;
				left = x.left;
				right = x.right;
				min = x.min;
				max = x.max;

				return *this;
			};

		protected:

			pointer	increment();
			pointer	decrement();
	};
};

#endif