// TCR
// NOT TESTED PROPERLY
// Finds Euler tour of graph in O(E) time

// Parameters are the adjacency list, number of nodes, 
// return value vector, and d=1 if the graph is directed
// Return array contains E+1 elements, the first and last
// elements are same

// Undefined behavior if Euler tour doesn't exist

// Note that Eulerian path can be reduced to Euler tour
// by adding an edge from the last vertex to the first

// In bidirectional graph edges must be in both direction
// Be careful to not add loops twice in case of bidirectional graph
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

struct EulerTour {
	int dir;
	vector<vector<pair<int, int> > > g;
	vector<int> used;
	
	void dfs(int x, vector<int>& ret) {
		int t=x;
		vector<int> c;
		while (1) {
			while (used[g[t].back().S]) g[t].pop_back();
			auto nx=g[t].back();
			g[t].pop_back();
			used[nx.S]=1;
			t=nx.F;
			c.push_back(t);
			if (t==x) break;
		}
		for (int a:c) {
			ret.push_back(a);
			while (g[a].size()>0&&used[g[a].back().S]) g[a].pop_back();
			if (g[a].size()>0) dfs(a, ret);
		}
	}
	
	EulerTour(vector<int>* og, int n, vector<int>& ret, int d=0) : dir(d), g(n+1) {
		int i2=0;
		for (int i=1;i<=n;i++) {
			for (int nx:og[i]) {
				if (d==1||nx<=i) {
					if (d==0&&nx<i) g[nx].push_back({i, i2});
					g[i].push_back({nx, i2++});
				}
			}
		}
		used.resize(i2);
		for (int i=1;i<=n;i++) {
			if (g[i].size()>0) {
				ret.push_back(i);
				dfs(i, ret);
				break;
			}
		}
	}
};