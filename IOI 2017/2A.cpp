#include <bits/stdc++.h>
#include "prize.h"
#define pii pair<int,int>
#define pb push_back
#define F first
#define S second
using namespace std;

set<int> s[200005];
int ans[200005];

int dnc(int l,int r)
{
	if(l>r) return -1;
	int mid = (l+r)/2;
	vector<int> tmp = ask(mid);
	ans[mid] = tmp[0];
	if(tmp[0]+tmp[1]==0) return mid;

	auto it = s[tmp[0]+tmp[1]].insert(mid).first;
	if(it == s[tmp[0]+tmp[1]].begin() || ans[*prev(it)]!=ans[mid])
	{
		int tmp = dnc(l,mid-1);
		if(tmp!=-1) return tmp;
	}
	if(it == --s[tmp[0]+tmp[1]].end() || ans[*next(it)]!=ans[mid])
	{
		int tmp = dnc(mid+1,r);
		if(tmp!=-1) return tmp;
	}
	return -1;
}

int find_best(int n)
{
	return dnc(0,n-1);
}