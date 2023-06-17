#include "dna.h"
#include <bits/stdc++.h>
using namespace std;

int prefac[100005] = {0};
int prefat[100005] = {0};
int prefca[100005] = {0};
int prefct[100005] = {0};
int prefta[100005] = {0};
int preftc[100005] = {0};

void init(string a, string b) 
{
	for(int i=1;i<=a.size();i++)
	{
		prefac[i] = prefac[i-1] + ('A'==a[i-1] && 'C'==b[i-1]);
		prefat[i] = prefat[i-1] + ('A'==a[i-1] && 'T'==b[i-1]);
		prefca[i] = prefca[i-1] + ('C'==a[i-1] && 'A'==b[i-1]);
		prefct[i] = prefct[i-1] + ('C'==a[i-1] && 'T'==b[i-1]);
		prefta[i] = prefta[i-1] + ('T'==a[i-1] && 'A'==b[i-1]);
		preftc[i] = preftc[i-1] + ('T'==a[i-1] && 'C'==b[i-1]);
	}
}

int get_distance(int x, int y) 
{
	int ans = 0;
	int ac = prefac[y+1]-prefac[x];
	int at = prefat[y+1]-prefat[x];
	int ca = prefca[y+1]-prefca[x];
	int ct = prefct[y+1]-prefct[x];
	int ta = prefta[y+1]-prefta[x];
	int tc = preftc[y+1]-preftc[x];

	int tmp = min(ac,ca);
	ans += tmp;
	ac -= tmp;
	ca -= tmp;
	tmp = min(at,ta);
	ans += tmp;
	at -= tmp;
	ta -= tmp;
	tmp = min(ct,tc);
	ans += tmp;
	ct -= tmp;
	tc -= tmp;

	if(tc+ct+ac+ca+at+ta==0) return ans; 
	else if(tc!=0 && ca!=0 && at!=0)
	{
		if(tc!=ca || ca!=at) return -1;
		else return ans+2*tc;
	}
	if(ct!=0 && ta!=0 && ac!=0)
	{
		if(ct!=ta || ta!=ac) return -1;
		else return ans+2*ct;
	}
	return -1;
}
