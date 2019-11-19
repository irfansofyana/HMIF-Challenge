#include<bits/stdc++.h>
#define pb push_back
#define fs first
#define sc second
#define mp make_pair
#define INF -1000000000
using namespace std;
	
int n,q,c,m;
int color[100005];
int val[100005];
int bapak[100005];
vector<int> isi[100005];
priority_queue<pair<int,int> > pq[100005];
int ans;
string label;

int caribapak(int a){
	if(bapak[a] == a) return a;
	return bapak[a] = caribapak(bapak[a]);
}

void gabung(int a, int b){
	int x = caribapak(a);
	int y = caribapak(b);
	if(x != y){
		if(isi[x].size() < isi[y].size()){
			for(int i = 0; i < isi[x].size(); i++){
				int now = isi[x][i];
				bapak[now] = y;
				isi[y].pb(now);
			}
		}else{
			for(int i = 0; i < isi[y].size(); i++){
				int now = isi[y][i];
				bapak[now] = x;
				isi[x].pb(now);
			}
		}
	}
}

int main(){
	cin >> label;
	cin >> n >> m >> c;
	for(int i = 1; i <= n; i++){
		cin >> color[i];
	}
	for(int i = 1; i <= n; i++){
		cin >> val[i];
	}
	for(int i = 1; i <= n; i++){
		bapak[i] = i;
		isi[i].pb(i);
	}
	for(int i = 1; i <= m; i++){
		int a,b; cin >> a >> b;
			if(color[a] == color[b]){
				gabung(a, b);
			}
	}
	cin >> q;

	for(int i = 1; i <= n; i++){
		if(bapak[i] == i){
			for(int j = 0; j < isi[i].size(); j++){
				int now = isi[i][j];
				pq[i].push(mp(val[now], now));
			}
		}
	}

	for(int i = 1; i <= q; i++){
		int tipe; cin >> tipe;
		if(tipe == 1){
			int x; cin >> x;
			int idx = bapak[x];
			while(pq[idx].top().fs != val[pq[idx].top().sc]){
				pq[idx].pop();
			}
			cout << pq[idx].top().fs << "\n";
		}else{
			int x,y; cin >> x >> y;
			val[x] = y;
			int idx = bapak[x];
			pq[idx].push(mp(y, x));
		}
	}

	return 0;
}