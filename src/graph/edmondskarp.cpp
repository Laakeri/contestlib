// Edmonds Karp algorithm for maxflow O(V E^2) or O(f E)
// f is the capacity network and the actual flow can be found in it
// If edges for both directions are used finding actual flow is harder
// Uses 1-indexing

#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int inf=2e9;

struct maxFlow{
	
	vector<vector<int> > f;
	vector<vector<int> > g;
	vector<int> fr;
	vector<int> used;
	
	int flow(int so, int si, int n) {
		queue<pair<pair<int, int>, int> > bfs;
		bfs.push({{0, so}, inf});
		int fl=0;
		while(!bfs.empty()){
			auto x=bfs.front();
			bfs.pop();
			if (used[x.F.S]) continue;
			used[x.F.S]=1;
			fr[x.F.S]=x.F.F;
			if (x.F.S==si){
				fl=x.S;
				break;
			}
			for (int nx:g[x.F.S]){
				if (f[x.F.S][nx]>0){
					bfs.push({{x.F.S, nx}, min(x.S, f[x.F.S][nx])});
				}
			}
		}
		for (int i=1;i<=n;i++) used[i]=0;
		if (fl>0){
			int x=si;
			while (fr[x]>0){
				f[x][fr[x]]+=fl;
				f[fr[x]][x]-=fl;
				x=fr[x];
			}
			return fl;
		}
		return 0;
	}
	
	ll getMaxFlow(int source, int sink){
		int n=fr.size()-1;
		for (int i=1;i<=n;i++){
			g[i].clear();
			for (int ii=1;ii<=n;ii++){
				if (f[i][ii]!=0||f[ii][i]!=0){
					g[i].push_back(ii);
				}
			}
		}
		ll r=0;
		while (1){
			int fl=flow(source, sink, n);
			if (fl==0) break;
			r+=(ll)fl;
		}
		return r;
	}
	
	void addEdge(int a, int b, int c){
		f[a][b]=c;
	}
	
	maxFlow(int n) : f(n+1), g(n+1), fr(n+1), used(n+1) {
		for (int i=1;i<=n;i++){
			f[i]=vector<int>(n+1);
		}
	}
};