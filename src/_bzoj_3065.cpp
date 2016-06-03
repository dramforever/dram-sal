#include <cstdio>
#include <algorithm>

using namespace std;

const int __ = (int) 2e5 + 30;

int parent[22][__];

int find(int M, int u) {
    int root;
    for (root = u; parent[M][root]; root = parent[M][root]);
    for (int k; parent[M][u]; k = parent[M][u], parent[M][u] = root, u = k);
    return root;
}

void onion(int M, int u, int v) {
    u = find(M, u);
    v = find(M, v);
    if (u != v) parent[M][u] = v;
}

int main() {
    int N, n_queries;
    scanf("%d%d", &N, &n_queries);
    while (n_queries --) {
        int u, v, p;
        scanf("%d%d%d%*d", &u, &p, &v);
        int len = p + 1 - u;
        for (int M = 0; len; len >>= 1, M ++)
            if (len & 1) {
                onion(M, u, v);
                u += (1 << M), v += (1 << M);
            }
    }

    for (int M = 20; M >= 1; M --)
        for (int i = 1; i <= N - (1 << M) + min((1 << M), 20); i ++) {
            onion(M - 1, i, find(M, i));
            onion(M - 1, i + (1 << (M - 1)), find(M, i) + (1 << (M - 1)));
        }
    int cnt = 0;
    for (int i = 1; i <= N; i ++) {
        if (find(0, i) == i) cnt ++;
    }

    unsigned long long ans = 9;
    for (int i = 2; i <= cnt; i ++)
        ans *= 10, ans %= (unsigned long long) (1e9) + 7ull;

    printf("%llu\n", ans);
    return 0;
}