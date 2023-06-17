#include "game.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
typedef long long ll;
using namespace std;
const ll N = 1<<30;
//creds to Berted for memory opt

inline ll gcd(ll x, ll y) 
{
    ll tmp;
	while(x!=y && y!=0)
	{
		tmp = x;
		x = y;
		y = tmp % y;
	}
	return x;
}

const int MAX = 1e7+5;
struct segtree
{
	int row,col;
	vector<pair<int,int>> Cx;
	vector<int> Rx;
	pair<int,int> C[MAX];
	int keep[MAX];
	ll val[MAX];
	int ptr = 0;

	int newnode()
	{
		C[ptr] = {-1,-1}; keep[ptr] = -2; ptr++;
		return ptr-1;
	}

	int newline()
	{
		Cx.pb({-1,-1}); Rx.pb(-1);
		Rx.back() = newnode();
		return Cx.size()-1;
	}

	void checkchildx(int curr,bool b)
	{
		int tmp;
		if(b && Cx[curr].fir==-1) tmp = newline(), Cx[curr].fir = tmp;
		if(!b && Cx[curr].sec==-1) tmp = newline(), Cx[curr].sec = tmp;
	}

	void checkchildy(int curr,bool b)
	{
		int tmp;
		if(b && C[curr].fir==-1) tmp = newnode(), C[curr].fir = tmp;
		if(!b && C[curr].sec==-1) tmp = newnode(), C[curr].sec = tmp;
	}

	int getroot(int curr)
	{
		if(curr==-1) return -1;
		else return Rx[curr];
	}

	int getchild(int curr,bool b)
	{
		if(curr==-1) return -1;
		else if(b) return C[curr].fir;
		else return C[curr].sec;
	}

	ll getval(int curr)
	{
		if(curr==-1) return 0;
		return val[curr];
	}

	void updy(int node,int l,int r,int pos,ll v)
	{
		if(l<r && (keep[node]!=-2 && keep[node]!=pos))
		{
			int mid = (l+r)/2;
			if(keep[node]!=-1)
			{
				checkchildy(node,keep[node]<=mid);
				if(keep[node]<=mid)
				{
					val[C[node].fir] = val[node];
					keep[C[node].fir] = keep[node];
				}
				else
				{
					val[C[node].sec] = val[node];
					keep[C[node].sec] = keep[node];
				}
				keep[node] = -1;
			}
			checkchildy(node,pos<=mid);
			if(pos<=mid) updy(C[node].fir,l,mid,pos,v);
			else updy(C[node].sec,mid+1,r,pos,v);
			val[node] = gcd(getval(C[node].fir),getval(C[node].sec));
		}
		else keep[node] = pos, val[node] = v;
	}

	ll queryy(int node,int L,int R,int l,int r)
	{
		l = max(L,l); r = min(R,r);
		if(node==-1) return 0;
		if(l<=r)
		{
			if(L==l && R==r) return val[node];
			else if(keep[node]!=-1)
			{
				if(l<=keep[node] && keep[node]<=r) return val[node];
				else return 0;
			}
			else
			{
				int mid = (L+R)/2;
				return gcd(queryy(C[node].fir,L,mid,l,r),
				queryy(C[node].sec,mid+1,R,l,r));
			}
		} 
		return 0;
	}

	void updx(int node,int l,int r,int x,int y,ll v)
	{
		if(l<r)
		{
			int mid = (l+r)/2;
			checkchildx(node,x<=mid);
			if(x<=mid) updx(Cx[node].fir,l,mid,x,y,v);
			else updx(Cx[node].sec,mid+1,r,x,y,v);
			v = gcd(queryy(getroot(Cx[node].fir),0,row-1,y,y),
			queryy(getroot(Cx[node].sec),0,row-1,y,y));
		}
		updy(Rx[node],0,row-1,y,v);
	}

	ll queryx(int node,int l,int r,int lx,int rx,int ly,int ry)
	{
		lx = max(lx,l); rx = min(rx,r);
		if(node==-1) return 0;
		if(lx<=rx)
		{
			if(l==lx && r==rx) return queryy(Rx[node],0,row-1,ly,ry);
			else
			{
				int mid = (l+r)/2;
				return gcd(queryx(Cx[node].fir,l,mid,lx,rx,ly,ry),
				queryx(Cx[node].sec,mid+1,r,lx,rx,ly,ry));
			}
		}
		return 0;
	}
	
};

segtree st;
void init(int R, int C) 
{
	st.row = R; st.col = C; st.newline();
	return;
}

void update(int P, int Q, ll K) 
{
	st.updx(0,0,st.col-1,Q,P,K);
}

ll calculate(int P, int Q, int U, int V) 
{
	return st.queryx(0,0,st.col-1,Q,V,P,U);
}