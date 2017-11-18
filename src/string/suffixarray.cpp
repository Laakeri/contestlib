// TCR
// Suffix array in O((n+S) log n)
// S is the size of alphabet, meaning that 0<=s[i]<S for all i
// You can change vector<int> s to string s. In that case S is 256
// This is CIRCULAR SUFFIX ARRAY. Append $ to the string to make if non circular
#include <bits/stdc++.h>
using namespace std;
vector<int> suffixArray(vector<int> s, int S) {
	int n=s.size();int N=n+S;
	vector<int> sa(n), ra(n);
	for(int i=0;i<n;i++) {sa[i]=i;ra[i]=s[i];}
	for(int k=0;k<n;k?k*=2:k++) {
		vector<int> nsa(sa), nra(n), cnt(N);
		for(int i=0;i<n;i++) nsa[i]=(nsa[i]-k+n)%n;
		for(int i=0;i<n;i++) cnt[ra[i]]++;
		for(int i=1;i<N;i++) cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--) sa[--cnt[ra[nsa[i]]]]=nsa[i];
		int r=0;
		for(int i=1;i<n;i++) {
			if(ra[sa[i]]!=ra[sa[i-1]]) r++;
			else if(ra[(sa[i]+k)%n]!=ra[(sa[i-1]+k)%n]) r++;
			nra[sa[i]]=r;
		}
		ra=nra;
	}
	return sa;
}