#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int n;
int a[1001];
bool v[1001];

bool check(int k)
{
	vector<int> q;
	memset(v, 0, sizeof(v));
	for (int i=0; i<=k; ++i) {
		v[a[i]] = true;
	}
	for (int i=1; i<=n; ++i) {
		if (!v[i]) q.push_back(i);
	}
	for (int i = k+1; i<n; ++i) {
		if (q[i-k-1] != a[i]) {
			return false;
		}
	}
	return true;
}

int main()
{
	cin >> n;
	for (int i=0; i<n; ++i) {
		cin >> a[i];
	}
	int l = 0, r = n, mid = l+(n-l)/2;
	while (l < r) {
		if (check(mid)) {
			r = mid;
		} else {
			l = mid + 1;
		}
		mid = l+(r-l)/2;
	}
	for (int i=0; i<r; ++i) {
		cout << a[i] << ' ';
	}
	cout << a[r] << endl;
	return 0;
}
