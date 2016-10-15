// TCR
// Aho-Corasick algorithm
// Building of automaton is O(L) where L is total length of dictionary
// Matching is O(n + number of matches), O(n sqrt(L)) in the worst case
// Add dictionary using addString and then use pushLinks
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
struct AhoCorasick {
	vector<map<char, int> > g;
	vector<int> link;
	vector<int> tlink;
	vector<int> te;
	// Use 1-indexing in id
	void addString(const string& s, int id) {
		int tn=0;
		for (int i=0;i<(int)s.size();i++) {
			if (g[tn][s[i]]==0) {
				g[tn][s[i]]=g.size();
				g.push_back(map<char, int>());
				link.push_back(0);
				tlink.push_back(0);
				te.push_back(0);
			}
			tn=g[tn][s[i]];
		}
		te[tn]=id;
	}
	void pushLinks() {
		queue<int> bfs;
		bfs.push(0);
		while (!bfs.empty()) {
			int x=bfs.front();
			bfs.pop();
			for (auto nx:g[x]) {
				int l=link[x];
				while (l!=-1&&g[l].count(nx.F)==0) l=link[l];
				if (l!=-1) link[nx.S]=g[l][nx.F];
				bfs.push(nx.S);
				if (te[link[nx.S]]) {
					tlink[nx.S]=link[nx.S];
				}
				else{
					tlink[nx.S]=tlink[link[nx.S]];
				}
			}
		}
	}
	// Returns matches {id, endpos}
	vector<pair<int, int> > match(const string& s) {
		int tn=0;
		vector<pair<int, int> > re;
		for (int i=0;i<(int)s.size();i++) {
			while (tn!=-1&&g[tn].count(s[i])==0) tn=link[tn];
			if (tn==-1) tn=0;
			tn=g[tn][s[i]];
			int f=tlink[tn];
			if (te[tn]) re.push_back({te[tn], i});
			while (f) {
				re.push_back({te[f], i});
				f=tlink[f];
			}
		}
		return re;
	}
	AhoCorasick() {
		g.push_back(map<char, int>());
		link.push_back(-1);
		tlink.push_back(0);
		te.push_back(0);
	}
};