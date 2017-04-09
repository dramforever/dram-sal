#include <cstdio>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <iostream>
 
using namespace std;
 
typedef int ll;
typedef long long realll;
 
const int LIM = 10000080, MOD = 20101009;
 
ll *sieve (ll *p0, ll sig[], char notprime[], ll lim)
{
    ll *p1 = p0;
    sig[1] = 1;
    for (ll i = 2; i <= lim; i ++)
    {
        if (! notprime[i]) *(p1 ++) = i, sig[i] = (MOD + 1 - i) % MOD;
 
        for (ll *j = p0; j != p1 && i * *j <= lim; j ++)
        {
            notprime[*j * i] = 1;
            if (0 == i % *j) { sig[*j * i] = sig[i]; break; }
            else { sig[*j * i] = (ll((1 - *j + MOD) % MOD) * sig[i]) % MOD; }
        }
    }
    return p1;
}
 
realll calc (ll n, ll m, ll pssig[])
{
    if (n > m) swap (n, m);
    realll ans = 0;
    for (ll i = 1, last; i <= n; i = last + 1)
    {
        last = min (n / (n / i), m / (m / i));
        realll val = n/i;
        val *= 1 + n/i; val %= MOD;
        val *= 1 + m/i; val %= MOD;
        val *= m/i; val %= MOD;
        val *= pssig[last] - pssig[i - 1] + MOD; val %= MOD;
        ans += val;
        ans %= MOD;
    }
    return ans;
}
 
int main ()
{
    static ll primes[LIM], sig[LIM], pssig[LIM];
    static char notprime[LIM];
     
    sieve (primes, sig, notprime, LIM - 20);
     
    for (int i = 1; i < LIM-20; i ++) pssig[i] = ((sig[i] * i) % MOD + pssig[i-1]) % MOD ;
 
    int n, m;
    scanf ("%d%d", &n, &m);
     
     
    if (n > m) swap (n, m);
    printf ("%I64d\n", (15075757ll * calc (n, m, pssig)) % MOD);
}