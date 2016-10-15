// TCR
// Finds bridges and 2-edge connected components of graph
// Component of vertex x is c[x]
// Edge is bridge iff its endpoints are in different components
// Graph in form {adjacent vertex, edge id}
// Uses 1-indexing
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
struct Bridges {
	vector<int> c, h;
	void dfs(vector<pair<int, int> >* g, int x, int pe, int d, vector<int>& ns) {
		if (h[x]) return;
		h[x]=d;
		ns.push_back(x);
		for (auto nx:g[x]) {
			if (nx.S!=pe) {
				dfs(g, nx.F, nx.S, d+1, ns);
				h[x]=min(h[x], h[nx.F]);
			}
		}
		if (h[x]==d) {
			while (ns.size()>0) {
				int t=ns.back();
				c[t]=x;
				ns.pop_back();
				if (t==x) break;
			}
		}
	}
	Bridges(vector<pair<int, int> >* g, int n) : c(n+1), h(n+1) {
		vector<int> ns;
		for (int i=1;i<=n;i++) {
			dfs(g, i, -1, 1, ns);
		}
	}
};