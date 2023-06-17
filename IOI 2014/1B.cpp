#include "wall.h"

#include <bits/stdc++.h>
using namespace std;

int N;
int INF = 1e9;
struct segtree
{
  vector<int> lazycut;
  vector<int> lazyadd;

  void init()
  {
    lazycut.assign(2*N,INF);
    lazyadd.assign(2*N,-1);
  }

  void op(int node,int val,int type)
  {
    if(type==1)
    {
      if(lazycut[node]<val)
      {
        lazycut[node] = val;
        lazyadd[node] = val;
      } 
      else lazyadd[node] = max(lazyadd[node],val);
    } 
    else
    {
      if(lazyadd[node]==-1) lazycut[node] = min(lazycut[node],val);
      if(lazyadd[node]>val) 
      {
        lazycut[node] = val;
        lazyadd[node] = val;
      }
      else lazycut[node] = min(lazycut[node],val);
    }  
  }

  void upd(int l,int r,int val,int type,int node,int lx,int rx)
  {
    if(lx>=r || l>=rx) return;
    if(l<=lx && rx<=r)
    {
      op(node,val,type);
      return;
    }
    if(lazyadd[node]!=-1)
    {
      op(2*node,lazyadd[node],1);
      op(2*node+1,lazyadd[node],1);
      lazyadd[node] = -1;
    }
    if(lazycut[node]!=INF)
    {
      op(2*node,lazycut[node],2);
      op(2*node+1,lazycut[node],2);
      lazycut[node] = INF;
    }

    int mid = (lx+rx)/2;
    upd(l,r,val,type,2*node,lx,mid);
    upd(l,r,val,type,2*node+1,mid,rx);
    return;
  }

};

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[])
{
  N = sizeof(int)*8-__builtin_clz(n);
  N = 1<<N;
  segtree st;
  st.init();
  for(int i=0;i<k;i++)
  {
    st.upd(left[i],right[i]+1,height[i],op[i],1,0,N);
  }
  for(int i=0;i<n;i++)
  {
    int tmp = 0;
    int node = i+N;
    while(node!=0)
    {
      if(st.lazyadd[node]>tmp) tmp = st.lazyadd[node];
      if(st.lazycut[node]<tmp) tmp = st.lazycut[node];
      node/=2;
    }
    finalHeight[i] = tmp;
  }
  return;
}