#include <bits/stdc++.h>
#define F first
#define S second
#define X real()
#define Y imag()
using namespace std;
typedef long long ll;
typedef complex<ll> co;

ll ccw(co a, co b, co c) {
	return ((c-a)*conj(b-a)).Y;
}

bool up(co p, vector<co>& h, int a, int b, int d){
	int n=h.size();
	return (ll)d*ccw(p, h[(a+n)%n], h[(b+n)%n])<=0;
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
	
	vector<co> hull;
	hull.push_back(ps[0]);
	for (int d=0;d<2;d++) {
		if (d) reverse(ps.begin(), ps.end());
		int s=hull.size();
		for (int i=1;i<n;i++) {
			while ((int)hull.size()>s&&ccw(hull[hull.size()-2], hull.back(), ps[i])<=0) {
				hull.pop_back();
			}
			hull.push_back(ps[i]);
		}
	}
	hull.pop_back();
	return hull;
}

int getTanP(co p, vector<co>& h, int d) {
	int n=h.size();
	int mi=0;
	int ma=n;
	while (mi+1<ma){
		int mid=(mi+ma)/2;
		if (up(p, h, mi, mi+1, d)){
			if (up(p, h, mid+1, mid, d)){
				ma=mid;
			}
			else if(up(p, h, mi, mid, d)){
				mi=mid;
			}
			else{
				ma=mid;
			}
		}
		else{
			if (up(p, h, mid, mid+1, d)){
				mi=mid;
			}
			else if(up(p, h, mid, mi, d)){
				mi=mid;
			}
			else{
				ma=mid;
			}
		}
	}
	int step=0;
	if (d==1){
		ma%=n;
		while (up(p, h, ma, ma+1, d)){
			ma=(ma+1)%n;
			step++;
			assert(step<2);
		}
		return ma;
	}
	else{
		while (up(p, h, mi, mi+1, d)){
			mi=(mi+1)%n;
			step++;
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