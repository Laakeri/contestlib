// Returns square of distance between closest 2 points
// O(n log n)
#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef complex<ll> co;

const ll inf=2e18;

ll csqrt(ll x){
	ll r=sqrt(x);
	while (r*r<x) r++;
	while (r*r>x) r--;
	return r;
}

ll sq(ll x){
	return x*x;
}

ll closestPoints(vector<co> points) {
	int n=points.size();
	vector<pair<ll, ll> > ps(n);
	for (int i=0;i<n;i++) {
		ps[i]={points[i].X, points[i].Y};
	}
	sort(ps.begin(), ps.end());
	int i2=0;
	ll d=inf;
	set<pair<ll, ll> > pss;
	for (int i=0;i<n;i++) {
		while (i2<i&&sq(ps[i].F-ps[i2].F)>d) {
			pss.erase({ps[i2].S, ps[i2].F});
			i2++;
		}
		auto it=pss.lower_bound({ps[i].S-csqrt(d), -inf});
		for (;it!=pss.end();it++){
			if (sq(it->F-ps[i].S)>d) break;
			d=min(d, sq(it->F-ps[i].S)+sq(it->S-ps[i].F));
		}
		pss.insert({ps[i].S, ps[i].F});
	}
	return d;
}