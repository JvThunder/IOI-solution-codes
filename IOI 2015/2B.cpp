#include "sorting.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;
int B[MAXN];
int posB[MAXN];
int A[MAXN];
int posA[MAXN];

bool check(int N,int S[],int M,int X[],int Y[],int P[],int Q[])
{
	for(int i=0;i<N;i++) 
	{
		B[i] = S[i];
		posB[B[i]] = i;
		A[i] = B[i];
	}
	for(int i=0;i<M;i++)
	{
		swap(A[X[i]],A[Y[i]]);
		P[i] = 0; Q[i] = 0;
	}
	for(int i=0;i<N;i++) posA[A[i]] = i;

	int ptr = 0;
	for(int i=0;i<M;i++)
	{
		while(ptr<N-1 && ptr==A[ptr]) ptr++;

		swap(posB[B[X[i]]],posB[B[Y[i]]]);
		swap(B[X[i]],B[Y[i]]);
		
		P[i] = posB[A[ptr]];
		Q[i] = posB[ptr];
		swap(B[P[i]],B[Q[i]]);
		swap(posB[A[ptr]],posB[ptr]);

		int j = posA[ptr];
		swap(posA[A[ptr]],posA[A[j]]);
		swap(A[ptr],A[j]);
	}

	bool done = true;
	for(int i=0;i<N;i++)
	{	
		if(B[i]!=i) done = false;	
	}
	return done;
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[])
{
	int l = 0; int r = M;
	int ret = M;
	while(l<=r)
	{
		int mid = (l+r)/2;
		if(check(N,S,mid,X,Y,P,Q)) ret = mid, r = mid-1;
		else l = mid+1;
	}
	check(N,S,ret,X,Y,P,Q);
	return ret;
}