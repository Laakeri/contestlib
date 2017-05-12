// TCR
// Minimum enclosing circle in expected O(n) time
// Remove duplicate points before using
#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define F first
#define S second
using namespace std;
typedef long double ld;
typedef complex<ld> co;
pair<co, ld> md2(vector<co> R) {
	if (R.size()==0) {
		return {{0, 0}, -1};
	} else if (R.size()==1) {
		return {R[0], 0};
	} else if (R.size()==2) {
		return {(R[0]+R[1])/(ld)2.0, hypot(R[0].X-R[1].X, R[0].Y-R[1].Y)/2.0};
	} else {
		ld s=(co(0, 1)*(R[0]-R[2])*conj(R[2]-R[1])).Y/((R[0]-R[1])*conj(R[2]-R[1])).Y;
		co c=(R[0]+R[1])/(ld)2.0+co(0, 1)*s*((R[0]-R[1])/(ld)2.0);
		return {c, hypot(R[0].X-c.X, R[0].Y-c.Y)};
	}
}
pair<co, ld> md(vector<co>& P, int i, vector<co> R) {
	if (i==(int)P.size()||R.size()==3) {
		return md2(R);
	} else {
		auto D=md(P, i+1, R);
		if (hypot(P[i].X-D.F.X, P[i].Y-D.F.Y)>D.S) {
			R.push_back(P[i]);
			D=md(P, i+1, R);
		}
		return D;
	}
}
pair<co, ld> minEnclosing(vector<co> P) {
	random_shuffle(P.begin(), P.end());
	return md(P, 0, vector<co>());
}