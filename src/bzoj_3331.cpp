#include <cstdio>
#include <stack>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
const int zS = 3000000;

typedef pair<int, int> Edge;
typedef vector<Edge>::iterator Iter;

int dfn[zS], low[zS], ix, scix;
stack<int> S;

struct Graph {
    vector<Edge> edges;
    vector<Iter> head;

    Graph ()
    {
        edges.reserve (zS);
        head.reserve (zS);
    }

    void link (int u, int v)
    {
        edges.push_back (make_pair (u, v));
        edges.push_back (make_pair (v, u));
    }

    void process ()
    {
        sort (edges.begin (), edges.end ());
        Iter e = edges.begin ();
        for (int i = 0; e != edges.end (); i ++) {
            head.push_back (e);
            while (e != edges.end () && e->first == i) e ++;
        }
        head.push_back (edges.end ());
    }


    void tarjan (int t, int from = -1);
    void jumptable (int t, int from = 0, int dep = 1);

    void dump ()
    {
        printf ("Edges:\n");
        for (Iter e = edges.begin (); e != edges.end (); e ++)
            printf ("%d -> %d\n", e->first, e->second);
        printf ("head:\n");
        for (vector<Iter>::iterator h = head.begin (); h != head.end (); h ++)
            printf ("%d -> %d\n", h - head.begin(), *h - edges.begin ());
    }

    void xmpaint ()
    {
        printf ("-----\n");
        for (Iter e = edges.begin (); e != edges.end (); e ++)
            if (e->first <= e->second)
                printf ("%d %d\n", e->first, e->second);
        printf ("-----\n");
    }

    void distribute (int n, int from = 0);
    
} gr, trg;

void Graph::tarjan (int t, int from)
{
    ix ++;
    dfn[t] = low[t] = ix;

    S.push (t);

    for (Iter e = head[t]; e != head[t + 1]; e ++)
        if (e->second != from)    
        {
            if (dfn[e->second])
            {
                low[t] = min (low[t], dfn[e->second]);
            }
            else
            {
                tarjan (e->second, t);
                if (dfn[t] <= low[e->second])
                {
                    scix ++;
                   // printf ("%d at %d\n", scix, t);
                    for (; S.top () != e->second; S.pop ()) {
                        trg.link (S.top (), scix);
                    }
                    S.pop ();
                    trg.link (e->second, scix);
                    trg.link (t, scix);
                }
                low[t] = min (low[t], low[e->second]);            
            }
        }
}

int up[30][zS], depth[zS];

void Graph::jumptable (int t, int from, int dep)
{
    up[0][t] = from;
    depth[t] = dep;
    for (Iter e = head[t]; e != head[t + 1]; e ++)
        if (e->second != from)
        {
            jumptable (e->second, t, dep + 1);
        }
}

void tabulate (int num)
{
    trg.jumptable (1);
    for (int lg = 1; lg <= 25; lg ++)
        for (int i = 1; i <= num; i ++)
            lg[up][i] = (lg - 1)[up][(lg - 1)[up][i]];
}

int lca (int u, int v)
{
    if (depth[u] < depth[v]) return lca (v, u);
    else
    {
        for (int lg = 25; lg >= 0; lg --)
            if (lg[up][u][depth] >= v[depth])
            {
                u = lg[up][u];
            }
        for (int lg = 25; lg >= 0; lg --)
            if (lg[up][u] != lg[up][v])
            {
                u = lg[up][u];
                v = lg[up][v];
            }
        if (u != v) return 0[up][u];
        else return u;
    }
}

int mark[zS];

void Graph::distribute (int t, int from)
{
    for (Iter e = head[t]; e != head[t + 1]; e ++)
        if (e->second != from)
        {
            distribute (e->second, t);
            mark[t] += mark[e->second];
        }    
}

int main ()
{
    freopen ("in.txt", "r", stdin);
    int N, M, Q;
    scanf ("%d%d%d", &N, &M, &Q);
    for (int i = 1; i <= M; i ++)
    {
        int u, v;
        scanf ("%d%d", &u, &v);
        gr.link (u, v);
    }
    gr.link (N + 1, 1);
    gr.process ();
    //gr.dump ();
    scix = N + 1;
    gr.tarjan (N + 1);
    /*
    for (int i = 1; i <= N + 1; i ++)
        printf ("%d ", dfn[i]);
    puts ("");
    for (int i = 1; i <= N + 1; i ++)
        printf ("%d ", low[i]);
    puts ("\n^^^");
    */
    trg.process ();
    //trg.xmpaint ();
    tabulate (scix);
    while (Q --)
    {
        int u, v;
        scanf ("%d%d", &u, &v);
        mark[u] ++;
        mark[v] ++;
        int lc = lca (u, v);
        mark[lc] --;
        if (0[up][lc])
        {
            mark[0[up][lc]] --;
        }
    }
    trg.distribute (1);
    /*
    for (int i = 1; i <= scix; i ++)
    {
        printf ("%4d | ", i);
        for (int lg = 0; lg <= 5; lg ++)
            printf (" %d", up[lg][i]);
        puts ("");
    }*/
    for (int i = 1; i <= N; i ++)
        printf ("%d\n", mark[i]);
}
