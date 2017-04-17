/// -g
/// -Wall
#include <cstdio>
#include <cstring>
#include <vector>
#include <new>

const int zS = (int) 3e5, inf = 0x3333333;

using namespace std;

struct Edge
{
    int v, cap;
    Edge *next, *rev;

    Edge () {}
    Edge (int v_, int cap_, Edge *next_, Edge *rev_):
        v (v_), cap (cap_), next (next_), rev (rev_) {}
} *epool = new Edge[zS * 10], *head[zS];

void addedge (int u, int v, int c)
{
    Edge *e1 = epool ++, *e2 = epool ++;
    head[u] = new (e1) Edge (v, c, head[u], e2);
    head[v] = new (e2) Edge (u, 0, head[v], e1);
}

int level[zS];

int N, M;

int makelevel ()
{
    static int Q[zS];
    int *q0 = Q, *q1 = Q;
    memset (level, 0xff, sizeof (level));
    *(q1 ++) = N + M + 1;
    level[N + M + 1] = 1;
    while (q0 != q1)
    {
        int me = *(q0 ++);
        for (Edge *e = head[me]; e; e = e->next)
            if (e->cap && -1 == level[e->v])
            {
                level[e->v] = level[me] + 1;
                *(q1 ++) = e->v;
            }

        if (level[N + M + 2] != -1) return true;
    }
    return false;
}

int dfs (int u, int mx = inf)
{
    if (u == N + M + 2) return mx;

    int cur = 0;
    for (Edge *e = head[u]; e && mx > cur; e = e->next)
        if (level[e->v] == 1 + level[u] && e->cap)
        {
            int res = dfs (e->v, min (mx - cur, e->cap));
            cur += res;
            e->cap -= res;
            e->rev->cap += res;
        }

    return cur;
}

int dinic ()
{
    int total = 0;
    while (makelevel ()) total += dfs (N + M + 1);
    return total;
}

int main ()
{
    scanf ("%d%d", &N, &M);
    int total = 0;
    for (int val, i = 1; i <= N; i ++)
    {
        scanf ("%d", &val);
        addedge (i, N + M + 2, val);
    }
    for (int a, b, c, i = 1; i <= M; i ++)
    {
        scanf ("%d%d%d", &a, &b, &c);
        addedge (i + N, a, inf);
        addedge (i + N, b, inf);
        addedge (N + M + 1, i + N, c);
        total += c;
    }
    int res = dinic ();
    printf ("%d\n", total - res);
}
