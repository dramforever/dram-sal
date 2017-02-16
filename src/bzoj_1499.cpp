#define $ if (0)

#include <cstdio>
#include <deque>

#define for_(i, n) for (int i = 0; i < n; i ++)
using namespace std;

const int zW = 202, zH = 202;
const int inf = 20000;

typedef pair<int, int> pii;
typedef deque<pii> dq_pii;

void ins (dq_pii &Q, int val, int t)
{
    if (val < inf)
    {
        while (! Q.empty () && val < Q.back ().first)
            Q.pop_back ();
        Q.push_back (make_pair (val, t));
    }
}

int get (dq_pii &Q, int time, int dur)
{
    while (! Q.empty () && time - Q.front ().second > dur)
        Q.pop_front ();
    return Q.empty () ? -1 : Q.front ().first;
}

void update (
        dq_pii &Q,
        int dur,
        int map[zW][zH],
        int in[zW][zH],
        int out[zW][zH],
        int time,
        int x, int y)
{
    $ printf ("(%d, %d) time = %d\n", x, y, time);
    if (map[x][y])
    {
        Q.clear();
    }
    else
    {
        ins (Q, in[x][y] + dur + time, time);
        int res = get (Q, time, dur);
        $ printf ("res = %d\n", res);
        if (res != -1) out[x][y] = min (out[x][y], res - time);
    }
}

void generate (
        int len_x, int len_y,
        int dir, int dur,
        int map[zW][zH],
        int in[zW][zH],
        int out[zW][zH])
{
    for_(x, len_x) for_(y, len_y)
        out[x][y] = min (inf, in[x][y] + dur);

    static const int xmajor[] = {0, 1, 1, 0, 0};
    dq_pii Q;
    if (xmajor[dir])
        for_(x, len_x)
        {
            Q.clear ();
            for_(time, len_y)
            {
                int y;
                if (dir == 1) y = len_y - time - 1;
                else /* dir == 2 */ y = time;

                update (Q, dur, map, in, out, time, x, y);
            }
        }
    else
        for_(y, len_y)
        {
            Q.clear ();
            for_(time, len_x)
            {
                int x;
                if (dir == 3) x = len_x - time - 1;
                else /* dir == 4 */ x = time;

                update (Q, dur, map, in, out, time, x, y);
            }
        }
}
int main ()
{
    static int len_x, len_y, init_x, init_y, T;
    scanf ("%d%d%d%d%d", &len_y, &len_x, &init_y, &init_x, &T);
    //                                   ^^^^^^^^^^^^^^^^
    // WTF, Stupid author!!!

    init_x --;
    init_y --;

    static int map[zW][zH], dp[2][zW][zH];

    for_(y, len_y) for_(x, len_x)
    {
        char d;
        do d = getchar ();
        while (d == '\n' || d == ' ');
        map[x][y] = d == 'x';
    }

    for_(y, len_y) for_(x, len_x)
        dp[1][x][y] = inf;

    dp[1][init_x][init_y] = 0;

    $ for_(y, len_y)
    {
        printf ("%4d |", y);
        for_(x, len_x)
            if (dp[1][x][y] == inf)
                printf ("   inf");
            else
                printf (" %5d", dp[1][x][y]);
        puts ("");
    }

    int L, R, dir;

    for_(k, T)
    {
        scanf ("%d%d%d", &L, &R, &dir);
        generate (len_x, len_y, dir, R - L + 1, map, dp[!(k&1)], dp[k&1]);

        $ for_(y, len_y)
        {
            printf ("%4d |", y);
            for_(x, len_x)
                if (dp[k&1][x][y] == inf)
                    printf ("   inf");
                else
                    printf (" %5d", dp[k&1][x][y]);
            puts ("");
        }
    }

    int ans = inf;
    for_(y, len_y) for_(x, len_x)
        ans = min (ans, dp[!(T&1)][x][y]);

    printf ("%d\n", R - ans);
    return 0;
}
