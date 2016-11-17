// TCR
// getHPI returns the points of the half place intersection in the ccw order
// The allowed half plane is the left side of the p1 -> p2 vector
// maxD defines the bounding square so that the resulting polygon is never infinite
// May return many points even though the intersection is empty.
// Compute the area to check the emptiness.
// May return duplicate points and is generally kind of numerically unstable.
#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define F first
#define S second
using namespace std;
typedef long double ld;
typedef complex<ld> co;
const ld eps=1e-14;
const ld maxD=1e8;
ld ccw(co a, co b) {
	return (b*conj(a)).Y;
}
pair<int, co> isLL(co a, co b, co c, co d) {
	co u=(c-a)/(b-a);
	co v=(d-a)/(b-a);
	if (abs(v.Y-u.Y)<eps) return {0, 0};
	ld p=(v*conj(u)).Y/(v.Y-u.Y);
	return {1, a*(1-p)+b*p};
}
int ar(co x) {
	if (x.Y>=0&&x.X<0) return 1;
	if (x.X>=0&&x.Y>0) return 2;
	if (x.Y<=0&&x.X>0) return 3;
	return 4;
}
bool cp(co p1, co p2) {
	if (ar(p1)!=ar(p2)) return ar(p1)>ar(p2);
	return ccw(p2, p1)<0;
}
struct hp_t {
	co p1, p2;
	bool operator==(const hp_t &r) const {
		co t=(p2-p1)*conj(r.p2-r.p1);
		return t.X>0&&abs(t.Y)<eps;
	}
	bool operator<(const hp_t &r) const {
		if (operator==(r)) return ccw(r.p2-r.p1, p2-r.p1)>0;
		else return cp(p2-p1, r.p2-r.p1);
	}
};
bool checkhp(hp_t h1, hp_t h2, hp_t h3) {
	auto p=isLL(h1.p1, h1.p2, h2.p1, h2.p2);
	return p.F==1&&ccw(p.S-h3.p1, h3.p2-h3.p1)>-eps;
}
vector<co> getHPI(vector<hp_t> hp) {
	hp.push_back({{-maxD, -maxD}, {maxD, -maxD}});
	hp.push_back({{maxD, -maxD}, {maxD, maxD}});
	hp.push_back({{maxD, maxD}, {-maxD, maxD}});
	hp.push_back({{-maxD, maxD}, {-maxD, -maxD}});
	sort(hp.begin(), hp.end());
	hp.erase(unique(hp.begin(), hp.end()), hp.end());
	deque<hp_t> dq;
	dq.push_back(hp[0]);
	dq.push_back(hp[1]);
	for (int i=2;i<(int)hp.size();i++) {
		while (dq.size()>1&&checkhp(*----dq.end(), *--dq.end(), hp[i])) dq.pop_back();
		while (dq.size()>1&&checkhp(*++dq.begin(), *dq.begin(), hp[i])) dq.pop_front();
		dq.push_back(hp[i]);
	}
	while (dq.size()>1&&checkhp(*----dq.end(), *--dq.end(), dq.front())) dq.pop_back();
	while (dq.size()>1&&checkhp(*++dq.begin(), *dq.begin(), dq.back())) dq.pop_front();
	dq.push_front(dq.back());
	vector<co> res;
	while (dq.size()>1) {
		hp_t tmp = dq.front();
		dq.pop_front();
		res.push_back(isLL(tmp.p1, tmp.p2, dq.front().p1, dq.front().p2).S);
	}
	return res;
}