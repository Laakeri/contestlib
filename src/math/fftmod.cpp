// TCR
// Precise FFT modulo mod
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long lll;
// Number of form (2^25)*k+1
const lll mod=2113929217; // between 2*10^9 and 2^31
// Number whose order mod mod is 2^25
const lll root=1971140334;
const lll root_pw=1<<25;
// 128 bit
// typedef __int128 lll;
// const lll mod=2013265920268435457; // between 2*10^18 and 2^61
// const lll root=1976010382590097340;
// const lll root_pw=1<<28;
lll pot(lll x, lll p) {
	if (p==0) return 1;
	if (p%2==0) {
		x=pot(x, p/2);
		return (x*x)%mod;
	}
	return (x*pot(x, p-1))%mod;
}
lll inv(lll x) {
	return pot(x, mod-2);
}
vector<lll> fft (vector<lll> a, int d) {
	lll root_1=inv(root);
	int n=(int)a.size();
	for (int i=1,j=0;i<n;i++) {
		int bit=n>>1;
		for (;j>=bit;bit>>=1) j-=bit;
		j+=bit;
		if (i<j) swap (a[i], a[j]);
	}
	for (int len=2;len<=n;len<<=1) {
		lll wlen=root;
		if (d==-1) wlen=root_1;
		for (int i=len;i<root_pw;i<<=1) wlen=(wlen*wlen)%mod;
		for (int i=0;i<n;i+=len) {
			lll w = 1;
			for (int j=0;j<len/2;j++) {
				lll u = a[i+j];
				lll v = (a[i+j+len/2]*w)%mod;
				if (u+v<mod) a[i+j]=u+v;
				else a[i+j]=u+v-mod;
				if (u-v>=0) a[i+j+len/2]=u-v;
				else a[i+j+len/2]=u-v+mod;
				w=(w*wlen)%mod;
			}
		}
	}
	if (d==-1) {
		lll nrev=inv(n);
		for (int i=0;i<n;i++) a[i]=(a[i]*nrev)%mod;
	}
	return a;
}
vector<lll> conv(const vector<ll>& a, const vector<ll>& b) {
	int as=a.size(), bs=b.size();
	int n=1;
	while (n<as+bs-1) n*=2;
	vector<lll> aa(n*2), bb(n*2);
	for (int i=0;i<as;i++) aa[i]=a[i];
	for (int i=0;i<bs;i++) bb[i]=b[i];
	aa=fft(aa, 1);bb=fft(bb, 1);
	vector<lll> c(2*n);
	for (int i=0;i<2*n;i++) c[i]=(aa[i]*bb[i])%mod;
	c=fft(c, -1);
	c.resize(as+bs-1);
	return c;
}
int main() {
	// Shoud print 12 11 30 7
	vector<ll> a={3, 2, 7};
	vector<ll> b={4, 1};
	vector<lll> c=conv(a, b);
	for (lll t:c) {
		cout<<(ll)t<<endl;
	}
}