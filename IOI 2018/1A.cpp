#include "combo.h"

#include <bits/stdc++.h>
using namespace std;

string ans = "";
string arr[4] = {"A","B","X","Y"};
int x = 0;
int GN;

void dofirst()
{
  x = press("AB");
  if(x>0)
  {
    x = press("B");
    ans += arr[x];
    return;
  }
  else
  {
    x = press("Y");
    ans += arr[x+2];
    return;
  }
}

void domid()
{
  string ask = "";
  int i = 0; int j = 0; int other = 0;
  while(arr[i][0]==ans[0]) i++;
  ask += ans + arr[i];
  while(arr[j][0]==ans[0] || arr[i]==arr[j]) j++;
  while(arr[other][0]==ans[0] || arr[i]==arr[other] || arr[other]==arr[j]) other++;
  for(int k=0;k<4;k++)
  {
    if(arr[k][0]==ans[0]) continue;
    ask += ans + arr[j] + arr[k];
  }
  x = press(ask);
  if(x==ans.size()+1) ans += arr[i];
  else if(x==ans.size()+2) ans += arr[j];
  else ans += arr[other];
  return;
}

void dolast()
{
  x = press(ans+"A"+ans+"B");
  if(x==GN)
  {
    x = press(ans+"A");
    if(x==GN) ans += "A";
    else ans += "B";
  }
  else
  {
    x = press(ans+"X");
    if(x==GN) ans += "X";
    else ans += "Y";
  }
  return;
}

string guess_sequence(int N) 
{
  GN = N;
  for(int i=1;i<=N;i++)
  {
    if(i==1) dofirst();
    else if(i==N) dolast();
    else domid();
  }
  return ans;
}