// TCR
// Fast Fourier transform and convolution using it
// O(n log n)
// Is accurate with integers if the numbers of the result array are <= 4e15
// Also accurate if input <= 1e6 and the lengths of input arrays are 2e5
// Can be speed up by a factor of 2 by implementing the complex class
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef complex<ld> co;
const ld PI=atan2((ld)0, (ld)-1);
void fft(vector<co>&a, int n, int k) {
	vector<co> ww(n);
	ww[1]=co(1, 0);
	for (int t=0;t<k-1;t++) {
		co c=polar((ld)1, PI/n*(1<<(k-1-t)));
		int p2=(1<<t),p3=p2*2;
		for (int j=p2;j<p3;j++) ww[j*2+1]=(ww[j*2]=ww[j])*c;
	}
	for (int i=0;i<n;i++) {
		int u=0;
		for (int j=1;j<n;j*=2) {u*=2;if (i&j) u++;}
		if (i<u) swap(a[i], a[u]);
	}
	for (int l=1;l<n;l*=2) {
		for (int i=0;i<n;i+=l) {
			for (int it=0,j=i+l,w=l;it<l;it++,i++,j++) {
				co t=a[j]*ww[w++];
				a[j]=a[i]-t;
				a[i]=a[i]+t;
			}
		}
	}
}
vector<ll> conv(const vector<ll>& a, const vector<ll>& b) {
	int as=a.size(), bs=b.size();
	if (as*bs==0) return {};
	int k=0;
	while ((1<<k)<as+bs-1) k++;
	int n=1<<k;
	vector<co> c(n+1);
	for (int i=0;i<n;i++) {
		if (i<as) c[i]=a[i];
		if (i<bs) c[i]={c[i].real(), (ld)b[i]};
	}
	fft(c, n, k);
	c[n]=c[0];
	for (int i=0;i<=n-i;i++) {
		c[i]=conj(c[i]*c[i]-conj(c[n-i]*c[n-i]))*co(0,(ld)1/n/4);
		c[n-i]=conj(c[i]);
	}
	fft(c, n, k);
	vector<ll> r(as+bs-1);
	for (int i=0;i<as+bs-1;i++) r[i]=round(c[i].real());
	return r;
}
int main() {// Shoud print 12 11 30 7
	vector<ll> a={3, 2, 7};
	vector<ll> b={4, 1};
	vector<ll> c=conv(a, b);
	for (ll t:c) cout<<t<<endl;
}