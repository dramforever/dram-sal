#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = (int)2e5, PSIZE = (int)5e6;

struct S
{
    S *lc, *rc;
    int val;
} *root[MAXN], pool[PSIZE], *ptp = pool;

inline S* alloc(S *l, S *r, int s)
{
    ptp ++;
    ptp->lc = l;
    ptp->rc = r;
    ptp->val = s;
    return ptp;
}

S* insert(S *x, int lb, int rb, int pos)
{
    x = x ? alloc(x->lc, x->rc, x->val) : alloc(0, 0, 0);

    if(lb != rb)
    {
        int mid = (lb + rb) >> 1;
        if(pos <= mid)
             x->lc = insert(x->lc, lb, mid, pos);
        else x->rc = insert(x->rc, mid+1, rb, pos);
    }

    x->val ++;

    return x;
}

inline int query(S *x, S *y, int lb, int rb, int k)
{
    while(lb != rb)
    {
        int mid = (lb + rb) >> 1;

#define lcv(x) ((x) ? ((x)->lc ? (x)->lc->val : 0): 0)
        int t = lcv(x) - lcv(y);
#undef lcv

        if(t >= k)
             x = x ? x->lc : 0, y = y ? y->lc : 0, rb = mid;
        else x = x ? x->rc : 0, y = y ? y->rc : 0, lb = mid + 1, k -= t;
    }
    return lb;
}

int A[MAXN], N, inl[MAXN], rec[MAXN], maxval, pcb[MAXN];

inline void prepare()
{
    for(int i = 1; i <= N; i ++)
        root[i] = insert(root[i-1], 1, maxval, inl[i]);
}

inline bool cmp(int i, int j)
{ return A[i] < A[j]; }

inline void lower()
{
    for(int i = 1; i <= N; i ++) rec[i] = i;
    sort(rec+1, rec+N+1, cmp);

    int last = A[rec[1]] - 1;
    for(int i = 1; i <= N; i ++)
    {
        maxval += A[rec[i]] != last;
        inl[rec[i]] = maxval;
        pcb[maxval] = last = A[rec[i]];
    }
}

int Q;


int main()
{
    scanf("%d%d", &N, &Q);
    for(int i = 1; i <= N; i ++)
        scanf("%d", A+i);
    lower();
    prepare();

    for(int i = 1; i <= Q; i ++)
    {
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);
        printf("%d\n", pcb[query(root[b], root[a-1], 1, maxval, k)]);
    }

    return 0;
}
