#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ep emplace
#define F first
#define S second

typedef pair<int,int>ii;
typedef  vector<int>vi;
typedef vector<vi>vvi;
typedef queue<ii> qpair;
typedef set<int>si;
const int N = 1e6+5;
const long long INF = LONG_LONG_MAX;

int max_divs[N], n, a, good;
long long ans,dist[N];
vi primes, divs[N], vertex[N];
vvi G;
bool visited[N];
si start;

void seive(){
	//memset(max_divs, 0, sizeof max_divs);
	primes.pb(1);
	for(int i = 2; i<N; i++){
		if(!max_divs[i]){
			for(int j = i; j<N; j+=i) max_divs[j] = i;
			primes.pb(i);
		}
		divs[i] = divs[i/max_divs[i]];
		auto it = find(divs[i].begin(), divs[i].end(), max_divs[i]);
		if(it !=  divs[i].end()) divs[i].erase(it);
		else divs[i].pb(max_divs[i]);
	}
}

void max_self(int &a,int b){
	a=max(a,b);
}

void min_self(long long &a, long long b){
	a = min(a,b);
}


void dijkstra(int p){
	for(const int prm : start)dist[prm]=0;
	qpair Q;
	for(const int n : vertex[p]){
		Q.ep(n, G[n][0] == p);
		dist[G[n][0] ^ G[n][1] ^ p] = 1;
	}
	while(!Q.empty()){
		const auto root = Q.front(); Q.pop();
		int node = G[root.F][root.S];
		//cerr << node << endl;
		for(const int &next : vertex[node]){
			if(next != root.F){
				ii child = mp(next,G[next][0] == node);
				int nnode = G[child.F][child.S];
				if(!dist[nnode] && nnode != p){
					dist[nnode] = dist[node] + 1;
					Q.push(child);
				}else  min_self(ans, dist[node] + dist[nnode] + 1);
			}
		}
	}
}

int main(int argc, char *argv[]){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	seive();
	assert(cin >> n);
	good = 0;
	for(int i = 0; i<n; i++){
		assert(cin >> a);
		max_self(good, a);
		if(divs[a].empty()){
			cout << 1 << endl;
			return 0;
		}
		if(divs[a].size() == 1) divs[a].pb(1);
		start.insert(divs[a][0]);
		start.insert(divs[a][1]);
		G.push_back({divs[a][0], divs[a][1]});
		vertex[divs[a][0]].push_back(i);
		vertex[divs[a][1]].push_back(i);

		
	}
	ans = INF;
	for(const auto p : start){
		if(p*p > good) break;
		dijkstra(p);
	}
	if(ans == INF) cout << -1 << endl;
	else cout << ans << endl;
	return 0;
}
