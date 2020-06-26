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
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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
template<ll MOD = 1'000'000'007>
struct Mod {
	ll val;
	Mod() : val(0) {}
	Mod(ll xx) {
		if (0 <= xx && xx < MOD) val = xx;
		else val = (xx % MOD + MOD) % MOD;
	}
	Mod operator+=(Mod b) { if ((val += b.val) >= MOD) val -= MOD; return *this; }
	Mod operator-=(Mod b) { if ((val += MOD - b.val) >= MOD) val -= MOD; return *this; }
	Mod operator*=(Mod b) { (val *= b.val) %= MOD; return *this; }
	Mod operator/=(Mod b) { (val *= b.inv().val) %= MOD; return *this; }
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
//! end modint

//! snippet ncr
//! use root
//! use modint
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
//! end ncr

//! snippet monoid
template<class T>
struct Monoid {
	T id;
	virtual T op(T a, T b) = 0;
};
//! end monoid

//! snippet segtree
//! use monoid
template<typename T, typename M, typename = enable_if<is_base_of<Monoid<T>, M>::value>>
struct SegTree {
	M monoid;
	vector<T> tree;
	int size;

	SegTree(vector<T> elems, M monoid) : size(elems.size()), monoid(monoid) {
		tree = vector<T>(2 * size);
		for (int i = 0; i < size; i++)
			tree[size + i] = elems[i];
		build();
	}

	SegTree(int size, M monoid) : size(size), monoid(monoid) {
		tree = vector<T>(size, monoid.id);
		build();
	}	

	void build() {
		for (int i = size - 1; i > 0; --i)
			tree[i] = monoid.op(tree[i << 1], tree[i << 1 | 1]);
	}

	T query(int l, int r) {
		T resl = monoid.id, resr = monoid.id;
		++r; // handle inclusive query range
		for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
			if (l & 1) resl = monoid.op(resl, tree[l++]);
			if (r & 1) resr = monoid.op(tree[--r], resr);
		}
		return monoid.op(resl, resr);
	}

	T get(int p) {
		return tree[size + p];
	}

	void update(int p, T val) {
		for (tree[p += size] = val; p >>= 1;)
			tree[p] = monoid.op(tree[p << 1], tree[p << 1 | 1]);
	}
};
//! end segtree

//! snippet monoidapply
template<typename T, typename U>
struct MonoidApply {
	virtual T op(U fn, T val) = 0;
};
//! end monoidapply

//! snippet segtreelazy
//! use monoid
//! use monoidapply
template<typename T, typename MT, typename U, typename MU, typename F,
	typename = enable_if<is_base_of<Monoid<T>, MT>::value>,
	typename = enable_if<is_base_of<Monoid<U>, MU>::value>,
	typename = enable_if<is_base_of<MonoidApply<T, U>, F>::value>>
struct SegTreeLazy {
	MU monoid_u;
	MT monoid_t;
	F apply;
	int size;
	vector<T> tree;
	vector<U> lazy;

	SegTreeLazy(int size, MT monoid_t, MU monoid_u, F apply) : size(size), monoid_t(monoid_t), monoid_u(monoid_u), apply(apply) {
		tree = vector<T>(size * 4, monoid_t.id);
		lazy = vector<U>(size * 4, monoid_u.id);
	}

	SegTreeLazy(vector<T> vals, MT monoid_t, MU monoid_u, F apply) : size(vals.size()), monoid_t(monoid_t), monoid_u(monoid_u), apply(apply) {
		tree = vector<T>(size * 4, monoid_t.id);
		lazy = vector<U>(size * 4, monoid_u.id);
		_build(1, 0, vals.size() - 1, vals);
	}

	void _build(int id, int l, int r, const vector<T>& vals) {
		if (l == r) {
			tree[id] = vals[l];
			return;
		}
	
		int m = l + r >> 1;
		_build(id << 1, l, m, vals);
		_build(id << 1 | 1, m + 1, r, vals);
		tree[id] = monoid_t.op(tree[id << 1], tree[id << 1 | 1]);
	}
	
	void _pushdown(int id) {
		lazy[id << 1] = monoid_u.op(lazy[id], lazy[id << 1]);
		lazy[id << 1 | 1] = monoid_u.op(lazy[id], lazy[id << 1 | 1]);
		lazy[id] = monoid_u.id;
		_recalc(id);
	}

	T _query(int id, int l, int r, int tl, int tr) {
		if (l == tl && r == tr) {
			return apply.op(lazy[id], tree[id]);
		}

		int tm = tl + tr >> 1;
		_pushdown(id);
		if (r <= tm)
			return _query(id << 1, l, r, tl, tm);
		else if (l > tm)
			return _query(id << 1 | 1, l, r, tm + 1, tr);
		else
			return monoid_t.op(
					_query(id << 1, l, tm, tl, tm),
					_query(id << 1 | 1, tm + 1, r, tm + 1, tr));
	}

	T query(int l, int r) {
		return _query(1, l, r, 0, size - 1);
	}

	void _recalc(int id) {
		tree[id] = monoid_t.op(
				apply.op(lazy[id << 1], tree[id << 1]), 
				apply.op(lazy[id << 1 | 1], tree[id << 1 | 1]));
	}	

	void _update(int id, int l, int r, int tl, int tr, U val) {
		if (l == tl && r == tr) {
			lazy[id] = monoid_u.op(val, lazy[id]);
			return;
		}
		
		_pushdown(id);
		int tm = tl + tr >> 1;
		if (r <= tm)
			_update(id << 1, l, r, tl, tm, val);
		else if (l > tm)
			_update(id << 1 | 1, l, r, tm + 1, tr, val);
		else
			_update(id << 1, l, tm, tl, tm, val),
			_update(id << 1 | 1, tm + 1, r, tm + 1, tr, val);

		_recalc(id);
	}

	void update(int l, int r, U val) {
		_update(1, l, r, 0, size - 1, val);
	}
};
//! end segtreelazy

//! snippet bs
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
//! end
