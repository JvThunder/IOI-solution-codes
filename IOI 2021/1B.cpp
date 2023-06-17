#include <bits/stdc++.h>
#include "keys.h"
#define fir first
#define sec second
using namespace std;
 
const int maxn = 3e5 + 5;
int n,m;

bool mk[maxn]; // mark whether we should still visit (no longer visit if no changes)
int r[maxn]; // room keys;
vector<pair<int,int>> conn[maxn]; // connections and the key value that is needed
vector<int> ans; // (to find) the number of rooms that can be visited if start from i 

// DSU
int par[maxn]; // root of group
int sz[maxn]; // size of group
int find(int x) 
{ 
	if (par[x]==x) return x; 
	return par[x]=find(par[x]); 
}

bool have[maxn]; // the keys we already have
bool vis[maxn]; // the nodes we already visit
vector<int> vec[maxn]; // pending nodes, vec[i]: nodes that need key i
int q[maxn]; // the queue for the bfs
int bfs(int s, bool flag = false) // return 0 if no changes else return the new root
{
	int ret = 0;

	// the two pointers for the queue
	int hd = 1;
	int tl = 0;
	
	// start BFS from s
	q[++tl] = s; 
	vis[s] = 1;

	// BFS until the queue is empty
	while (hd<=tl) 
	{
		int x = q[hd++]; // current node of the BFS
		if (!have[r[x]]) // if we have not yet have any keys from current node
		{
			while (!vec[r[x]].empty()) // upadte all from the pending vector
			{
				int y = vec[r[x]].back();
				if (find(y)!=s) ret = find(y); // if node y is from a different roots
				if (!vis[y]) // add y to the BFS
				{
					q[++tl] = y;
					vis[y] = 1;
				}
				vec[r[x]].pop_back();
			}
			have[r[x]] = 1;
		}
		for (pair<int,int> A:conn[x])
		{
			int y = A.fir;
			if (have[A.sec]) // if have the key
			{
				if (find(y)!=s) ret = find(y); // if node y is from a different roots
				if (!vis[y]) // add y to the BFS
				{
					q[++tl] = y;
					vis[y] = 1;
				}
			} 
			else vec[A.sec].push_back(y);
		}
		if (ret) break; //terminate early if we reach a room from a different root
	}

	// reset
	for (int i=1;i<=tl;i++) vis[q[i]] = 0;
	for (int i=1;i<hd;i++) 
	{
		int x = q[i];
		have[r[x]] = 0;
		for (pair<int,int> A : conn[x]) 
			vec[A.sec].clear();
	}

	// in the final BFS, update the answer
	if (flag)
	{
		for (int i=1;i<=tl;i++) 
			ans[q[i]-1] = tl;
	}
	return ret;
}
 
vector<int> find_reachable(vector<int> R,vector<int> U,vector<int> V, vector<int> C) 
{
	n = R.size(); m = U.size();

	// initializing the DSU
	for (int i=1;i<=n;i++) 
	{
		par[i] = i;
		sz[i] = 1;
	}

	// storing the room keys (1-based)
	for (int i=0;i<n;i++) r[i+1] = R[i] + 1;
	
	//initializing the answer array
	ans = vector<int> (n,n+1);

	// converting to the connection list (1-based)
	for (int i=0;i<m;i++) 
	{
		int x,y,z; 
		x=U[i]+1; y=V[i]+1; z=C[i]+1;
		conn[x].push_back({y,z});
		conn[y].push_back({x,z});
	}
	
	// maximum log(n) times
	while (true) 
	{
		bool flag = false; // this tells us whether there is any changes at all 
		// set roots done state initially to 0
		for (int i=1;i<=n;i++) mk[i] = false;
		for (int i=1;i<=n;i++) 
		{
			// starting a BFS from a root that still have changes
			if (find(i)==i && !mk[i]) 
			{
				int t = bfs(i); // the new root of the node
				if (t!=0)
				{
					par[i] = t; // assign a new node as a new root
					mk[t] = true;
					flag = true;
				}
				else mk[i] = true; // if no change, mark the node as done
			}
		}
		if (!flag) break;
	}
	
	for (int i=1;i<=n;i++) 
	{
		// only bfs to the roots
		if (find(i)==i) bfs(i,1);
	}

	// formatting the answer: ans[i] is the number of rooms vis
	// formatting: 1 if is minimum value and 0 otherwise
	int mn = n+1;
	for (int i=1;i<=n;i++) mn = min(mn,ans[i-1]);
	for (int i=1;i<=n;i++) 
	{
		if (mn==ans[i-1]) ans[i-1] = 1; 
		else ans[i-1] = 0;
	}
	return ans;
}