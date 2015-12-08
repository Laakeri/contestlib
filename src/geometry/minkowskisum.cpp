// TCR
// Computes the Minkowski sum of 2 convex polygons in O(n+m log n+m)
// Returns convex polygon in counterclockwise order
// The points on the edges of the hull are listed
// The convex hulls must be in counterclockwise order
#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define F first
#define S second
using namespace std;
typedef long double ld;
typedef long long ll;
// Coordinate type
typedef ll CT;
typedef complex<CT> co;

bool ccw(co a, co b, co c) {
	return ((c-a)*conj(b-a)).Y>0;
}

int ar(co x) {
	if (x.Y>=0&&x.X<0) return 1;
	if (x.X>=0&&x.Y>0) return 2;
	if (x.Y<=0&&x.X>0) return 3;
	return 4;
}

bool cp(pair<co, pair<int, int> > p1, pair<co, pair<int, int> > p2) {
	if (ar(p1.F)!=ar(p2.F)) {
		return ar(p1.F)<ar(p2.F);
	}
	return ccw({0, 0}, p2.F, p1.F)>0;
}

vector<co> minkowski(vector<co>&a, vector<co>&b) {
	int n=a.size();
	int m=b.size();
	if (n==0) return b;
	if (m==0) return a;
	if (n==1) {
		vector<co> ret(m);
		for (int i=0;i<m;i++) {
			ret[i]=b[i]+a[0];
		}
		return ret;
	}
	if (m==1) {
		vector<co> ret(n);
		for (int i=0;i<n;i++) {
			ret[i]=a[i]+b[0];
		}
		return ret;
	}
	vector<pair<co, pair<int, int> > > pp;
	for (int i=0;i<n;i++) {
		pp.push_back({a[(i+1)%n]-a[i], {1, i}});
	}
	for (int i=0;i<m;i++) {
		pp.push_back({b[(i+1)%m]-b[i], {2, i}});
	}
	sort(pp.rbegin(), pp.rend(), cp);
	co s={0, 0};
	co ad={0, 0};
	for (int i=0;i<(int)pp.size();i++) {
		s+=pp[i].F;
		if (pp[i].S.F!=pp[i+1].S.F) {
			if (pp[i].S.F==1) ad=a[(pp[i].S.S+1)%n]+b[(pp[i+1].S.S)%m];
			else ad=b[(pp[i].S.S+1)%m]+a[(pp[i+1].S.S)%n];
			ad-=s;
			break;
		}
	}
	s=ad;
	vector<co> ret(pp.size());
	for (int i=0;i<(int)pp.size();i++) {
		ret[i]=s;
		s+=pp[i].F;
	}
	return ret;
}