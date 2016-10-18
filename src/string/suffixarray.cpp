// TCR
// Suffix array in O(n log^2 n)
// ~300ms runtime for 10^5 character string, ~2000ms for 5*10^5
// You can change vector<int> s to string s
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
vector<int> suffixArray(vector<int> s) {
	int n=s.size();
	vector<int> k(n);
	for (int i=0;i<n;i++) k[i]=s[i];
	vector<pair<pair<int, int>, int> > v(n);
	for (int t=1;t<=n;t*=2) {
		for (int i=0;i<n;i++) {
			int u=-1;
			if (i+t<n) u=k[i+t];
			v[i]={{k[i], u}, i};
		}
		sort(v.begin(), v.end());
		int c=0;
		for (int i=0;i<n;i++) {
			if (i>0&&v[i-1].F!=v[i].F) c++;
			k[v[i].S]=c;
		}
		if (c==n-1) break;
	}
	vector<int> sa(n);
	for (int i=0;i<n;i++) sa[k[i]]=i;
	return sa;
}