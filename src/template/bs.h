#ifndef _TEMPLATE_BS
#define _TEMPLATE_BS

#include "root.h"

template<class T, class U>
T lower_bound_on(T first, T last, const U& value, const function<U(T)>& fn) {
	T it, step, count = last - first;
	while (count > 0) {
		it = first + (step = count / 2);
		if (fn(it) < value)
			first = ++it, count -= step + 1;
		else
			count = step;
	}
	return first;
}
template<class T, class U>
T upper_bound_on(T first, T last, const U& value, const function<U(T)>& fn) {
	T it, step, count = last - first;
	while (count > 0) {
		it = first + (step = count / 2);
		if (!(value < fn(it)))
			first = ++it, count -= step + 1;
		else	
			count = step;
	}
	return first;
}

#endif
