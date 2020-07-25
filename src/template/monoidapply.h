#ifndef _TEMPLATE_MONOIDAPPLY
#define _TEMPLATE_MONOIDAPPLY

template<typename T, typename U>
struct MonoidApply {
	virtual T op(U fn, T val) = 0;
};

#endif
