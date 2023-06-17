#include <bits/stdc++.h>
#include "game.h"

using namespace std;

void initialize(int n) 
{
    return;
}

int c[1505];
int hasEdge(int u, int v) 
{
    int x = max(u,v);
    return ++c[x] == x;
}