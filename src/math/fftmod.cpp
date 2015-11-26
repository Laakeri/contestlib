// precise FFT modulo mod
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//luku muotoa (2^20)*k+1
const ll mod=1045430273;
//luku jonka order 2^20
const ll root=363;
//sen kaanteisluku
const ll root_1=296637240;
const ll root_pw=1<<20;

ll pot(ll x, ll p){
	if (p==0) return 1;
	if (p%2==0){
		x=pot(x, p/2);
		return (x*x)%mod;
	}
	return (x*pot(x, p-1))%mod;
}

ll inv(ll x){
	return pot(x, mod-2);
}

vector<ll> fft (vector<ll> a, int d) {
	int n=(int)a.size();
	for (int i=1,j=0;i<n;i++) {
		int bit=n>>1;
		for (;j>=bit;bit>>=1) {
			j-=bit;
		}
		j+=bit;
		if (i<j) swap (a[i], a[j]);
	}
	for (int len=2;len<=n;len<<=1) {
		ll wlen=root;
		if (d==-1) {
			wlen=root_1;
		}
		for (int i=len;i<root_pw;i<<=1) wlen=(wlen*wlen)%mod;
		for (int i=0;i<n;i+=len) {
			ll w = 1;
			for (int j=0;j<len/2;j++) {
				ll u = a[i+j];
				ll v = (a[i+j+len/2]*w)%mod;
				if (u+v<mod) {
					a[i+j]=u+v;
				}
				else {
					a[i+j]=u+v-mod;
				}
				if (u-v>=0) {
					a[i+j+len/2]=u-v;
				}
				else {
					a[i+j+len/2]=u-v+mod;
				}
				w=(w*wlen)%mod;
			}
		}
	}
	if (d==-1) {
		ll nrev=inv(n);
		for (int i=0;i<n;i++) a[i]=(a[i]*nrev)%mod;
	}
	return a;
}

vector<ll> conv(vector<ll> a, vector<ll> b) {
	int as=a.size();
	int bs=b.size();
	vector<ll> aa(as);
	vector<ll> bb(bs);
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
	vector<ll> c(2*n);
	for (int i=0;i<2*n;i++) {
		c[i]=(aa[i]*bb[i])%mod;
	}
	c=fft(c, -1);
	c.resize(as+bs-1);
	return c;
}

int main(){
	// Shoud print 12 11 30 7
	vector<ll> a={3, 2, 7};
	vector<ll> b={4, 1};
	vector<ll> c=conv(a, b);
	for (ll t:c){
		cout<<t<<endl;
	}
}