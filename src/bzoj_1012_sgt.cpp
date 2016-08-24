#include <bits/stdc++.h>
using namespace std;

const int __ (1e6);

int v[__];


inline int lc (int u) { return u << 1; }
inline int rc (int u) { return lc (u) | 1; }

inline void update (int u) {
    v [u] = max (v [lc (u)], v [rc (u)]);
}

void change (int pos, int val, int id, int lb, int rb) {
    if (lb == rb) v [id] = val;
    else {
        int mid = (lb + rb) >> 1;
        if (pos <= mid) change (pos, val, lc (id), lb, mid);
        else change (pos, val, rc (id), mid + 1, rb);
        update (id);
    }
}

int query (int l, int r, int id, int lb, int rb) {
    if (lb == l && rb == r) return v [id];
    else {
        int mid = (lb + rb) >> 1;
        if (r <= mid) return query (l, r, lc (id), lb, mid);
        else if (l > mid) return query (l, r, rc (id), mid + 1, rb);
        else return max(
                query (l, mid, lc (id), lb, mid),
                query (mid + 1, r, rc (id), mid + 1, rb));
    }
}

int main () {
    int m, D;
    scanf ("%d%d", &m, &D);
    int top = 0, lastans = 0;
    for (int i = 1; i <= m; i ++) {
        char cmd; scanf (" %c", &cmd);
        if (cmd == 'A') {
            top ++;
            int val; scanf ("%d", &val);
            val += lastans; val %= D;
            change (top, val, 1, 1, m);
        } else {
            int l; scanf ("%d", &l);
            printf ("%d\n", lastans = query (top - l + 1, top, 1, 1, m));
        }
    }
}
