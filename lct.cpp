#include <cstdio>

using namespace std;

const int MAXN = (int)5e4 + 10;

int c[MAXN][2], parent[MAXN], N;

inline int flag(int x) { return x[parent][c][1] == x; }

inline void rotate(int x)
{
  int k = flag(x);
  int p = x[parent], g = p[parent], r = x[c][k^1];
  int m = g > 0 ? flag(p) : 0;
  x[parent] = g; x[c][k^1] = p; if(g > 0) g[c][m] = x;
  p[parent] = x; p[c][k] = r;
  if(r) r[parent] = p;
}

inline void splay(int x)
{
  for(; x[parent] > 0; rotate(x))
    if(x[parent][parent] > 0 && flag(x) == flag(x[parent]))
      rotate(x[parent]);
}

inline void access(int x)
{
  splay(x);

  if(x[c][1])
    {
      x[c][1][parent] = -x;
      x[c][1] = 0;
    }
  
  while(x[parent] < 0)
    {
      int w = -x[parent];
      splay(w);
      if(w[c][1])
	w[c][1][parent] = -w;
      w[c][1] = x;
      x[parent] = w;
      x = w;
    }
}

int QUERY(int x)
{
  access(x);
  splay(x);
  while(x[c][0]) x = x[c][0];
  splay(x);
  return x;
}

void MOVE(int i, int j)
{
  if(i == j) return;
  
  if(j)
    {
      access(j);
      access(i);
      splay(j);
      if(j[parent] == -i) return;
    }

  access(i);
  splay(i);
  
  if(i[c][0]) i[c][0][parent] = 0, i[c][0] = 0;

  if(j)
    {
      access(j);
      splay(j);
      i[c][0] = j;
      j[parent] = i;
    }
}

int main()
{
  char cmd[10];
  bool flag = false;
  while(scanf("%d", &N) != EOF)
    {
      if(flag) puts("");
      else flag = true;
      
      for(int i = 1; i <= N; i ++)
	{
	  scanf("%d", &parent[i]);
	  parent[i] = -parent[i];
	  i[c][0] = i[c][1] = 0;
	}
      
      int Q;
      scanf("%d", &Q);
      while(Q --)
        {
	  scanf("%s", cmd);
	  if(*cmd == 'Q')
            {
	      int a;
	      scanf("%d", &a);
	      printf("%d\n", QUERY(a));
            }
	  else if(*cmd == 'M')
            {
	      int a, b;
	      scanf("%d%d", &a, &b);
	      MOVE(a, b);
            }
        }
    }
}
