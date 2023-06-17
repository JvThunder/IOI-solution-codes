#include "railroad.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
typedef long long ll;
using namespace std;

map<ll,ll> inter;
int INF = 1e9+1;

int par[400005] = {0};
int find(int x)
{
    if(par[x]==x) return x;
    return par[x] = find(par[x]);
}
void join(int a,int b)
{
    int ra = find(a); int rb = find(b);
    if(ra==rb) return;
    par[rb] = ra; 
}

vector<pair<int,pair<int,int>>> edges;
ll plan_roller_coaster(vector<int> s, vector<int> t) 
{
    for(int i=0;i<s.size();i++)
    {
        inter.insert(mp(s[i],0));
        inter.insert(mp(t[i],0));
    }
    inter.insert(mp(0,0));
    inter.insert(mp(INF,0));

    int ind = 1;
    for(auto x:inter) inter[x.fir] = ind++;
    
    vector<pair<pair<int,int>,int>> v;
    v.pb({{0,INF},-1});
    for(int i=0;i<s.size();i++)
    {
        int type = 1;
        if(s[i]>t[i]) type = -1;
        v.pb({{min(s[i],t[i]),max(s[i],t[i])},type});
    }
    int n = v.size();
    sort(v.begin(),v.end());

    for(auto x:v) 
        edges.pb({0,{inter[x.fir.fir],inter[x.fir.sec]}});

    int cnt = 0;
    int ptr = 0;
    int prv = -1;
    ll ans = 0;
    priority_queue<pair<int,int>> pq;
    for(auto x:inter)
    {
        if(x.fir!=0)
        {
            if(cnt==0) edges.pb({x.fir-prv,{inter[x.fir],inter[prv]}});
            else edges.pb({0,{inter[x.fir],inter[prv]}}); 
        }
        ans += max(0,cnt)*(x.fir-prv);

        while(ptr<v.size() && v[ptr].fir.fir<=x.fir)
        {
            pq.push(mp(-v[ptr].fir.sec,v[ptr].sec));
            cnt += v[ptr].sec;
            ptr++;
        }
        while(!pq.empty() && -pq.top().fir<=x.fir) 
        {
            cnt -= pq.top().sec;
            pq.pop();
        }
        prv = x.fir;
    }
    
    sort(edges.begin(),edges.end());
    cnt = ind-2;
    ptr = 0;
    for(int i=1;i<ind;i++) par[i] = i;
    while(ptr<edges.size())
    {
        if(find(edges[ptr].sec.fir)!=find(edges[ptr].sec.sec))
        {
            join(edges[ptr].sec.fir,edges[ptr].sec.sec);
            ans += edges[ptr].fir;
            ptr++;
            cnt--;
        }
        else ptr++;
    }
    return ans;
}