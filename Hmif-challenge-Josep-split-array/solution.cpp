#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

long long dp[MAXN+5][55];
long long prefiks[MAXN+5];
int n, m;

long long query(int a,int b){
    return prefiks[b] - (a == 0 ? 0 : prefiks[a-1]);    
}

long long cari(int pos, int rem){
    if (pos == n && rem == 0){
        return 0;
    }
    if (pos == n || rem < 0){
        return 1e18;
    }
    if (rem == 0 && pos != n){
        return 1e18;
    }
    long long &ret = dp[pos][rem];
    if (ret != -1) return ret;
    for (int i = pos; i < n; ++i){
        if (ret == -1){
            ret = max(query(pos, i), cari(i+1, rem-1));
        }else {
            ret = min(ret, max(query(pos, i), cari(i+1, rem-1)));
        }
    }
    return ret;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i){
        long long x; cin >> x;
        prefiks[i] = (i == 0 ? x : prefiks[i-1] + x);
    }
    memset(dp, -1, sizeof dp);
    cout << cari(0, m) << '\n';
    return 0;
}