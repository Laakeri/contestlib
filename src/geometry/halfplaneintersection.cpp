// TCR
// work in process
#include <bits/stdc++.h>
#define X real()
#define Y imag()
using namespace std;
typedef long double ld;
typedef complex<ld> co;
const ld eps=1e-12;
const ld pi=atan2(0, -1);
const int maxN=1e6;
int cnt=0;
const ld maxd=1e9;

int dblcmp(ld x) {
  return (x < -eps ? -1 : x > eps);
}

ld ccw(co a, co b) {
  return (b*conj(a)).Y;
}

co isLL(co a, co b, co c, co d) {
	co p1=b-a;
	co p2=d-c;
	ld a1=p1.Y;
	ld b1=-p1.X;
	ld a2=p2.Y;
	ld b2=-p2.X;
	assert(dblcmp(a1 * b2 - a2 * b1) != 0);
	ld c1=a1*a.X+b1*a.Y;
	ld c2=a2*c.X+b2*c.Y;
	return co((c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1), (c1 * a2 - c2 * a1) / (b1 * a2 - b2 * a1));
}

struct hp_t {
	co p1, p2;
	ld a;
	hp_t() { }
	hp_t(co tp1, co tp2) : p1(tp1), p2(tp2) {
		tp2 = tp2 - tp1;
		a = atan2(tp2.Y, tp2.X);
	}
	bool operator==(const hp_t &r) const {
		return dblcmp(a - r.a) == 0;
	}
	bool operator<(const hp_t &r) const {
		if (dblcmp(a - r.a) == 0) return dblcmp(ccw(r.p2 - r.p1, p2 - r.p1)) >= 0;
		else return a < r.a;
	}
};

bool checkhp(hp_t h1, hp_t h2, hp_t h3) {
	co p = isLL(h1.p1, h1.p2, h2.p1, h2.p2);
	return dblcmp(ccw(p - h3.p1, h3.p2 - h3.p1)) > 0;
}

vector<co> ishp(vector<hp_t> hp) {
	hp.push_back({{-maxd, -maxd}, {maxd, -maxd}});
	hp.push_back({{maxd, -maxd}, {maxd, maxd}});
	hp.push_back({{maxd, maxd}, {-maxd, maxd}});
	hp.push_back({{-maxd, maxd}, {-maxd, -maxd}});
	sort(hp.begin(), hp.end());
	hp.erase(unique(hp.begin(), hp.end()), hp.end());
	cnt=hp.size();
	deque<hp_t> dq;
	dq.push_back(hp[0]);
	dq.push_back(hp[1]);
	for (int i = 2; i < cnt; ++i) {
		while (dq.size() > 1 && checkhp(*----dq.end(), *--dq.end(), hp[i])) dq.pop_back();
		while (dq.size() > 1 && checkhp(*++dq.begin(), *dq.begin(), hp[i])) dq.pop_front();
		dq.push_back(hp[i]);
	}
	while (dq.size() > 1 && checkhp(*----dq.end(), *--dq.end(), dq.front())) dq.pop_back();
	while (dq.size() > 1 && checkhp(*++dq.begin(), *dq.begin(), dq.back())) dq.pop_front();
	dq.push_front(dq.back());
	vector<co> res;
	while (dq.size() > 1) {
		hp_t tmp = dq.front();
		dq.pop_front();
		res.push_back(isLL(tmp.p1, tmp.p2, dq.front().p1, dq.front().p2));
	}
	return res;
}

int main(){
	vector<hp_t> hp;
	hp.push_back({{2, 2}, {3, 6}});
	hp.push_back({{4, 4}, {1, 6}});
	hp.push_back({{1, 7}, {3, 2}});
	auto ps=ishp(hp);
	for (auto p:ps){
		cout<<p<<endl;
	}
}