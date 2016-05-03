#include <complex>
#include <iostream>
#include <ios>

using namespace std;

typedef complex<double> C;

const int __ = (int) 3e6;
const double PI = acos(- 1);

int rev[__];

void makerev(int n) {
    for (int i = 1, u = n; i <= n; i <<= 1, u >>= 1)
        for (int j = 0; j < (i >> 1); j ++)
            rev[j | (i >> 1)] = rev[j] | u;
}

int m, n;
C a[__], b[__];

void fft(C x[], int n, int dir) {
    C u[2][n];

    for (int i = 0; i < n; i ++)
        u[0][rev[i]] = x[i];

    int num = 0;
    for (int i = 2; i <= n; i <<= 1, num = ! num) {
        C w = polar(1., (double)dir * 2 * PI / (double) i);
        for (int j = 0; j < n; j += i) {
            C now = 1.;
            for (int k = 0; k < (i >> 1); k ++, now *= w) {
                u[! num][j + k] = u[num][j + k] + now * u[num][j + (i >> 1) + k];
                u[! num][j + k + (i >> 1)] = u[num][j + k] - now * u[num][j + (i >> 1) + k];
            }
        }
    }

    for (int i = 0; i < n; i ++)
        x[i] = u[num][i];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n;

    for (int i = 0; i <= m; i ++) {
        double k;
        cin >> k;
        a[i] = C(k, 0.);
    }

    for (int i = 0; i <= n; i ++) {
        double k;
        cin >> k;
        b[i] = C(k, 0.);
    }

    int len = 2 * (max(m, n) + 1);

    len --;
    len |= len >> 1;
    len |= len >> 2;
    len |= len >> 4;
    len |= len >> 8;
    len |= len >> 16;
    len ++;

    makerev(len);

    fft(a, len, 1);
    fft(b, len, 1);

    for (int i = 0; i < len; i ++) a[i] *= b[i];

    fft(a, len, - 1);

    for (int i = 0; i <= m + n; i ++)
        cout << (int) round(a[i].real() / len) << (i == m + n ? "\n" : " ");

    return 0;
}