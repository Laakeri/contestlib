// Build parent array of tree using O(n log n) space
// Query i:th parent in O(log n) time
// Query lca in O(log n) time
// Query distance in O(log n) time
// Uses 1-indexing
#include <bits/stdc++.h>
using namespace std;

struct RootedTree{
	// This has to be at least ceil(log2(n))
	const int logOfSize=22;
	
    vector<int> d;
    vector<array<int, logOfSize> > p;

	// Dfs for building parent array
    void dfs(vector<int>*g, int x, int pp, int dd){
        p[x][0]=pp;
        for (int i=1;i<22;i++){
            p[x][i]=p[p[x][i-1]][i-1];
        }
        d[x]=dd;
        for (int nx:g[x]){
            dfs(g, nx, x, dd+1);
        }
    }

    // Construct parent array data structure of tree of size n
    // g is the adjacency list of the tree
    RootedTree(vector<int>*g, int n, int root=1):d(n+1),p(n+1){
        dfs(g, root, 0, 0);
    }

    // Returns the node h edges above x.
    // Returns 0 if no such node exists
    int parent(int x, int h){
        for (int i=21;i>=0;i--){
            if ((1<<i)&h){
                x=p[x][i];
            }
        }
        return x;
    }

    // Returns lca of nodes a and b
    int lca(int a, int b){
        if (d[a]<d[b]) swap(a, b);
        a=parent(a, d[a]-d[b]);
        if (a==b) return a;
        for (int i=21;i>=0;i--){
            if (p[a][i]!=p[b][i]){
                a=p[a][i];
                b=p[b][i];
            }
        }
        return p[a][0];
    }

    // Returns distance from a to b
    int dist(int a, int b){
        int l=lca(a, b);
        return d[a]+d[b]-2*d[l];
    }
};
