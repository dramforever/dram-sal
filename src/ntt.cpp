#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

typedef long long Val;

const int __ = (int) 3e6;

const Val MOD = 479 << 21 | 1, G = 3;

int rev[__];

void makerev(int n) {
    for (int i = 1, u = n; i <= n; i <<= 1, u >>= 1)
        for (int j = 0; j < (i >> 1); j ++)
            rev[j | (i >> 1)] = rev[j] | u;
}

int m, n;
Val a[__], b[__];

Val mod_pow(Val u, Val p) {
    Val ans = 1;
    for (Val cur = u; p; cur = (cur * cur) % MOD, p >>= 1)
        if (p & 1) ans = (ans * cur) % MOD;
    return ans;
}

Val roots[2][31];

void prepare() {
    Val g_inv = mod_pow(G, MOD - 2);
    for (int i = 0; i <= 30; i ++) {
        roots[0][i] = mod_pow(g_inv, (MOD - 1) >> i);
        roots[1][i] = mod_pow(G, (MOD - 1) >> i);
    }
}

#ifdef LOCAL
#undef LOCAL
#endif

void fft(Val u[], int n, int dir) {
    int num = 0;

    Val x[n];

    for (int i = 0; i < n; i ++)
        x[rev[i]] = u[i];

#ifdef LOCAL
    cout << "##################" << endl;
    cout << "==================" << endl;
    for (int i = 0; i < n; i ++)
        cout << x[i] << (i == n - 1 ? "\n" : " ");
    cout << "==================" << endl;
#endif
    for (int i = 2, id = 1; i <= n; i <<= 1, num = ! num, id ++) {
        Val w = roots[dir][id] % MOD;
        for (int j = 0; j < n; j += i) {
            Val now = 1;
            for (int k = 0; k < (i >> 1); k ++, now = now * w % MOD) {
                Val xx = x[j + k] % MOD;
                Val yt = x[j + (i >> 1) + k];
                Val yy = (now * yt) % MOD;
                x[j + k] = (xx + yy) % MOD;
                x[j + k + (i >> 1)] = (MOD + (xx - yy) % MOD) % MOD;
            }
        }
#ifdef LOCAL
        cout << "==================" << endl;
        for (int ii = 0; ii < n; ii ++)
            cout << x[ii] << (ii == n - 1 ? "\n" : " ");
#endif
    }
    memcpy(u, x, sizeof(x));

#ifdef LOCAL
    cout << "==================" << endl;
    for (int i = 0; i < n; i ++)
        cout << x[i] << (i == n - 1 ? "\n" : " ");
    cout << "==================" << endl;
    cout << "^^^^^^^^^^^^^^^^^^" << endl;
#endif
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n;

    for (int i = 0; i <= m; i ++)
        cin >> a[i];

    for (int i = 0; i <= n; i ++)
        cin >> b[i];

    int len = 2 * (max(m, n) + 1);

    len --;
    len |= len >> 1;
    len |= len >> 2;
    len |= len >> 4;
    len |= len >> 8;
    len |= len >> 16;
    len ++;

    makerev(len);
    prepare();

    fft(a, len, 1);
    fft(b, len, 1);

    for (int i = 0; i < len; i ++) a[i] = a[i] * b[i] % MOD;

    fft(a, len, 0);

    Val inv = mod_pow((Val) len, MOD - 2);

    for (int i = 0; i <= m + n; i ++)
        cout << a[i] % MOD * inv % MOD << (i == m + n ? "\n" : " ");
    return 0;
}
