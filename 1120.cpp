#include <iostream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

struct point{
	point(int a, int b): x(a), y(b) {}
	int x;
	int y;
};

typedef bitset<16> Word;

const int boom = 100;

int t, n, m;
int a[12][12];
vector<point> q;

inline int get_number(int x, int y)
{
	return ((a[x-1][y-1] == boom) + (a[x-1][y] == boom) + (a[x-1][y+1] == boom) +
		(a[x+1][y-1] == boom) + (a[x+1][y] == boom) + (a[x+1][y+1] == boom) +
		(a[x][y-1] == boom) + (a[x][y+1] == boom));
}

bool check()
{
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=m; ++j) {
			if (a[i][j] >= 0 && a[i][j] <= 8) {
				if (a[i][j] != get_number(i, j))
					return false;
			}
		}
	}
	return true;
}

int main()
{
	cin >> t;
	while (t--) {
		cin >> n >> m;
		q.clear();
		memset(a, 0, sizeof(a));
		for (int i=1; i<=n; ++i) {
			for (int j=1; j<=m; ++j) {
				cin >> a[i][j];
				if (a[i][j] == -1) {
					q.push_back(point(i, j));
				}
			}
		}
		Word ans1(0xFFFF), ans2(0xFFFF);
		int limit = (1 << q.size()) - 1;
		for (int i=0; i<=limit; ++i) {
			Word v(i);
			for (size_t j=0; j<q.size(); ++j) {
				int x = q[j].x, y = q[j].y;
				if (v.test(j)) {
					a[x][y] = boom;
				} else {
					a[x][y] = boom-1;
				}
			}
			if (check()) {
				ans1 &= v;
				ans2 &= (~v);
			}
		}
		ans1 &= limit, ans2 &= limit;
		cout << ans1.count() << ' ' << ans2.count() << endl;
	}
	return 0;
}
