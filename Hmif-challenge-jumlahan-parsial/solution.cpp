/* by Ashar Fuadi [fushar] */
 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
 
#include <set>
#include <map>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define REP(i,n) for (int i = 1; i <= (int)n; i++)
#define REPE(u,c) for (int i = 0, u; i < (int)c.size() && (u = c[i], 1); i++)
#define RESET(c,v) memset(c, v, sizeof(c))
#define FOREACH(i,c) for (typeof((c).end()) i = (c).begin(); i != (c).end(); ++i)
 
typedef long long ll;
 
#define pb push_back
#define mp make_pair
 
const int MAX = 2005;
const ll MOD = 1000000007;
int N, K;
ll A[MAX], S[MAX], P[MAX], F[MAX];
 
ll modpow(ll n, ll p)
{
	if (p == 0)
		return 1;
	if (p % 2)
		return (n * modpow(n, p-1)) % MOD;
	ll x = modpow(n, p/2);
	return (x*x) % MOD;
}
 
int main()
{
	cin >> N >> K;
	REP(i, N)
		cin >> A[i];
	
	F[0] = 1;
	REP(i, N)
		F[i] = (i * F[i-1]) % MOD;
	
	REP(i, N)
	{
		ll A = K + i - 1;
		ll B = i;
		P[i] = 1;
		REP(j, i)
			P[i] = (P[i] * (A-j+1)) % MOD;
		P[i] = (P[i] * modpow(F[B], MOD-2)) % MOD;
	}
	
	REP(i, N)
	{
		S[i] = A[i];
		for (int j = 1; j < i; j++)
			S[i] = (S[i] + P[i - j] * A[j]) % MOD;
		
		if (i > 1)
			cout << " ";
		cout << S[i];
	}
	cout << endl;
}