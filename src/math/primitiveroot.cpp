// TCR
// Computes primitive root
// O(sqrt(n))
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
ll primitiveRoot(ll p) {
	vector<ll> fact;
	ll phi=p-1;
	ll n=phi;
	for (ll i=2;i*i<=n;i++) {
		if (n%i==0) {
			fact.push_back(i);
			while (n%i==0) n/=i;
		}
	}
	if (n>1) fact.push_back (n);
	for (ll res=2;res<=p;res++) {
		bool ok = true;
		for (int i=0;i<(int)fact.size()&&ok;i++) ok&=pot(res, phi/fact[i], p)!=1;
		if (ok)  return res;
	}
	return -1;
}
int main() {
	cout<<primitiveRoot(1000000007)<<endl;// should print 5
}