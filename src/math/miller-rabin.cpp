// TCR
// Deterministic Miller-Rabin primality test
// Works for all 64 bit integers
// Support of 128 bit integers is required to test over 32 bit integers
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
lll powmod(lll a, lll p, lll mod) {
	if (p==0) return 1;
	if (p%2==0) {
		a=powmod(a, p/2, mod);
		return (a*a)%mod;
	}
	return (a*powmod(a, p-1, mod))%mod;
}
bool is_w(ll a, ll even, ll odd, ll p) {
	lll u = powmod(a, odd, p);
	if (u==1) return 0;
	for (ll j=1;j<even;j*=2) {
		if (u==p-1) return 0;
		u*=u;
		u%=p;
	}
	return 1;
}
bool isPrime(ll p) {
	if (p==2) return 1;
	if (p<=1||p%2==0) return 0;
	ll odd=p-1;
	ll even=1;
	while (odd%2==0) {
		even*=2;
		odd/=2;
	}
	ll b[7]={2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	for (ll i=0;i<7;i++) {
		ll a=b[i]%p;
		if (a==0) return 1;
		if (is_w(a, even, odd, p)) return 0;
	}
	return 1;
}