#include "parks.h"
#include <bits/stdc++.h>
#define fir first
#define sec second
#define pb push_back
typedef long long ll;
using namespace std;

// c is the index of a pair
map<pair<int,int>,int> c;
// taken is the set of points already taken by a bench 
set<pair<int,int>> taken;
// coordinates of the parks
vector<pair<int,int>> coor;

//DSU
int par[200005] = {0};
int find(int x)
{
    if(par[x]==x) return x;
    return par[x] = find(par[x]);
}
void join(int a,int b)
{
    if(find(a)==find(b)) assert(false);
    par[find(a)] = par[find(b)];
}

int cnt = 0;
vector<int> u,v,a,b;
// try making a line from a to b
void addline(int ax,int ay,int bx,int by,int inda,int indb)
{
    if(find(c[{ax,ay}])==find(c[{bx,by}])) return;

    // benches are connected according to chessboard coloring
    pair<int,int> bench = {-1,-1};
    if(ax==bx)
    {
        pair<int,int> tmp = {ax-1,(ay+by)/2};
        if(taken.find(tmp)==taken.end() && (tmp.fir-tmp.sec)%4==0) bench = tmp;
        tmp = {ax+1,(ay+by)/2};
        if(taken.find(tmp)==taken.end() && (tmp.fir-tmp.sec)%4==0) bench = tmp;
    }
    if(ay==by)
    {
        pair<int,int> tmp = {(ax+bx)/2,ay-1};
        if(taken.find(tmp)==taken.end() && (tmp.fir-tmp.sec)%4!=0) bench = tmp;
        tmp = {(ax+bx)/2,ay+1};
        if(taken.find(tmp)==taken.end() && (tmp.fir-tmp.sec)%4!=0) bench = tmp;
    }

    // if we can place a bench, make the road
    if(bench != make_pair(-1,-1))
    {
        join(inda,indb);
        taken.insert(bench);
        u.pb(inda);
        v.pb(indb);
        a.pb(bench.fir);
        b.pb(bench.sec);
        cnt++;
    }
}

int construct_roads(vector<int> x, vector<int> y) 
{
    int n = x.size();
    // init DSU
    for(int i=0;i<n;i++) par[i] = i;
    // 
    for(int i=0;i<n;i++) c[{x[i],y[i]}] = i;
    for(int i=0;i<n;i++) coor.pb({x[i],y[i]});
    sort(coor.begin(),coor.end());
    // sweep from smallest {x,y}

    vector<pair< pair<int,int>,pair<int,int> >> ret;
    for(int i=0;i<n;i++)
    {
        int tx = coor[i].fir;
        int ty = coor[i].sec;
        // if there is a point below or left, check if can connect 
        if(c.count({tx,ty-2})) addline(tx,ty-2,tx,ty,c[{tx,ty}],c[{tx,ty-2}]);
        if(c.count({tx-2,ty})) addline(tx-2,ty,tx,ty,c[{tx,ty}],c[{tx-2,ty}]);
    }

    // if n-1, then a tree is made, else it is not connected
    if(cnt==n-1) 
    {
        build(u,v,a,b); 
        return 1;
    }
    else return 0;
}