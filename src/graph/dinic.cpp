// TCR
// Dinic's algorithm for maxflow
// O(n^2 m) theoretical, really fast (near linear) in practice
// O(m^(3/2)) in unit network graphs
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=1e18;
struct MaxFlow {
	struct edge {
		int a, b;
		ll c;
	};
	vector<edge> es;
	vector<vector<int> > g;
	vector<int> d, pt;
	MaxFlow(int n) : g(n+1), d(n+1), pt(n+1) {}
	void addEdge(int a, int b, ll c) {
		es.push_back({a, b, c});
		g[a].push_back((int)es.size()-1);
		es.push_back({b, a, 0});
		g[b].push_back((int)es.size()-1);
	}
	bool bfs(int source, int sink) {
		queue<int> q({source});
		fill(d.begin(), d.end(), (int)g.size()+1);
		d[source]=0;
		while(!q.empty()) {
			int x=q.front();q.pop();
			if (x==sink) break;
			for (int k:g[x]) {
				edge& e=es[k];
				if (e.c>0&&d[e.b]>d[e.a]+1) {
					d[e.b]=d[e.a]+1;
					q.push(e.b);
				}
			}
		}
		return d[sink]!=(int)g.size()+1;
	}
	ll flow(int x, int sink, ll fl=inf) {
		if (x==sink||fl==0) return fl;
		for (int& i=pt[x];i<(int)g[x].size();i++) {
			edge& e=es[g[x][i]];
			edge& oe=es[g[x][i]^1];
			if (d[e.b]==d[e.a]+1) {
				if (ll pf=flow(e.b, sink, min(e.c, fl))) {
					e.c-=pf;
					oe.c+=pf;
					return pf;
				}
			}
		}
		return 0;
	}
	ll getMaxFlow(int source, int sink) {
		ll r=0;
		while (bfs(source, sink)) {
			fill(pt.begin(), pt.end(), 0);
			while (ll t=flow(source, sink)) r+=t;
		}
		return r;
	}
};