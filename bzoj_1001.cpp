#include <bits/stdc++.h>
using namespace std;

const int __ = (int)5e6;

int N, M, src, sink;

// {{{ Point encoding
inline int pack(int row, int col, int dir) {
    return dir - 1 + 2 * ((row-1)*(M-1) + col);
}
// }}}

// {{{ Graph
struct Edge {
    int to, len;
    Edge *next;
    Edge() {}
    Edge(int to_, int len_, Edge *next_):
        to(to_), len(len_), next(next_) {}
} *pool = new Edge[__], *head[__];

void newEdge(int u, int v, int len) {
    // cout << "UndirectedEdge[" << u << "," << v << "]," << endl;
    head[u] = new(pool ++) Edge(v, len, head[u]);
    head[v] = new(pool ++) Edge(u, len, head[v]);
}
// }}}

// {{{ Dijkstra's
int dist[__];

struct Cmp {
    bool operator()(int u, int v) {
        if (dist[u] == dist[v])
            return u < v;
        else
            return dist[u] < dist[v];
    }
};

typedef set<int, Cmp> dset;
dset S;

const int inf = 0x3f3f3f3f;

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[src] = 0;
    S.insert(src);

    while (! S.empty()) {
        int t = *S.begin(); S.erase(S.begin());
        for (Edge *e = head[t]; e; e = e->next)
            if (dist[e->to] > dist[t] + e->len) {
                if (dist[e->to] != 0x3f3f3f3f)
                    S.erase(e->to);
                dist[e->to] = dist[t] + e->len;
                S.insert(e->to);
            }
    }
}
// }}}

// {{{ Main
int main() {
    cin >> N >> M;

    if (N == 1 || M == 1) {
        int x = 0x3f3f3f3f, l;
        while (scanf("%d", &l) != -1)
            x = min(l, x);
        cout << x;
    } else {
        src = pack(N-1, M-1, 2);
        sink = pack(N-1, M-1, 3);

        for (int c = 1; c <= M - 1; c ++) {
            int l; cin >> l;
            newEdge(pack(1, c, 1), sink, l);
        }
        for (int r = 2; r <= N - 1; r ++)
            for (int c = 1; c <= M - 1; c ++) {
                int l; cin >> l;
                newEdge(pack(r - 1, c, 0), pack(r, c, 1), l);
            }
        for (int c = 1; c <= M - 1; c ++) {
            int l; cin >> l;
            newEdge(pack(N - 1, c, 0), src, l);
        }
        for (int r = 1; r <= N - 1; r ++) {
            int l; cin >> l;
            newEdge(pack(r, 1, 0), src, l);
            for(int c = 2; c <= M - 1; c ++) {
                cin >> l;
                newEdge(pack(r, c, 0), pack(r, c-1, 1), l);
            }
            cin >> l;
            newEdge(pack(r, M-1, 1), sink, l);
        }
        for(int r = 1; r <= N - 1; r ++)
            for(int c = 1; c <= M - 1; c ++) {
                int l; cin >> l;
                newEdge(pack(r, c, 0), pack(r, c, 1), l);
            }

        dijkstra();

        cout << dist[sink] << endl;
        return 0;
    }
}
// }}}
