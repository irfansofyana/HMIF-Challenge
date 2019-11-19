#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

struct edge {
	int u, v, w;
} ed[MAXN];

long long prefix[MAXN], size[MAXN];
int n, q;
int parent[MAXN];

bool cmp (edge a, edge b) {
	return a.w < b.w;
}

long long nC2 (long long x) {
	return (x * (x - 1)) / 2;
}

int findParent (int u) {
	if(parent[u] == u) return u;
	return parent[u] = findParent(parent[u]);
}

void uni (int u, int v) {
	size[u] += size[v];
	parent[v] = u; 
}

int lBound (int x) {
	int l = 1, r = n - 1, ans = n;
	while (l <= r){
		int mid = (l + r) / 2;
		if (ed[mid].w >= x){
			r = mid - 1;
			ans = mid;
		} else l = mid + 1;
	}
	return ans;
}

int rBound (int x) {
	int l = 1, r = n - 1, ans = 0;
	while (l <= r){
		int mid = (l + r) / 2;
		if (ed[mid].w <= x){
			l = mid + 1;
			ans = mid;
		} else r = mid - 1;
	}
	return ans;
}

void solve () {
	sort(ed + 1, ed + n, cmp);
	for(int i = 1; i <= n; i++) parent[i] = i, size[i] = 1;	
	for(int i = 1; i < n; i++) {
		prefix[i] = prefix[i-1];
		int u = findParent(ed[i].u), v = findParent(ed[i].v);
		prefix[i] -= (nC2(size[u]) + nC2(size[v]));
		uni(u, v);
		prefix[i] += nC2(size[u]);
	}
}

int main () {
    cin >> n >> q;
    for(int i = 1; i < n; i++) cin >> ed[i].u >> ed[i].v >> ed[i].w;
    solve();
	for(int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		l = lBound(l);
		r = rBound(r);
		if(r < l) cout << 0 << endl;
		else cout << prefix[r] - prefix[l-1] << endl;
	}
}