#include <cstdio>
#include <new>

using namespace std;

const int __ = (int) 2e5, __max = (1 << 18) - 1;

int n;

struct T {
    int val;
    T *lc, *rc;

    inline T() { }

    inline T(T *l, T *r, int v) :
            val(v), lc(l), rc(r) { }
} *root[__], *pool = new T[__ * 60];

int A[__];

T *insert(T *x, int pos, int lb = 0, int rb = __max) {
    x = new(pool ++) T(x->lc, x->rc, x->val);

    if (lb != rb) {
        int mid = (lb + rb) >> 1;
        if (pos <= mid)
            x->lc = insert(x->lc, pos, lb, mid);
        else x->rc = insert(x->rc, pos, mid + 1, rb);
    }

    x->val ++;

    return x;
}

bool has(T *x, T *y, int l, int r, int lb = 0, int rb = __max) {
    if(l > r) return false;
    if(l < lb) l = lb;
    if(r > rb) r = rb;
    if (lb == l && rb == r) return bool(y->val - x->val);
    else {
        int mid = (lb + rb) >> 1;
        if (r <= mid) return has(x->lc, y->lc, l, r, lb, mid);
        else if (l > mid) return has(x->rc, y->rc, l, r, mid + 1, rb);
        else
            return has(x->lc, y->lc, l, mid, lb, mid)
                   || has(x->rc, y->rc, mid + 1, r, mid + 1, rb);
    }
}

int query(int b, int x, int l, int r) {
    int ans = 0, offset = 0;
    for (int M = 17; M >= 0; M --) {
        if (b & (1 << M)) {
            if (has(root[l - 1], root[r], offset - x, offset + (1 << M) - x - 1))
                ans |= 1 << M;
            else offset |= 1 << M;
        } else {
            if (has(root[l - 1], root[r], offset + (1 << M) - x, offset + (1 << M + 1) - x - 1))
                ans |= 1 << M, offset |= 1 << M;
        }
    }
    return ans;
}

void prepare() {
    root[0] = pool ++;
    root[0] = new(root[0]) T(root[0], root[0], 0);
    for (int i = 1; i <= n; i ++)
        root[i] = insert(root[i - 1], A[i]);
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++)
        scanf("%d", A + i);
    prepare();
    while (m --) {
        int b, x, l, r;
        scanf("%d%d%d%d", &b, &x, &l, &r);
        printf("%d\n", query(b, x, l, r));
    }
    return 0;
}