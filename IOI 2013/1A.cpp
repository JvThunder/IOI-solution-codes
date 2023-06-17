#include "dreaming.h"

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fir first
#define sec second
typedef long long ll;

struct edge
{
	int v,w;
};
vector<edge> conn[100005];

int vis[100005] = {0};
int up[100005] = {0};
int up2[100005] = {0};
int upi[100005] = {0};
int down[100005] = {0};
int mxtot = 0;

int dfs(int node,int prv,int d)
{
	vis[node] = 1;
	down[node] = d;
	int mx = 0;
	int mx2 = 0;
	int mxi = 0;
	for(auto x:conn[node])
	{
		if(x.v==prv) continue;
		int tmp = dfs(x.v,node,d+x.w)+x.w;
		if(mx<=tmp)
		{
			upi[node] = x.v;
			mx2 = mx;
			mx = tmp;
		}
		else if(mx2<=tmp) mx2 = tmp;
 	}
	up[node] = mx;
	up2[node] = mx2;
	return mx;
}

int mn = 2e9;
void reroot(int node,int prv)
{
	vis[node] = 1;
	mn = min(mn,up[node]);
	mxtot = max(mxtot,up[node]+up2[node]);
	for(auto x:conn[node])
	{
		if(x.v==prv) continue;
		int save = up[x.v];
		int save2 = up2[x.v];
		int save3 = upi[x.v];

		int tmp;
		if(upi[node]==x.v) tmp = up2[node]+x.w;
		else tmp = up[node]+x.w;
		if(up[x.v]<=tmp)
		{
			upi[x.v] = node;
			up2[x.v] = up[x.v];
			up[x.v] = tmp;
		}
		else if(up2[x.v]<=tmp) up2[x.v] = tmp;

		reroot(x.v,node);
		upi[x.v] = save3;
		up[x.v] = save;
		up2[x.v] = save2;
	}
	return;
}

vector<int> v;
int travelTime(int N, int M, int L, int A[], int B[], int T[]) 
{
	for(int i=0;i<M;i++)
	{
		conn[A[i]].pb({B[i],T[i]});
		conn[B[i]].pb({A[i],T[i]});
	}

	for(int i=0;i<N;i++)
	{
		if(vis[i]) continue;
		dfs(i,-1,0);
	}

	memset(vis,0,sizeof(vis));
	for(int i=0;i<N;i++)
	{
		if(vis[i]) continue;
		mn = 2e9;
		reroot(i,-1);
		v.pb(mn);
	}
	sort(v.begin(),v.end(),greater<int>());
	int fmx = v[0];
	int fmx2 = 0;
	for(int i=1;i<v.size();i++)
	{
		if(v[i]+L>=fmx)
		{
			fmx2 = fmx;
			fmx = v[i]+L;
		}
		else if(v[i]+L>=fmx2) fmx2 = v[i]+L;
	}
	int ret = max(fmx+fmx2,mxtot);
	return ret;
}