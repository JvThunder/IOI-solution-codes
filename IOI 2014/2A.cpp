#include <bits/stdc++.h>
#include "gondola.h"
using namespace std;
typedef long long ll;

int xcnt = 0;
vector<int> ch;
int valid(int n, int A[])
{
  int pos = -1;
  int val = -1;
  vector<int> v;
  for(int i=0;i<n;i++)
  {
    if(A[i]<=n)
    {
      pos = i;
      val = A[i];
    }
    v.push_back(A[i]);
  }
  sort(v.begin(),v.end());
  for(int i=0;i<v.size();i++) if(v[i]>n) ch.push_back(v[i]), xcnt++;
  for(int i=1;i<v.size();i++) if(v[i]==v[i-1]) return 0;

  if(pos==-1) return 1;
  int ret = 1;
  for(int i=0;i<n;i++)
  {
    int ind = (pos+i)%n;
    int cval = (val+i-1)%n+1;
    if(A[ind]<=n && A[ind]!=cval) ret = 0;
  }
  return ret;
}

//----------------------

int replacement(int n, int A[], int R[])
{
  int pos = 0;
  int val = 1;
  for(int i=0;i<n;i++)
  {
    if(A[i]<=n)
    {
      pos = i;
      val = A[i];
      break;
    }
  }

  vector<pair<int,int>> ch;
  for(int i=0;i<n;i++)
  {
    int ind = pos+i;
    if(ind>=n) ind -= n;
    int cval = val+i;
    if(cval>n) cval -= n;
    if(A[ind]>n) ch.push_back({A[ind],cval});
  }
  sort(ch.begin(),ch.end());
  
  int ptr = 0;
  int curr = n+1;
  for(auto x:ch)
  {
    R[ptr++] = x.second;
    for(int i=curr;i<x.first;i++) R[ptr++] = i;
    curr = x.first+1;
  }
  return ptr;
}

//----------------------

int MOD = 1e9+9;
ll exp(int a,int pow)
{
	if(a==0) return 0;
	if(pow==1) return a;
	if(pow<=0) return 1;
	ll tmp = exp(a,pow/2);
	tmp = (tmp*tmp)%MOD;
	if(pow%2) tmp = (tmp*a)%MOD;
	return tmp;
}

int countReplacement(int n, int A[])
{
  if(!valid(n,A)) return 0;
  
  ll ans = 1;
  if(xcnt==n) ans = n;

  int prv = n;
  for(auto x:ch)
  {
    ans = (ans*exp(xcnt--,x-prv-1))%MOD;
    prv = x;
  }
  return ans;
}