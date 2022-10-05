#ifndef __FT_PAIR__
#define __FT_PAIR__

namespace ft {
	
	template <typename T1, typename T2>
	struct pair {
		typedef T1	first_type;
    	typedef T2	second_type;

		T1	first;
		T2	second;

		/*
		**	Constructor
		*/

		pair() : first(), second() {}

		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(val.second) {}

		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& pr) {
			first = pr.first;
			second = pr.second;

			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs == rhs);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs != rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs < rhs);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs <= rhs);
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs > rhs);
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs >= rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
		return (pair<T1, T2><x, y>);
	}
};


#endif