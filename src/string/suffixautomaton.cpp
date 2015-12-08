// TCR
// Online suffix automaton construction algorithm
// Time complexity of adding one character is amortized O(1)
#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomaton {
	vector<map<char, int> > g;
	vector<int> link;
	vector<int> len;
	int last;
	void addC(char c) {
		int p=last;
		int t=link.size();
		link.push_back(0);
		len.push_back(len[last]+1);
		g.push_back(map<char, int>());
		while (p!=-1&&g[p].count(c)==0) {
			g[p][c]=t;
			p=link[p];
		}
		if (p!=-1) {
			int q=g[p][c];
			if (len[p]+1==len[q]) {
				link[t]=q;
			}
			else {
				int qq=link.size();
				link.push_back(link[q]);
				len.push_back(len[p]+1);
				g.push_back(g[q]);
				while (p!=-1&&g[p][c]==q) {
					g[p][c]=qq;
					p=link[p];
				}
				link[q]=qq;
				link[t]=qq;
			}
		}
		last=t;
	}
	suffixAutomaton() : suffixAutomaton("") {}
	suffixAutomaton(string s) {
		last=0;
		g.push_back(map<char, int>());
		link.push_back(-1);
		len.push_back(0);
		for (int i=0;i<(int)s.size();i++) {
			addC(s[i]);
		}
	}
};