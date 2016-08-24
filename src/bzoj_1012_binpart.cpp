#define $ if (0)
#include <bits/stdc++.h>
using namespace std;

const int __ (1e6);

struct part {
    int start, len;
    part (int start_, int len_):
        start (start_), len (len_) {}
};

int vals [__];

inline part merge (const part &a, const part &b) {
    $ printf ("merge [%d %d] [%d %d]\n", a.start, a.len, b.start, b.len);
    for (int i = a.start; i < a.start + a.len; i ++)
        vals [i] = max (vals [i], vals [b.start]);
    return part (a.start, a.len + b.len);
}

vector <part> ps;

void dump () {
    for (vector<part>::iterator it = ps.begin();
            it != ps.end(); it ++) {
        printf ("[%d %d] ", it->start, it->len);
        for (int i = it->start; i < it->start + it->len; i ++)
            printf("%d%c", vals[i], " \n"[i == it->start + it->len - 1]);
    }
    puts ("------------------");
}

void insert (int u) {
    int pos;
    if (ps.size()) pos = ps.rbegin()->start + ps.rbegin()->len;
    else pos = 1;
    vals [pos] = u;
    ps.push_back (part(pos, 1));
    while (ps.size() > 1 && ps.rbegin()->len == ps.rbegin()[1].len) {
        $ dump();
        part x = ps.rbegin()[0]; ps.pop_back ();
        part y = ps.rbegin()[0]; ps.pop_back ();
        ps.push_back(merge(y, x));
    }
}

int query (int l) {
    int curmax = -1;
    vector<part>::reverse_iterator p;
    for (p = ps.rbegin(); p != ps.rend() && p->len <= l; l -= p->len, p ++)
        curmax = max (curmax, vals[p->start]);
    if (l)
        curmax = max (curmax, vals[p->start + p->len - l]);
    return curmax;
}

int main () {
    int m, D; scanf ("%d%d", &m, &D);
    int lastans = 0;
    for (int i = 1; i <= m; i ++) {
        char cmd; scanf (" %c", &cmd);
        if (cmd == 'A') {
            int val; scanf ("%d", &val);
            val += lastans; val %= D;
            insert (val);
        } else {
            int l; scanf ("%d", &l);
            printf ("%d\n", lastans = query (l));
        }
        $ dump();
    }
    return 0;
}
