#ifndef _TEMPLATE_VECTOR
#define _TEMPLATE_VECTOR

#include "root.h"

template<class T, int S>
struct GVector {
	T val[S];
	
	GVector() { rep(i, 0, S) val[i] = 0; }
	GVector(array<T, S> init_val) { rep(i, 0, S) val[i] = init_val[i]; }

	GVector& operator+=(GVector v) { rep(i, 0, S) val[i] += v.val[i]; return *this; }
	GVector& operator-=(GVector v) { rep(i, 0, S) val[i] -= v.val[i]; return *this; }
	GVector& operator*=(T v) { rep(i, 0, S) val[i] *= v; return *this; }
	GVector& operator/=(T v) { rep(i, 0, S) val[i] /= v; return *this; }

	GVector operator+(GVector v) { GVector<T, S> tmp(*this); return tmp += v; }
	GVector operator-(GVector v) { GVector<T, S> tmp(*this); return tmp -= v; }
	GVector operator*(T v) { GVector<T, S> tmp(*this); return tmp *= v; }
	GVector operator/(T v) { GVector<T, S> tmp(*this); return tmp /= v; }

	double norm2() { double r = 0; rep(i, 0, S) r += val[i] * val[i]; return r; }
	double norm() { return sqrt(norm2()); }	
	
	GVector unit() { double scale = norm(); return scale == 0.0 ? *this : (*this / scale); }

	friend istream& operator>>(istream &is, GVector &v) {
		rep(i, 0, S) is >> v.val[i];
		return is;
	}
	friend ostream& operator<<(ostream &os, const GVector& v) {
		rep(i, 0, S - 1) os << v.val[i] << ' ';
		os << v.val[S - 1];
		return os;
	}
};

using Vector2 = GVector<double, 2>;
using Vector3 = GVector<double, 3>;

#endif
