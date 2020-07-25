#ifndef _TEMPLATE_MONOID
#define _TEMPLATE_MONOID

template<class T>
struct Monoid {
	T id;
	virtual T op(T a, T b) = 0;
};

#endif
