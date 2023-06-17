#include <bits/stdc++.h>
#include "aliens.h"
#define fir first
#define sec second
#define mp make_pair
#define pb push_back
typedef long long ll;

using namespace std;

vector<pair<ll,ll>> v;
int N,K,M; // v size

ll sq(ll x){return x*x;}

bool comp(pair<int,int> a, pair<int,int> b)
{
    if(a.fir<b.fir) return true;
    else if(a.fir>b.fir) return false;
    else
    {
        if(a.sec<=b.sec) return false;
        else return true;
    }
    return false;
}

bool Q;
struct Line 
{
	mutable ll k, m, p, ph;
	bool operator<(const Line& o) const 
    {
		return Q ? p < o.p : k < o.k;
	}
};
 
struct LineContainer : multiset<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }

	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}

	void add(ll k, ll m,ll ph) {
		auto z = insert({k, m, 0, ph}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}

	pair<ll,ll> query(ll x) 
    {
		assert(!empty());
		Q = 1; auto l = *lower_bound({0,0,x,0}); Q = 0;
		return mp(l.k * x + l.m, l.ph);
	}
};

ll g[100005] = {0}; 
pair<ll,ll> calc(ll penalty)
{

    LineContainer CHT;
    ll m = -2*(v[0].fir-1);
    ll b = g[0]+sq(v[0].fir-1);
    ll phcnt = 0;
    CHT.add(-m,-b,0);
    for(int i=1;i<=N;i++)
    {
        auto x = CHT.query(v[i-1].sec);
        ll tmp = -x.fir;
        tmp += sq(v[i-1].sec)+penalty;
        g[i] = tmp;

        ll m = -2*(v[i].fir-1);
        ll b = g[i]+sq(v[i].fir-1)-sq(max(0LL,v[i-1].sec-v[i].fir+1));
        CHT.add(-m,-b,x.sec+1);
        phcnt = x.sec+1;
    } 
    return mp(g[N]-phcnt*penalty,phcnt); // return f(N) and P(C)
}

ll binser()
{
    ll l = 0; ll r =1e11;
    ll ret = 0;
    while(l<=r)
    {
        ll mid = (l+r)/2;
        auto x = calc(mid);
        if(x.sec>=K)
        {
            ret = mid;
            l = mid+1;
        }
        else
        {
            r = mid-1;
        }
    }
    auto z1 = calc(ret);
    auto z2 = calc(ret+1);
    ll f1 = z1.fir; ll f2 = z2.fir;
    ll p1 = z1.sec; ll p2 = z2.sec;
    if(p1==p2) return f1;
    ll ans = f2-(f2-f1)*(K-p2)/(p1-p2);
    return ans;
}

ll take_photos(int n, int m, int k, vector<int> r, vector<int> c) 
{
    vector<pair<int,int>> tmp;
    for(int i=0;i<r.size();i++) 
    {
        int x = min(r[i],c[i]);
        int y = max(r[i],c[i]);
        tmp.pb(mp(x,y));
    }
    sort(tmp.begin(),tmp.end(),comp);
    
    for(int i=0;i<tmp.size();i++)
    {
        if(v.empty()) v.pb(tmp[i]);
        else if(v.back().fir>tmp[i].fir || tmp[i].sec>v.back().sec) v.pb(tmp[i]);
    }
    N = v.size();
    K = k;
    M = m;
    return binser();
}