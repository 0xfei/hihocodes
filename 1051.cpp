#include <iostream>
#include <vector>
using namespace std;

int v1051()
{
	int T;
	cin >> T;
	while (T--) {
		int n, m, ans = 0;
		cin >> n >> m;
		vector<int> day;
		for (int i=0; i<n; ++i) {
			int k;
			cin >> k;
			day.push_back(k);
		}
		day.push_back(101);
		if (m >= n) {
			cout << 100 << endl;
		} else {
			ans = day[m] - 1;
			for (int i=1; i<n-m+1; ++i) {
				int temp = day[i+m] - day[i-1] - 1;
				if (temp > ans) {
					ans = temp;
				}
			}
			cout << ans << endl;
		}
	}
	return 0;
}
