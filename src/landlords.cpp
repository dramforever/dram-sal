#include <iostream>
#include <numeric>
#include <functional>
#include <climits>
#include <iomanip>
#include <cstring>

using namespace std;

int t, n;

unsigned int dp[30][20][15][10][5];

struct Solver {
    int a[9];
    unsigned ans;

    Solver(int a1, int a2, int a3, int a4, int a5) {
        a[1] = a1;
        a[2] = a2;
        a[3] = a3;
        a[4] = a4;
        a[5] = a5;
        ans = 200000u;
    }

#define MUT(ix, n, k) \
    do { \
        if (a[ix] + n >= 0) { \
            a[ix] += n; \
            k; \
            a[ix] -= n; \
        } \
    } while (0)

#define UPDATE ans = min(ans, 1 + dp[a[1]][a[2]][a[3]][a[4]][a[5]])

#define FIND_N(minu, k) \
    do { \
        if (minu == 1) { \
            for (int i = 1; i <= 5; i ++) \
                if (i == 1 || i == 5) MUT(i, -1, k); \
                else MUT(i, -1, MUT(i-1, +1, k)); \
        } else { \
            for (int i = minu; i <= 4; i++) \
                if (i == minu) \
                    MUT(i, -1, k); \
                else \
                    MUT(i, -1, MUT(i - minu, +1, k)); \
        } \
    } while (0)


    void find(int n) {
        FIND_N(n, UPDATE);
    }

    void find(int n1, int n2) {
        FIND_N(n1, FIND_N(n2, UPDATE));
    }

    void find(int n1, int n2, int n3) {
        FIND_N(n1, FIND_N(n2, FIND_N(n3, UPDATE)));
    }

    void solve() {
        if (accumulate(a + 1, a + 6, false, logical_or<int>())) {
            // Have cards left
            MUT(5, -2, UPDATE); // two cats
            for (int i = 1; i <= 4; i++) find(i); // 1 to 4
            find(3, 2);
            find(3, 1);
            find(4, 1, 1);
            find(4, 2, 2);
        } else ans = 0;

    }
};

void gen_table() {
    memset(dp, 0x3f, sizeof dp);
    for (int a4 = 0; a4 <= 8; a4++)
        for (int a3 = 0; a3 <= 10; a3++)
            for (int a2 = 0; a2 <= 14; a2++)
                for (int a1 = 0; a1 <= 25; a1++)
                    for (int a5 = 0; a5 <= 2; a5++) {
                        Solver x(a1, a2, a3, a4, a5);
                        x.solve();
                        dp[a1][a2][a3][a4][a5] = x.ans;
                    }
}

struct Seq {
    int cnt[50];
    Seq () {
        memset(cnt, 0, sizeof cnt);
    }
    void read () {
        for (int i = 1; i <= n; i ++) {
            int a, b; cin >> a >> b;
            if (a == 0) cnt[20] ++;
            else if(a == 1) cnt[14] ++;
            else cnt[a] ++;
        }
    }
    unsigned stat();
    void shun(int dep, int len, int nu);
    void go(int dep = 0);
};

unsigned Seq::stat() {
    int a[9];
    memset(a, 0, sizeof a);
    for (int i = 2; i <= 14; i ++) a[cnt[i]] ++;
    a[5] = cnt[20];
    return dp[a[1]][a[2]][a[3]][a[4]][a[5]];
}

unsigned totan;

void Seq::shun(int dep, int len, int nu) {
    for (int i = 3; i + len - 1 <= 14; i ++)
        for (int j = i + len - 1; j <= 14; j ++) {
            bool flag = true;
            for (int t = i; t <= j; t ++)
                flag = flag && (cnt[t] >= nu);
            if (flag) {
                for (int t = i; t <= j; t ++) cnt[t] -= nu;
                go(dep + 1);
                for (int t = i; t <= j; t ++) cnt[t] += nu;
            }
        }
}

void Seq::go(int dep) {
    unsigned sqd = dep + stat();
    totan = min(totan, sqd);
    shun(dep, 3, 2);
    shun(dep, 2, 3);
    shun(dep, 5, 1);
}

int main() {
    ios::sync_with_stdio(false);
    gen_table();
    cin >> t >> n;
    while (t --) {
        totan = 200000;
        Seq sq;
        sq.read();
        sq.go();
        cout << totan << endl;
    }
}
