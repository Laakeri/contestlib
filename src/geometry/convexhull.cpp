// TCR
// Computes the convex hull of given set of points in O(n log n)
// Uses Andrew's algorithm
// The points on the edges of the hull are not listed
// Change > to >= in ccw function to list the points on the edges
// Returns points in counterclockwise order
#include <bits/stdc++.h>
#define X real()
#define Y imag()
using namespace std;
typedef long double ld;
typedef long long ll;
// Coordinate type
typedef ll CT;
typedef complex<CT> co;
bool ccw(co a, co b, co c) {
	return ((c-a)*conj(b-a)).Y>0;
}
vector<co> convexHull(vector<co> ps) {
	auto cmp = [](co a, co b) {
		if (a.X==b.X) return a.Y<b.Y;
		else return a.X<b.X;
	};
	sort(ps.begin(), ps.end(), cmp);
	ps.erase(unique(ps.begin(), ps.end()), ps.end());
	int n=ps.size();
	if (n<=2) return ps;
	vector<co> hull;hull.push_back(ps[0]);
	for (int d=0;d<2;d++) {
		if (d) reverse(ps.begin(), ps.end());
		int s=hull.size();
		for (int i=1;i<n;i++) {
			while ((int)hull.size()>s&&!ccw(hull[hull.size()-2],hull.back(),ps[i])){
				hull.pop_back();
			}
			hull.push_back(ps[i]);
		}
	}
	hull.pop_back();
	return hull;
}