#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

class BalancedTree {
public:
	BalancedTree(): weight(0), value(0), count(0), ltree(NULL), rtree(NULL) {}
	BalancedTree(int w, int v): weight(w), value(v), count(0), ltree(NULL), rtree(NULL) {}
	~BalancedTree();

	BalancedTree* father() { return ftree; }
	BalancedTree* left_tree() { return ltree; }
	BalancedTree* right_tree() { return rtree; }
	void set_left_tree(BalancedTree *tree) { ltree = tree; }
	void set_right_tree(BalancedTree *tree) { rtree = tree; }

	int get_weight() { return weight; }
	int get_value() { return value; }
	int get_count() { return count; }
	void inc_count() { ++count; }
	void set_weight(int w) { weight = w; }
	void set_value(int v) { value = v; }

	BalancedTree& rotate_left();
	BalancedTree& rotate_right();
	BalancedTree& insert(int v, int w);
	int query(int value);
private:
	BalancedTree *ftree;
	BalancedTree *ltree;
	BalancedTree *rtree;
	int weight;
	int value;
	int count;
};

BalancedTree::~BalancedTree()
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

BalancedTree& BalancedTree::rotate_left()
{
	return *this;
}

BalancedTree& BalancedTree::rotate_right()
{
	return *this;
}

BalancedTree& BalancedTree::insert(int v, int w)
{
	this->inc_count();
	if (this->get_value() == 0) {
		this->set_value(v);
		this->set_weight(w);
		return *this;
	}
	if (v < this->get_value()) {
		if (this->left_tree() == NULL) {
			this->set_left_tree(new BalancedTree);
		}
		this->left_tree()->insert(v, w);
		return *this->left_tree();
	} else {
		if (this->right_tree() == NULL) {
			this->set_right_tree(new BalancedTree);
		}
		this->right_tree()->insert(v, w);
		return *this->right_tree();
	}
	return *this;
}

int BalancedTree::query(int value)
{
	if (this->get_value() > value) {
		if (this->left_tree()) {
			return this->left_tree()->query(value);
		} else {
			// must retur a very big number
			return -1000000001;
		}
	} else {
		if (this->right_tree()) {
			return max(this->get_value(), this->right_tree()->query(value));
		} else {
			return this->get_value();
		}
	}
}

BalancedTree root;


int main()
{
	srand(static_cast<size_t>(time(NULL)));

	int n;
	cin >> n;	
	while (n--) {
		char k;
		int v, w;
		cin >> k >> v;
		if (k == 'I') {
			w = rand();
			root.insert(v, w);
		} else {
			cout << root.query(v) << endl;
		}
	}
	return 0;
}
