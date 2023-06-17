#include <vector>
#include <bits/stdc++.h>
#include "messy.h"
using namespace std;

int gn;
vector<int> ans;

string fill(int l,int r)
{
    string ret = "";
    for(int i=1;i<=gn;i++)
    {
        if(l<=i && i<=r) ret += "0";
        else ret += "1";
    }
    return ret;
}

void add_dnc(int l,int r)
{
    if(l==r) return; 
    int mid = (l+r)/2;
    string tmp = fill(l,r);

    for(int i=l;i<=mid;i++)
    {
        tmp[i-1] = '1';
        //cout << tmp << endl;
        add_element(tmp);
        tmp[i-1] = '0';
    }

    add_dnc(l,mid);
    add_dnc(mid+1,r);
    return;
}

void ask_dnc(int l,int r,vector<int> v)
{
    if(l==r)
    {
        if(v.size()!=gn-1) assert(false);
        int vis[205] = {0};
        for(auto x:v)
        {
            vis[x] = 1;
        }
        for(int i=1;i<=gn;i++)
        {
            if(vis[i] == 0) ans[i-1] = l-1; 
        }
        return;
    }

    string tmp = fill(1,gn);
    vector<int> o = v;
    for(auto x:v) tmp[x-1] = '1';
    for(int i=1;i<=gn;i++)
    {
        if(tmp[i-1] == '1') continue;
        tmp[i-1] = '1';
        bool ispres = check_element(tmp);
        //cout << tmp << " " << ispres << endl;
        if(ispres) v.push_back(i);
        else o.push_back(i); 
        tmp[i-1] = '0';
    }

    int mid = (l+r)/2;
    ask_dnc(l,mid,o);
    ask_dnc(mid+1,r,v);
    return;
}

vector<int> restore_permutation(int n, int w, int r) 
{
    gn = n;
    ans.assign(n,-1);
    add_dnc(1,n);
    compile_set();
    vector<int> empt;
    ask_dnc(1,n,empt);
    return ans;
}