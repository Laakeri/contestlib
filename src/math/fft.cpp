// TCR
// Fast Fourier transform and convolution using it
// O(n log n)
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef complex<ld> co;
const ld PI=atan2(0, -1);

vector<co> fft(vector<co> x, int d) {
	int n=x.size();
	for (int i=0;i<n;i++) {
		int u=0;
		for (int j=1;j<n;j*=2) {
			u*=2;
			if (i&j) u++;
		}
		if (i<u) {
			swap(x[i], x[u]);
		}
	}
	for (int m=2;m<=n;m*=2) {
		co wm=exp(co{0, d*2*PI/m});
		for (int k=0;k<n;k+=m) {
			co w=1;
			for (int j=0;j<m/2;j++) {
				co t=w*x[k+j+m/2];
				co u=x[k+j];
				x[k+j]=u+t;
				x[k+j+m/2]=u-t;
				w*=wm;
			}
		}
	}
	if (d==-1) {
		for (int i=0;i<n;i++) {
			x[i]/=n;
		}
	}
	return x;
}

vector<ll> conv(vector<ll> a, vector<ll> b) {
	int as=a.size();
	int bs=b.size();
	vector<co> aa(as);
	vector<co> bb(bs);
	for (int i=0;i<as;i++) {
		aa[i]=a[i];
	}
	for (int i=0;i<bs;i++) {
		bb[i]=b[i];
	}
	int n=1;
	while (n<as+bs-1) n*=2;
	aa.resize(n*2);
	bb.resize(n*2);
	aa=fft(aa, 1);
	bb=fft(bb, 1);
	vector<co> c(2*n);
	for (int i=0;i<2*n;i++) {
		c[i]=aa[i]*bb[i];
	}
	c=fft(c, -1);
	c.resize(as+bs-1);
	vector<ll> r(as+bs-1);
	for (int i=0;i<as+bs-1;i++) {
		r[i]=(ll)round(c[i].real());
	}
	return r;
}

int main() {
	// Shoud print 12 11 30 7
	vector<ll> a={3, 2, 7};
	vector<ll> b={4, 1};
	vector<ll> c=conv(a, b);
	for (ll t:c) {
		cout<<t<<endl;
	}
}