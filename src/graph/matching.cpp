// TCR
// General matching in O(n^3) time
#include <bits/stdc++.h>
using namespace std;
struct Matching {
	int n;
	vector<int> vLabel, ma, s, u;
	queue<int> q;
	void rm(int x, int y) {
		int m=ma[x];ma[x]=y;
		if (ma[m]==x) {
			if (vLabel[x]<=n) {
				ma[m]=vLabel[x];
				rm(vLabel[x], m);
			}
			else {
				int a=1+(vLabel[x]-n-1)/n;
				int b=1+(vLabel[x]-n-1)%n;
				rm(a, b);rm(b, a);
			}
		}
	}
	void tr(int x) {
		for (int i=1;i<=n;i++) s[i]=ma[i];
		rm(x, x);
		for (int i=1;i<=n;i++) {
			if (ma[i]!=s[i]) u[i]++;
			ma[i]=s[i];
		}
	}
	void rl(int x, int y) {
		for (int i=1;i<=n;i++) u[i]=0;
		tr(x);tr(y);
		for (int i=1;i<=n;i++) {
			if (u[i]==1&&vLabel[i]<0) {
				vLabel[i]=n+x+(y-1)*n;
				q.push(i);
			}
		}
	}
	vector<pair<int, int> > solve(vector<int>* g) {
		for (int i=1;i<=n;i++) {
			if (ma[i]==0) {
				for (int j=1;j<=n;j++) vLabel[j]=-1;
				vLabel[i]=0;q.push(i);
				while (!q.empty()) {
					int x=q.front();q.pop();
					for (int y:g[x]) {
						if (ma[y]==0&&i!=y) {
							ma[y]=x;rm(x, y);
							while (!q.empty()) q.pop();
							break;
						}
						if (vLabel[y]>=0) {
							rl(x, y);
							continue;
						}
						if (vLabel[ma[y]]<0) {
							vLabel[ma[y]]=x;
							q.push(ma[y]);
						}
					}
				}
			}
		}
		vector<pair<int, int> > res;
		for (int i=1;i<=n;i++) if (ma[i]>i) res.push_back({i, ma[i]});
		return res;
	}
	Matching(int nn) : n(nn), vLabel(n+1), ma(n+1), s(n+1), u(n+1) {}
};