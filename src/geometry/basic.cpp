// TCR
// Basic geometry functions using complex numbers
// Mostly copied from https://github.com/ttalvitie/libcontest/
/* Useful functions of complex number class
	CT abs(co x): Length
	CT norm(co x): Square of length
	CT arg(co x): Angle
	co polar(CT length, CT angle): Complex from polar components*/
#include <bits/stdc++.h>
#define X real()
#define Y imag()
using namespace std;
typedef long double ld;
typedef long long ll;
// Coordinate type
typedef ld CT;
typedef complex<CT> co;
ld eps=1e-12;
// Return true iff points a, b, c are CCW oriented.
bool ccw(co a, co b, co c) {
	return ((c-a)*conj(b-a)).Y>0;
}
// Return true iff points a, b, c are collinear.
// Note: doesn't make much sense with non-integer CT.
bool collinear(co a, co b, co c) {
	return abs(((c-a)*conj(b-a)).Y)<eps;
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
// x=a*(1-t)+b*t
CT intersectionParam(co a, co b, co c, co d) {
	co u=(c-a)/(b-a);
	co v=(d-a)/(b-a);
	return (u.X*v.Y-u.Y*v.X)/(v.Y-u.Y);
}
// Intersection points of circles with centers p1 and p2 with radiuses r1 and r2
// The first return value is the number of intersection points, 3 for infinite
pair<int, pair<co, co> > circleIntersection(co p1, CT r1, co p2, CT r2) {
	if (norm(p1-p2)>(r1+r2)*(r1+r2)||norm(p1-p2)<(r1-r2)*(r1-r2)) 
		return {0, {{0, 0}, {0, 0}}};
	if (abs(p1-p2)<eps&&abs(r1-r2)<eps) 
		return {3, {{p1.X, p1.Y+r1}, {p1.X+r1, p1.Y}}};
	CT a=abs(p1-p2);
	CT x=(r1*r1-r2*r2+a*a)/(2*a);
	co v1={x, sqrt(r1*r1-x*x)};
	co v2={x, -sqrt(r1*r1-x*x)};
	v1=v1*(p2-p1)/a+p1;
	v2=v2*(p2-p1)/a+p1;
	if (abs(v1-v2)<eps) return {1, {v1, v1}};
	return {2, {v1, v2}};
}
// Intersection of lines a..b and c..d
// Only for doubles
pair<int, co> lineIntersection(co a, co b, co c, co d) {
	if (collinear(a, b, c)&&collinear(a, b, d)) {
		return {2, a};
	}
	else if(abs(((b-a)/(c-d)).Y)<eps) {
		return {0, {0, 0}};
	}
	else {
		CT t=intersectionParam(a, b, c, d);
		return {1, a*(1-t)+b*t};
	}
}
// Is b between a and c
// Only for doubles
int between(co a, co b, co c) {
	return abs(abs(a-b)+abs(b-c)-abs(a-c))<eps;
}
// Intersection of segments a..b and c..d
// Only for doubles
// The first return value is the number of intersection points, 2 for infinite
// The second values are the endpoints of the intersection segment
pair<int, pair<co, co> > segmentIntersection(co a, co b, co c, co d) {
	if (abs(a-b)<eps) {
		if (between(c, a, d)) return {1, {a, a}};
		else return {0, {0, 0}};
	}
	else if (abs(c-d)<eps) {
		if (between(a, c, b)) return {1, {c, c}};
		else return {0, {0, 0}};
	}
	else if (collinear(a, b, c)&&collinear(a, b, d)) {
		if (((b-a)/(d-c)).X<0) swap(c, d);
		co beg;
		if (between(a,c,b)) beg=c;
		else if (between(c,a,d)) beg=a;
		else return {0, {{0, 0}, {0, 0}}};
		co en=d;
		if (between(c, b, d)) en=b;
		if (abs(beg-en)<eps) return {1, {beg, beg}};
		return {2, {beg, en}};
	}
	else if(abs(((b-a)/(c-d)).Y)<eps) {
		return {0, {0, 0}};
	}
	else {
		CT u=intersectionParam(a, b, c, d);
		CT v=intersectionParam(c, d, a, b);
		if (u<-eps||u>1+eps||v<-eps||v>1+eps) {
			return {0, {{0, 0}, {0, 0}}};
		}
		else {
			co p=a*(1-u)+b*u;
			return {1, {p, p}};
		}
	}
}
// Returns a point from the ray bisecting the non-reflex angle abc.
// Only for doubles. Returns 0 if the points are collinear.
pair<co,int> angleBisector(co a, co b, co c) {
	if (collinear(a,b,c)) return {{0, 0}, 0};
	co aa=(a-b)/abs(a-b);
	co cc=(c-b)/abs(c-b);
	co bb=sqrt(aa/cc);
	return {b+bb*cc, 1};
}
