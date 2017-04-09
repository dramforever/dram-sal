#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long Val;

Val inf = 1LL<<60;

// dp[hsize][vsize][hdock][vdock]
Val dp[310][310][3][3];

Val n, m, k;

void getdp (Val hs, Val vs, int hd, int vd)
{
    Val &ans = dp[hs][vs][hd][vd];
    if (hd || vd)
    {
        ans = (hs * vs - k) * (hs * vs - k);

        if (hd >= 1) // Cut H
            for (Val newz = 1; newz < vs; newz ++)
                ans = min (ans,
                    dp[hs][newz][hd][vd >= 1]
                    + dp[hs][vs - newz][hd][vd >= 2]);

        if (hd >= 2) // Cut V
            for (Val newz = 1; newz < hs; newz ++)
                ans = min (ans,
                    dp[newz][vs][1][vd]
                    + dp[hs - newz][vs][1][vd]);

        if (vd >= 1) // Cut V
            for (Val newz = 1; newz < hs; newz ++)
                ans = min (ans,
                    dp[newz][vs][hd >= 1][vd]
                    + dp[hs - newz][vs][hd >= 2][vd]);

        if (vd >= 2) // Cut H
            for (Val newz = 1; newz < vs; newz ++)
                ans = min (ans,
                    dp[hs][newz][hd][1]
                    + dp[hs][vs - newz][hd][1]);
    }
    else
        ans = inf;
}

int main ()
{
    scanf ("%lld%lld%lld", &n, &m, &k);
#define for_(i, n) for (int i = 1; i <= n; i ++)
    for_(a, n) for_(b, m) for_(c, 3) for_(d, 3)
        getdp (a, b, c-1, d-1);
    printf ("%lld\n", dp[n][m][2][2]);
}
