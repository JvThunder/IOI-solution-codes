#include "paint.h"
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

int pref[2][200005] = {0};
int suff[2][200005] = {0};
int P[105][200005] = {0};
int S[105][200005] = {0};
int canw[200005] = {0};
int canb[200005] = {0};
int n,k;
vector<int> block;
string str;
string sret = "";

int prefdp(int i,int j)
{
    int ret;
    if(P[i][j]!=-1) return P[i][j];
    if(i==0)
    {
        if(pref[1][j]==0) ret = 1;
        else ret = 0;
    }
    else
    {
        int c = block[i-1];
        int tmp;
        if(j<c) tmp = 0; 
        else if(str[j-c-1]=='X' || pref[0][j]-pref[0][j-c]!=0) tmp = 0;
        else 
        {
            if(j==c && i==1) tmp = 1;
            else tmp = prefdp(i-1,j-c-1);
        }

        if(j<c) ret = 0;
        else if(str[j-1]=='_') ret = prefdp(i,j-1);
        else if(str[j-1]=='X') ret = tmp;
        else ret = (prefdp(i,j-1) || tmp);
    }
    //if(P[i][j-1]==1) ret = 1;
    return P[i][j] = ret;
}

int suffdp(int i,int j)
{
    int ret;
    if(S[i][j]!=-1) return S[i][j];
    if(i==0)
    {
        if(suff[1][j]==0) ret = 1;
        else ret = 0;
    }
    else
    {
        int c = block[i-1];
        int tmp;
        if(j+c>n+1) tmp = 0; 
        else if(str[j+c-1]=='X' || suff[0][j]-suff[0][j+c]!=0) tmp = 0;
        else 
        {
            if(j+c==n+1 && i==1) tmp = 1;
            else tmp = suffdp(i-1,j+c+1);
        }

        if(j+c>n+1) ret = 0;
        else if(j==n+1) ret = 1; 
        else if(str[j-1]=='_') ret = suffdp(i,j+1);
        else if(str[j-1]=='X') ret = tmp;
        else ret = (suffdp(i,j+1) || tmp);
    }
    //if(S[i][j+1]==1) ret = 1;
    return S[i][j] = ret;
}

string solve_puzzle(string s, vector<int> c) 
{
    n = s.length();
    k = c.size();
    str = s;

    // step 1 (precompute prefix and suffix)
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='_') pref[0][i+1] = pref[0][i]+1;
        else pref[0][i+1] = pref[0][i];
        if(s[i]=='X') pref[1][i+1] = pref[1][i]+1;
        else pref[1][i+1] = pref[1][i];
    }
    for(int i=s.length()-1;i>=0;i--)
    {
        if(s[i]=='_') suff[0][i+1] = suff[0][i+2]+1;
        else suff[0][i+1] = suff[0][i+2];
        if(s[i]=='X') suff[1][i+1] = suff[1][i+2]+1;
        else suff[1][i+1] = suff[1][i+2];
    }

    // step 2 (compute P[i][j])
    block = c;
    memset(P,-1,sizeof(P));
    P[0][0] = 1;
    P[0][n+1] = 1;
    for(int i=0;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            prefdp(i,j);
            //cout << prefdp(i,j) << " ";
        }
        //cout << endl;
    }

    // step 3 (compute S[i][j])
    reverse(block.begin(),block.end());
    memset(S,-1,sizeof(S));
    S[0][0] = 1;
    S[0][n+1] = 1;
    for(int i=0;i<=k;i++)
    {
        for(int j=n;j>=1;j--)
        {
            suffdp(i,j);
            //cout << suffdp(i,j) << " ";
        }
        //cout << endl;
    }

    // step 4 (find which can be white) 
    for(int i=1;i<=n;i++)
    {
        if(s[i-1]=='X') continue;
        bool poss = false;
        for(int j=0;j<=k;j++)
        {
            if(P[j][i-1]==1 && S[k-j][i+1]==1) poss = true; 
        }
        if(poss) canw[i] = 1;
    }

    // step 5 (find which can be black) 
    int cont = 0;
    for(int t=0;t<k;t++)
    {
        int ct = c[t];
        bool can;
        for(int i=1;i<=n;i++)
        {
            if(cont>0)
            {
                cont--;
                canb[i] = 1;
            }
            can = true;
            if(s[i-1]=='_')
            {
                canb[i] = 0;
                continue;
            }

            if(i-1>=1)
                if(s[i-2]=='X') can = false;
            if(i+ct<=n)
                if(s[i+ct-1]=='X') can = false;

            if(pref[0][min(n,i+ct-1)]-pref[0][i-1]>0) can = false;

            if(t==0)
            {
                if(i>=2 && P[t][i-2]==0) can = false;
            }
            else
            {
                if(i<=2 || P[t][i-2]==0) can = false;
            }
                

            if(i+ct-1>n || S[k-t-1][i+ct+1]==0) can = false;
            if(can) 
            {
                canb[i] = 1;
                cont =  ct-1;
            }
        }
    }

    for(int i=1;i<=n;i++)
    {
        if(canw[i]==1 && canb[i]==1) sret += "?";
        else if(canw[i]==1) sret += "_";
        else if(canb[i]==1) sret += "X";
        else assert(false);
    }
    return sret;
}