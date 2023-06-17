#include "rail.h"
#include <bits/stdc++.h>
using namespace std;

int dist[5005][5005] = {0};
int getdist(int i,int j)
{
  if(i==j) assert(false);
  if(dist[i][j]) return dist[i][j];
  return dist[i][j] = dist[j][i] = getDistance(i,j);
}

void findLocation(int N, int frst, int pos[], int type[])
{
  vector<pair<int,int>> v;
  set<int> type1;
  set<int> type2;
  for(int i=1;i<N;i++) v.push_back({getdist(0,i),i});
  sort(v.begin(),v.end());
  pos[0] = frst;
  type[0] = 1;
  pos[v[0].second] = pos[0]+v[0].first;
  type[v[0].second] = 2;
  type1.insert(pos[0]);
  type2.insert(pos[v[0].second]);

  int L = 0; int R = v[0].second;
  for(int i=1;i<v.size();i++)
  {
    bool isrdir;
    int cind = v[i].second;
    int cposL = pos[L]+getdist(cind,L);
    int cposR = pos[R]-getdist(cind,R);

    auto it = type1.upper_bound(cposL);
    it--;
    // if ( ) )
    //      ^      (check cind to R)
    if(getdist(R,cind)==cposL-*it+pos[R]-*it) isrdir = false;
    else
    {
      auto it2 = type2.upper_bound(cposR);
      // if ( ( )
      //      ^      (check cind to L)
      if(getdist(L,cind)==*it2-cposR+*it2-pos[L]) isrdir = true;
      // if (   (   ) 
      //    0   ^  firD    (check cind to 0)
      else if(getdist(0,cind)==pos[v[0].second]-pos[0]+pos[v[0].second]-cposR) isrdir = true;
      else isrdir = false;
    }

    if(isrdir) 
    {
      pos[cind] = cposR;
      type[cind] = 1;
      if(pos[cind]<pos[L]) L = cind;
      type1.insert(pos[cind]);
    }
    else 
    {
      pos[cind] = cposL;
      type[cind] = 2;
      if(pos[cind]>pos[R]) R = cind;
      type2.insert(pos[cind]);
    }
  }
  return;
}