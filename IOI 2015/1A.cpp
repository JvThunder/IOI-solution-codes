#include "boxes.h"
#include <bits/stdc++.h>
#define pii pair<int,int>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int MAXN = 1e7+5;
ll prefl[MAXN], prefr[MAXN];
ll delivery(int N, int K, int L, int p[])
{
    ll ret = 1e18;
    prefl[0] = 0; prefr[N+1] = 0;
    for(int i=0;i<K;i++) prefl[i+1] = p[i];
    for(int i=K;i<N;i++) prefl[i+1] = p[i] + prefl[i+1-K];
    for(int i=N-1;i>=N-K;i--) prefr[i+1] = L - p[i];
    for(int i=N-K-1;i>=0;i--) prefr[i+1] = L - p[i] + prefr[i+1+K];
    
    // no full loop
    int rhalf = N;
    for(int i=0;i<N;i++)
    {
        if(p[i]>=(L+1)/2)
        {
            if(i==0) ret = min(ret,2*prefr[i+1]);
            else ret = min(ret,2*prefl[i]+2*prefr[i+1]);
            rhalf = i;
            break;
        }
    }
    if(rhalf==N) ret = min(ret,2*prefl[N]);
    //cout << ret << endl;

    for(int i=0;i<N;i++)
    {
        int rstop = min(rhalf+i,N);
        int lstop = max(rhalf+i-K-1,-1);
        if(lstop>=N) continue;
        //cout << L << " " << 2*prefl[lstop+1] << " " << 2*prefr[rstop+1] << endl;
        ret = min(ret,L+2*prefl[lstop+1]+2*prefr[rstop+1]);   
    }
    
    return ret;
}