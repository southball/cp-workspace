#ifndef _TEMPLATE_MODINT
#define _TEMPLATE_MODINT

#include "root.h"
#include "euclid.h"

template<ll MOD = 1'000'000'007>
struct Mod {
	ll val;
	Mod() : val(0) {}
	Mod(ll xx) {
		if (0 <= xx && xx < MOD) val = xx;
		else val = (xx % MOD + MOD) % MOD;
	}
	Mod& operator+=(Mod b) { if ((val += b.val) >= MOD) val -= MOD; return *this; }
	Mod& operator-=(Mod b) { if ((val += MOD - b.val) >= MOD) val -= MOD; return *this; }
	Mod& operator*=(Mod b) { (val *= b.val) %= MOD; return *this; }
	Mod& operator/=(Mod b) { (val *= b.inv().val) %= MOD; return *this; }
	Mod operator+(Mod b) const { Mod<MOD> tmp(*this); return tmp += b; }
	Mod operator-(Mod b) const { Mod<MOD> tmp(*this); return tmp -= b; }
	Mod operator*(Mod b) const { Mod<MOD> tmp(*this); return tmp *= b; }
	Mod operator/(Mod b) const { Mod<MOD> tmp(*this); return tmp /= b; }
	Mod& operator++() { *this += 1; return *this; }
	Mod& operator--() { *this -= 1; return *this; }
	Mod operator++(int) { Mod<MOD> tmp(*this); operator++(); return tmp; }
	Mod operator--(int) { Mod<MOD> tmp(*this); operator--(); return tmp; }
	Mod inv() const {
		ll v, y, g = euclid(val, MOD, v, y);
		assert(g == 1); return Mod((v + MOD) % MOD);
	}
	Mod operator^(ll p) const {
		ll r = 1, b = val;
		for (; p; p >>= 1, b = b * b % MOD) if (p & 1) r = r * b % MOD;
		return Mod(r);
	}
	friend istream& operator>>(istream &is, Mod& mod) {
		ll tmp; is >> tmp;
		mod = Mod<MOD>(tmp);
		return is;
	}
	friend ostream& operator<<(ostream &os, const Mod& mod) {
		return os << mod.val;
	}
};

#endif
