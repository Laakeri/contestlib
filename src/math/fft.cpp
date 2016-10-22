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
		if (i<u) swap(x[i], x[u]);
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
	if (d==-1) for (int i=0;i<n;i++) x[i]/=n;
	return x;
}
vector<ll> conv(const vector<ll>& a, const vector<ll>& b) {
	int as=a.size(), bs=b.size();
	int n=1;
	while (n<as+bs-1) n*=2;
	vector<co> aa(n*2), bb(n*2);
	for (int i=0;i<as;i++) aa[i]=a[i];
	for (int i=0;i<bs;i++) bb[i]=b[i];
	aa=fft(aa, 1);bb=fft(bb, 1);
	vector<co> c(2*n);
	for (int i=0;i<2*n;i++) c[i]=aa[i]*bb[i];
	c=fft(c, -1);
	c.resize(as+bs-1);
	vector<ll> r(as+bs-1);
	for (int i=0;i<as+bs-1;i++) r[i]=(ll)round(c[i].real());
	return r;
}
// Double FFT trick, not necessary
pair<vector<co>, vector<co> > tfft(vector<co>& a, vector<co>& b, int d) {
	vector<co> fv(a.size());
	for (int i=0;i<(int)a.size();i++) fv[i]=a[i]+co(0, 1)*b[i];
	vector<co> r=fft(fv, d);
	vector<co> r1(a.size()), r2(a.size());
	for (int i=0;i<(int)a.size();i++) {
		if (d==-1||i==0||i==(int)a.size()/2) {
			r1[i]=r[i].real();r2[i]=r[i].imag();
		} else {
			co t=r[i]-r[(int)a.size()-i];
			r1[i]={r[i].real()-t.real()/2, t.imag()/2};
			r2[i]=(r[i]-r1[i])*co(0, -1);
		}
	}
	return {r1, r2};
}
int main() {
	// Shoud print 12 11 30 7
	vector<ll> a={3, 2, 7};
	vector<ll> b={4, 1};
	vector<ll> c=conv(a, b);
	for (ll t:c) cout<<t<<endl;
}