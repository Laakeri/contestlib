// TCR
#include <bits/stdc++.h>
using namespace std;
int main(){
	// Iterate all submasks in increasing order. Does not list 0.
	int mask=13;
	for (int sub=0;(sub=(sub-mask)&mask);) {
		cout<<sub<<endl;// Should print 1 4 5 8 9 12 13
	}cout<<endl;
	// Iterate all submasks in decreasing order. Does not list 0.
	for (int sub=mask;sub;sub=(sub-1)&mask) {
		cout<<sub<<endl;// Should print 13 12 9 8 5 4 1
	}cout<<endl;
	int n=24;
	cout<<(n&-n)<<endl;// Smallest bit set. Should print 8
	cout<<__builtin_popcountll(n)<<endl;// Remember ll when using 64bit
	// Compute the next number that has the same number of bits set as n
	// Returns -1 for 0
	int t=n|(n-1);
	int w=(t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(n) + 1));
	cout<<w<<endl;// Should print 33
}