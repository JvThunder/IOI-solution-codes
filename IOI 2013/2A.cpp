#include "cave.h"
#include <bits/stdc++.h>
using namespace std;

int ctry[5005] = {0};
int on[5005] = {0};
int door[5005] = {0};
int vis[5005] = {0};

void invert(int l,int r)
{
    for(int i=l;i<=r;i++)
    {
        if(!vis[i]) ctry[i] = 1-ctry[i];
    }
    return;
}

void exploreCave(int N) 
{
    int cnt = 0;
    while(cnt<N)
    {
        int l = 0; int r = N-1;
        while(vis[l]) l++;
        int ret = l;
        int val = 1;
        int pt = 0;
        int prv = tryCombination(ctry);
        pt = prv;
        if(prv==-1) break;
        while(l<r)
        {
            int mid = (l+r)/2;
            invert(l,mid);
            int x = tryCombination(ctry);
            invert(l,mid);
            if(x==prv)
            {
                l = mid+1;
                ret = mid+1;
            }
            else 
            {
                r = mid;
                if(x<prv && x!=-1) 
                {
                    val = 0;
                    if(x!=-1) pt = x;
                }
                else 
                {
                    val = 1;
                    pt = prv;
                }
            }
        }
        on[ret] = val;
        ctry[ret] = val;
        vis[ret] = 1;
        door[ret] = pt;
        cnt++;
    }
    for(int i=0;i<N;i++)
    {
        if(vis[i]) continue;
        ctry[i] = 1-ctry[i];
        int x = tryCombination(ctry);
        ctry[i] = 1-ctry[i];
        door[i] = x;
    }
    answer(on,door);
    return;
}