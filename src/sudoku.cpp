#include <iostream>
#include <deque>
#include <cstring>
#include <set>

#define for_(v) for(int v = 0; v < 9; v ++)

using namespace std;

unsigned popcount (unsigned u) {
    u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
    u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
    u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
    u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
    u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
    return u;
}

int grid[20][20];

int blk[9][9] =
        {{0, 0, 0, 1, 1, 1, 2, 2, 2},
         {0, 0, 0, 1, 1, 1, 2, 2, 2},
         {0, 0, 0, 1, 1, 1, 2, 2, 2},
         {3, 3, 3, 4, 4, 4, 5, 5, 5},
         {3, 3, 3, 4, 4, 4, 5, 5, 5},
         {3, 3, 3, 4, 4, 4, 5, 5, 5},
         {6, 6, 6, 7, 7, 7, 8, 8, 8},
         {6, 6, 6, 7, 7, 7, 8, 8, 8},
         {6, 6, 6, 7, 7, 7, 8, 8, 8}};

int score[9][9] =
        {{6, 6, 6, 6, 6,  6, 6, 6, 6},
         {6, 7, 7, 7, 7,  7, 7, 7, 6},
         {6, 7, 8, 8, 8,  8, 8, 7, 6},
         {6, 7, 8, 9, 9,  9, 8, 7, 6},
         {6, 7, 8, 9, 10, 9, 8, 7, 6},
         {6, 7, 8, 9, 9,  9, 8, 7, 6},
         {6, 7, 8, 8, 8,  8, 8, 7, 6},
         {6, 7, 7, 7, 7,  7, 7, 7, 6},
         {6, 6, 6, 6, 6,  6, 6, 6, 6}};

int nfilled;

int mxsc = -1;

int basesc = 0;

void getbase () {
    for_(i) for_(j)
            basesc += score[i][j] * grid[i][j];
}

int ht[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

unsigned hash_grid () {
    unsigned hash = 2313;
    for_(i) for_(j)
            hash = hash * 41 + ht[grid[i][j]];
    return hash;
}

unsigned char hst[1 << 23];

void dfs (int depth = nfilled, int cursc = basesc) {
    unsigned hg = hash_grid () & ((1u << 26) - 1);
    if (hst[hg >> 3] & (1 << hg & 7)) return;
    else hst[hg >> 3] |= (1 << hg & 7);
    if (depth == 81) {
        mxsc = max (mxsc, cursc);
    } else {
        unsigned rowfl[9], colfl[9], blkfl[9];
        memset (rowfl, 0, sizeof rowfl);
        memset (colfl, 0, sizeof colfl);
        memset (blkfl, 0, sizeof blkfl);

        for_(i) for_(j)
                if (grid[i][j]) {
                    rowfl[i] |= 1u << (grid[i][j] - 1);
                    colfl[j] |= 1u << (grid[i][j] - 1);
                    blkfl[blk[i][j]] |= 1u << (grid[i][j] - 1);
                }

        unsigned mnpc = 0;
        int mxi, mxj;

        for_(i) for_(j)
                if (!grid[i][j]) {
                    unsigned mnr = rowfl[i] | colfl[j] | blkfl[blk[i][j]];
                    if (popcount (mnr) > popcount (mnpc))
                        mnpc = mnr, mxi = i, mxj = j;
                }

        if (!popcount (mnpc)) return;


        for_(nu)
            if (!(mnpc & (1u << nu))) {
                grid[mxi][mxj] = nu + 1;
                dfs (depth + 1, cursc + (nu + 1) * score[mxi][mxj]);
                grid[mxi][mxj] = 0;
            }
    }
}

int main () {
    for_(i) for_(j) {
            int n;
            cin >> n;
            if (n) nfilled++;
            grid[i][j] = n;
        }
    getbase ();
    dfs ();
    cout << mxsc << endl;
}
