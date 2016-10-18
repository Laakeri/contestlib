// TCR
// O(log n log m)
// poinHullTan
// Finds the common tangents of a convex polygon and a point
// The polygon should be strictly convex and in counterclockwise order
// Pointhulltan returns {-1, -1} if the point is inside the polygon, otherwise
// it returs {maximal, minimal} vertices in terms of visibility from point p
// Remember to implement the special case n<=2
// Points on the boundary are considered to be inside
// hullHullTan
// Finds the common tangents of two convex polygons
// All of the conditions as above and it probably does not work if n<=2 or m<=2
// 1 is maximal and -1 is minimal
#include <bits/stdc++.h>
#define X real()
#define Y imag()
using namespace std;
typedef long long ll;
typedef complex<ll> co;
ll ccw(co a, co b, co c) {
	return ((c-a)*conj(b-a)).Y;
}
bool up(co p, vector<co>& h, int a, int b, int d) {
	int n=h.size();
	return (ll)d*ccw(p, h[(a+n)%n], h[(b+n)%n])<=0;
}
int getTanP(co p, vector<co>& h, int d) {
	int n=h.size();int mi=0;int ma=n;
	while (mi+1<ma) {
		int mid=(mi+ma)/2;
		if (up(p, h, mi, mi+1, d)) {
			if (up(p, h, mid+1, mid, d)) ma=mid;
			else if(up(p, h, mi, mid, d)) mi=mid;
			else ma=mid;
		}
		else {
			if (up(p, h, mid, mid+1, d)) mi=mid;
			else if(up(p, h, mid, mi, d)) mi=mid;
			else ma=mid;
		}
	}
	int step=0;
	if (d==1) {
		ma%=n;
		while (up(p, h, ma, ma+1, d)) {
			ma=(ma+1)%n;step++;
			assert(step<2);
		}
		return ma;
	}
	else {
		while (up(p, h, mi, mi+1, d)) {
			mi=(mi+1)%n;step++;
			if (step>=3) return -1;
		}
		if (up(p, h, mi, mi-1, d)) mi=(mi-1+n)%n;
		return mi;
	}
}
pair<int, int> pointHullTan(co p, vector<co>& h) {
	if ((int)h.size()<=2) return {0, 0};
	int t1=getTanP(p, h, -1);
	if (t1==-1) return {-1, -1};
	return {getTanP(p, h, 1), t1};
}
bool up2(vector<co>& h1, vector<co>& h, int a, int b, int d1, int d2) {
	int n=h.size();int k=getTanP(h[(b+n)%n], h1, d1);
	return (ll)d2*ccw(h[(a+n)%n], h[(b+n)%n], h1[k])<=0;
}
pair<int, int> getTanH(vector<co>& h1, vector<co>& h, int d1, int d2) {
	int n=h.size();int mi=0;int ma=n;
	while (mi+1<ma) {
		int mid=(mi+ma)/2;
		if (up2(h1, h, mi, mi+1, d1, d2)) {
			if (up2(h1, h, mid+1, mid, d1, d2)) ma=mid;
			else if(up2(h1, h, mi, mid, d1, d2)) mi=mid;
			else ma=mid;
		}
		else {
			if (up2(h1, h, mid, mid+1, d1, d2)) mi=mid;
			else if(up2(h1, h, mid, mi, d1, d2)) mi=mid;
			else ma=mid;
		}
	}
	int step=0;
	if (d2==1) {
		ma%=n;
		while (up2(h1, h, ma, ma+1, d1, d2)) {
			ma=(ma+1)%n;step++;
			assert(step<2);
		}
		return {getTanP(h[ma], h1, d1), ma};
	}
	else {
		while (up2(h1, h, mi, mi+1, d1, d2)) {
			mi=(mi+1)%n;step++;
			assert(step<3);
		}
		if (up2(h1, h, mi, mi-1, d1, d2)) mi=(mi-1+n)%n;
		return {getTanP(h[mi], h1, d1), mi};
	}
}
vector<pair<int, int> > hullHullTan(vector<co>& h1, vector<co>& h2) {
	vector<pair<int, int> > ret;
	ret.push_back(getTanH(h1, h2, 1, 1));
	ret.push_back(getTanH(h1, h2, 1, -1));
	ret.push_back(getTanH(h1, h2, -1, 1));
	ret.push_back(getTanH(h1, h2, -1, -1));
	return ret;
}