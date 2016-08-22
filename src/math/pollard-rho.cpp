// TCR
// Pollard Rho Integer factorization
// Support of 128 bit integers is required to factor over 32 bit integers
// requires isPrime function
// expected time complexity is O(n^(1/4))
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
void step(ll& x, ll n, ll c) {x=(lll)((lll)x*(lll)x+(lll)c)%n;}
void rFactor(ll n, map<ll, ll>& r) {
	while (n%2==0) {
		n/=2;r[2]++;
	}
	if (n==1) return;
	if (isPrime(n)) r[n]++;
	else {
		while (1) {
			ll x=rand()%n;ll y=x;
			ll c=rand()%n;
			for (ll i=0;i*i<=n;i++) {
				step(x, n, c);step(x, n, c);step(y, n, c);
				ll g=__gcd(max(x, y)-min(x, y), n);
				if (g==n) break;
				else if(g>1) {
					rFactor(n/g, r);
					rFactor(g, r);
					return;
				}
			}
		}
	}
}
map<ll, ll> factor(ll n) {
	map<ll, ll> ret;
	if (n>1) rFactor(n, ret);
	return ret;
}