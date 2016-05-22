#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 5e5;

#define MS(t) ((t) ? (t)->size : 0)

struct Splay
{
  Splay *c[2], *parent;
  int val, size, lazy;

  inline void maintain()
  { size = MS(c[0]) + 1 + MS(c[1]); }

  inline void pass()
  {
    if(! this) return;
    if(lazy)
      {
	lazy = 0;
	swap(c[0], c[1]);
	if(c[0]) c[0]->lazy ^= 1;
	if(c[1]) c[1]->lazy ^= 1;
      }
  }

  inline int flag() { return parent->c[1] == this; }

  inline void rotate()
  {
    int k = flag();
    Splay *p = parent, *g = p->parent, *r = c[k^1];
    int m = g ? p->flag() : -1;
    parent = g;
    if(g) g->c[m] = this;
    c[k^1] = p;
    p->parent = this;
    p->c[k] = r;
    if(r) r->parent = p;
    p->maintain();
    maintain();
  }

  void splay()
  {
    for(; parent; rotate())
      if(parent->parent && flag() == parent->flag())
	parent->rotate();
  }

  Splay* find(int pos)
  {
    Splay *x = this;

    x->pass();

    while(pos != MS(x->c[0]))
      {
	if(pos < MS(x->c[0]))
	  x = x->c[0];
	else
	  pos -= MS(x->c[0]) + 1, x = x->c[1];

	x->pass();
      }

    x->splay();

    return x;
  }
} *pool = new Splay[MAXN], *ptop = pool, *root;

inline Splay* alloc() { return ptop ++; }

inline void construct(int tot)
{
  for(int i = 1; i <= tot; i ++) pool[i].val = i-1, pool[i].size = 1;
  for(int i = 1; i <  tot; i ++) pool[i].c[0] = 0, pool[i].c[1] = pool+i+1;
  for(int i = 2; i <= tot; i ++) pool[i].parent = pool+i-1;
  for(int i = tot; i >= 1; i --) pool[i].maintain();
  root = pool+1;
}

inline void FLIP(int m, int n)
{
  if(n <= m) return;
  root = root->find(m-1);
  root->c[1]->parent = 0;
  root->c[1] = root->c[1]->find(n-m+1);
  root->c[1]->parent = root;
  root->c[1]->c[0]->lazy ^= 1;
}

inline void CUT(int m, int n, int k)
{
  FLIP(m, n);
  if(k >= m)
    FLIP(n+1, n-m+k+1), FLIP(m, n-m+k+1);
  else
    FLIP(k+1, m-1), FLIP(k+1, n);
}

int main()
{
  while(true)
    {
      memset(pool, 0, sizeof(Splay)*MAXN);
      int N, Q;
      scanf("%d %d", &N, &Q);
      if(N < 0 && Q < 0) return 0;
      construct(N+3);
      while(Q --)
	{
	  char s[6];
	  int a, b, c;
	  scanf("%s%d%d", s, &a, &b);
	  if(s[0] == 'C') 	// CUT
	    {
	      scanf("%d", &c);
	      CUT(a, b, c);
	    }
	  else 			// FLIP
	    FLIP(a, b);
	}

      for(int i = 1; i <= N; i ++)
	{
	  root = root->find(i);
	  printf(i == N ? "%d" : "%d ", root->val);
	}
      puts("");
    }
}
