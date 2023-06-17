#include <bits/stdc++.h>
#include "horses.h"
typedef long long ll;
typedef long double ld;
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 5e5;

struct Node
{
	int x,y,ans;
	double logx,logy,logans;
};

const int N = 1<<19;
struct segtree
{
	vector<Node> v;
	void init()
	{
		Node tmp;
		v.assign(2*N,tmp);
	}
	
	void upd(int pos,int type,int val,int node,int lx,int rx)
	{
		if(rx-lx==1)
		{
			if(type==1) v[node].x = val;
			else v[node].y = val;
			v[node].ans = (1LL*v[node].x*v[node].y)%MOD;
			v[node].logx = log(v[node].x);
			v[node].logy = log(v[node].y);
			v[node].logans = v[node].logx + v[node].logy;
			return;
		}
		int mid = (lx+rx)/2;
		if(pos<mid) upd(pos,type,val,2*node,lx,mid);
		else upd(pos,type,val,2*node+1,mid,rx);

		v[node].x = (1LL*v[2*node].x*v[2*node+1].x)%MOD;
		v[node].logx = v[2*node].logx + v[2*node+1].logx;

		if(v[2*node].logx+v[2*node+1].logans>v[2*node].logans)
		{
			v[node].ans =  (1LL*v[2*node].x*v[2*node+1].ans)%MOD;
			v[node].logans = v[2*node].logx+v[2*node+1].logans;
		}
		else
		{
			v[node].ans = v[2*node].ans;
			v[node].logans = v[2*node].logans;
		}
	}
} st;

int init(int n, int X[], int Y[])
{
	st.init();
	for(int i=0;i<n;i++)
	{
		st.upd(i,1,X[i],1,0,N);
		st.upd(i,2,Y[i],1,0,N);
	}
	return st.v[1].ans;
}

int updateX(int pos, int val)
{	
	st.upd(pos,1,val,1,0,N);
	return st.v[1].ans;
}

int updateY(int pos, int val)
{
	st.upd(pos,2,val,1,0,N);
	return st.v[1].ans;
}