// TCR
// O(n log^2 n) offline solution for the dynamic connectivity problem.
// The purpose of this code is not to be a black box but rather a template
// Optimize memory by using vector<int>& es instead of vector<Edge>& es
// Uses 1-indexing
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
struct Edge {
	int a, b, l, r;
};
struct DynamicConnectivity {
	vector<int> u, us;
	vector<pair<int, int> > st;
	int getu(int a) {
		if (u[a]==a) return a;
		else return getu(u[a]);
	}
	int uni(int a, int b) {
		a=getu(a);
		b=getu(b);
		if (a==b) return 0;
		if (us[a]>us[b]) swap(a, b);
		st.push_back({a, b});
		u[a]=b;
		us[b]+=us[a];
		return 1;
	}
	void undo() {
		us[st.back().S]-=us[st.back().F];
		u[st.back().F]=st.back().F;
		st.pop_back();
	}
	void go(int l, int r, vector<Edge>& es) {
		int use=0;
		vector<Edge> nes;
		for (auto e:es) {
			if (e.l>r||e.r<l) continue;
			if (e.l<=l&&r<=e.r) use+=uni(e.a, e.b);
			else nes.push_back(e);
		}
		if (l<r) {
			go(l, (l+r)/2, nes);
			go((l+r)/2+1, r, nes);
		}
		for (int i=0;i<use;i++) undo();
	}
	DynamicConnectivity(int n) : u(n+1), us(n+1) {
		for (int i=1;i<=n;i++) {
			u[i]=i;
			us[i]=1;
		}
	}
};