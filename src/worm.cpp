#include <algorithm>
#include <cstdio>
using namespace std;

const int __ = (int) 2e6, inf = (int) 1e9, Cs = 3, Ds = 3, Comp = 2;

void solve (int n, int hs[], int valids[Comp][50], int *vtop[Comp], int out[Comp][50][2])
{
    for (int i = 0; i < n; i ++)
    {
        int ixn = i & 1, prn = ixn ^ 1;

        vtop[ixn] = valids[ixn];

        for (int j = min(i + Cs - 1, n); j >= 0 && (i - j) < Cs; j --)
        {
            for (int hj = hs[j]; hj < hs[j] + Ds; hj ++)
            {
                if (hj >= hs[i]) *(vtop[ixn] ++) = hj;
            }
        }

        if (i == 0)
        {
            for (int *nowh = valids[ixn]; nowh != vtop[ixn]; nowh ++)
            {
                out[ixn][nowh - valids[ixn]][0] = *nowh - hs[0];
                out[ixn][nowh - valids[ixn]][1] = inf;
            }
        }
        else
        {
            for (int *nowh = valids[ixn]; nowh != vtop[ixn]; nowh ++)
                for (int nowdir = 0; nowdir < 2; nowdir ++)
                {
                    int nowk = nowh - valids[ixn];

                    int &ans = out[ixn][nowk][nowdir];
                    ans = inf;

                    for (int *prh = valids[prn]; prh != vtop[prn]; prh ++)
                        for (int prdir = 0; prdir < 2; prdir ++)
                        {
                            int prk = prh - valids[prn];

                            if (*prh == *nowh
                                    ? prdir == nowdir
                                    : (prdir != nowdir && (prdir < nowdir) == (*prh < *nowh)) )
                            {
                                ans = min (ans, out[prn][prk][prdir] + *nowh - hs[i]);
                            }
                        }
                }
        }
    }
};

int n;
int L[__], vL[Comp][50], *tL[Comp], oL[Comp][50][2];
int R[__], vR[Comp][50], *tR[Comp], oR[Comp][50][2];

void dump (int n, int hs[], int valids[Comp][50], int *vtop[Comp], int out[Comp][50][2]) {
    puts ("----- height -----");

    for (int i = 0; i < n; i ++)
        printf ("[%4d] %4d\n", i, hs[i]);

    for (int i = 0; i < n; i ++)
    {
        printf ("[%4d]", i);
        for (int *v = valids[i]; v != vtop[i]; v ++)
            printf (" %d", *v);
        puts ("");
    }

    puts ("----- out -----");

    for (int i = 0; i < n; i ++) {
        printf ("[%4d]", i);
        for (int *v = valids[i]; v != vtop[i]; v ++)
            printf (" %d", *v);
        puts ("");
        for (int dir = 0; dir < 2; dir ++)
        {
            printf ("+%4d  ", dir);
            for (int j = 0; j < vtop[i] - valids[i]; j ++)
                if (out[i][j][dir] == inf)
                    printf (" inf");
                else
                    printf (" %d", out[i][j][dir]);
            puts ("");
        }
    }
}

int main () {
    scanf ("%d", &n);

    for (int i = 0; i < n; i ++)
        scanf ("%d %d", L + i, R + i);

    for (int i = 0; i < n; i ++)
        L[i] = -L[i];

    solve (n, L, vL, tL, oL);
    solve (n, R, vR, tR, oR);

    //dump (n, L, vL, tL, oL);
    //dump (n, R, vR, tR, oR);

    int in = (n-1) & 1;

    int mnL = inf;
    for (int i = 0; i < tL[in] - vL[in]; i ++)
        mnL = min (mnL, oL[in][i][0]);

    int mnR = inf;
    for (int i = 0; i < tR[in] - vR[in]; i ++)
        mnR = min (mnR, oR[in][i][0]);

    printf ("%d\n", mnL + mnR);
    return 0;
}
