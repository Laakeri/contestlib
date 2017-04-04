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
using namespace std;
typedef long double ld;
typedef complex<ld> co;
const ld eps=1e-12;
const ld maxD=1e8;
ld ccw(co a, co b) {
	return (b*conj(a)).Y;
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
	co a, b;
	hp_t(co p1, co p2) {
		a=p1;
		b=(p2-p1)/abs(p2-p1);
	}
	ld d(co p) const {
		return ccw(b, p-a);
	}
	bool operator==(const hp_t& o) const {
		return abs(b.X-o.b.X)<eps&&abs(b.Y-o.b.Y)<eps;
	}
	bool operator<(const hp_t& o) const {
		if ((*this)==o){
			return d(o.a)<-eps;
		}
		return cp(b, o.b);
	}
};
co getI(hp_t a, hp_t b) {
	ld c=ccw(a.b, b.b);
	assert(!(abs(c)<eps));
	return ccw(b.a, b.b)*a.b/c+ccw(a.b, a.a)*b.b/c;
}
vector<co> getHPI(vector<hp_t> hp) {
	hp.push_back({{-maxD, -maxD}, {maxD, -maxD}});
	hp.push_back({{maxD, -maxD}, {maxD, maxD}});
	hp.push_back({{maxD, maxD}, {-maxD, maxD}});
	hp.push_back({{-maxD, maxD}, {-maxD, -maxD}});
	sort(hp.begin(), hp.end());
	hp.erase(unique(hp.begin(), hp.end()), hp.end());
	int del=0;
	vector<co> p;
	for (int i=1;i<(int)hp.size();i++){
		while ((int)p.size()>del&&hp[i].d(p.back())<eps) p.pop_back();
		while ((int)p.size()>del&&hp[i].d(p[del])<eps) del++;
		if (del==(int)p.size()&&ccw(hp[p.size()].b, hp[i].b)<eps) return {};
		co np=getI(hp[i], hp[p.size()]);
		if (hp[del].d(np)>-eps){
			p.push_back(np);
			hp[p.size()]=hp[i];
		}
	}
	rotate(p.begin(), p.begin()+del, p.end());
	rotate(hp.begin(), hp.begin()+del, hp.begin()+p.size()+1);
	p.resize((int)p.size()-del);
	if (p.empty()) return p;
	p.push_back(getI(hp[0], hp[p.size()]));
	return p;
}