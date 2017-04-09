#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int __ = (int)2e6;

// {{{ Tree
struct Edge
{
    int to, len;
    Edge *next;

    inline
    Edge () {}

    inline
    Edge (int to_, int len_, Edge *next_) :
        to (to_), len (len_), next (next_) {}
} *epool = new Edge[__], *head[__];

inline
void connect (int u, int v, int len)
{
    head[u] = new (epool ++) Edge (v, len, head[u]);
    head[v] = new (epool ++) Edge (u, len, head[v]);
}
// }}}

// {{{ Generation
struct node
{
    int *x1, *x2, *lim;

    // Precondition: x1 <= lim, x2 <= lim
    inline
    node (int *x1_, int *x2_, int *lim_) :
        x1 (x1_), x2 (x2_), lim (lim_) {}

    inline
    int get () const
    { return *x1 + *x2; }

    inline
    bool valid () const
    { return x1 != lim && x2 != lim; }
};

inline
bool operator< (const node &a, const node &b)
{ return a.get () < b.get (); }

typedef priority_queue<node> pqn;

inline
void add (pqn &x, const node &A)
{ if (A.valid ()) x.push (A); }

inline
void step (pqn &x)
{
    node z = x.top (); x.pop ();
    if (z.x1 == z.x2)
        add (x, node (z.x1 + 1, z.x2 + 1, z.lim));
    add (x, node (z.x1, z.x2 + 1, z.lim));
}

pqn qins, qdel;

int get_next ()
{
    while (! qdel.empty () && qins.top().get() == qdel.top().get())
    { step (qins); step (qdel); }

    int res = qins.top().get();
    step (qins);
    return res;
}
// }}}

// {{{ Divide & Conquer
int *Mem = new int[(int) 1e7];
int kill[__];
int size[__];

void dfs_size (int x, int par = -1)
{
    size[x] = 1;
    for (Edge *e = head[x]; e; e = e->next)
        if (! kill[e->to] && par != e->to)
        {
            dfs_size (e->to, x);
            size[x] += size[e->to];
        }
}

int find_c (int x)
{
    dfs_size (x);
    int size_lim = size[x] / 2;
    int par = -1;
    while (true)
    {
        for (Edge *e = head[x]; e; e = e->next)
            if (! kill[e->to]
                    && par != e->to
                    && size[e->to] > size_lim)
            {
                par = x;
                x = e->to;
                goto fail;
            }
        return x;

        fail:;
    }
}

int *dfs_depth (int x, int *out, int dep = 0, int par = -1)
{
    for (Edge *e = head[x]; e; e = e->next)
        if (! kill[e->to] && par != e->to)
            out = dfs_depth (e->to, out, dep + e->len, x);

    *(out ++) = dep;

    return out;
}

void d_c (int r)
{
    int x = find_c (r);

    int *z = Mem;
    Mem = dfs_depth (x, z);
    sort (z, Mem, std::greater<int>());
    qins.push (node (z, z, Mem));

    for (Edge *e = head[x]; e; e = e->next)
        if (! kill[e->to])
        {
            int *z = Mem;
            Mem = dfs_depth (e->to, z, e->len, x);
            sort (z, Mem, std::greater<int>());
            qdel.push (node (z, z, Mem));
        }

    kill [x] = 1;
    for (Edge *e = head[x]; e; e = e->next)
        if (! kill[e->to]) d_c (e->to);
}
// }}}

// {{{ Main
int main ()
{
    int N, M;
    scanf ("%d%d", &N, &M);
    for (int i = 1; i <= N - 1; i ++)
    {
        int a, b, c;
        scanf ("%d%d%d", &a, &b, &c);
        connect (a, b, c);
    }

    d_c (1);

    while (M --) printf ("%d\n", get_next ());
}
// }}}

