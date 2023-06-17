#include "wiring.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
typedef long long ll;
using namespace std;

ll INF = 1e18;
int n,i,j;
vector<pair<ll,ll>>v;
ll st[200005],en[200005],pref[200005],ans[200005];
ll min_total_length(vector<int> r, vector<int> b) 
{
	n = r.size()+b.size();
	for(int i=1;i<=n;i++) ans[i] = INF;
	ans[0] = 0;
	for(auto x:r) v.pb({x,0});
	for(auto x:b) v.pb({x,1});
	v.pb({-1,-1}); //so it is 1-based
	sort(v.begin(),v.end());
	
	// st[i] first index such that arr[i-1]=/=arr[i]
	i = j = 1;
	while(i<=n)
	{
		while(j<=n && v[i].sec==v[j].sec) st[j++] = i;
		i = j;
	}
	
	// en[i]: st[i] but in reverse
	i = j = n;
	while(i>=1)
	{
		while(j>=1 && v[i].sec==v[j].sec) en[j--] = i;
		i = j;
	}

	pref[0] = 0;
	for(int i=1;i<=n;i++) pref[i] = pref[i-1]+v[i].fir;

	// ans[i] min cost to connect 1...i
	for(int i=1;i<=n;i++)
	{
		//connect to nearest
		if(st[i]!=1) ans[i] = min(ans[i],ans[i-1]+v[i].fir-v[st[i]-1].fir);
		if(en[i]!=n) ans[i] = min(ans[i],ans[i-1]+v[en[i]+1].fir-v[i].fir);
		if(st[i]==1) continue;
		
		//greedily connect prvblock to currind  
		if(st[i]==i)
		{
			ll tmp = 0;
			for(int j=i-1;j>=st[i-1];j--)
			{
				tmp += v[i].fir-v[j].fir;
				ans[i] = min(ans[i],ans[j-1]+tmp);
			}
		}

		//greedy connect currblock with prvblock
		int prvb = st[i]-st[st[i]-1];
		int currb = i-st[i]+1;
		if(currb<=prvb)
		{
			ll tmp = (pref[i]-pref[st[i]-1]) - (pref[st[i]-1]-pref[st[i]-currb-1]);
			ans[i] = min(ans[i],ans[st[i]-currb-1]+tmp);
		}
	}
	return ans[n];
}