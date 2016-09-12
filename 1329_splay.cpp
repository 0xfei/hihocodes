#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Splay {
public:
	Splay(): value(Splay::Min()), weight(0), count(0), allvalues(0), change(0), ltree(NULL), rtree(NULL), ftree(NULL){}
	Splay(int v, int w, Splay *f): value(v), weight(w), count(0), allvalues(0), change(0), ltree(NULL), rtree(NULL), ftree(f){}
	~Splay();

	Splay* insert(int v, long long w);
	Splay* findtree(int v);
	Splay* remove(int value);
	Splay* remove(int l, int r);
	void modify(int l, int r, long long w);

	int biggerThan(int v);
	int lessEqualThan(int v);
	int numberK(int k);
	int biggest();
	int smallest();
	long long getValue(int l, int r);
	long long getValues() { return allvalues; }

	static int Max() { return 2000000000;  }
	static int Min() { return -2000000000; }
	static int Zero() { return 0; }
private:
	void marking(long long delta);
	void send();
	void update();
	void treap_act();
	void splay_act(Splay* Father);
	Splay* rotate_left();
	Splay* rotate_right();

	Splay *ftree;
	Splay *ltree;
	Splay *rtree;
	long long change;
	long long allvalues;
	long long weight;
	long long count;
	int value;
};

Splay *root = new Splay;

Splay::~Splay()
{
	if (ltree) {
		delete ltree;
		ltree = NULL;
	}
	if (rtree) {
		delete rtree;
		rtree = NULL;
	}
}

void Splay::marking(long long delta)
{
	this->allvalues += this->count*delta;
	this->change += delta;
	this->weight += delta;
}

void Splay::send()
{
	if (ltree && ltree->value != Min()) {
		ltree->marking(this->change);
	}
	if (rtree && rtree->value != Min()) {
		rtree->marking(this->change);
	}
	this->change = 0;
	this->update();
}

void Splay::update()
{
	this->allvalues = this->weight;
	this->count = 1;
	if (ltree && ltree->value != Min()) {
		this->allvalues += ltree->allvalues;
		this->count += ltree->count;
	}
	if (rtree && rtree->value != Min()) {
		this->allvalues += rtree->allvalues;
		this->count += rtree->count;
	}
}

Splay* Splay::rotate_left()
{
	Splay *r = this->rtree;

	this->send();
	r->send();

	r->ftree = this->ftree;

	if (this->ftree)
	{
		if (this->ftree->ltree == this) {
			this->ftree->ltree = r;
		} else {
			this->ftree->rtree = r;
		}
	} else {
		root = r;
	}

	this->rtree = r->ltree;
	r->ltree->ftree = this;

	this->ftree = r;
	r->ltree = this;

	this->update();
	r->update();

	return r;
}

Splay* Splay::rotate_right()
{
	Splay *l = this->ltree;

	this->send();
	l->send();

	l->ftree = this->ftree;

	if (this->ftree)
	{
		if (this->ftree->ltree == this) {
			this->ftree->ltree = l;
		} else {
			this->ftree->rtree = l;
		}
	} else {
		root = l;
	}

	this->ltree = l->rtree;
	l->rtree->ftree = this;

	this->ftree = l;
	l->rtree = this;

	this->update();
	l->update();

	return l;
}

void Splay::splay_act(Splay* Father)
{
	while (this->ftree != Father) {
		Splay* f = this->ftree;
		if (f->ftree == Father) {
			if (f->ltree == this) {
				f->rotate_right();
			} else {
				f->rotate_left();
			}
		} else {
			Splay* ff = f->ftree;
			if (ff->ltree == f) {
				if (f->ltree == this) {
					ff->rotate_right();
					f->rotate_right();
				} else {
					this->ftree->rotate_left();
					this->ftree->rotate_right();
				}
			} else {
				if (f->rtree == this) {
					ff->rotate_left();
					f->rotate_left();
				} else {
					this->ftree->rotate_right();
					this->ftree->rotate_left();
				}
			}
		}
	}
	return;
}

void Splay::treap_act()
{
	Splay *node = this;
	while (node->ftree) {
		Splay *father = node->ftree;
		if (node->weight < father->weight) {
			if (node == father->ltree) {
				node = father->rotate_right();
			} else {
				node = father->rotate_left();
			}
		} else {
			break;
		}
	}
}

