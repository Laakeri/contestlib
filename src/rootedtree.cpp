//build parent array of tree O(n log n) space
//query i:th parent in O(log n) time
//query lca in O(log n) time
//query distance in O(log n) time
//uses 1-indexing
#include <bits/stdc++.h>
using namespace std;

struct RootedTree{
    vector<int> d;//depth
    vector<array<int, 22> > p;//parent array

    void dfs(vector<int>*g, int x, int pp, int dd){//init dfs
        p[x][0]=pp;
        for (int i=1;i<22;i++){
            p[x][i]=p[p[x][i-1]][i-1];
        }
        d[x]=dd;
        for (int nx:g[x]){
            dfs(g, nx, x, dd+1);
        }
    }

    RootedTree(vector<int>*g, int n, int root=1):d(n+1),p(n+1){
        dfs(g, root, 0, 0);
    }

    int parent(int x, int h){//returns the node h edges above x. else 0 is returned
        for (int i=21;i>=0;i--){
            if ((1<<i)&h){
                x=p[x][i];
            }
        }
        return x;
    }

    int lca(int a, int b){//returns lca of a and b
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

    int dist(int a, int b){//returns distance from a to b
        int l=lca(a, b);
        return d[a]+d[b]-2*d[l];
    }
};
