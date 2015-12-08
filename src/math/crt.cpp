// TCR
// Solves x from system of equations x == a_i (mod p_i)
// Overflows only if p_1*...*p_n overflows
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll pot(ll x, ll p, ll mod) {
	if (p==0) return 1;
	if (p%2==0) {
		x=pot(x, p/2, mod);
		return (x*x)%mod;
	}
	return (x*pot(x, p-1, mod))%mod;
}

ll inv(ll x, ll mod) {
	return pot(x%mod, mod-2, mod);
}

ll solve(vector<ll> a, vector<ll> p) {
	vector<ll> x(a.size());
	ll r=0;
	ll k=1;
	for (int i=0;i<(int)a.size();i++) {
		x[i]=a[i];
		for (int j=0;j<i;j++) {
			x[i]=inv(p[j], p[i])*(x[i]-x[j]);
			x[i]=x[i]%p[i];
			if (x[i]<0) x[i]+=p[i];
		}
		r+=k*x[i];
		k*=p[i];
	}
	return r;
}