#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int __ = 5e5, sigma = 300;

char s[__];
int N, rank[__], cnt[__], A[__], B[__], sa[__], tmp[__], height[__];

void make() {
    int *r1 = rank, *r2 = tmp;
    for (int i = 1; i <= N; i ++) cnt[(unsigned int) s[i]] ++;
    for (int i = 1; i <= sigma; i ++) cnt[i] += cnt[i - 1];
    for (int i = N; i >= 1; i --) A[cnt[(unsigned int) s[i]] --] = i;
    for (int i = 1, c = 0; i <= N; i ++)
        r1[A[i]] = c += s[A[i]] != s[A[i - 1]];

    for (int l = 1; l < N; l <<= 1) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= N; i ++) cnt[r1[A[i] + l]] ++;
        for (int i = 1; i <= N; i ++) cnt[i] += cnt[i - 1];
        for (int i = N; i >= 1; i --) B[cnt[r1[A[i] + l]] --] = A[i];
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= N; i ++) cnt[r1[B[i]]] ++;
        for (int i = 1; i <= N; i ++) cnt[i] += cnt[i - 1];
        for (int i = N; i >= 1; i --) A[cnt[r1[B[i]]] --] = B[i];
        for (int i = 1, c = 0; i <= N; i ++)
            r2[A[i]] = c += (r1[A[i]] != r1[A[i - 1]]
                             || r1[A[i] + l] != r1[A[i - 1] + l]);
        swap(r1, r2);
    }

    if (r1 != rank) memcpy(rank, tmp, sizeof(rank));
    for (int i = 1; i <= N; i ++) sa[rank[i]] = i;

    for (int i = 1, k = 0; i <= N; height[rank[i]] = k, i ++)
        for (k -= k > 0; s[i + k] == s[sa[rank[i] - 1] + k]; k ++);
}

int main() {
    scanf("%s%n", s + 1, &N);
    make();
    for(int i = 1; i <= N; i ++)
        printf("%d%c", sa[i], i == N ? '\n' : ' ');
    for(int i = 2; i <= N; i ++)
        printf("%d%c", height[i], i == N ? '\n' : ' ');
}
