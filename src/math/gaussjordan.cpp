// TCR
// Solves system of linear equations in O(n m^2)
// Using doubles or mod 2
// Using doubles might have large precision errors or overflow
// Returns 0 if no solution exists, 1 if there is one solution
// or 2 if infinite number of solutions exists
// If at least one solution exists, it is returned in ans
// You can modify the general algorithm to work mod p by using modular inverse
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld eps=1e-12;

// Using doubles
int gaussD (vector<vector<ld> > a, vector<ld>& ans) {
	int n=(int)a.size();
	int m=(int)a[0].size()-1;
	
	vector<int> where(m,-1);
	for (int col=0,row=0;col<m&&row<n;col++) {
		int sel=row;
		for (int i=row;i<n;i++) {
			if (abs(a[i][col])>abs(a[sel][col])) sel=i;
		}
		if (abs(a[sel][col])<eps) continue;
		for (int i=col;i<=m;i++) {
			swap (a[sel][i], a[row][i]);
		}
		where[col]=row;
		
		for (int i=0;i<n;i++) {
			if (i!=row) {
				ld c=a[i][col]/a[row][col];
				for (int j=col;j<=m;j++) {
					a[i][j]-=a[row][j]*c;
				}
			}
		}
		row++;
	}
	
	ans.assign(m, 0);
	for (int i=0;i<m;i++) {
		if (where[i]!=-1) ans[i]=a[where[i]][m]/a[where[i]][i];
	}
	for (int i=0;i<n;i++) {
		ld sum=0;
		for (int j=0;j<m;j++) {
			sum+=ans[j]*a[i][j];
		}
		if (abs(sum-a[i][m])>eps) return 0;
	}
	
	for (int i=0;i<m;i++) {
		if (where[i]==-1) return 2;
	}
	return 1;
}

// mod 2
// n is number of rows m is number of variables
const int M=4;
int gaussM(vector<bitset<M> > a, int n, int m, bitset<M-1>& ans) {
	vector<int> where (m, -1);
	for (int col=0,row=0;col<m&&row<n;col++) {
		for (int i=row;i<n;i++) {
			if (a[i][col]) {
				swap (a[i], a[row]);
				break;
			}
		}
		if (!a[row][col]) continue;
		where[col]=row;
		
		for (int i=0;i<n;i++) {
			if (i!=row&&a[i][col]) {
				a[i]^=a[row];
			}
		}
		row++;
	}
	ans=0;
	for (int i=0;i<m;i++) {
		if (where[i]!=-1) ans[i]=a[where[i]][m];
	}
	for (int i=0;i<n;i++) {
		int sum=0;
		for (int j=0;j<m;j++) {
			sum^=ans[j]*a[i][j];
		}
		if (sum!=a[i][m]){
			return 0;
		}
	}
	for (int i=0;i<m;i++){
		if (where[i]==-1) return 2;
	}
	return 1;
}

int main() {
	// Should output 2, 1 2 0
	vector<vector<ld> > d(3);
	d[0]={3, 3, -15, 9};
	d[1]={1, 0, -2, 1};
	d[2]={2, -1, -1, 0};
	vector<ld> da;
	cout<<gaussD(d, da)<<endl;
	cout<<da[0]<<" "<<da[1]<<" "<<da[2]<<endl;
	
	// Should output 1, 110
	// Note that bitsets are printed in reverse order
	bitset<M> r1("0110");
	bitset<M> r2("1101");
	bitset<M> r3("0111");
	vector<bitset<M> > m={r1, r2, r3};
	bitset<M-1> ma;
	cout<<gaussM(m, 3, 3, ma)<<endl;
	cout<<ma<<endl;
}