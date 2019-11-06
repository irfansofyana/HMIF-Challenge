#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n,m,i,j;
ll andi[150005],budi[150005],coki[150005];
ll ans,tmp;
ll tree[500005];
ll smt[150005];

ll leftt(ll x){
	return (x<<1);
}

ll rightt(ll x){
	return (x<<1)+1;
}

void build(ll l,ll r,ll nomor) {
	if (l == r) {
		tree[nomor] = l;
	}
	else {
		ll mid = (l+r)/2;
		build(l,mid,leftt(nomor));
		build(mid+1,r,rightt(nomor));
		tree[nomor] = (smt[tree[leftt(nomor)]] <= smt[tree[rightt(nomor)]] ? tree[leftt(nomor)] : tree[rightt(nomor)]);
	}
}

ll query(ll kiri,ll kanan,ll l,ll r,ll nomor){
	if (kanan < l || kiri > r) return -10000000000;
	else if (l <= kiri && kanan <= r) {
		return tree[nomor];
	}
	else {
		ll mid = (kiri+kanan)/2;
		ll tempa,tempb;
		tempa = query(kiri,mid,l,r,leftt(nomor));
		tempb = query(mid+1,kanan,l,r,rightt(nomor));
		if (tempa == -10000000000) return tempb;
		if (tempb == -10000000000) return tempa;
		return (smt[tempa] <= smt[tempb] ? tempa: tempb);
	}
}

void ulang(){
	memset(tree,0,sizeof tree);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	/*cin >> n;
	for (i = 1 ; i <= n ; i++)
		cin >> smt[i];
	build(1,n,1);
	int q;
	cin >> q;
	while (q--) {
		int a,b;
		cin >> a >> b;
		cout << query(1,n,a,b,1) << endl;
	}*/
	cin >> n;
	for (i = 1 ; i <= n ; i++) {
		cin >> andi[i];
		andi[i] += andi[i-1];
	}
	for (i = 1 ; i <= n ; i++) {
		cin >> budi[i];
		budi[i] += budi[i-1];
	}
	for (i = 1 ; i <= n ; i++) {
		cin >> coki[i];
		coki[i] += coki[i-1];
	}
	
	bool pertama = true;
	for (i = 1 ; i <= n ; i++)
		smt[i] = budi[i]-coki[i];
	build(1,n,1);
	for (i = 1 ; i <= n-2 ; i++) {
		tmp = andi[i]-budi[i];
		tmp += coki[n];
		tmp += smt[query(1,n,i+1,n-1,1)];
		if (pertama) {
			pertama = false;
			ans = tmp;
		}
		else ans = min(ans,tmp);
	}
	ulang();
	for (i = 1 ; i <= n ; i++) 
		smt[i] = coki[i]-budi[i];
	build(1,n,1);
	for (i = 1 ; i <= n-2; i++) {
		tmp = andi[i]-coki[i];
		tmp += budi[n];
		tmp += smt[query(1,n,i+1,n-1,1)];
		if (pertama) {
			pertama = false;
			ans = tmp;
		}
		else ans = min(ans,tmp);
	}
	ulang();
	for (i = 1 ; i <= n ; i++) 
		smt[i] = andi[i]-coki[i];
	build(1,n,1);
	for (i = 1 ; i <= n-2; i++) {
		tmp = budi[i]-andi[i];
		tmp += coki[n];
		tmp += smt[query(1,n,i+1,n-1,1)];
		//ans = min(ans,tmp);
		if (pertama) {
			pertama = false;
			ans = tmp;
		}
		else ans = min(ans,tmp);
	}
	ulang();
	for (i = 1 ; i <= n ; i++)
		smt[i] = coki[i]-andi[i];
	build(1,n,1);
	for (i = 1; i <= n-2; i++) {
		tmp = budi[i]-coki[i];
		tmp += andi[n];
		tmp += smt[query(1,n,i+1,n-1,1)];
		if (pertama) {
			pertama = false;
			ans = tmp;
		}
		else ans = min(ans,tmp);
	}
	ulang();	
	for (i = 1 ; i <= n ; i++)
		smt[i] = andi[i]-budi[i];
	build(1,n,1);
	for (i = 1; i <= n-2; i++) {
		tmp = coki[i]-andi[i];
		tmp += budi[n];
		tmp += smt[query(1,n,i+1,n-1,1)];
		if (pertama) {
			pertama = false;
			ans = tmp;
		}
		else ans = min(ans,tmp);
	}	
	ulang();
	for (i = 1 ; i <= n ; i++)
		smt[i] = budi[i]-andi[i];
	build(1,n,1);
	for (i = 1; i <= n-2; i++) {
		tmp = coki[i]-budi[i];
		tmp += andi[n];
		tmp += smt[query(1,n,i+1,n-1,1)];
		if (pertama) {
			pertama = false;
			ans = tmp;
		}
		else ans = min(ans,tmp);
	}
	cout << ans << '\n';
	return 0;
}