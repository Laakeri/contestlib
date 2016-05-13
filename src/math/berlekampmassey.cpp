#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef __int128 lll;

using namespace std;

lll powmod(lll a, lll p, lll modd) {
	if (p==0) return 1;
	if (p%2==0) {
		a=powmod(a, p/2, modd);
		return (a*a)%modd;
	}
	return (a*powmod(a, p-1, modd))%modd;
}

ll invp(ll a, ll p) {
	return powmod(a, p - 2, p);
}

vector<ll> solve(vector<ll> S, ll mod) {
	vector<ll> C = {1};
	vector<ll> B = {1};
	ll L = 0;
	ll m = 1;
	ll b = 1;
	ll N = S.size();
	for (ll i = 0; i < N; i++) {
		ll d = S[i];
		for (ll j = 1; j <= L; j++) {
			d += C[j]*S[i - j];
			d %= mod;
		}
		if (d == 0) {
			m++;
		} else if (2*L <= i) {
			vector<ll> T = C;
			ll a = (invp(b, mod)*d)%mod;
			for (ll j = m; j <= L; j++) {
				C[j] -= a*B[j - m];
				C[j] %= mod;
			}
			for (ll j = L + 1; j <= i + 1 - L; j++) {
				C.push_back((-a*B[j - m])%mod);
			}
			L = i + 1 - L;
			B = T;
			b = d;
			m = 1;
		} else {
			ll a = (invp(b, mod)*d)%mod;
			for (ll j = m; j <= L; j++) {
				C[j] -= a*B[j - m];
				C[j] %= mod;
			}
			m++;
		}
	}
	for (ll i = 0; i <= L; i++) {
		C[i] += mod;
		C[i] %= mod;
	}
	return C;
}

int main() {
	vector<ll> S = {1,1,2,3,5, 8, 13, 21, 34, 55};
	vector<ll> C = solve(S, 1000000007);
	for (ll x : C) {
		cout << x << " ";
	}
	cout << "\n";
	return 0;
}