#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
using namespace std;

struct T {
  int prio, val;
  T *lc, *rc;

  T(int v, T *l, T *r): prio(rand()), val(v), lc(l), rc(r) {}
  T() {}
} tpool[(int)5e5], *ptop = tpool;

// new(ptop ++) T(v, l, r)

T* merge(T *x, T *y) {
  if(x && y) {
    if(x->prio > y->prio) {
      x->rc = merge(x->rc, y);
      return x;
    } else {
      y->lc = merge(x, y->lc);
      return y;
    }
  } else {
    return x ?: y;
  }
}

void split(int k, T *x, T **a, T **b) {
  if(x) {
    if(k > x->val) {
      split(k, x->rc, &x->rc, b);
      *a = x;
    } else {
      split(k, x->lc, a, &x->lc);
      *b = x;
    }
  } else {
    *a = *b = 0;
  }
}

int main() {
  T *root = 0;

  int n;

  scanf("%d", &n);

  int ans = 0;
  while(n --) {
    int m;
    m = 0;
    scanf("%d", &m);

    T *a, *b;
    split(m, root, &a, &b);

    int mnv = 20000000;

    if(a) {
      T *x;
      for(x = a; x->rc; x = x->rc);
      mnv = min(mnv, m - x->val);
    }

    if(b) {
      T *x;
      for(x = b; x->lc; x = x->lc);
      mnv = min(mnv, x->val - m);
    }

    ans += !(a || b) ? m : mnv;

    a = merge(a, new(ptop++) T(m, 0, 0));
    root = merge(a, b);
  }

  printf("%d\n", ans);
  return 0;
}
