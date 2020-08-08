#ifndef _TEMPLATE_IO
#define _TEMPLATE_IO

#include "root.h"

template<typename H> void read(H& head) { cin >> head; }
template<typename H, typename ...T> void read(H& head, T& ...tail) { cin >> head; read(tail...); }

template<typename H> void write(H head) { cout << head << '\n'; }
template<typename H, typename ...T> void write(H head, T ...tail) { cout << head << " "; write(tail...); }
template<typename ...T> void writef(T ...tail) { write(tail...); cout << flush; }

template<typename ...T> void die(T ...tok) { write(tok...); exit(0); }

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
  if (v.size()) {
    rep(i, 0, sz(v) - 1)
      out << v[i] << " ";
    out << v.back();
  }
  return out;
}

#endif
