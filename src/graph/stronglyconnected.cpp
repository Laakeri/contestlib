// TCR
// Kosaraju's algorithm for strongly connected components O(V+E)
// Components will be returned in topological order
// Uses 1-indexing
// Returns strongly connected components of the graph in vector ret
// n is the size of the graph, g is the adjacency list
#include <bits/stdc++.h>
using namespace std;
struct SCC {
	vector<int> used;
	vector<vector<int> > g2;
	void dfs1(vector<int>* g, int x, vector<int>& ns) {
		if (used[x]==1) return;
		used[x]=1;
		for (int nx:g[x]) {
			g2[nx].push_back(x);
			dfs1(g, nx, ns);
		}
		ns.push_back(x);
	}
	void dfs2(int x, vector<int>& co) {
		if (used[x]==2) return;
		used[x]=2;
		co.push_back(x);
		for (int nx:g2[x]) dfs2(nx, co);
	}
	SCC(vector<int>* g, int n, vector<vector<int> >& ret) : used(n+1), g2(n+1) {
		vector<int> ns;
		for (int i=1;i<=n;i++) dfs1(g, i, ns);
		for (int i=n-1;i>=0;i--) {
			if (used[ns[i]]!=2) {
				ret.push_back(vector<int>());
				dfs2(ns[i], ret.back());
			}
		}
	}
};
