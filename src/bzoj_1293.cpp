#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

typedef vector<int> vii;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vii::iterator viter;

struct vintw
{
    int ty;
    viter p0, p1;

    vintw (int ty_, viter p0_, viter p1_):
        ty (ty_), p0 (p0_), p1 (p1_) {}
};

typedef priority_queue<vintw> pqpvint;

bool operator< (const vintw &A, const vintw &B)
{
    return *A.p0 > *B.p0;
}

vintw readone (int ty, int nu) {
    vii *pv = new vii(nu);
    for (viter i = pv->begin(); i != pv->end(); i ++)
        scanf ("%d", &*i);
    return vintw (ty, pv->begin (), pv->end ());
}

int N, K;
int counts[128], ctys;

void insert (int A)
{
    //printf ("ins %d\n", A);
    if (counts[A] == 0) ctys ++;
    counts[A] ++;
}

void remove (int A)
{
    //printf ("del %d\n", A);
    counts[A] --;
    if (counts[A] == 0) ctys --;
}

int main () {
    pqpvint PQ;

    scanf ("%d%d", &N, &K);
    for (int i = 0; i < K; i ++)
    {
        int nu;
        scanf ("%d", &nu);
        PQ.push (readone (i, nu));
    }

    vpii X (N);
    for (vpii::iterator i = X.begin(); i != X.end(); i ++)
    {
        vintw z = PQ.top(); PQ.pop();
        *i = make_pair(*z.p0, z.ty);
        //printf ("%d %d\n", i->first, i->second);
        z.p0 ++;
        if (z.p0 != z.p1) PQ.push (z);
    }

    vpii::iterator l = X.begin();
    vpii::iterator r = X.begin();
    while (ctys != K) insert ((r ++)->second);
    int ans = (r - 1)->first - l->first;
    for (; r != X.end(); r ++) {
        insert (r->second);
        while (counts[l->second] > 1) remove ((l ++)->second);
        ans = min (ans, r->first - l->first);
    }
    printf ("%d\n", ans);
}
