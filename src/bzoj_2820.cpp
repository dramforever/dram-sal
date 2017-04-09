#include <cstdio>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

void sieve (
    int *primes,
    int not_prime[],
    int mu[],
    int sig[],
    int lim)
{
    int *base = primes;
    not_prime[1] = 1;
    for (int i = 1; i <= lim; i ++)
    {
        if (! not_prime[i]) 
        {
            *(primes ++) = i;
            mu[i] = -1;
            sig[i] = 1;
        }

        for (int *j = base; j != primes && *j * i <= lim; j ++)
        {
            not_prime[*j * i] = 1;
            
            if (i % *j == 0)
            {
                mu[*j * i] = 0;
                sig[*j * i] = mu[i];
                break;
            }
            else
            {
                mu[*j * i] = - mu[i];
                sig[*j * i] = mu[i] - sig[i];
            }
        }
    }
}

typedef long long ll;

ll calc (
    int n, int m,
    ll pssig[])
{
    if (n > m) swap (n, m);
    ll ans = 0;
    for (int i = 1, last; i <= n; i = last + 1)
    {
        last = min (n / (n / i), m / (m / i));
        ans += ll(n / i) * ll(m / i) * (pssig[last] - pssig[i - 1]);
    }
    return ans;
}

const int __ = 10000070, LIM = 10000000;

int main ()
{
    static int primes[__], not_prime[__], mu[__], sig[__];
    static long long pssig[__];
    sieve (primes, not_prime, mu, sig, LIM);
    
    partial_sum (sig, sig + LIM + 1, pssig, std::plus<long long>());

    int T; scanf ("%d", &T);
    while (T --)
    {
        int a, b;
        scanf ("%d%d", &a, &b);
        printf ("%lld\n", calc (a, b, pssig));
    }
}
