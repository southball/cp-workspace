//! snippet root
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
template<typename H> bool chmin(H& v1, const H v2) { if (v1 > v2) { v1 = v2; return true; } return false; }
template<typename H> bool chmax(H& v1, const H v2) { if (v1 < v2) { v1 = v2; return true; } return false; }
//! end root

//! snippet io
//! use root
template<typename H> void read(H& head) { cin >> head; }
template<typename H, typename ...T> void read(H& head, T& ...tail) { cin >> head; read(tail...); }
template<typename H> void write(H head) { cout << head << '\n'; }
template<typename H, typename ...T> void write(H head, T ...tail) { cout << head << " "; write(tail...); }
template<typename ...T> void die(T ...tok) { write(tok...); exit(0); }
//! end io

//! snippet modpow
//! use root
ll modpow(ll b, ll p, ll m) {
	ll r = 1;
	for (; p; p >>= 1, b = b * b % m) if (p & 1) r = r * b % m;
	return r;
}
//! end modpow

//! snippet modint
//! use root
//! use modpow
template<int MOD>
struct ModInt {
	int val;
	ModInt(ll v) {
		if (0 <= v && v < MOD) val = v;
		else val = (v % MOD + MOD) % MOD;
	}
	const ModInt inv() { return ModInt(modpow(val, MOD - 2, MOD)); }
};
//! end modint
