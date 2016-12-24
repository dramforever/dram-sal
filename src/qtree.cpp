#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <memory>
using namespace std;

const int Size = 100000, inf = 3000000;

int N;

struct Edge {
    int v, len, eid;
    Edge *next;

    Edge (int v, int len, int eid, Edge *next):
        v (v), len (len), eid (eid), next (next) {}

    Edge () {}
};

Edge *pool = new Edge [Size];
Edge *head [Size];

void addedge (int u, int v, int len, int eid) {
    head [u] = new (pool ++) Edge (v, len, eid, head [u]);
    head [v] = new (pool ++) Edge (u, len, eid, head [v]);
}

int parent[Size], top[Size], ix[Size], ixv[Size];
int depth[Size], size[Size], val[Size], edgenode[Size];

void dfs1 (int x, int from = 0, int dep = 0, Edge *fromedge = 0) {
    x [parent] = from;
    x [depth] = dep;

    if (fromedge) {
        fromedge->eid [edgenode] = x;
        x [val] = fromedge->len;
    }

    int mysize = 1;

    for (Edge *e = head [x]; e; e = e->next)
        if (e->v != from) {
            dfs1 (e->v, x, dep + 1, e);
            mysize += e->v [size];
        }

    x [size] = mysize;
}

int ixtop;

void dfs2 (int x, int from = 0, int tp = 1) {
    x [ix] = ++ ixtop;
    x [ix] [ixv] = x [val];
    x [top] = tp;

    int maxson = 0;

    for (Edge *e = head [x]; e; e = e->next)
        if (e->v != from
            && (maxson == 0 || e->v [size] > maxson [size]))
            maxson = e->v;

    if (maxson) {
        dfs2 (maxson, x, tp);
        for (Edge *e = head [x]; e; e = e->next)
            if (e->v != from && e->v != maxson)
                dfs2 (e->v, x, e->v);
    }
}

typedef pair<int, int> pii;

pii* decompose (int a, int b, pii *out) {
    while (a [top] != b [top]) {
        if (a [top] [depth] < b [top] [depth]) swap (a, b);

        *(out ++) = pii (a [top] [ix], a [ix]);
        a = a [top] [parent];
    }
    if (a [depth] < b [depth]) swap (a, b);
    if (a != b) *(out ++) = pii (b [ix] + 1, a [ix]);
    return out;
}

int tr [Size], Len;

void buildtree () {
    Len = 1;
    while (Len <= N) Len <<= 1;
    for (int i = 0; i < Len; i ++)
        tr [Len | i] = - inf;
    for (int i = 1; i <= N; i ++)
        tr [Len | i] = ixv [i];
    for (int i = Len - 1; i; i --)
        tr [i] = max (tr [i << 1], tr [i << 1 | 1]);
}

int query (int l, int r) {
    int res = -inf;
    for (
        int x = Len | (l - 1), y = Len | (r + 1);
        (x ^ y) != 1; x >>= 1, y >>= 1) {
        if (~x&1) res = max (res, tr [x^1]);
        if ( y&1) res = max (res, tr [y^1]);
    }
    return res;
}

void update (int pos, int newv) {
    tr [Len | pos] = newv;
    for (int x = (Len | pos) >> 1; x; x >>= 1)
        tr [x] = max (tr [x << 1], tr [x << 1 | 1]);
}

void CHANGE (int a, int b) {
    update (a [edgenode] [ix], b);
}

pii ops [2000];

void QUERY (int a, int b) {
    pii *top = decompose (a, b, ops);
    int res = - inf;
    for (pii *x = ops; x != top; x ++)
        res = max (res, query (x->first, x->second));
    printf ("%d\n", res);
}

void reset () {
    // TODO init graph
    ixtop = 0;
    memset (pool, 0, sizeof(Edge) * Size);
#define clear(x) memset (x, 0, sizeof(x))
    clear(head); clear(parent); clear(top);
    clear(ix); clear(depth); clear(size);
    clear(val); clear(edgenode);
    clear(tr);
#undef clear
}

int main () {
    int T;
    scanf ("%d", &T);
    Edge *origpool = pool;
    while (T --) {
        pool = origpool;
        reset ();
        scanf ("%d", &N);
        for (int i = 1; i <= N - 1; i ++) {
            int u, v, l;
            scanf ("%d%d%d", &u, &v, &l);
            addedge (u, v, l, i);
        }
        dfs1 (1);
        dfs2 (1);
        buildtree ();
        char cmd [20];
        while (true) {
            scanf ("%s", cmd);
            if (cmd[0] == 'D') // DONE
                break;
            else {
                int a, b;
                scanf ("%d%d", &a, &b);
                if (cmd[0] == 'Q') QUERY (a, b);
                else CHANGE (a, b);
            }
        }
    }
    return 0;
}
