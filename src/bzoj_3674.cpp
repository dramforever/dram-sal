#include <bits/stdc++.h>
using namespace std;

const int __ (2e5 + 7), __p (1e7 + 7);

struct pnode {
    union {
        int val;
        pnode *c[2];
    } x;

    pnode () {}
    pnode (int lb, int rb);

    int get (int ix, int lb, int rb);
    pnode* set (int ix, int val, int lb, int rb);
} * node_pool = new pnode[__p];

pnode::pnode (int lb, int rb) {
    if (lb == rb) x.val = 0;
    else {
        int mid = (lb + rb) >> 1;
        x.c[0] = new (node_pool ++) pnode (lb, mid);
        x.c[1] = new (node_pool ++) pnode (mid + 1, rb);
    }
}

int pnode::get (int ix, int lb, int rb) {
    if (lb == rb) return x.val;
    else {
        int mid = (lb + rb) >> 1;
        if (ix <= mid) return x.c[0]->get(ix, lb, mid);
        else           return x.c[1]->get(ix, mid + 1, rb);
    }
}

pnode* pnode::set (int ix, int val, int lb, int rb) {
    pnode *dup = new (node_pool ++) pnode (*this);
    if (lb == rb) dup->x.val = val;
    else {
        int mid = (lb + rb) >> 1;
        if (ix <= mid) dup->x.c[0] = dup->x.c[0]->set(ix, val, lb, mid);
        else           dup->x.c[1] = dup->x.c[1]->set(ix, val, mid + 1, rb);
    }
    return dup;
}

pnode *ranks [__], *pars [__];

int n, m;

int find (pnode *ps, int x) {
    int px ;
    if ( (px = ps->get(x, 1, n)) ) return find(ps, px);
    else return x;
}

void onion(int i, int x, int y) {
    x = find (pars [i], x);
    y = find (pars [i], y);
    if (x != y) {
        int rx = ranks [i]->get (x, 1, n), ry = ranks [i]->get (y, 1, n);
        if (rx > ry) swap (x, y);
        pars [i] = pars [i]->set (x, y, 1, n);
        if (rx == ry) ranks [i] = ranks [i]->set (y, rx + 1, 1, n);
    }
}

int main () {
    scanf ("%d%d", &n, &m);
    pars [0] = new (node_pool ++) pnode(1, n);
    ranks [0] = new (node_pool ++) pnode(1, n);
    int lastans = 0;
    for (int i = 1; i <= m; i ++) {
        int ty; scanf ("%d", &ty);
        pars [i] = pars [i-1];
        ranks [i] = ranks [i-1];
        if (ty == 1) {
            int u, v; scanf ("%d%d", &u, &v);
            u ^= lastans; v ^= lastans;
            onion (i, u, v);
        } else if (ty == 2) {
            int k; scanf ("%d", &k);
            k ^= lastans;
            pars [i] = pars [k];
            ranks [i] = ranks [k];
        } else {
            int u, v; scanf("%d%d", &u, &v);
            printf ("%d\n", lastans = find (pars [i], u) == find(pars [i], v));
        }
    }
    return 0;
}
