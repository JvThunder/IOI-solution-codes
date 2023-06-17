#include "shoes.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
queue<int> s1[2][200005];
ll ft[200005] = {0};

void upd(ll i,ll val)
{
	for(;i<=200000;i+=i&-i)
	{
		ft[i] += val;
	}
	return;
}

ll query(int j)
{
	ll ans = 0;
	for(;j;j-=j&-j)
	{
		ans += ft[j];
	}
	return ans;
}

ll count_swaps(std::vector<int> s) 
{
	for(int i=1;i<=200000;i++)
	{
		upd(i,1);
	}
	ll ans = 0;
	for(int i=0;i<s.size();i++)
	{
		ll type = 1;
		if(s[i]<0) type = 0;
		ll tmp = abs(s[i]);
		if(!s1[type][tmp].empty())
		{
			ll x = s1[type][tmp].front();
			ll tans = query(i)-query(x);
			upd(i+1,-1);
			upd(x,1); 
			s1[type][tmp].pop();
			if(type==0) tans++;
			ans += tans;		
		}
		else s1[1-type][tmp].push(i+1);
	}
	return ans;
}