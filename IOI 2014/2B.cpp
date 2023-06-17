#include "friend.h"
#include "bits/stdc++.h"
using namespace std;

const int MAXN = 1000005;
int p[MAXN],q[MAXN];
int findSample(int n,int c[],int host[],int pr[])
{
	for(int i=0;i<n;i++) p[i] = c[i];
	for(int i=n-1;i>=1;i--)
	{
		int o = host[i];
		int tp = 0; int tq = 0;
		if(pr[i]==0)
		{
			tp = p[o]+q[i];
			tq = max(p[i]+q[o],q[o]+q[i]);
		}
		else if(pr[i]==1)
		{
			tp = max(p[o]+q[i],max(p[i]+q[o],p[i]+p[o]));
			tq = q[i]+q[o];
		}
		else
		{
			tp = max(p[o]+q[i],p[i]+q[o]);
			tq = q[i]+q[o];
		}
		p[o] = tp; q[o] = tq;
	}
	return max(p[0],q[0]);
}