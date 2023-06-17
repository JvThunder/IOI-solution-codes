#include "robots.h"

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fir first
#define sec second
typedef long long ll;
int ga,gb;
vector<pair<int,int>> v;

bool greedy(int S)
{
	priority_queue<int> pq;
	int cp = 0;
	for(int i=ga;i>=0;i--)
	{
		while(cp<v.size() && v[cp].fir>=i) pq.push(-v[cp++].sec);
		if(i==0) break;
		int cnt = S;
		while(!pq.empty() && cnt>0)
		{
			pq.pop();
			cnt--;
		}
	}

	for(int i=1;i<=gb;i++)
	{
		if(pq.empty()) return true;
		if(-pq.top()<i) return false; 

		int cnt = S;
		while(!pq.empty() && cnt>0)
		{
			pq.pop();
			cnt--;
		}
	}
	if(!pq.empty()) return false;
	return true;
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) 
{
    ga = A;
	gb = B;

	vector<int> weak;
	for(int i=0;i<A;i++)
	{
		weak.push_back(X[i]);
	}
	sort(weak.begin(),weak.end());

	vector<int> small;
	for(int i=0;i<B;i++)
	{
		small.push_back(Y[i]);
	}
	sort(small.begin(),small.end());

	for(int i=0;i<T;i++)
	{
		int x,y;
		x = weak.end()-upper_bound(weak.begin(),weak.end(),W[i]);
		y = small.end()-upper_bound(small.begin(),small.end(),S[i]);
		v.pb(mp(x,y));
	}
	sort(v.begin(),v.end(),greater<pair<int,int>>());

	//for(auto i:v)
	//{
	//	cout << i.fir << " " << i.sec << endl;
	//}

	int l = 1; int r = T; int ret = -1;
	while(l<=r)
	{
		int mid = (l+r)/2;
		if(greedy(mid))
		{
			r = mid-1;
			ret = mid;
		}
		else l = mid+1;
	}
	return ret;
}