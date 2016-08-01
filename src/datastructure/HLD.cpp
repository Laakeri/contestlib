// TCR
// Builds Heavy-light decomposition of tree in O(n) time
// getPath returns decomposed path from a to b in a vector which contains
// {{u, v}, {index[u], index[v]}} index[u]<=index[v], depth[u]<=depth[v]
// lca(a, b) is in the last path of the vector
// Uses 1-indexing
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

struct HLD {
	vector<int> aps, pRoot, pLI, pRI, nPath, nPathId, p;
	int index;
	void dfs1(vector<int>* g, int x) {
		aps[x]=1;
		for (int nx:g[x]) {
			if (nx!=p[x]) {
				p[nx]=x;
				dfs1(g, nx);
				aps[x]+=aps[nx];
			}
		}
	}
	void dfs2(vector<int>* g, int x, int path, int pi) {
		if (path==-1) {
			path=pRoot.size();
			pRoot.push_back(x);
			pLI.push_back(index);
			pRI.push_back(index);
		}
		nPath[x]=path;
		nPathId[x]=pi;
		pRI[path]=index++;
		int ma=0;
		for (int nx:g[x]){
			if (nx!=p[x]&&aps[nx]>aps[ma]) ma=nx;
		}
		if (ma) dfs2(g, ma, path, pi+1);
		for (int nx:g[x]){
			if (nx!=p[x]&&nx!=ma) dfs2(g, nx, -1, 0);
		}
	}
	HLD(vector<int>* g, int n) : aps(n+1), nPath(n+1), nPathId(n+1), p(n+1) {
		index=0;
		dfs1(g, 1);
		dfs2(g, 1, -1, 0);
	}
	vector<pair<pair<int, int>, pair<int, int> > > getPath(int a, int b) {
		vector<pair<pair<int, int>, pair<int, int> > > ret;
		while (nPath[a]!=nPath[b]) {
			int pa=nPath[a];
			int pb=nPath[b];
			if (pa>pb) {
				ret.push_back({{pRoot[pa], a}, {pLI[pa], pLI[pa]+nPathId[a]}});
				a=p[pRoot[pa]];
			}
			else {
				ret.push_back({{pRoot[pb], b}, {pLI[pb], pLI[pb]+nPathId[b]}});
				b=p[pRoot[pb]];
			}
		}
		int pa=nPath[a];
		if (nPathId[a]>nPathId[b]) swap(a, b);
		ret.push_back({{a, b}, {pLI[pa]+nPathId[a], pLI[pa]+nPathId[b]}});
		return ret;
	}
};