// O(n log n) offline solution for dynamic connectivity problem
// ? count the number of connected components
// + A B add edge between A and B
// - A B remove edge between A and B
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

struct e{
	int a,b,l,r;
};
int qqs[603030];
int qv[603030];
int is[603030];
int uf[603030];
int id[603030];

int getu(int a){
	if (uf[a]==a) return a;
	return uf[a]=getu(uf[a]);
}

void un(int a, int b){
	a=getu(a);
	b=getu(b);
	if (a!=b) uf[a]=b;
}

void go(int l, int r, int uc, int n, vector<e> es){
	for (int i=1;i<=n;i++){
		is[i]=0;
	}
	int i2=1;
	vector<pair<int, int> > te;
	vector<e> ce;
	for (e ee:es){
		if (ee.a!=ee.b&&(!(ee.l>r||ee.r<l))){
			if (is[ee.a]==0){
				is[ee.a]=i2;
				ee.a=i2++;
			}
			else{
				ee.a=is[ee.a];
			}
			if (is[ee.b]==0){
				is[ee.b]=i2;
				ee.b=i2++;
			}
			else{
				ee.b=is[ee.b];
			}
			if (ee.l<=l&&r<=ee.r){
				te.push_back({ee.a, ee.b});
			}
			else{
				ce.push_back(ee);
			}
		}
	}
	for (int i=1;i<=n;i++){
		if (is[i]==0){
			uc++;
		}
	}
	for (int i=1;i<i2;i++){
		uf[i]=i;
		id[i]=0;
	}
	for (auto ee:te){
		un(ee.F, ee.S);
	}
	int i3=1;
	for (int i=1;i<i2;i++){
		if (id[getu(uf[i])]==0){
			id[getu(uf[i])]=i3++;
		}
	}
	for (e&ee:ce){
		ee.a=id[getu(ee.a)];
		ee.b=id[getu(ee.b)];
	}
	if (l==r){
		qv[l]=uc+i3-1;
	}
	else{
		int m=(l+r)/2;
		go(l, m, uc, i3-1, ce);
		go(m+1, r, uc, i3-1, ce);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,k;
	cin>>n>>k;
	int qs=0;
	vector<e> es;
	map<pair<int, int>, int> ae;
	for (int i=1;i<=k;i++){
		char t;
		cin>>t;
		if (t=='?'){
			qqs[qs++]=i;
		}
		else{
			int a,b;
			cin>>a>>b;
			if (t=='+'){
				pair<int, int> lol={min(a, b), max(a, b)};
				ae[lol]=i;
			}
			else{
				pair<int, int> lol={min(a, b), max(a, b)};
				int s=ae[lol];
				ae[lol]=0;
				es.push_back({a, b, s, i});
			}
		}
	}
	for (auto t:ae){
		if (t.S>0){
			es.push_back({t.F.F, t.F.S, t.S, k});
		}
	}
	go(0, (1<<19)-1, 0, n, es);
	for (int i=0;i<qs;i++){
		cout<<qv[qqs[i]]<<'\n';
	}
}