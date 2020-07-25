#ifndef _TEMPLATE_SEGTREE_LAZY
#define _TEMPLATE_SEGTREE_LAZY

#include "root.h"
#include "monoid.h"
#include "monoidapply.h"

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

#endif
