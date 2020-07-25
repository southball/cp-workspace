#ifndef _TEMPLATE_EUCLID
#define _TEMPLATE_EUCLID

#include "root.h"

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (b) { ll d = euclid(b, a % b, y, x);
		return y -= a/b * x, d; }
	return x = 1, y = 0, a;
}

#endif
