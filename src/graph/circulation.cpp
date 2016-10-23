// TCR
// Min cost circulation
// O(VE) on average, probably something like O(ans * E) worst case
// Use by adding edges with addEdge and then calling minCostCirculation
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<int V, int E> struct Circulation {
	struct Edge {
		int a, b;
		ll ca, co;
	} es[E*2];
	int eu=0,cookie=1;
	int how[V+1], good[V+1], bio[V+1];
	ll dist[V+1];
	void addEdge(int from, int to, ll ca, ll co) {
		es[eu++]={from, to, ca, co};
		es[eu++]={to, from, 0, -co};
	}
	void reset() {
		for (int i=1;i<=V;i++) {
			dist[i]=0;how[i]=-1;bio[i]=0;
		}
	}
	bool relax() {
		bool ret=false;
		for (int e=0;e<eu;e++) {
			if (es[e].ca) {
				int x=es[e].a;int y=es[e].b;
				if (dist[x]+es[e].co<dist[y]) {
					dist[y]=dist[x]+es[e].co;
					how[y]=e;ret=true;
				}
			}
		}
		return ret;
	}
	ll cycle(int s, bool flip = false) {
		int x=s;ll c=es[how[x]].ca;
		do {
			int e=how[x];c=min(c, es[e].ca);x=es[e].a;
		} while (x!=s);
		ll cost=0;
		do {
			int e=how[x];
			if (flip) {
				es[e].ca-=c;es[e^1].ca+=c;
			}
			cost+=es[e].co*c;x=es[e].a;
		} while (x!=s);
		return cost;
	}
	ll push(int x) {
		for (cookie++;bio[x]!=cookie;x=es[how[x]].a) {
			if (!good[x]||how[x]==-1||es[how[x]].ca==0) return 0;
			bio[x]=cookie;good[x]=false;
		}
		return cycle(x)>=0?0:cycle(x, true);
	}
	ll minCostCirculation() {
		reset();
		ll cost=0;
		for (int step=0;step<2*V;step++) {
			if (step == V) reset();
			if (!relax()) continue;
			for (int i=1;i<=V;i++) good[i]=true;
			for (int i=1;i<=V;i++) if (ll w=push(i)) {cost+=w;step=0;}
		}
		return cost;
	}
};