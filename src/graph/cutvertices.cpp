// TCR
// Finds cutvertices and 2-vertex-connected components of graph
// 2-vertex-connected components are stored in bg
// Uses 1-indexing
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
struct Biconnected {
	vector<int> cut, h, d, used;
	vector<map<int, vector<int> > > bg;
	vector<pair<int, int> > es;
	int cc;
	void dfs(vector<int>* g, int x, int p) {
		h[x]=d[x];
		int f=0;
		for (int nx:g[x]) {
			if (nx!=p) {
				if (!used[nx]) es.push_back({x, nx});
				if (d[nx]==0) {
					f++;d[nx]=d[x]+1;
					int ts=es.size();
					dfs(g, nx, x);
					h[x]=min(h[x], h[nx]);
					if (h[nx]>=d[x]) {
						cut[x]=1;
						while ((int)es.size()>=ts) {
							auto e=es.back();
							bg[e.F][cc].push_back(e.S);
							bg[e.S][cc].push_back(e.F);
							used[e.S]=1;used[e.F]=1;
							es.pop_back();
						}
						used[x]=0;cc++;
					}
				}
				h[x]=min(h[x], d[nx]);
			}
		}
		if (p==0) {
			if (f>1) cut[x]=1;
			else cut[x]=0;
		}
	}
	Biconnected(vector<int>* g, int n):cut(n+1),h(n+1),d(n+1),used(n+1),bg(n+1){
		cc=1;
		for (int i=1;i<=n;i++) {
			if (d[i]==0) {
				d[i]=1;dfs(g, i, 0);
			}
		}
	}
};