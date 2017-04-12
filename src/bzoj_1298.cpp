/// -g
/// -O2

#define $ if (0)

#include <cstdio>
#include <deque>
using namespace std;

const int zS = 400;

int next[zS], dice[zS][zS];
int vis[zS], vix, use;

/*
########  ########  ######  
##     ## ##       ##    ## 
##     ## ##       ##       
##     ## ######    ######  
##     ## ##             ## 
##     ## ##       ##    ## 
########  ##        ######  
*/

deque<int> S;

int n, m;

int dfs (int u, int mino = vix)
{
    $ printf ("%u start\n", 1 + u);
    u[vis] = ++ vix;

    if (u[next][vis])
    {
        if (u[next][vis] <= mino) {
            for (int base = 0; base < m; base ++)
                dice[u][base] = ++ use;
            $ printf ("%d no cycle\n", 1 + u);
            return -1;
        }
        else
        {
            
            S.push_back (u);
            $ printf ("%d ~~> %d\n", 1 + u, 1 + u[next]);
            return u[next];
        }
    }
    else
    {
        int res = dfs(u[next], mino);
        if (res == -1)
        {
            for (int base = 0; base < m; base ++)
                dice[u][base] = ++ use;
            return -1;
        }
        else if (res == u)
        {
            S.push_front (u);
            $ {
                printf ("The cycle is");
                for (int i = 0; i < S.size(); i ++)
                    printf (" %d", S[i] + 1);
                puts("");
            }
            if (m == 4 && S.size() == 3)
            {
                $ printf ("Qipacycle\n");
                dice[S[0]][0] = ++ use;
                dice[S[2]][0] = ++ use;
                dice[S[0]][1] = ++ use;
                dice[S[1]][0] = ++ use;
                dice[S[1]][1] = ++ use;
                dice[S[1]][2] = ++ use;
                dice[S[2]][1] = ++ use;
                dice[S[2]][2] = ++ use;
                dice[S[2]][3] = ++ use;
                dice[S[0]][2] = ++ use;
                dice[S[0]][3] = ++ use;
                dice[S[1]][3] = ++ use;
            }
            else
            {
                for (int base = 0; base < m; base ++)
                    for (int i = 0; i < S.size(); i ++)
                    {
                        // (base + i) % S.size()
                        int z = (base + i) % S.size();
                        dice[S[z]][base] = ++ use;
                    }
            }
            $ printf ("%d cycle\n", 1 + u);            
            S.clear ();
            return -1;
        }
        else
        {
            S.push_back (u);
            $ printf ("%d far %d\n", 1 + u, 1 + res);
            return res;
        }
    }
}


/*
##     ##    ###    #### ##    ## 
###   ###   ## ##    ##  ###   ## 
#### ####  ##   ##   ##  ####  ## 
## ### ## ##     ##  ##  ## ## ## 
##     ## #########  ##  ##  #### 
##     ## ##     ##  ##  ##   ### 
##     ## ##     ## #### ##    ## 
*/

int main ()
{
    //freopen ("C:/users/dramf/desktop/dice/dice1.in", "r", stdin);
    scanf ("%d%d", &n, &m);
    for (int i = 0; i < n; i ++)
    {
        scanf ("%d", &next[i]);
        next[i] --;
    }
    for (int i = 0; i < n; i ++)
        if (i[next] == i || i[next][next] == i)
        {
            printf ("0\n");
            return 0;
        }
    for (int i = 0; i < n; i ++)
        if (! vis[i]) dfs (i); 
    for (int i = 0; i < n; i ++)
        for (int base = 0; base < m; base ++)
            printf ("%d%c", dice[i][base], " \n"[base == m - 1]);
    return 0;
}