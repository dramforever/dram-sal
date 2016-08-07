#include <bits/stdc++.h>

using namespace std;

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

const int __ = 166666, inf = (int) 1e9;

int n, m, maxn[__], val[__], par[__], c[__][2], rev[__];

struct Edge {
    int u, v, a, b;
} edges[__];

bool operator<(const Edge &x, const Edge &y) {
    return x.a < y.a;
}

int ulink[__];

int ufind(int x) {
    int root;
    for (root = x; ulink[root]; root = ulink[root]);
    for (int k; ulink[x]; k = ulink[x], ulink[x] = root, x = k);
    return root;
}

bool is_sp(int x) {
    return c[par[x]][0] == x || c[par[x]][1] == x;
}

void update(int x) {
    maxn[x] = x;
    if (val[maxn[c[x][0]]] > val[maxn[x]])
        maxn[x] = maxn[c[x][0]];
    if (val[maxn[c[x][1]]] > val[maxn[x]])
        maxn[x] = maxn[c[x][1]];
}

void pass(int x) {
    if (rev[x]) {
        swap(c[x][0], c[x][1]);
        rev[c[x][0]] = ! rev[c[x][0]];
        rev[c[x][1]] = ! rev[c[x][1]];
        rev[x] = 0;
    }
}

void pass_all(int x) {
    if (is_sp(x)) pass_all(par[x]);
    pass(x);
}

int flag(int x) {
    return c[par[x]][1] == x;
}

void rotate(int x) {
    int k = flag(x), p = par[x], g = par[p], r = c[x][! k];

    if (is_sp(p)) c[g][flag(p)] = x;
    par[x] = g;
    c[x][! k] = p;
    par[p] = x;
    c[p][k] = r;
    if (r) par[r] = p;
    update(p);
}

void splay(int x) {
    pass_all(x);
    for (; is_sp(x); rotate(x))
        if (is_sp(par[x])) {
            if (flag(x) == flag(par[x]))
                rotate(par[x]);
            else
                rotate(x);
        }
    update(x);
}

void access(int x) {
    splay(x);
    c[x][1] = 0;
    update(x);
    if (par[x]) {
        access(par[x]);
        c[par[x]][1] = x;
        update(par[x]);
        rotate(x);
    }
}

void make_root(int x) {
    access(x);
    splay(x);
    rev[x] = ! rev[x];
}

void link(int x, int y) {
    make_root(x);
    par[x] = y;
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

Edge get_edge() {
    Edge x;
    get(x.u);
    get(x.v);
    get(x.a);
    get(x.b);
    return x;
}

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
