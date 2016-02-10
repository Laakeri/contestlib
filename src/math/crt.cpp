// TCR
// (Generalised) Chinese remainder theorem (for arbitrary moduli):
// Solves x from system of equations x == a_i (mod m_i), giving answer modulo m = lcm(m_1,...,m_n)
// Runs in O(log(m)+n) time
// Overflows only if m overflows
// Returns {1, {x, m}} if solution exists, and {-1, {0,0}} otherwise
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

ll ee(ll ca, ll cb, ll xa, ll xb, ll&x) {
	if (cb) return ee(cb, ca%cb, xb, xa-(ca/cb)*xb, x);
	x = xa;
	return ca;
}

pair<int, pair<ll, ll>> crt(vector<ll> as, vector<ll> ms) {
	ll aa = 0, mm = 1, d, a, x;
	for (int i = 0; i < (int) as.size(); i++) {
		d = ee(ms[i], mm, 1, 0, x);
		if ((aa-as[i])%d) return {-1,{0,0}};
		a = ms[i]/d;
		mm *= a;
		aa = (as[i] + (aa-as[i])*(((lll)a*x)%mm))%mm;
	}
	if (aa < 0) aa += mm;
	return {1, {aa, mm}};
}