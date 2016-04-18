#include <cstdio>
#include <iostream>
#include <queue>
#include <climits>
using namespace std;
int top, numnodes;
struct node {
	int flow, dst;
	node *next, *rev;
} pool[12580], *H[12580];

void Edge(int from, int to, int cap) {
	node *pA = &pool[top++], *re = &pool[top++];
	pA->dst = to;
	pA->flow = cap;
	pA->next = H[from];
	H[from] = pA;
	pA->rev = re;
	
	re->dst = from;
	re->flow = 0;
	re->next = H[to];
	H[to] = re;
	re->rev = pA;
}

queue<int> Q;

int Level[12580];
bool makelevel() {
	for(int i = 1; i <= numnodes; i ++) Level[i] = -1;
	while(! Q.empty()) Q.pop();
	Q.push(1);
	Level[1] = 0;
	while(! Q.empty()) {
		int i = Q.front(); Q.pop();
		for(node *p = H[i]; p; p = p->next)
			if(Level[p->dst] == -1 && p->flow) {
				Level[p->dst] = Level[i] + 1;
				Q.push(p->dst);
			}
		if(Level[numnodes] > 0)	
			return true;
	}
	return false;
}

int Find(int frx, int mxx) {
	if(frx == numnodes) return mxx;
	int sum = 0, t;
	for(node *p = H[frx]; p && sum <= mxx; p = p->next) {
		if(p->flow && Level[p->dst] == Level[frx] + 1) {
			t = Find(p->dst, min(mxx - sum, p->flow));
			if(t) {
				sum += t;
				p->flow -= t;
				p->rev->flow += t;
			}
		}
		
	}
	if(!sum) Level[frx] = -1;
	return sum;
}

int Wx() {
	int su = 0, t;
	while(makelevel()) while(t=Find(1, INT_MAX)) su+=t;
	return su;
}

int main() {
	int numedges;
	while(scanf("%d%d", &numedges, &numnodes) != -1) {
		for(int i = 1; i <= numnodes; i ++) H[i] = 0;
		top = 0;
		for(int i = 1; i <= numedges; i ++) {
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			Edge(x, y, c);
		}
		printf("%d\n", Wx());
		
	}
}

