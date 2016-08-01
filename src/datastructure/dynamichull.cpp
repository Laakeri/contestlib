// TCR
// Data structure that maintains a set of lines in O(log n) query time
// Operations: insert line, find the highest line at x coordinate x
// Works with integers and doubles
// Cast too large integers to doubles when comparing to avoid overflow
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll isQuery=-(1LL<<62);
struct Line {
	ll m, b;
	int id;
	Line(ll m_, ll b_, int id_) : m(m_), b(b_), id(id_) {}
	mutable multiset<Line>::iterator it,e;
	const Line* succ() const {
		return next(it)==e ? 0 : &*next(it);
	}
	bool operator<(const Line& rhs) const {
		if (rhs.b!=isQuery) return m<rhs.m;
		const Line* s=succ();
		if (!s) return 0;
		ll x=rhs.m;
		return b-s->b<(s->m-m)*x;
	}
};
struct DynamicHull : public multiset<Line> {
	bool bad(iterator y) {
		auto z=next(y);
		if (y==begin()) {
			if (z==end()) return 0;
			return y->m==z->m&&y->b<=z->b;
		}
		auto x=prev(y);
		if (z==end()) return y->m==x->m&&y->b<=x->b;
		return (x->b-y->b)*(z->m-y->m)>=(y->b-z->b)*(y->m-x->m);
	}
	void insertLine(ll m, ll b, int id) {
		auto y=insert({m, b, id});
		y->it=y;y->e=end();
		if (bad(y)) {erase(y);return;}
		while (next(y)!=end()&&bad(next(y))) erase(next(y));
		while (y!=begin()&&bad(prev(y))) erase(prev(y));
	}
	pair<ll, int> getMax(ll x) {
		auto l=*lower_bound({x, isQuery, 0});
		return {l.m*x+l.b, l.id};
	}
};