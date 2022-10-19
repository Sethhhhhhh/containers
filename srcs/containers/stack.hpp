#ifndef	__FT_STACK__
#define __FT_STACK__

#include "vector.hpp"

namespace ft {
	template <typename T, typename Container = vector<T> >
	class stack {

		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;

			explicit stack(container_type const &ctnr = container_type()) : _ctnr(ctnr) {}

			bool				empty() const { return _ctnr.empty(); }

			size_type			size() const { return _ctnr.size(); }

			value_type			&top() { return _ctnr.back(); }

			const value_type	&top() const { return _ctnr.back(); }

			void				push(value_type const &val) { _ctnr.push_back(val); }

			void				pop() { _ctnr.pop_back(); }

			friend bool		operator==(stack<T, Container> const &lhs, stack<T, Container> const &rhs) {
				return (lhs._ctnr == rhs._ctnr);
			}

			friend bool		operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) {
				return (!(lhs == rhs));
			}

			friend bool		operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs) {
				return (lhs._ctnr < rhs._ctnr);
			}

			friend bool		operator<=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) {
				return (!(rhs < lhs));
			}
			
			friend bool		operator>(stack<T, Container> const &lhs, stack<T, Container> const &rhs) {
				return (rhs < lhs);
			}

			friend bool		operator>=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) {
				return (!(lhs < rhs));
			}

		protected:
			container_type		_ctnr;
	};

};

#endif