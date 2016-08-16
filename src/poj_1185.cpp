#include <iostream>
#include <ios>
#include <cctype>
#include <cstdio>

using namespace std;

#define SIGMA ((1 << m) - 1)

unsigned vs[90], valid_num;
int num[90];
int dp[110][90][90];
int row[110], n, m;

inline int pop_count(unsigned s) {
    int u = 0;
    while(s) s &= s-1, u ++;
    return u;
}

inline void generate() {
    for (unsigned i = 0; i <= SIGMA; i++)
        if (!(i & i >> 1 || i & i >> 2))
            vs[++valid_num] = i, num[valid_num] = pop_count(i);
}


inline void work() {
    for (int cur = 1; cur <= valid_num; cur++)
        if (!(vs[cur] & row[1]))
            for (int i = 1; i <= valid_num; i++)
                dp[1][cur][i] = num[cur];

    for (int cur = 1; cur <= valid_num; cur++)
        for (int prev = 1; prev <= valid_num; prev++)
            if (!(vs[cur] & row[2] || vs[prev] & vs[cur]))
                dp[2][cur][prev] = num[cur] + dp[1][prev][1];

    for (int i = 3; i <= n; i++)
        for (int cur = 1; cur <= valid_num; cur++)
            for (int p1 = 1; p1 <= valid_num; p1++)
                for (int p2 = 1; p2 <= valid_num; p2++)
                    if (!(vs[cur] & vs[p1] || vs[p1] & vs[p2] || vs[p2] & vs[cur] || vs[cur] & row[i]))
                        dp[i][cur][p1] = max(dp[i][cur][p1], dp[i - 1][p1][p2] + num[cur]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    generate();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char h;
            do cin >> h; while (isspace(h));
            row[i] <<= 1;
            row[i] |= h == 'H';
        }

    if (n == 1) {
        int ans = 0;
        for (int st = 1; st <= valid_num; st++)
            if (!(vs[st] & row[1]))
                ans = max(ans, num[st]);
        cout << ans << endl;

    } else {
        work();
        int ans = 0;
        for (int i = 1; i <= valid_num; i++)
            for (int j = 1; j <= valid_num; j++)
                ans = max(ans, dp[n][i][j]);
        cout << ans << endl;
    }

    return 0;
}
