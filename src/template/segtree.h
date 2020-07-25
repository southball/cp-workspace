#ifndef _TEMPLATE_SEGTREE
#define _TEMPLATE_SEGTREE

#include "root.h"
#include "monoid.h"

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
		tree = vector<T>(2 * size, monoid.id);
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

#endif
