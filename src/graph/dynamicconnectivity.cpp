// TCR
// O(n log n) offline solution for dynamic connectivity problem.
// Query types:
// {1, {a, b}} add edge. If edge already exists nothing happns.
// {2, {a, b}} remove edge. If no edge exists nothing happens.
// {3, {0, 0}} count number of connected components.
// Uses 1-indexing
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
struct DynamicConnectivity {
	struct Edge {
		int a, b, l, r;
	};
	vector<int> ret, tq, id, is;
	vector<vector<int> > g;
	int dfs(int x, int c) {
		id[x]=c;
		int r=is[x];
		for (int nx:g[x])
			if (!id[nx]) r|=dfs(nx, c);
		return r;
	}
	void go(int l, int r, int n, int out, vector<Edge>& es) {
		vector<Edge> nes;
		for (int i=1;i<=n;i++) {
			g[i].clear();
			id[i]=0;
			is[i]=0;
		}
		for (auto e:es) {
			if (e.l>r||e.r<l||e.a==e.b) continue;
			if (e.l<=l&&r<=e.r) {
				g[e.a].push_back(e.b);
				g[e.b].push_back(e.a);
			}
			else {
				nes.push_back(e);
				is[e.a]=1;
				is[e.b]=1;
			}
		}
		int i2=1;
		for (int i=1;i<=n;i++) {
			if ((int)g[i].size()>0||is[i]) {
				if (!id[i]) {
					int a=dfs(i, i2);
					if (!a) out++;
					else i2++;
				}
			}
			else {
				out++;
			}
		}
		for (auto&e:nes) {
			e.a=id[e.a];
			e.b=id[e.b];
		}
		if (l==r) {
			if (tq[l]) ret[tq[l]-1]=out+i2-1;
		}
		else {
			int m=(l+r)/2;
			go(l, m, i2-1, out, nes);
			go(m+1, r, i2-1, out, nes);
		}
	}
	vector<int> solve(int n, vector<pair<int, pair<int, int> > > queries) {
		map<pair<int, int>, int> ae;
		tq.resize(queries.size());
		id.resize(n+1);
		is.resize(n+1);
		g.resize(n+1);
		int qs=0;
		vector<Edge> es;
		for (int i=0;i<(int)queries.size();i++) {
			auto q=queries[i];
			if (q.S.F>q.S.S) swap(q.S.F, q.S.S);
			if (q.F==1) {
				if (ae[q.S]==0) ae[q.S]=i+1;
			}
			else if(q.F==2) {
				if (ae[q.S]) {
					es.push_back({q.S.F, q.S.S, ae[q.S]-1, i});
					ae[q.S]=0;
				}
			}
			else if (q.F==3) {
				tq[i]=1+qs++;
			}
		}
		for (auto e:ae) {
			if (e.S) es.push_back({e.F.F, e.F.S, e.S-1, (int)queries.size()});
		}
		ret.resize(qs);
		if ((int)queries.size()>0) go(0, (int)queries.size()-1, n, 0, es);
		return ret;
	}
};