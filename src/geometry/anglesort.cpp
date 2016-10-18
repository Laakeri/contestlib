// TCR
// Comparasion function for sorting points around origin
// Points are sorted in clockwise order
// Works with integers and doubles
/*122
  143
  443*/
#include <bits/stdc++.h>
#define X real()
#define Y imag()
using namespace std;
typedef long double ld;
typedef long long ll;
typedef complex<ll> co;
bool ccw(co a, co b, co c) {
	return ((c-a)*conj(b-a)).Y>0;
}
int ar(co x) {
	if (x.Y>=0&&x.X<0) return 1;
	if (x.X>=0&&x.Y>0) return 2;
	if (x.Y<=0&&x.X>0) return 3;
	return 4;
}
bool cp(co p1, co p2) {
	if (ar(p1)!=ar(p2)) {
		return ar(p1)<ar(p2);
	}
	return ccw({0, 0}, p2, p1)>0;
}