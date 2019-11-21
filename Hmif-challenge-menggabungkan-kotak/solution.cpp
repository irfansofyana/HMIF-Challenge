#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
#define ll long long
#define ull unsigned long long
#define rep(i,n,N) for(ll i=n;i<=N;++i)
#define rap(i,n,N) for(ll i=n;i>=N;--i)
#define mp make_pair
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define fi first
#define se second
#define ff fi.fi
#define fs fi.se
#define sf se.fi
#define ss se.se
#define lc (id<<1)
#define rc ((id<<1)|1)
#define db(x) cout << ">>>>>> " << #x << " -> " << x << endl;
#define all(x) x.begin(),x.end()
#define pii pair<int,int> 
#define pll pair<ll,ll>
#define piii pair<int,pii>
#define piiii pair<pii,pii>
#define psi pair<string,int>
#define endl "\n"
const int MAX = 455;
const ll MAX2 = 11;
const ll MOD = 1000000007;
const ll INF = 2e18;
const int dr[]={1,0,-1,0,1,1,-1,-1,0};
const int dc[]={0,1,0,-1,1,-1,1,-1,0};
const double pi = acos(-1);
const double EPS = 1e-9;
const int block = 455;

ll n,x[MAX],ans;
bool dp[MAX][MAX],vis[MAX][MAX];

bool f(int le,int ri){
	if(le>=ri)return true;
	if(vis[le][ri])return dp[le][ri];
	vis[le][ri] = true;
	ll a = x[le], b = x[ri], idl = le, idr = ri;
	while(idl<idr){
		if(a<b)a+=x[++idl];
		else if(a>b)b+=x[--idr];
		else {
			if(f(le,idl)&&f(idl+1,idr-1)&&f(idr,ri))return dp[le][ri] = true;
			a+=x[++idl], b+=x[--idr];
		}
	}
	return dp[le][ri] = false;
}
 
int main(){
//	cout<<fixed<<setprecision(15);
//    freopen("input.txt", "r", stdin);
//	freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin>>n;
    rep(i,1,n)cin>>x[i];
    ll tmp;
    rep(i,1,n){
    	tmp = 0;
    	rep(j,i,n){
    		tmp+=x[j];
    		if(f(i,j))ans = max(ans,tmp);
		}
	}
	cout<<ans<<endl;
	return 0;
}