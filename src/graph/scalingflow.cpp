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
	struct e {
		int to,r;
		ll f;
	};
	vector<vector<e> > g;
	vector<int> used;
	int cc;
	ll flow(int x, int t, ll fl, ll miv) {
		if (x==t) return fl;
		used[x]=cc;
		for (auto& nx:g[x]) {
			if (used[nx.to]!=cc&&nx.f>=miv) {
				ll r=flow(nx.to, t, min(fl, nx.f), miv);
				if (r>0) {
					nx.f-=r;g[nx.to][nx.r].f+=r;
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
		g[a].push_back({b, (int)g[b].size(), c});
		g[b].push_back({a, (int)g[a].size()-1, 0});
	}
	MaxFlow(int n) : g(n+1), used(n+1) {}
};