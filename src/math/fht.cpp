// TCR
// Fast Hadamard Transform for computing xor, and, or, convolutions in O(n log n)
// The length of the input vector must be a power of 2
// Works also in mod arithmetic, just remember to handle negative numbers and
// the division in inverse xor
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void fht(vector<ll>& a, vector<vector<ll> > m) {
	for (int len=1;2*len<=(int)a.size();len*=2) {
		for (int i=0;i<(int)a.size();i+=2*len) {
			for (int j=0;j<len;j++) {
				ll u=a[i+j];
				ll v=a[i+len+j];
				a[i+j]=m[0][0]*u+m[0][1]*v;
				a[i+len+j]=m[1][0]*u+m[1][1]*v;
}}}}
void xorTr(vector<ll>& a) {fht(a, {{1, 1}, {1, -1}});}
void xorInv(vector<ll>& a) {
	fht(a, {{1, 1}, {1, -1}});
	for (int i=0;i<(int)a.size();i++) a[i]/=(ll)a.size();
}
void andTr(vector<ll>& a) {fht(a, {{0, 1}, {1, 1}});}
void andInv(vector<ll>& a) {fht(a, {{-1, 1}, {1, 0}});}
void orTr(vector<ll>& a) {fht(a, {{1, 1}, {1, 0}});}
void orInv(vector<ll>& a) {fht(a, {{0, 1}, {1, -1}});}
int main() {// Should print 92 73 78 69
	vector<ll> a={3, 2, 7, 1};
	vector<ll> b={5, 4, 9, 6};
	xorTr(a);xorTr(b);
	vector<ll> c(4);
	for (int i=0;i<4;i++) c[i]=a[i]*b[i];
	xorInv(c);
	for (ll t:c) cout<<t<<endl;
}