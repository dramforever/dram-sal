#include <map>

using namespace std;

const int __ = (int) 1e6;

struct machine {
    struct state {
        int depth;
        state *parent;
        map<char, state *> go;

        inline state() {
            depth = 0;
            parent = 0;
        }
    } *spool, *last, *head;

    inline machine() {
        spool = new state[__];
        head = last = new(spool++) state();
    }

    inline void add(char c) {
        state *u = new(spool++) state();
        u->depth = last->depth + 1;
        state *p;
        for (p = last; p != 0 && !p->go.count(c); p = p->parent)
            p->go[c] = u;
        if (p) {
            state *q = p->go[c];
            if (p->depth + 1 == q->depth)
                u->parent = q;
            else {
                state *clone = new(spool ++) state(*q);
                clone->depth = p->depth + 1;
                for(; p && p->go[c] == q; p = p->parent)
                    p->go[c] = clone;
                q->parent = u->parent = clone;
            }
        } else
            u->parent = head;
        last = u;
    }
};

int prt[__], plen[__];

int find(int u) {
    int root, sum;
    for(root = u, sum = 0; prt[root]; sum += plen[root], root = prt[root]);
    for(int k; prt[u]; k = prt[u], prt[u] = root, sum -= plen[u], plen[u] += sum, u = k);
    return root;
}
