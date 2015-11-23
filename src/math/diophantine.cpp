// solves ax+by=c in O(log a+b) time
// returns {is, {x, y}}, is=0 if there is no solution
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	return __gcd(abs(a), abs(b));
}

void ee(ll a, ll b, ll ca, ll cb, ll xa, ll xb, ll&x, ll&y) {
	if (cb==0) {
		x=xa;
		if (b==0) y=0;
		else y=(ca-a*xa)/b;
	}
	else return ee(a, b, cb, ca%cb, xb, xa-(ca/cb)*xb, x, y);
}

pair<int, pair<ll, ll> > solve(ll a, ll b, ll c) {
	if (c==0) return {1, {0, 0}};
	if (a==0&&b==0) return {0, {0, 0}};
	ll g=gcd(a, b);
	if (abs(c)%g>0) return {0, {0, 0}};
	ll x,y;
	ee(a, b, a, b, 1, 0, x, y);
	return {1, {x*(c/g), y*(c/g)}};
}