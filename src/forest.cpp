#include <bits/stdc++.h>

using namespace std;

// {{{ Reading

char *buf;

inline void read_all() {
    size_t len = (size_t) 1e6, read_len = 0;
    do {
        buf = (char *) realloc(buf, (size_t) len * 2);
        read_len += fread(buf + read_len, 1, len, stdin);
        len *= 2;
    } while (! feof(stdin));
    *(buf + read_len) = 0;
}

inline void get(int &x) {
    x = (int) strtol(buf, &buf, 0);
}

// }}}

// {{{ Data & types
const int __ = 166666, inf = (int) 1e9;

int n, m, maxn[__], val[__], par[__], c[__][2], rev[__];

struct Edge {
    int u, v, a, b;
} edges[__];

bool operator<(const Edge &x, const Edge &y) {
    return x.a < y.a;
}
// }}}

// {{{ Union-find

int ulink[__];

int ufind(int x) {
    int root;
    for (root = x; root[ulink]; root = root[ulink]);
    for (int k; x[ulink]; k = x[ulink], x[ulink] = root, x = k);
    return root;
}
// }}}

// {{{ Utilities
bool is_sp(int x) {
    return x[par][c][0] == x || x[par][c][1] == x;
}

int flag(int x) {
    return x[par][c][1] == x;
}

Edge get_edge() {
    Edge x;
    get(x.u);
    get(x.v);
    get(x.a);
    get(x.b);
    return x;
}

// }}}

// {{{ Splay

void update(int x) { 
    x[maxn] = x;
    if (x[c][0][maxn][val] > x[maxn][val]) maxn[x] = maxn[c[x][0]];
    if (x[c][1][maxn][val] > x[maxn][val]) maxn[x] = maxn[c[x][1]];
}

void pass(int x) {
    if (x[rev]) {
        swap(x[c][0], x[c][1]);
        x[c][0][rev] ^= 1;
        x[c][1][rev] ^= 1;
        x[rev] = 0;
    }
}

void pass_all(int x) {
    if (is_sp(x)) pass_all(x[par]);
    pass(x);
}

void rotate(int x) {
    int k = flag(x), p = x[par], g = p[par], r = x[c][! k];

    if (is_sp(p)) g[c][flag(p)] = x;
    x[par] = g;
    x[c][! k] = p;
    p[par] = x;
    p[c][k] = r;
    if (r) r[par] = p;
    update(p);
}

void splay(int x) {
    pass_all(x);
    for (; is_sp(x); rotate(x))
        if (is_sp(x[par])) {
            if (flag(x) == flag(x[par]))
                rotate(x[par]);
            else
                rotate(x);
        }
    update(x);
}

// }}}

// {{{ Link/cut tree
void access(int x) {
    splay(x);
    x[c][1] = 0;
    update(x);
    if (x[par]) {
        access(x[par]);
        x[par][c][1] = x;
        update(x[par]);
        rotate(x);
    }
}

void make_root(int x) {
    access(x);
    splay(x);
    x[rev] ^= 1;
}

void link(int x, int y) {
    make_root(x);
    x[par] = y;
}

void cut(int x, int y) {
    make_root(x);
    access(y);
    splay(y);
    c[y][0] = par[x] = 0;
}

int query(int x, int y) {
    make_root(x);
    access(y);
    splay(y);
    return maxn[y];
}
// }}}

// {{{ Main

int main() {
    read_all();
    get(n);
    get(m);
    generate_n(edges + 1, m, get_edge);
    sort(edges + 1, edges + 1 + m);

    for (int i = 1; i <= m; i ++) {
        val[n + i] = edges[i].b;
        maxn[n + i] = n + i;
    }

    int ans = inf;

    for (int i = 1; i <= m; i ++) {
        const Edge &e = edges[i];
        int p = ufind(e.u), q = ufind(e.v);
        if (p == q) {
            int t = query(e.u, e.v);
            if (edges[i].b < val[t]) {
                cut(edges[t - n].u, t);
                cut(edges[t - n].v, t);
                link(e.u, n + i);
                link(e.v, n + i);
            }
        } else {
            ulink[p] = q;
            link(e.u, n + i);
            link(e.v, n + i);
        }
        if (ufind(1) == ufind(n))
            ans = min(ans, val[query(1, n)] + edges[i].a);
    }
    printf("%d\n", ans == inf ? - 1 : ans);
    return 0;
}

// }}}

// vim: sw=4 ts=4 et
