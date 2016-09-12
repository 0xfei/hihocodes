#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Trie_tree {
public:
	Trie_tree(): numbers(0), value(0) {}
    Trie_tree(int n, int v): numbers(n), value(v) {}
    int add_string(const string& s);
    int get_prev_string_count(const string& s);
    void display_tree(int level);

private:
    bool is_subtree_exist(int index);
    Trie_tree& get_subtree(int index);
    inline int get_number() { return numbers; }
    inline int get_value() { return value; }
    inline void set_value(int v) { value = v; }
    inline void add_number(int t=1) { numbers += t; }

    int value;
    int numbers;
    vector<Trie_tree> subtree;
};

bool Trie_tree::is_subtree_exist(int index)
{
    vector<Trie_tree>::iterator it;
    for (it = subtree.begin(); it != subtree.end(); ++it) {
        if (it->get_value() == index) {
            return true;
        }
    }
    return false;
}

Trie_tree& Trie_tree::get_subtree(int index)
{
    if (!is_subtree_exist(index)) {
        this->subtree.push_back(Trie_tree(0, index));
    }

    vector<Trie_tree>::iterator it;
    for (it = subtree.begin(); it != subtree.end(); ++it) {
        if (it->get_value() == index) {
            return *it;
        }
    }

    return *this;
}

int Trie_tree::add_string(const string& s)
{
    if (!s.empty()) {
        string t(s.begin()+1, s.end());
        Trie_tree& node = this->get_subtree(s[0]);
        node.add_string(t);
        node.add_number();
    }
    return 0;
}

int Trie_tree::get_prev_string_count(const string& s)
{
    if (!s.empty()) {
        if (!this->is_subtree_exist(s[0])) {
            return 0;
        } else {
            return this->get_subtree(s[0]).get_prev_string_count(string(s.begin()+1, s.end()));
        }
    }
    return this->get_number();
}

void Trie_tree::display_tree(int level)
{
    if (!subtree.empty()) {
        cout << "level: " << level << endl;
        vector<Trie_tree>::iterator it;
        for (it = subtree.begin(); it != subtree.end(); ++it) {
            cout << it->get_value() << ' ';
        }
        cout << endl;
        for (it = subtree.begin(); it != subtree.end(); ++it) {
            it->display_tree(level+1);
        }
    }
}

void Trie_tree_test()
{
    Trie_tree root(0,0);
    int n;
    cin >> n;
    for (int i=0; i < n; i++) {
        string s;
        cin >> s;
        root.add_string(s);
    }
    cin >> n;
    for (int i=0; i < n; i++){
        string s;
        cin >> s;
        cout << root.get_prev_string_count(s) << endl;
    }
}
