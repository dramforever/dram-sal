#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <cstdlib>
using namespace std;

#define for_(i, t) for (int i = 0; i < t; i ++)

// {{{ Basic structure
struct State {
    int blk[10][10];

    bool is_empty ();
    void kill ();
    bool drop ();
    void move (int x, int y, int dir);
    void read ();
    void dump ();

    State () {
        memset (blk, 0, sizeof blk);
    }
};

struct Op {
    int x, y, dir;
    Op (int x_, int y_, int dir_) :
        x(x_), y(y_), dir(dir_) {}
};

void dfs (State s, int remsteps);

int main () {
    int n; scanf ("%d", &n);
    State initial; initial.read ();
    /*initial.dump (); puts ("");
    initial.kill ();
    // initial.drop ();
    initial.dump (); puts ("");
    initial.drop ();
    initial.dump (); puts ("");*/
    dfs (initial, n);
    // If control flow reaches here, no solution is found
    printf ("-1\n");
    return 0;
}
// }}}

// {{{ State manip
bool State::is_empty () {
    for_(y, 7) for_(x, 5) {
        if (blk[x][y]) return false;
    }
    return true;
}

void State::kill () {
    int marked[10][10];
    memset (marked, 0, sizeof marked);
    for_(y, 7) {
        int last_color = -1, count = 1;
        for_(x, 5) {
            if (blk[x][y] == last_color)
                count ++;
            else {
                last_color = blk[x][y];
                count = 1;
            }

            if (count == 3)
                marked[x-1][y] = marked[x-2][y] = 1;
            if (count >= 3)
                marked[x][y] = 1;
        }
    }
    for_(x, 5) {
        int last_color = -1, count = 1;
        for_(y, 7) {
            if (blk[x][y] == last_color) {
                count ++;
            } else {
                last_color = blk[x][y];
                count = 1;
            }

            if (count == 3)
                marked[x][y-2] = marked[x][y-1] = 1;
            if (count >= 3)
                marked[x][y] = 1;
        }
    }
    for_(y, 7) for_(x, 5)
        if (marked[x][y]) blk[x][y] = 0;
}
 
bool State::drop () {
    int acted = 0;
    for_(y, 7) for_(x, 5)
        if (y && blk[x][y] && !blk[x][y-1]) {
            acted = 1;
            for (int h = y; h && ! blk[x][h-1]; h --)
                swap (blk[x][h], blk[x][h-1]);
        }
    return (bool) acted;
}

void State::move (int x, int y, int dir) {
    swap (blk[x][y], blk[x + dir][y]);
}

void State::read () {
    for_(x, 5) {
        int i = 0;
        int u;
        do {
            scanf ("%d", &u);
            blk[x][i++] = u;
        } while (u);
    }
}

void State::dump () {
    for_(y, 7) for_(x, 5)
        printf ("%d%c", blk[x][y], " \n"[x == 4]);
}
// }}}

// {{{ Search
deque<Op> osk;

void dfs (State s, int remsteps) {
/*    printf ("[[ %d ]]\n", remsteps);
    for (deque<Op>::iterator i = osk.begin (); i != osk.end (); i ++)
        printf ("%d %d %d\n", 1 + i->x, 1 + i->y, i->dir);
    puts("");
*/
    if (! remsteps && s.is_empty ()) {
        for (deque<Op>::iterator i = osk.begin (); i != osk.end (); i ++)
            printf ("%d %d %d\n", i->x, i->y, i->dir);
        exit (0);
    }
    else if (! remsteps)
        return;
    else
        for_(x, 5) for_(y, 7)
            if (s.blk[x][y]) {
                if (x != 4) {
                    State dup(s); dup.move (x, y, 1);
                    do dup.kill ();
                    while (dup.drop ());
                    osk.push_back (Op(x, y, 1));
                    dfs (dup, remsteps - 1);
                    osk.pop_back ();
                }
                if (x && ! s.blk[x-1][y]) {
                    State dup(s); dup.move (x, y, -1);
                    do dup.kill ();
                    while (dup.drop ());
                    osk.push_back (Op(x, y, -1));
                    dfs (dup, remsteps - 1);
                    osk.pop_back ();
                }
            }
}
// }}}
