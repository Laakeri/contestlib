// TCR
// Computes the Z array in linear time
// z[i] is the length of the longest common prefix of substring
// starting at i and the string
// You can use string s instead of vector<int> s
// z[0]=0 by definition
#include <bits/stdc++.h>
using namespace std;

vector<int> zAlgo(vector<int> s) {
	int n=s.size();
	vector<int> z(n);
	int l=0;
	int r=0;
	for (int i=1;i<n;i++) {
		z[i]=max(0, min(z[i-l], r-i));
		while (i+z[i]<n&&s[z[i]]==s[i+z[i]]) z[i]++;
		if (i+z[i]>r) {
			l=i;
			r=i+z[i];
		}
	}
	return z;
}