#define $ if (0)
#include <bits/stdc++.h>
using namespace std;

const int __ (3e6);

int mxv [__], lazy [__];

inline int lc (int id) { return id << 1; }
inline int rc (int id) { return lc (id) | 1; }

void update (int id) {
    mxv [id] = max (mxv [lc (id)], mxv [rc (id)]);
}

void apply (int id, int laz) {
    mxv [id] += laz;
    lazy [id] += laz;
}

void pass (int id) {
    apply (lc (id), lazy [id]);
    apply (rc (id), lazy [id]);
    lazy [id] = 0;
}

void change (int l, int r, int delt, int id, int lb, int rb) {
    if (l == lb && r == rb) apply (id, delt);
    else {
        int mid = (lb + rb) >> 1;
        pass (id);
        if (l > mid) change (l, r, delt, rc (id), mid + 1, rb);
        else if (r <= mid) change (l, r, delt, lc (id), lb, mid);
        else {
            change (l, mid, delt, lc (id), lb, mid);
            change (mid + 1, r, delt, rc (id), mid + 1, rb);
        }
        update (id);
    }
}

int vals[__], rls[__], rrs[__];

pair<int, int> rgs[__];

bool cmp(pair<int, int> a, pair<int, int> b) {
    return (a.second - a.first) < (b.second - b.first);
}

int main () {
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++) {
        scanf ("%d%d", &rgs[i].first, &rgs[i].second);
    }
    sort (rgs + 1, rgs + n + 1, cmp);
    $ for (int i = 1; i <= n; i ++) {
        printf ("(%d %d)\n", rgs[i].first, rgs[i].second);
    }

    for (int i = 1; i <= n; i ++) {
        rls[i] = rgs[i].first; rrs[i] = rgs[i].second;
        vals[2*i-1] = rls[i]; vals[2*i] = rrs[i];
    }
    sort (vals + 1, vals + n + n + 1);
    int *last = unique (vals + 1, vals + n + n + 1) ;
    $ printf ("%ld\n", last - vals);
    for (int i = 1; i <= n; i ++) {
        rls[i] = lower_bound (vals + 1, last, rls[i]) - vals;
        rrs[i] = lower_bound (vals + 1, last, rrs[i]) - vals;
    }
    $ for (int i = 1; i <= n; i ++) {
        printf ("[%d %d]\n", rls[i], rrs[i]);
    }
    int ans = 1023456789;
    for (int i = 1, j = 0; i <= n; i ++) {
        while (j < n && mxv [1] < m) j ++, change (rls[j], rrs[j], 1, 1, 1, last - vals);
        if (mxv [1] >= m)
            ans = min (ans, (vals[rrs[j]] - vals[rls[j]]) - (vals[rrs[i]] - vals[rls[i]]));
        else break;
        change (rls[i], rrs[i], -1, 1, 1, last - vals);
    }
    printf ("%d", ans == 1023456789 ? -1 : ans);
    return 0;
}
