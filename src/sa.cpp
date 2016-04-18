#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int __ = 5e5, sigma = 300;

char s[__];
int N, rank[__], cnt[__], A[__], B[__], sa[__], tmp[__], height[__];

void make()
{
  int *r1 = rank, *r2 = tmp;
  for(int i = 1; i <= N; i ++) cnt[(unsigned int)s[i]] ++;
  for(int i = 1; i <= sigma; i ++) cnt[i] += cnt[i - 1];
  for(int i = N; i >= 1; i --) A[cnt[(unsigned int)s[i]]--] = i;
  for(int i = 1, c = 0; i <= N; i ++)
    r1[A[i]] = c += s[A[i]] != s[A[i-1]];
  
  for(int l = 1; l < N; l <<= 1)
    {
      memset(cnt, 0, sizeof(cnt));
      for(int i = 1; i <= N; i ++) cnt[r1[A[i]+l]] ++;
      for(int i = 1; i <= N; i ++) cnt[i] += cnt[i-1];
      for(int i = N; i >= 1; i --) B[cnt[r1[A[i]+l]]--] = A[i];
      memset(cnt, 0, sizeof(cnt));
      for(int i = 1; i <= N; i ++) cnt[r1[B[i]]] ++;
      for(int i = 1; i <= N; i ++) cnt[i] += cnt[i-1];
      for(int i = N; i >= 1; i --) A[cnt[r1[B[i]]]--] = B[i];
      for(int i = 1, c = 0; i <= N ;i ++)
	r2[A[i]] = c += (r1[A[i]] != r1[A[i-1]]
			 || r1[A[i]+l] != r1[A[i-1]+l]);
      swap(r1, r2);
    }
  
  if(r1 != rank) memcpy(rank, tmp, sizeof(rank));
  for(int i = 1; i <= N; i ++) sa[rank[i]] = i;
}

void in() {
  cin.getline(s + 1, __);
  N = strlen(s+1);
  for(int i = 1; i <= N; i ++) {
    s[i+N] = s[i];
  }
  N *= 2;
}

int main() {
  in();
  make();
  for(int i = 1; i <= N; i ++) {
    if(sa[i] <= N/2) {
      printf("%c", s[sa[i] + N/2 - 1]);
    }
  }
  puts("");
  return 0;
}
