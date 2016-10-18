// TCR
// Scaling flow algorithm for maxflow
// O(E^2 log U), where U is maximum possible flow
// In practice O(E^2)
// Uses 1-indexing
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
struct MaxFlow {
	// Use vector<map<int, ll> > for sparse graphs
	vector<vector<ll> > f;
	vector<vector<int> > g;
	vector<int> used;
	int cc;
	ll flow(int x, int t, ll fl, ll miv) {
		if (x==t) return fl;
		used[x]=cc;
		for (int nx:g[x]) {
			if (used[nx]!=cc&&f[x][nx]>=miv) {
				ll r=flow(nx, t, min(fl, f[x][nx]), miv);
				if (r>0) {
					f[x][nx]-=r;f[nx][x]+=r;
					return r;
				}
			}
		}
		return 0;
	}
	// maxv is maximum expected maxflow
	ll getMaxFlow(int source, int sink, ll maxv) {
		cc=1;ll r=0;ll k=1;
		while (k*2<=maxv) k*=2;
		for (;k>0;k/=2) {
			while (ll t=flow(source, sink, maxv, k)) {
				r+=t;cc++;
			}
			cc++;
		}
		return r;
	}
	void addEdge(int a, int b, ll c) {
		if (f[a][b]==0&&f[b][a]==0) {
			g[a].push_back(b);
			g[b].push_back(a);
		}
		f[a][b]+=c;
	}
	MaxFlow(int n) : f(n+1), g(n+1), used(n+1) {
		for (int i=1;i<=n;i++) {
			f[i]=vector<ll>(n+1);
		}
	}
};