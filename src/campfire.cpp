#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

#define for_(i, k) for (int i = 1; i <= k; i ++)
#define for_z(i, k) for (int i = 0; i < k; i ++)

const int __ = 200000;

int n, s1[__], s2[__];
int want[__][2];

int ix;

int co[__];

int check (int s[]) {
    memset (co, 0, sizeof co);
    for_(i, n * 2 - 1) {
        int r = i - s[i] + 1;
        if (r >= 1 && r <= n) co [r] ++;
    }
    return *max_element (co + 1, co + n + 1);
}

int main () {
    scanf ("%d", &n);
    for_(i, n)
        scanf ("%d%d", &want[i][0], &want[i][1]);

    for_(i, n)
        for_z(j, 2)
            if (   want[want[i][j]][0] != i
                && want[want[i][j]][1] != i) goto fail;

    {
        int prev = -1, node = 1;

        do {
            ix ++;
            s1[ix] = node;
            if (want[node][0] == prev)
                prev = node, node = want[node][1];
            else
                prev = node, node = want[node][0];
        } while (node != 1);
        
        if (ix != n) goto fail;

        for_(i, n)
            s2[n + 1 - i] = s1[i];

        for_(i, n-1)
            s1[i + n] = s1[i], s2[i + n] = s2[i];

        printf ("%d", n - max (check (s1), check (s2)));
        return 0;
    }
fail:
    puts ("-1");
    return 0;
}
