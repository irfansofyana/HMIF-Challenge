#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
using namespace std;

const int N = (int)1e5;

int t,n,i,j,k;
int arr[N + 5];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    memset(arr, -1, sizeof arr);
    for (i = 1 ; i <= n ; i++) {
        if (i - k >= 1 && i - k <= n && arr[i-k] == -1) {
            arr[i - k] = i;
        }
        else if (i + k >= 1 && i + k <= n && arr[i + k] == -1) {
            arr[i + k] = i;
        }
        else break;
    }
    if (i != n+1) cout << -1 << '\n';
    else for (i = 1; i <= n ; i++) {
        cout << arr[i];
        cout << (i == n ? '\n' : ' ');
    }
	return 0;
}