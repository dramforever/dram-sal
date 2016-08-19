#include <bits/stdc++.h>
using namespace std ;

int n, m ;
const int __ = (int) 2e5, __t = (int) 3e6;

// {{{ Chair Tree
struct psgt {
    int val;
    psgt *lc, *rc;

    psgt (): val (0), lc (this), rc (this) {}
    psgt (int v, psgt *l, psgt *r): val (v), lc (l), rc (r) {}

    inline int lcv () { return lc->val; }

    psgt* insert (int pos, int delt, int lb, int rb);
} *sg_pool = new psgt [__t];

psgt* psgt::insert (int pos, int delt, int lb, int rb) {
    psgt *clone = new (sg_pool ++) psgt (*this);
    clone->val += delt;

    if (lb != rb) {
        int mid = (lb + rb) >> 1;
        if (pos <= mid) clone->lc = clone->lc->insert (pos, delt, lb, mid);
        else            clone->rc = clone->rc->insert (pos, delt, mid + 1, rb);
    }

    return clone;
}

int get_kth (psgt *u_t, psgt *v_t, psgt *lc_t, psgt *plc_t, int k, int lb, int rb) {
    while (lb != rb) {
        int mid = (lb + rb) >> 1;
        int t = u_t->lcv() + v_t->lcv() - lc_t->lcv() - plc_t->lcv();

        if (k <= t) {
            u_t = u_t->lc, v_t = v_t->lc, lc_t = lc_t->lc, plc_t = plc_t->lc ;
            rb = mid;
        } else {
            u_t = u_t->rc, v_t = v_t->rc, lc_t = lc_t->rc, plc_t = plc_t->rc;
            k -= t; lb = mid+1;
        }
    }
    return lb;
}
// }}}

int vals [__], fixvals [__], recover [__], ixs [__], mxfix;

// {{{ LCA
struct Edge {
    int to;
    Edge *next;

    Edge () {}
    Edge (int t, Edge *x): to (t), next (x) {}
} *epool = new Edge [__], *head [__];

void link (int u, int v) {
    head [u] = new (epool ++) Edge (v, head[u]);
    head [v] = new (epool ++) Edge (u, head[v]);
}

psgt *treeno [__];
int jmp [__] [30], depth [__] ;

void dfs (int u, int from = 0) {
    depth [u] = depth [from] + 1 ;
    jmp [u] [0] = from;
    treeno [u] = treeno [from]->insert (fixvals [u], 1, 1, mxfix);
    for (Edge *e = head [u]; e; e = e->next)
        if (e->to != from) dfs (e->to, u);
}

void start_dfs () {
    treeno [0] = new (sg_pool ++) psgt ();
    dfs (1);
}

void fill_jmp (int n) {
    for (int lg = 1; lg <= 25; lg ++)
        for (int i = 1; i <= n; i ++)
            i [jmp] [lg] = i [jmp] [lg-1] [jmp] [lg-1];
}

int query_lca (int u, int v) {
    if ( depth [u] < depth [v] ) swap (u, v);

    int dd = depth [u] - depth [v];
    for (int lg = 25; lg >= 0; lg --)
        if ( dd & (1 << lg) ) u = u [jmp] [lg];

    if (u == v) return u;

    for (int lg = 25; lg >= 0; lg --)
        // TODO Is the first check required?
        if ( u [jmp] [lg] != 0 && u [jmp] [lg] != v [jmp] [lg] )
            u = u [jmp] [lg] , v = v [jmp] [lg];

    return u [jmp] [0];
}
// }}}

// {{{ Main
bool cmp (int i, int j) {
    return vals [i] < vals [j];
}
int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++)
        scanf ("%d", &vals [i]);
    for (int i = 1; i <= n; i ++)
        ixs [i] = i;
    sort (ixs + 1, ixs + 1 + n, cmp);
    int i;
    for (mxfix = 0, i = 1; i <= n; i ++) {
        mxfix += vals [ ixs [i] ] != vals [ ixs [i-1] ];
        fixvals [ ixs [i] ] = mxfix ;
        recover [ mxfix ] = vals [ ixs [i] ];
    }
    for (int i = 1; i <= n - 1; i ++) {
        int u, v; scanf ("%d%d", &u, &v);
        link (u, v);
    }

    start_dfs ();
    fill_jmp (n);
    int lastans = 0;
    while (m --) {
        int u, v, k;
        scanf ("%d%d%d", &u, &v, &k);
        u ^= lastans;
        int lc = query_lca (u, v);
        int ans = recover [ get_kth (treeno [u], treeno [v], treeno [lc], treeno [lc [jmp] [0]], k, 1, mxfix ) ];
        if (m == 0)
            printf ("%d", ans);
        else
            printf ("%d\n", ans);

        lastans = ans;
    }
}
// }}}

