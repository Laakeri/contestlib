// Treap implementation with pointers
// Expected running time of split and merge is O(log n)
#include <bits/stdc++.h>
using namespace std;

typedef struct node* pnode;
struct node {
	pnode l,r;
	int pr,c;
	node() {
		l=0;
		r=0;
		c=1;
		pr=rand();
	}
};

// Returns the size of the subtree t
int cnt(pnode t) {
	if (t) return t->c;
	return 0;
}

// Updates the size of the subtree t
void upd(pnode t) {
	if (t) t->c=cnt(t->l)+cnt(t->r)+1;
}

// Put lazy updates here
void push(pnode t) {
	if (t) {
		// Something
	}
}

// Merges trees l and r into tree t
void merg(pnode& t, pnode l, pnode r) {
	push(l);
	push(r);
	if (!l) t=r;
	else if(!r) t=l;
	else {
		if (l->pr>r->pr) {
			merg(l->r, l->r, r);
			t=l;
		}
		else {
			merg(r->l, l, r->l);
			t=r;
		}
	}
	upd(t);
}

// Splits tree t into trees l and r
// Size of tree l will be k
void split(pnode t, pnode& l, pnode& r, int k) {
	if (!t) {
		l=0;
		r=0;
		return;
	}
	else {
		push(t);
		if (cnt(t->l)>=k) {
			split(t->l, l, t->l, k);
			r=t;
		}
		else {
			split(t->r, t->r, r, k-cnt(t->l)-1);
			l=t;
		}
	}
	upd(t);
}