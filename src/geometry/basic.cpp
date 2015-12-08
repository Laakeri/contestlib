// TCR
// Basic geometry functions using complex numbers
// Mostly copied from https://github.com/ttalvitie/libcontest/
/* Useful functions of complex number class
	CT abs(co x): Length
	CT norm(co x): Square of length
	CT arg(co x): Angle
	co polar(CT length, CT angle): Complex from polar components
*/
#include <bits/stdc++.h>
#define X real()
#define Y imag()
using namespace std;
typedef long double ld;
typedef long long ll;
// Coordinate type
typedef ld CT;
typedef complex<CT> co;

// Return true iff points a, b, c are CCW oriented.
bool ccw(co a, co b, co c) {
	return ((c-a)*conj(b-a)).Y>0;
}

// Return true iff points a, b, c are collinear.
// Note: doesn't make much sense with non-integer CT.
bool collinear(co a, co b, co c) {
	return ((c-a)*conj(b-a)).Y==0;
}

// Rotate x with agle ang
co rotate(co x, CT ang) {
	return x*polar((CT)1, ang);
}

// Check whether segments [a, b] and [c, d] intersect.
// The segments must not be collinear. Doesn't handle edge cases (endpoint of
// a segment on the other segment) consistently.
bool intersects(co a, co b, co c, co d) {
	return ccw(a, d, b)!=ccw(a, c, b)&&ccw(c, a, d)!=ccw(c, b, d);
}

// Interpolate between points a and b with parameter t.
co interpolate(CT t, co a, co b) {
	return a+t*(b-a);
}

// Return interpolation parameter between a and b of projection of v to the
// line defined by a and b.
// Note: no rounding behavior specified for integers.
CT projectionParam(co v, co a, co b) {
	return ((v-a)/(b-a)).X;
}

// Compute the distance of point v from line a..b.
// Note: Only for non-integers!
CT pointLineDistance(co p, co a, co b) {
	return abs(((p-a)/(b-a)).Y)*abs(b-a);
}

// Compute the distance of point v from segment a..b.
// Note: Only for non-integers!
CT pointSegmentDistance(co p, co a, co b) {
	co z=(p-a)/(b-a);
	if(z.X<0) return abs(p-a);
	if(z.X>1) return abs(p-b);
	return abs(z.Y)*abs(b-a);
}

// Return interpolation parameter between a and b of the point that is also
// on line c..d.
// Note: Only for non-integers!
CT intersectionParam(co a, co b, co c, co d) {
	co u=(c-a)/(b-a);
	co v=(d-a)/(b-a);
	return (u.X*v.Y-u.Y*v.X)/(v.Y-u.Y);
}