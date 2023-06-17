#include "molecules.h"
typedef long long ll;
#include <bits/stdc++.h>
using namespace std;

vector<int> find_subset(int l,int u,vector<int> w)
{
    int lp = 0;
    ll sum = 0;
    int rp;
    bool done = false;
    vector<pair<int,int> > x;
    for(int i=0;i<w.size();i++)
    {
        x.push_back(make_pair(w[i],i));
    }
    sort(x.begin(),x.end());
    for(rp=0;rp<x.size();rp++)
    {
        sum += x[rp].first;
        while(sum>u) sum -= x[lp++].first;
        if(l<=sum && sum<=u) 
        {
            done = true;
            break;
        }
    }
    vector<int> ans;
    if(!done) return ans;
    for(int i=lp;i<=rp;i++)
    {   
        ans.push_back(x[i].second);
    }
    return ans;
}