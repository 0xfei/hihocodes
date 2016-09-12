#include <iostream>
#include <cmath>

using namespace std;

struct v {
	v(): highest(0), high(0), left(0) {}
	int highest;
	int high;
	int left;
};

int a[100001], b[100001];
v f[100001], g[100001][101];
int n, m;

inline int cut(int left, int k, int &high)
{
	if (left < k) {
		high = static_cast<int>(ceil(static_cast<double>(left*high)/k));
		return 0;
	} else  {
		return left - k;
	}
}

int main()
{
	cin >> m >> n;
	f[0].left = m;
	int preva = 0;
	for (int i=1; i<=n; ++i) {
		int high;
		cin >> a[i] >> b[i];
		f[i] = f[i-1];
		high = b[i];
		f[i].left = cut(f[i].left, a[i], high);
		if (high > f[i].highest) {
			f[i].highest = high;
		}
		if (f[i].left == 0) {
			f[i].left = m;
			f[i].high += f[i].highest;
			f[i].highest = 0;
		}
	}

	for (int i=1; i<=m; ++i) {
		int high = b[n];
		if (a[n]+i-1 >= m) {
			high = static_cast<int>(ceil(static_cast<double>((m-i+1)*high)/a[n]));
		}
		g[n][i].highest = high;
		if (i == 1) {
			g[n][i].high = high;
			g[n][i].highest = 0;
		}
	}

	for (int i=n-1; i>0; --i) {
		for (int j=m; j>=1; --j) {
			int high = b[i];
			if (a[i] + j - 1>= m) {
				// fuck! j is not i !!!!!!
				high = static_cast<int>(ceil(static_cast<double>((m-j+1)*high)/a[i]));
				g[i][j].highest = high;
				g[i][j].high = g[i+1][1].high;
			} else {
				g[i][j] = g[i+1][a[i]+j];
				if (high > g[i][j].highest) {
					g[i][j].highest = high;
				}
			}
			if (j == 1) {
				g[i][j].high += g[i][j].highest;
				g[i][j].highest = 0;
			}
		}
	}

	int ans = f[n-1].high + f[n-1].highest;

	for (int i=1; i<n; ++i) {
		int highest = f[i-1].highest;
		int s = m-f[i-1].left+1;
		if (g[i+1][s].highest > highest) {
			highest = g[i+1][s].highest;
		}
		int h1 = g[i+1][s].high + f[i-1].high + highest;
		if (h1 < ans) {
			ans = h1;
		}
	}

	cout << ans << endl;
	return 0;
}
