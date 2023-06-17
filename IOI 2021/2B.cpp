#include "dungeons.h"
#include <bits/stdc++.h>
#define fir first
#define sec second
typedef long long ll;
using namespace std;

//constants
int base = 5; // base here means doing in 2^base
			  // use a higher base instead of 2 for the phase ranges to make the memory efficient
			  // note: using a smaller base decreases runtime but increases memory
			  
const int nop = 5; // no of phase
const int noa = 20; // no of ancestor for binlift
const int sz = 400005; // max size of N
int INF = 1e9+7;

ll add[sz] = {0}; // add[i] = str increase if start at i & win all
pair<int,pair<int,ll>> jump[nop][noa][sz]; // store: jump dest, min(str_opp - str_gained), str_inc
										 // jump[a][b][i] is game simulation starting from index i &
										 // jump 2^b steps ahead assuming only win against everything <=8^a

int N;
vector<int> S,P,W,L; 

void init(int n, vector<int> s, vector<int> p, vector<int> w, vector<int> l) 
{
	S = s; P = p; W = w; L = l; N = n;

	// add dummy node for index n
	S.push_back(INF);
	P.push_back(INF);
	W.push_back(n);
	L.push_back(n);
	
	// assume always wins
	for(int i=n-1; i>=0; i--) add[i] = add[W[i]] + S[i];

	for(int ph=0; ph<nop; ph++) // ph: phase
	{
		// current phase range
		ll l = 1<<(base*ph);
		ll r = 1<<(base*(ph+1));

		for(int i=0; i<=n; i++) 
		{
			// if in range, assume lose but store its min(str_opp - str_gained)
			if ((l<S[i] && S[i]<r) || i==n) jump[ph][0][i] = {L[i], {S[i], P[i]}};
			// if below range, assume win
			else if (S[i]<=l) jump[ph][0][i] = {W[i], {INF, S[i]}};
			// if above range, assume lose
			else jump[ph][0][i] = {L[i], {INF, P[i]}};
		}
		
		// binlift
		for(int b=1; b<noa; b++) // no of jump = 2^b
		{
			for (int i=0; i<=n; i++)
			{
				int pos = i;
				ll min_S = INF, str_add = 0;
				for (int it=0; it<2; it++) // 2 jumps of 2^(i-1) -> 1 jump of 2^i
				{
					auto pr = jump[ph][b-1][pos];
					min_S = min(min_S, pr.sec.fir-str_add); // min(str_opp - str_gained) of all prefixes up to 2^b jumps
					str_add += pr.sec.sec; // strength inc from 2^b jumps
					pos = pr.first; // landing position after 2^b jumps
				}
				jump[ph][b][i] = {pos, {min_S, str_add}};
			}
		}
	}
	return;
}
 
ll simulate(int x, int z) 
{
	ll pos = x; // current position
	ll str = z; // current strength

	for(int a=0; a<nop; a++)
	{
		// current phase range
		ll l = 1<<(base*a);
		ll r = 1<<(base*(a+1));
		while(pos!=N && l<=str && str<r)
		{
			for(int b=noa-1; b>=0; b--) // binlift until 1 step before you can beat a person with a higher phase
			{
				// condition 1 is true if still in current phase range
				// condition 2 is true if no win against a current phase range
				while(str+jump[a][b][pos].sec.sec < r && str-jump[a][b][pos].sec.fir < 0)
				{
					str += jump[a][b][pos].sec.sec;
					pos = jump[a][b][pos].fir;
				}
			}

			if(pos!=N) // simulate 1 move naive
			{
				if(str>=S[pos]) str += S[pos], pos = W[pos];
				else str += P[pos], pos = L[pos];
			}
		}
	}

	str += add[pos]; //assume win all
	return str;
}