#ifndef _TEMPLATE_MODPOW
#define _TEMPLATE_MODPOW

#include "root.h"

ll modpow(ll b, ll p, ll m) {
	ll r = 1;
	for (; p; p >>= 1, b = b * b % m) if (p & 1) r = r * b % m;
	return r;
}

#endif
