// Fast union find
// Uses 1-indexing
#include <bits/stdc++.h>
using namespace std;

struct unionFind{
    vector<int> u;
    vector<int> us;
	
	// Construct union find data structure of n vertices
    unionFind(int n):u(n+1),us(n+1){
        for (int i=1;i<=n;i++){
            u[i]=i;
            us[i]=1;
        }
    }
    
	// Get the union of x
    int get(int x){
        if (x==u[x]) return x;
        return u[x]=get(u[x]);
    }

    // Union a and b
    void un(int a, int b){
        a=get(a);
        b=get(b);
        if (a!=b){
            if (us[a]<us[b]) swap(a, b);
            us[a]+=us[b];
            u[b]=a;
        }
    }
};
