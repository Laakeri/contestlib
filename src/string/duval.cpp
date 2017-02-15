// Finds the Lyndon decomposition of a string in O(n)
// Returns the lyndon substrings as inclusive intervals
#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int> > duval(vector<int> s) {
	int k=-1;
	vector<pair<int, int> > ret;
	while (k+1<(int)s.size()) {
		int i=k+1;
		for (int j=k+2;;j++){
			if (j>=(int)s.size()||s[i]>s[j]) {
				while (k<i) {
					ret.push_back({k+1, k+(j-i)});
					k+=(j-i);
				}
				break;
			}
			else if(s[i]<s[j]) i=k+1;
			else i++;
		}
	}
	return ret;
}