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

//! snippet opt
#pragma gcc optimize("Ofast")
#pragma gcc target("avx2")
//! end opt

//! snippet modpow
//! use root
ll modpow(ll b, ll p, ll m) {
	ll r = 1;
	for (; p; p >>= 1, b = b * b % m) if (p & 1) r = r * b % m;
	return r;
}
//! end modpow

//! snippet euclid
ll euclid(ll a, ll b, ll &x, ll &y) {
	if (b) { ll d = euclid(b, a % b, y, x);
		return y -= a/b * x, d; }
	return x = 1, y = 0, a;
}
//! end euclid

//! snippet modint
//! use root
//! use euclid
template<ll MOD = 1000000007>
struct Mod {
	ll val;
	Mod() : val(0) {}
	Mod(ll xx) {
		if (0 <= xx && xx < MOD) val = xx;
		else val = (xx % MOD + MOD) % MOD;
	}
	Mod operator+(Mod b) { return Mod((val + b.val) % MOD); }
	Mod operator-(Mod b) { return Mod((val - b.val + MOD) % MOD); }
	Mod operator*(Mod b) { return Mod((val * b.val) % MOD); }
	Mod operator/(Mod b) { return *this * invert(b); }
	Mod operator+=(Mod b) { *this = *this + b; return *this; }
	Mod operator-=(Mod b) { *this = *this - b; return *this; }
	Mod operator*=(Mod b) { *this = *this * b; return *this; }
	Mod operator/=(Mod b) { *this = *this / b; return *this; }
	Mod& operator++() { *this += 1; return *this; }
	Mod& operator--() { *this -= 1; return *this; }
	Mod operator++(int) { Mod<MOD> tmp(*this); operator++(); return tmp; }
	Mod operator--(int) { Mod<MOD> tmp(*this); operator--(); return tmp; }
	Mod invert(Mod a) {
		ll val, y, g = euclid(a.val, MOD, val, y);
		assert(g == 1); return Mod((val + MOD) % MOD);
	}
	Mod operator^(ll e) {
		if (!e) return Mod(1);
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
	friend istream& operator>>(istream &is, Mod& mod) {
		is >> mod.val; mod.val = (mod.val % MOD + MOD) % MOD; return is;
	}
	friend ostream& operator<<(ostream &os, const Mod& mod) {
		os << mod.val; return os;
	}
};
//! end modint

//! snippet ncr
//! use root
//! use modint
template<ll MOD = 1000000007>
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
//! end ncr
