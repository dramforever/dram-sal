#include <cstdio>
#include <iterator>

using namespace std;

const int __ = (int) 3e5;

int N, rank[__], height[__], sa[__], cnt;
char s[__];

struct state;

struct machine {
    struct state {
        int depth, mark;
        state *parent;
        state *fast;
        int fast_length;
        state *go[26];

        inline state *fast_go() {
            state *root;
            int sum = 0;
            for (root = this; root->fast; sum += root->fast_length, root = root->fast);
            for (state *u, *m = this; m->fast;
                 u = m->fast,
                 sum -= m->fast_length, m->fast_length += sum,
                 m->fast = root, m = u);
            return root;
        }

        void dfs(int d) {
            if (mark) sa[cnt ++] = d;

            for (int i = 0; i < 26; i ++)
                if (go[i]) {
                    go[i]->fast_go();
                    if (go[i]->fast)
                        go[i]->fast->dfs(d - 1 - go[i]->fast_length);
                    else
                        go[i]->dfs(d - 1);
                }

        }
    } *sbase, *spool, *last, *head;

    inline machine() {
        spool = sbase = new state[__];
        head = last = new(spool ++) state();
    }

    inline void add(char c) {
        state *u = new(spool ++) state();
        u->depth = last->depth + 1;
        state *p;
        for (p = last; p != 0 && ! p->go[c]; p = p->parent)
            p->go[c] = u;
        if (p) {
            state *q = p->go[c];
            if (p->depth + 1 == q->depth)
                u->parent = q;
            else {
                state *clone = new(spool ++) state(*q);
                clone->depth = p->depth + 1;
                for (; p && p->go[c] == q; p = p->parent)
                    p->go[c] = clone;
                q->parent = u->parent = clone;
            }
        } else
            u->parent = head;
        last = u;
    }

    inline void label() {
        for (state *u = last; u; u = u->parent)
            u->mark = 1;
    }

    inline void optimize() {
        int flag;
        state *pt;
        for (state *p = sbase; p != spool; p ++) {
            flag = 0;
            pt = 0;
            for (int i = 0; i < 26; i ++)
                if (p->go[i]) {
                    flag ++;
                    pt = p->go[i];
                }

            if (flag == 1 && ! p->mark) p->fast = pt, p->fast_length = 1;
        }
    }
} mch;

void make() {
    for (int i = 1; i <= N; i ++) rank[sa[i]] = i;

    for (int i = 1, k = 0; i <= N; height[rank[i]] = k, i ++)
        for (k -= k > 0; s[i + k] == s[sa[rank[i] - 1] + k]; k ++);
}

inline void write(int x){

    char buf[35];
    int i=0;
    do {
        buf[i++]=char((x%10)+'0');
        x/=10;
    } while(x);
    i--;
    while(i>=0) putchar_unlocked(buf[i--]);
}

int main() {
    int c;

    while (! isspace(c = getchar()) && c != - 1) mch.add((s[++ N] = (char) c) - 'a');

    mch.label();
    mch.optimize();

    mch.head->dfs(N + 1);
    make();

    for(int i = 1; i <= N; i ++) {
        write(sa[i]);
        putchar_unlocked(i == N ? '\n' : ' ');
    }

    for(int i = 2; i <= N; i ++) {
        write(height[i]);
        putchar_unlocked(i == N ? '\n' : ' ');
    }

    return 0;
}
