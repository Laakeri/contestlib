// TCR
// Solves ax+by=c in O(log a+b) time
// Returns {is, {x, y}}, is=0 if there is no solution
// Use __int128 for 64 bit numbers
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
ll ee(ll a, ll b, ll ca, ll cb, ll xa, ll xb, ll&x, ll&y) {
	if (cb==0) {
		x=xa;
		if (b==0) y=0;
		else y=(ca-a*xa)/b;
		return ca;
	}
	else return ee(a, b, cb, ca%cb, xb, xa-(ca/cb)*xb, x, y);
}
pair<int, pair<ll, ll> > solve(ll a, ll b, ll c) {
	if (c==0) return {1, {0, 0}};
	if (a==0&&b==0) return {0, {0, 0}};
	ll x,y;
	ll g=ee(a, b, a, b, 1, 0, x, y);
	if (abs(c)%g>0) return {0, {0, 0}};
	return {1, {x*(c/g), y*(c/g)}};
}