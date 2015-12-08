// TCR
// Finds minimum-cost k-flow
// O(V E^2 log U), where U is maximum possible flow
// Finding augmenting path is O(V E), usually faster
// Uses scaling flow and finds augmenting path with SPFA
// Only 1-directional edges allowed
// Doesn't work if graph contains negative cost cycles
// Uses 1-indexing

#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double ld;

const ll inf=1e18;

struct MinCostFlow {
	vector<vector<ll> > f;
	vector<vector<int> > g;
	vector<vector<ll> > c;
	vector<ll> d;
	vector<int> from;
	vector<int> inq;
	queue<int> spfa;
	
	void relax(int x, ll di, int p) {
		if (di>=d[x]) return;
		d[x]=di;
		from[x]=p;
		if (!inq[x]) {
			spfa.push(x);
			inq[x]=1;
		}
	}
	
	ll augment(ll x, ll s, ll fl) {
		if (x==s) return fl;
		ll r=augment(from[x], s, min(fl, f[from[x]][x]));
		f[from[x]][x]-=r;
		f[x][from[x]]+=r;
		return r;
	}
	
	pair<ll, ll> flow(int s, int t, ll miv, ll kf) {
		int n=g.size()-1;
		for (int i=1;i<=n;i++) {
			d[i]=inf;
			inq[i]=0;
		}
		relax(s, 0, 0);
		while (!spfa.empty()) {
			int x=spfa.front();
			spfa.pop();
			inq[x]=0;
			for (int nx:g[x]) {
				if (f[x][nx]>=miv) relax(nx, d[x]+c[x][nx], x);
			}
		}
		if (d[t]<inf) {
			ll fl=augment(t, s, kf);
			return {fl, fl*d[t]};
		}
		return {0, 0};
	}
	
	// maxv is maximum possible flow on a single augmenting path
	// kf is inteded flow, set infinite for maxflow
	// returns {flow, cost}
	pair<ll, ll> getKFlow(int source, int sink, ll maxv, ll kf) {
		int n=g.size()-1;
		for (int i=1;i<=n;i++) {
			g[i].clear();
			for (int ii=1;ii<=n;ii++) {
				if (f[i][ii]!=0||f[ii][i]!=0) g[i].push_back(ii);
			}
		}
		ll r=0;
		ll k=1;
		ll co=0;
		while (k*2<=maxv) k*=2;
		for (;k>0&&kf>0;k/=2) {
			while (1) {
				pair<ll, ll> t=flow(source, sink, k, kf);
				r+=t.F;
				kf-=t.F;
				co+=t.S;
				if (kf==0||t.F==0) break;
			}
		}
		return {r, co};
	}
	
	void addEdge(int a, int b, ll capa, ll cost) {
		f[a][b]=capa;
		c[a][b]=cost;
		c[b][a]=-cost;
	}
	
	MinCostFlow(int n) : f(n+1), g(n+1), c(n+1), d(n+1), from(n+1), inq(n+1) {
		for (int i=1;i<=n;i++) {
			f[i]=vector<ll>(n+1);
			c[i]=vector<ll>(n+1);
		}
	}
};