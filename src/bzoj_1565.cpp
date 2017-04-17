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

int source, sink;

void addedge (int u, int v, int c)
{
    //printf ("%d %d %d\n", u, v, c);
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
    *(q1 ++) = source;
    level[source] = 1;
    while (q0 != q1)
    {
        int me = *(q0 ++);
        for (Edge *e = head[me]; e; e = e->next)
            if (e->cap && -1 == level[e->v])
            {
                level[e->v] = level[me] + 1;
                *(q1 ++) = e->v;
            }

        if (level[sink] != -1) return true;
    }
    return false;
}

int dfs (int u, int mx = inf)
{
    if (u == sink) return mx;

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
    while (makelevel ()) total += dfs (source);
    return total;
}

int score[zS], degree[zS];
vector<int> edges[zS];

int main ()
{
    scanf ("%d%d", &N, &M);
    for (int i = 1; i <= N * M; i ++)
    {
        int num;
        scanf ("%d%d", &score[i], &num);
        if (i % M != 1)
        {
            edges[i].push_back (i - 1);
            //printf ("%d %d\n", i, i - 1);
            degree[i - 1] ++;
        }
        for (int r, c, j = 1; j <= num; j ++)
        {
            scanf ("%d%d", &r, &c);
            edges[i].push_back (r * M + c + 1);
            //printf ("%d %d\n", i, r * M + c + 1);
            degree[r * M + c + 1] ++;
        }
    }

    static int Q[zS];
    int *q0 = Q, *q1 = Q;
    source = N * M + 1;
    sink = N * M + 2;
    
    int ans = 0;

    for (int i = 1; i <= N * M; i ++)
    {
        if (degree[i] == 0) *(q1 ++) = i;
    }

    while (q0 != q1)
    {
        int me = *(q0 ++);
        //printf ("# %d\n", me);
        if (score[me] > 0)
        {
            addedge (source, me, score[me]);
            ans += score[me];
        }
        else
        {
            addedge (me, sink, -score[me]);
        }

        for (vector<int>::iterator pv = edges[me].begin(); pv != edges[me].end(); pv ++)
        {
            addedge (*pv, me, inf);
            degree[*pv] --;
            if (degree[*pv] == 0)
            {
                *(q1 ++) = *pv;
            }
        }
    }
    ans -= dinic();
    printf ("%d\n", ans);
}
