//! snippet root
typedef long long ll;
//! end root

//! snippet modpow
//! require root
ll modpow(ll b, ll p, ll m) {
	ll r = 1;
	for (; p; p >>= 1, b = b * b % m) if (p & 1) r = r * b % m;
	return r;
}
//! end modpow

//! snippet modint
//! require root
//! require modpow
template<int MOD>
struct Modint {
	int val;
	Modint(ll v) {
		if (0 <= v && v < MOD) val = v;
		else val = (v % MOD + MOD) % MOD;
	}
	const Modint inv() { return Modint(modpow(val, MOD - 2, MOD)); }
};
//! end modint
