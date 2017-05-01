// TCR
// Link/cut tree. All operations are amortized O(log n) time
// This implementation supports finding minimum value on a path (usual MST case)
// evert(x) makes x the root
// expose(x, y) now the path from x to y is in the tree whose root is x
#include <bits/stdc++.h>
using namespace std;
struct Node {
	Node* c[2], *p;
	int id, rev;
	int v, mv;
	int isr() {
		return !p||(p->c[0]!=this&&p->c[1]!=this);
	}
	int dir() {
		return p->c[1]==this;
	}
	void upd(){
		mv=v;
		if (c[0]) mv=min(mv, c[0]->mv);
		if (c[1]) mv=min(mv, c[1]->mv);
	}
	void setc(Node* s, int d) {
		c[d]=s;
		if (s) s->p=this;
		upd();
	}
	void push() {
		if (rev) {
			swap(c[0], c[1]);
			if (c[0]) c[0]->rev^=1;
			if (c[1]) c[1]->rev^=1;
			rev=0;
		}
	}
	Node(int i, int val) : id(i), v(val), mv(val) {
		c[0]=0;c[1]=0;p=0;rev=0;
	}
};
struct LinkCut {
	void rot(Node* x) {
		Node* p=x->p;int d=x->dir();
		if (!p->isr()) p->p->setc(x, p->dir());
		else x->p=p->p;
		p->setc(x->c[!d], d);x->setc(p, !d);
	}
	void pp(Node* x) {
		if (!x->isr()) pp(x->p);
		x->push();
	}
	void splay(Node* x) {
		pp(x);
		while (!x->isr()) {
			if (x->p->isr()) rot(x);
			else if(x->dir()==x->p->dir()) {
				rot(x->p);rot(x);
			}
			else {
				rot(x);rot(x);
			}
		}
	}
	Node* expose(Node* x) {
		Node* q=0;
		for (;x;x=x->p) {
			splay(x);x->c[1]=q;x->upd();q=x;
		}
		return q;
	}
	void evert(Node* x) {
		x=expose(x);x->rev^=1;x->push();
	}
	void link(Node* x, Node* y) {
		evert(x);evert(y);splay(y);x->setc(y, 1);
	}
	void expose(Node* x, Node* y) {
		evert(x);expose(y);splay(x);
	}
	void cut(Node* x, Node* y) {
		expose(x, y);x->c[1]=0;x->upd();y->p=0;
	} 
	int rootid(Node* x) {
		expose(x);splay(x);
		while(x->c[0]) {
			x=x->c[0];x->push();
		}
		splay(x);
		return x->id;
	}
	Node* getMin(Node* x) {
		if (x->v==x->mv) {
			splay(x);
			return x;
		}
		if (x->c[0]&&x->c[0]->mv==x->mv) return getMin(x->c[0]);
		else return getMin(x->c[1]);
	}
	Node* getMinP(Node* x, Node* y) {
		expose(x, y);
		return getMin(x);
	}
};