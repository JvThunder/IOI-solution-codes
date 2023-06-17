#include <bits/stdc++.h>
#include "holiday.h"
#define F first
#define S second
typedef long long ll;
using namespace std;

const int MAXN = 1<<17;
struct segtree
{
    vector<ll> v,sum,act;

    void init()
    {
        v.clear();
        sum.clear();
        act.clear();
        v.assign(2*MAXN,0LL);
        sum.assign(2*MAXN,0LL);
        act.assign(2*MAXN,0LL);
    }

    void upd(int pos,int node=1,int l=0,int r=MAXN)
    {
        if(r-l==1)
        {
            if(act[node]) sum[node] = 0;
            else sum[node] = v[node];
            act[node] = 1-act[node];
            return;
        }
        int mid = (l+r)/2;
        if(pos<mid) upd(pos,2*node,l,mid);
        else upd(pos,2*node+1,mid,r);
        sum[node] = sum[2*node]+sum[2*node+1];
        act[node] = act[2*node]+act[2*node+1];
    }

    ll query(int x,int node=1,int l=0,int r=MAXN)
    {
        if(node>=MAXN)
        {
            if(x>=act[node]) return sum[node];
            return 0;
        }
        if(x>=act[node]) return sum[node];
        int mid = (l+r)/2;
        if(x>=act[2*node+1]) 
            return sum[2*node+1]+query(x-act[2*node+1],2*node,l,mid);
        else
            return query(x,2*node+1,mid,r);
    }
} st;
int start;

int f[4*MAXN+5] = {0};
ll ans[4*MAXN+5] = {0};
int ind[MAXN] = {0};

void solve(int d,int lx,int rx)
{
    if(ans[d]!=0) return;

    int z = d;
    vector<int> inv;
    d -= (lx-start);
    ans[z] = st.query(d);
    f[z] = lx;
    for(int i=lx;i<=rx;i++)
    {
        st.upd(ind[i]);
        inv.push_back(ind[i]);
        ll tmp = st.query(d);
        if(tmp>ans[z])
        {
            ans[z] = tmp;
            f[z] = i;
        }
        d--;
        if(d<=0) break;
    }
    
    for(auto x:inv) st.upd(x);
    return;
}

void dnc(int l,int r,int lx,int rx)
{
    int mid = (l+r)/2;
    solve(mid,lx,rx);
    if(l==r) return;
    dnc(l,mid,lx,f[mid]);
    for(int i=lx;i<f[mid];i++) st.upd(ind[i]);
    dnc(mid+1,r,f[mid],rx);
    for(int i=lx;i<f[mid];i++) st.upd(ind[i]);
    return;   
}

int f2[4*MAXN+5] = {0};
ll ans2[4*MAXN+5] = {0};

void solve2(int d,int lx,int rx)
{
    if(ans2[d]!=0) return;
    int z = d;
    vector<int> inv;
    d -= (start-1-rx);
    ans2[z] = st.query(d);
    f2[z] = rx;
    for(int i=rx;i>=lx;i--)
    {
        st.upd(ind[i]);
        inv.push_back(ind[i]);
        ll tmp = st.query(d);
        if(tmp>ans2[z])
        {
            ans2[z] = tmp;
            f2[z] = i;
        }
        d--;
        if(d<=0) break;
    }
    
    for(auto x:inv) st.upd(x);
    return;
}

void dnc2(int l,int r,int lx,int rx)
{
    if(rx<lx) return;
    int mid = (l+r)/2;
    solve2(mid,lx,rx);
    if(l==r) return;
    dnc2(l,mid,f2[mid],rx);
    for(int i=rx;i>f2[mid];i--) st.upd(ind[i]);
    dnc2(mid+1,r,lx,f2[mid]);
    for(int i=rx;i>f2[mid];i--) st.upd(ind[i]);
    return;
}

ll findMaxAttraction(int n, int tstart, int d, int A[]) 
{   
    start = tstart;

    st.init();
    vector<pair<int,int>> tmp;
    for(int i=0;i<n;i++) tmp.push_back({A[i],i});
    sort(tmp.begin(),tmp.end());
    for(int i=0;i<n;i++) ind[tmp[i].S] = i, st.v[i+MAXN] = tmp[i].F;
    dnc(1,4*MAXN,start,n-1);

    st.init();
    for(int i=0;i<n;i++) ind[tmp[i].S] = i, st.v[i+MAXN] = tmp[i].F;
    dnc2(1,4*MAXN,0,start-1);

    f[0] = start;
    f2[0] = start;

    ll mx = 0;
    for(int i=0;i<=d;i++)
    {
        int d2 = d-i-(f[i]-start)-1;
        if(d2<0) d2=0;
        mx = max(mx,ans[i]+ans2[d2]);
    }
    for(int i=1;i<=d-1;i++)
    {
        int d2 = d-i-(start-f2[i])-1;
        if(d2<0) d2=0;
        mx = max(mx,ans[d2]+ans2[i]);
    }
    return mx;
}