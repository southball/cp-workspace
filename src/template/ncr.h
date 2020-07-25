#ifndef _TEMPLATE_NCR
#define _TEMPLATE_NCR

#include "root.h"
#include "modint.h"

template<ll MOD = 1'000'000'007>
struct NCR {
	int size;
	vector<Mod<MOD>> fact;
	NCR(int size) : size(size) {
		fact = vector<Mod<MOD>>(size + 1);
		fact[0] = 1;
		for (int i = 1; i < size; i++)
			fact[i] = fact[i - 1] * i;
	}
	Mod<MOD> ncr(int n, int r) {
		return fact[n] / fact[r] / fact[n - r];
	}
};

#endif
