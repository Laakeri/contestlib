// TCR
// Constructs LCP array from suffix array in O(n) time
// You can change vector<int> s to string s
#include <bits/stdc++.h>
using namespace std;
vector<int> lcpArray(vector<int> s, vector<int> sa) {
	int n=s.size();
	int k=0;
	vector<int> ra(n), lcp(n);
	for (int i=0;i<n;i++) ra[sa[i]]=i;
	for (int i=0;i<n;i++) {
		if (k) k--;
		if (ra[i]==n-1) {
			k=0;
			continue;
		}
		int j=sa[ra[i]+1];
		while (k<n&&s[(i+k)%n]==s[(j+k)%n]) k++;
		lcp[ra[i]]=k;
		if (ra[(sa[ra[i]]+1)%n]>ra[(sa[ra[j]]+1)%n]) k=0;
	}
	return lcp;
}