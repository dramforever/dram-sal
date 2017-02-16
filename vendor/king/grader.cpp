/* This is a sample grader for the contestant */
#include "king.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define debug(...) //fprintf(stderr,__VA_ARGS__)

static double clock_start;

inline static int get_int(FILE *f)
{
	int x;
	assert(fscanf(f,"%d",&x)==1);
	return x;
}

inline static void __exit()
{
	printf("\n");
	debug("time: %.0lf ms\n",(clock()-clock_start)*1000.0/CLOCKS_PER_SEC);
	exit(0);
}

#define WA(...) {puts("Incorrect");printf(__VA_ARGS__);__exit();}
#define AC(...) {puts("Correct");printf(__VA_ARGS__);__exit();}

static int task_id,n,M,T;

#define LIM_N 100000
#define LIM_M (5*1000*1000)
#define MAXN (LIM_N*2+LIM_M+5)

static int m;

inline static int max(int a,int b)
{
	return a>b?a:b;
}

static int *A,*B;
static char *F;

int add_flea(int a,int b,int f)
{
	if (m==M) {
		WA("Too many fleas");
	}
	int id=2*n+m;
	if (a<0 || a>=id || b<0 || b>=id || f<0 || f>=16) {
		WA("Invalid arguments of flea #%d: a = %d, b = %d, f = %d",id,a,b,f);
	}
	A[id]=a;B[id]=b;F[id]=f;
	++m;
	return id;
}

static int output_id[LIM_N];

void set_output(int i,int id)
{
	if (i<0 || i>=n) {
		WA("Invalid use of set_output: %d has already been set",i);
	}
	if (id<0 || id>=2*n+m) {
		WA("Invalid id of flea: %d",id);
	}
	output_id[i]=id;
}

inline static void init()
{
	int i;
	for (i=0;i<n;i++) {
		output_id[i]=-1;
	}
}

const static int cases=10;

static bool *val;
static int *_T;

static bool ans[LIM_N];

static int max_T;

inline static void check_T()
{
	memset(_T,0,2*n*sizeof(int));
	int i,id;
	max_T=0;
	for (i=0,id=2*n;i<m;i++,id++) {
		_T[id]=max(_T[A[id]],_T[B[id]])+1;
		if (_T[id]>T) {
			WA("flea #%d's val can't be determined in T hours",id);
		}
		max_T=max(max_T,_T[id]);
	}
}

inline void get_ans(const bool *A,const bool *B,bool *C)
{
	if (task_id==1) {
		C[0]=A[0]^1;
		bool c=A[0];
		int i;
		for (i=1;i<n;i++) {
			C[i]=A[i]^c;
			c=C[i]<A[i];
		}
	} else if (task_id==2) {
		C[0]=A[0]^B[0];
		bool c=A[0]&B[0];
		int i;
		for (i=1;i<n;i++) {
			C[i]=A[i]^B[i]^c;
			c=(A[i]&B[i])|((A[i]|B[i])&c);
		}
	} else if (task_id==3) {
		int c=0;
		int i,j;
		for (i=0;i<n;i++) {
			for (j=0;j<=i;j++) {
				c+=A[j]&B[i-j];
			}
			C[i]=c&1;
			c>>=1;
		}
	} else {
		assert(0);
	}
}

inline static void check_case()
{
	int i,id;
	for (i=0;i<2*n;i++) {
		val[i]=(rand()>>5)&1;
	}
	get_ans(val,val+n,ans);
	for (i=0,id=2*n;i<m;i++,id++) {
		int a=val[A[id]],b=val[B[id]],f=F[id];
		val[id]=(f>>(2*a+b))&1;
	}
	for (i=0;i<n;i++) {
		if (val[output_id[i]]!=ans[i]) {
			WA("Wrong answer");
		}
	}
}

inline static void check()
{
	int i;
	for (i=0;i<n;i++) {
		if (output_id[i]==-1) {
			WA("output %d has not been set",i);
		}
	}
	check_T();
	for (i=0;i<cases;i++) {
		check_case();
	}
	AC("m = %d, t = %d",m,max_T);
}

int main()
{
	clock_start=clock();
	
	task_id=get_int(stdin);
	n=get_int(stdin);
	M=get_int(stdin);
	T=get_int(stdin);
	
	assert(M>0 && M<=LIM_M);
	
	A=(int*)calloc(MAXN,sizeof(int));
	B=(int*)calloc(MAXN,sizeof(int));
	F=(char*)calloc(MAXN,sizeof(char));
	
	val=(bool*)calloc(MAXN,sizeof(bool));
	_T=(int*)calloc(MAXN,sizeof(int));
	
	init();
	
	build_computer(task_id,n,M,T);
	
	check();
	
	return 0;
}
