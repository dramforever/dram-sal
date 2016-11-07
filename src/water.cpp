#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int __ = 501;

int n, m;
int ht[__][__], watered[__], vis[__][__];
int wmin[__], wmax[__];

void input () {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf ("%d", &ht[i][j]);
}

void preflow (int i, int j, int goh = 200000) {
    if (i < 1 || j < 1 || i > n || j > m || vis[i][j] || goh <= ht[i][j]) return;
    vis[i][j] = 1;
    if (i == n) watered[j] = 1;
    preflow (i - 1, j, ht[i][j]);
    preflow (i + 1, j, ht[i][j]);
    preflow (i, j - 1, ht[i][j]);
    preflow (i, j + 1, ht[i][j]);
}

void waterify (int i, int j, int from, int goh = 200000) {
    if (i < 1 || j < 1 || i > n || j > m || vis[i][j] || goh <= ht[i][j]) return;
    vis[i][j] = 1;
    if (i == n) {
        if (!wmin[from] || wmin[from] > j) wmin[from] = j;
        if (!wmax[from] || wmax[from] < j) wmax[from] = j;
    }
    waterify (i - 1, j, from, ht[i][j]);
    waterify (i + 1, j, from, ht[i][j]);
    waterify (i, j - 1, from, ht[i][j]);
    waterify (i, j + 1, from, ht[i][j]);
}

bool cmp (int i, int j) {
    return wmin[i] == wmin[j] ? wmax[i] < wmax[j] : wmin[i] < wmin[j];
}

int main () {
    input ();

    for (int i = 1; i <= m; i++)
        preflow (1, i);

    int count = 0;
    for (int i = 1; i <= m; i++)
        count += !watered[i];
    if (count) {
        printf ("0\n%d\n", count);
    } else {

        for (int i = 1; i <= m; i++) {
            memset (vis, 0, sizeof vis);
            waterify (1, i, i);
        }
        int cs[m + 5];
        for (int i = 1; i <= m; i++) cs[i] = i;
        sort (cs + 1, cs + m + 1, cmp);
        int cur = 0, ptr = 0, cn = 0;
        for (int i = 1; i <= m; i++) {
            if (wmin[cs[i]] > cur + 1) cur = ptr, cn++;
            ptr = max (ptr, wmax[cs[i]]);
        }
        cn += cur != m;
        printf ("1\n%d\n", cn);
    }
    return 0;
}
