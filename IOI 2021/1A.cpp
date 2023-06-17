#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;

const ll INF = (ll)(1e18);

// make a segtree where each leaf represents time of update
// every time we update, we change from considering pos x to x+1
struct segtree
{
    vector<ll> smx, smn, sum; 
    int N;
    segtree()
    {
        N = 1<<18;
        smx.assign(2*N,0); // suffix max
        smn.assign(2*N,0); // suffix min
        sum.assign(2*N,0); // range sum
    }

    void upd(ll v, int t, int node, int lx, int rx) // updates val v into position t 
    {
	    if(rx-lx==1) 
        {
            // set leaf to v
            smx[node] = max(0LL, v);
            smn[node] = min(0LL, v);
            sum[node] = v;
            return;
        }
 
        int mid = (lx+rx)/2;
        if(t<mid) upd(v, t, 2*node, lx, mid);
        else upd(v, t, 2*node+1, mid, rx);
        
        // change values after update
        sum[node] = sum[2*node]+sum[2*node+1];
        smx[node] = max(smx[2*node],sum[2*node]+smx[2*node+1]);
        smn[node] = min(smn[2*node],sum[2*node]+smn[2*node+1]);
        return;
    }
    
    // return the sum of the suffix of the last index smx-smn>c 
    ll get(ll c,int node, int lx, int rx) 
    {
        if(rx-lx==1) return min(max(sum[node], 0LL), c);
    
        int mid = (lx+rx)/2;

        // binary search last index smx-smn>c    
        // if found in right side, directly go right
        if(smx[2*node+1]-smn[2*node+1]>c) return get(c, 2*node+1, mid, rx);
        
        // else go left
        ll a = get(c, 2*node, lx, mid);
        // guarantees not touching the bottom
        if(a+smx[2*node+1]>c) return c-(smx[2*node+1]-sum[2*node+1]);
        // guarantees not touching the top
        if(a+smn[2*node+1]<0) return 0+(sum[2*node+1]-smn[2*node+1]);
        // guarantees not touching both
        return a+sum[2*node+1];

        /*
        Logic behind this 
        Consider the case when it guarantees not touching the bottom
        and that it touches the top at least once.
        We can think of it as if there is a wall on the top.
        When the update touches the wall, the wall moves along with it.
        When the update stop touching, the wall stays.
        After all updates, the wall is the maximum value it ever reaches.
        However, the final value (sum[i]) is not the answer,
        because at some point it exceeds the capacity, thus some value "leaks"
        Fortunately, the relative difference of the wall is preserved
        Thus, diff = wall_height - total_sum
        Analog, it also works when it guarantees not touching the top
        */ 
    }

} st;
 
vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v) 
{
	int n=c.size(), q=l.size();
	vector<int> final_A; // final array
	vector<vector<int>> upd(n+1); // upd[i] store update at pos i

    // positive or negative to show left or right
	for (int i=1; i<=q; i++) upd[l[i-1]].pb(i), upd[r[i-1]+1].pb(-i); 
	for (int i=0; i<n; i++) 
    {
		for (auto j:upd[i]) 
        {
            // j is the index of query
			if (j>0) st.upd(v[j-1], j-1, 1, 0, q);
			else st.upd(0, -j-1, 1, 0, q); // set back pos x to 0
		}
		final_A.pb(st.get(c[i], 1, 0, q));
	}
	return final_A;
}