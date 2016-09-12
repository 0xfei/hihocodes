#include <iostream>
#include <algorithm>

using namespace std;

int n, w, h, p;
int a[1001];

bool check(int size)
{
	int k = 0, line = h/size, num = w/size;
	int left_line = line;
	for (int i = 0; i < n; ++i) {
		int t = (a[i]+num-1)/num;
		if (t >= line) {
			k += t/line;
			t = t%line;
		}
		if (t >= left_line) {
			++k;
			left_line = line - (t - left_line);
		} else {
			left_line -= t;
		}
	}
	return k <= p;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> p >> w >> h;
		for (int i=0; i<n; ++i) {
			cin >> a[i];
		}
		int r = min(w, h)+1, l = 1;
		while (l < r) {
			int mid = l+(r-l)/2;
			if (!check(mid)) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		cout << l-1 << endl;
	}
	return 0;
}
