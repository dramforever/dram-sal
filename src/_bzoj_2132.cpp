#define TRACE if(0)

#include <cstdio>
#include <iostream>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;
int top;
struct node {
    int flow, dst;
    node *next, *rev;
} pool[12580], *H[12580];

int N, M;

void Edge(int from, int to, int cap) {
    node *pA = &pool[top ++], *re = &pool[top ++];
    pA->dst = to;
    pA->flow = cap;
    pA->next = H[from];
    H[from] = pA;
    pA->rev = re;

    re->dst = from;
    re->flow = cap;
    re->next = H[to];
    H[to] = re;
    re->rev = pA;
}

queue<int> Q;

int c[500][500];
int Level[12580];

bool makelevel() {
    memset(Level, 0xff, sizeof(Level));
    while (! Q.empty()) Q.pop();
    Q.push(0);
    Level[0] = 0;
    while (! Q.empty()) {
        int i = Q.front();

        Q.pop();
        for (node *p = H[i]; p; p = p->next)
            if (Level[p->dst] == - 1 && p->flow) {
                Level[p->dst] = Level[i] + 1;
                Q.push(p->dst);
            }
        if (Level[N * M + 1] > 0)
            return true;
    }
    return false;
}

int Find(int frx, int mxx) {
    if (frx == N * M + 1) return mxx;
    int sum = 0, t;
    for (node *p = H[frx]; p && sum <= mxx; p = p->next) {
        if (p->flow && Level[p->dst] == Level[frx] + 1) {
            t = Find(p->dst, min(mxx - sum, p->flow));
            if (t) {
                sum += t;
                p->flow -= t;
                p->rev->flow += t;
            }
        }

    }
    if (! sum) Level[frx] = - 1;
    return sum;
}

int Wx() {
    int su = 0, t;

    TRACE {
        puts("Graph[{");
        for (int i = 0; i <= N * M + 1; i ++)
            for (node *it = H[i]; it; it = it->next)
                if(it->flow) printf("Labeled[%d \\[DirectedEdge] %d, %d],", i, it->dst, it->flow);
        puts("}//Most, GraphLayout \\[Rule] \"LayeredEmbedding\"]");
    }
    while (makelevel())
        while ((t = Find(0, INT_MAX))) {
            su += t;

            TRACE {
                puts("Graph[{");
                for (int i = 0; i <= N * M + 1; i ++)
                    for (node *it = H[i]; it; it = it->next)
                        if(it->flow) printf("Labeled[%d \\[DirectedEdge] %d, %d],", i, it->dst, it->flow);
                puts("}//Most, GraphLayout \\[Rule] \"LayeredEmbedding\"]");
            }
        }
    return su;
}

const int dx[] = {1, - 1, 0, 0};
const int dy[] = {0, 0, 1, - 1};

int main() {
    scanf("%d%d", &N, &M);
    int tot = 0;
    for (int i = 1; i <= M; i ++)
        for (int j = 1; j <= N; j ++) {
            int u;
            scanf("%d", &u);
            tot += u;
            if ((i + j) & 1) Edge(0, N * (i - 1) + j, u);
            else Edge(N * (i - 1) + j, M * N + 1, u);
        }

    for (int i = 1; i <= M; i ++)
        for (int j = 1; j <= N; j ++) {
            int u;
            scanf("%d", &u);
            tot += u;
            if ((i + j) & 1) Edge(N * (i - 1) + j, M * N + 1, u);
            else Edge(0, N * (i - 1) + j, u);
        }

    for (int i = 1; i <= M; i ++)
        for (int j = 1; j <= N; j ++)
            scanf("%d", &c[i][j]);
    for (int i = 1; i <= M; i ++)
        for (int j = 1; j <= N; j ++)
            if ((i + j) & 1)
                for (int k = 0; k < 4; k ++) {
                    int new_i = i + dx[k];
                    int new_j = j + dy[k];
                    if (new_i >= 1 && new_i <= N && new_j >= 1 && new_j <= M) {
                        tot += c[i][j] + c[new_i][new_j];
                        Edge((i - 1) * N + j, (new_i - 1) * N + new_j, c[i][j] + c[new_i][new_j]);
                        //Edge((new_i - 1) * N + new_j, (i - 1) * N + j, c[i][j] + c[new_i][new_j]);
                    }
                }
    printf("%d\n", tot - Wx());
    return 0;
}
