#include <cstring>
#include <cstdio>
using namespace std;

#define for_(i, n) for (int i = 1; i <= n; i ++)

int n, m;
int dist[200][200];
double count[200][200];

int main () { 
    scanf("%d%d", &n, &m);
    memset (dist, 0x3f, sizeof dist);
    
    for_(i, m) {
        int a, b, len;
        scanf("%d%d%d", &a, &b, &len);
        dist[a][b] = dist[b][a] = len;
        count[a][b] = count[b][a] = 1.;
    }
    for_(k, n) for_(i, n) for_(j, n)
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
            count[i][j] = count[i][k] * count[j][k];
        } else if (dist[i][j] == dist[i][k] + dist[k][j])
            count[i][j] += count[i][k] * count[j][k];

    for_(i, n) count[i][i] = 0.;
    
    for_(k, n) {
        double ans = 0.;
        for_(i, n) for_(j, n)
            if (dist[i][j] == dist[i][k] + dist[k][j] && count[i][j] > 1e-8)
                ans += count[i][k] * count[k][j] / count[i][j];
        printf ("%.3lf\n", ans);
    }
    return 0;
}