Splay* Splay::insert(int v, long long w)
{
	++this->count;
	this->allvalues += w;
	this->send();
	if (value == Splay::Min()) {
		value = v;
		weight = w;
		ltree = new Splay(Splay::Min(), 0, this);
		rtree = new Splay(Splay::Min(), 0, this);
		splay_act(NULL);
		return this;
	}
	if (v < value) {
		return ltree->insert(v, w);
	} else {
		return rtree->insert(v, w);
	}
}

Splay* Splay::remove(int v)
{
	root->remove(v, v);
	return this;
}

Splay* Splay::remove(int l, int r)
{
	if (!root->findtree(l)) {
		root->insert(l, 0);
	}
	if (!root->findtree(r)) {
		root->insert(r, 0);
	}
	Splay* prev = root->findtree(root->lessEqualThan(l-1));
	Splay* next = root->findtree(root->biggerThan(r));
	prev->splay_act(NULL);
	next->splay_act(prev);
	if (next->ltree && next->ltree->value != Min()) {
		next->count -= next->ltree->count;
		prev->count -= next->ltree->count;
		delete next->ltree;
		next->ltree = new Splay(Min(), 0, next);
	}
	return this;
}

void Splay::modify(int l, int r, long long w)
{
	Splay* prev = root->findtree(root->lessEqualThan(l-1));
	Splay* next = root->findtree(root->biggerThan(r));
	prev->splay_act(NULL);
	next->splay_act(prev);
	if (next->ltree && next->ltree->value != Min()) {
		next->ltree->marking(w);
	}
}

long long Splay::getValue(int l, int r)
{
	Splay* prev = root->findtree(root->lessEqualThan(l-1));
	Splay* next = root->findtree(root->biggerThan(r));
	prev->splay_act(NULL);
	next->splay_act(prev);
	return next->ltree->allvalues;
}

Splay* Splay::findtree(int v)
{
	if (this->value == v) {
		return this;
	}
	if (this->value == Min()) {
		return NULL;
	}
	if (this->value < v) {
		return rtree->findtree(v);
	} else {
		return ltree->findtree(v);
	}
	return NULL;
}

int Splay::lessEqualThan(int value)
{
	if (this->value > value) {
		if (ltree) {
			return ltree->lessEqualThan(value);
		} else {
			return Splay::Min();
		}
	} else {
		if (rtree) {
			return max(this->value, rtree->lessEqualThan(value));
		} else {
			return this->value;
		}
	}
}

int Splay::biggerThan(int value)
{
	int v = this->value;
	if (this->value <= value) {
		if (rtree) {
			v = rtree->biggerThan(value);
		} else {
			v = Splay::Min();
		}
	} else {
		if (ltree) {
			v = ltree->biggerThan(value);
			if (v == Splay::Min()) {
				v = this->value;
			}
		}
	}
	if (v == value) {
		v = Splay::Min();
	}
	return v;
}

int Splay::numberK(int k)
{
	if (k > this->count) {
		return Min();
	}
	if (ltree->count == k-1) {
		return value;
	}
	if (ltree->count >= k) {
		return ltree->numberK(k);
	} else {
		return rtree->numberK(k - (int)ltree->count - 1);
	}
}

int Splay::biggest()
{
	if (rtree->value == Min()) {
		return this->value;
	} else {
		return this->rtree->biggest();
	}
}

int Splay::smallest()
{
	if (ltree->value == Min()) {
		return this->value;
	} else {
		return this->ltree->smallest();
	}
}

int main()
{
	int n;
	cin >> n;

	root->insert(Splay::Min()+1, 0);
	root->insert(Splay::Max()-1, 0);

	while (n--) {
		char k;
		int a, b, v;
		cin >> k;
		if (k == 'I') {
			cin >> a >> v;
			root->insert(a, v);
		} else if (k == 'Q') {
			cin >> a >> b;
			cout << root->getValue(a, b) << endl;
		} else if (k == 'D') {
			cin >> a >> b;
			root->remove(a, b);
		} else if (k == 'M') {
			cin >> a >> b >> v;
			root->modify(a, b, v);
		}
	}

	delete root;
	return 0;
}
