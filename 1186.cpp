#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> a;
vector<int> b;

void parse(int x, vector<int> &a)
{
	for (int i=1; i <=x; ++i) {
		if (i*i > x) break;
		if (x % i == 0) {
			a.push_back(i);
			if (x/i != i) {
				a.push_back(x/i);
			}
		}
	}
	std::sort(a.begin(), a.end());
}

int main()
{
	int n, m;
	cin >> n >> m;
	parse(n, a);
	parse(m, b);
	for (vector<int>::iterator i=a.begin(); i != a.end(); ++i) {
		for (vector<int>::iterator j=b.begin(); j != b.end(); ++j) {
			cout << *i << ' ' << *j << endl;
		}
	}
	return 0;
}
