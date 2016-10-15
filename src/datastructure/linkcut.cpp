// TCR
// Link/cut tree. All operations are amortized O(log n) time
#include <bits/stdc++.h>
using namespace std;
struct Node {
	Node* c[2], *p;
	int id, rev;
	int isr() {
		return !p||(p->c[0]!=this&&p->c[1]!=this);
	}
	int dir() {
		return p->c[1]==this;
	}
	void setc(Node* s, int d) {
		c[d]=s;
		if (s) s->p=this;
	}
	void push() {
		if (rev) {
			swap(c[0], c[1]);
			if (c[0]) c[0]->rev^=1;
			if (c[1]) c[1]->rev^=1;
			rev=0;
		}
	}
	Node(int i) : id(i) {
		c[0]=0;c[1]=0;p=0;rev=0;
	}
};
struct LinkCut {
	void rot(Node* x) {
		Node* p=x->p;
		int d=x->dir();
		if (!p->isr()) {
			p->p->setc(x, p->dir());
		}
		else {
			x->p=p->p;
		}
		p->setc(x->c[!d], d);
		x->setc(p, !d);
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
			splay(x);
			x->c[1]=q;
			q=x;
		}
		return q;
	}
	void evert(Node* x) {
		x=expose(x);
		x->rev^=1;
		x->push();
	}
	void link(Node* x, Node* y) {
		evert(x);
		evert(y);
		splay(y);
		x->setc(y, 1);
	}
	void cut(Node* x, Node* y) {
		evert(x);
		expose(y);
		splay(x);
		x->c[1]=0;
		y->p=0;
	} 
	int rootid(Node* x) {
		expose(x);
		splay(x);
		while(x->c[0]) {
			x=x->c[0];
			x->push();
		}
		splay(x);
		return x->id;
	}
};