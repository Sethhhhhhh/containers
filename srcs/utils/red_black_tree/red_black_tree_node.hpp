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
			typedef T*						data_pointer;

			/*
			**	Variable
			*/

			data_pointer	data;
			bool			color;
			pointer			p;
			pointer			left;
			pointer			right;
			pointer			nil;

			pointer			min;
			pointer			max;

			/*
			**	Constructor
			*/

			red_black_tree_node() : color(false), p(), left(), right(), min(), max(), nil() {};

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
				nil	= x.nil;

				return *this;
			};

		protected:

			pointer	increment();
			pointer	decrement();
	};

	template <typename T>
	struct Node {
		T				data;
		bool			color;
		struct node*	left;
		struct node*	right;
		struct node*	p;

	};
};


#endif