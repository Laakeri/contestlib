// TCR
// 3d convex hull in O(n^2 log n)
// first 4 points should not be coplanar
struct v3 {
	ld x,y,z;
	v3() : x(0), y(0), z(0) {}
	v3(ld xx, ld yy, ld zz) : x(xx), y(yy), z(zz) {};
};
v3 operator+(v3 a, v3 b) {
	return v3(a.x+b.x, a.y+b.y, a.z+b.z);
}
v3 operator-(v3 a, v3 b) {
	return v3(a.x-b.x, a.y-b.y, a.z-b.z);
}
v3 operator*(v3 a, v3 b) {
	return v3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
ld operator^(v3 a, v3 b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}
bool onSameHalfSpace(v3 a, v3 b, v3 p1, v3 p2, v3 p3) {
	v3 hlp = (p2-p1)*(p3-p1);
	return (hlp^(a-p1))*(hlp^(b-p1))>=0;
}
int n;
v3 pts[1010];
map<pair<pair<int,int>,int>,int> convHull;
void toggleHull(int i1, int i2, int i3, int ref) {
	if (convHull.count({{i1,i2},i3})) {
		convHull.erase({{i1,i2},i3});
	} else convHull[{{i1,i2},i3}]=ref;
}
void makeHull() {
	convHull[{{0,1},2}]=3;
	convHull[{{0,1},3}]=2;
	convHull[{{0,2},3}]=1;
	convHull[{{1,2},3}]=0;
	for (int i=4;i<n;i++) {
		vector<pair<pair<int,int>,pair<int,int>>> toChange;
		for (auto hullFace : convHull) {
			int i1=hullFace.F.F.F;
			int i2=hullFace.F.F.S;
			int i3=hullFace.F.S;
			v3 pt1=pts[i1];
			v3 pt2=pts[i2];
			v3 pt3=pts[i3];
			v3 ref=pts[hullFace.S];
			if (!onSameHalfSpace(pts[i],ref,pt1,pt2,pt3)) {
				toChange.push_back({{i1,i2},{i,i3}});
				toChange.push_back({{i1,i3},{i,i2}});
				toChange.push_back({{i2,i3},{i,i1}});
				toChange.push_back({{i1,i2},{i3,i}});
			}
		}
		for (auto diff : toChange) {
			toggleHull(diff.F.F,diff.F.S,diff.S.F, diff.S.S);
		}
	}
}