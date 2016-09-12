#include <iostream>
#include <string>

using namespace std;

long long a[100][100];

void floyd(long long n)
{
	for (long long k = 1; k<=n; ++k) {
		for (long long i=1; i<=n; ++i) {
			for (long long j=1; j<=n; ++j) {
				if (a[i][k] == 0 || a[k][j] == 0) {
					continue;
				} else {
					if (i != j && (a[i][j] == 0 || a[i][j] > a[i][k] + a[k][j]))
						a[i][j] = a[i][k] + a[k][j];
				}
			}
		}
	}
}

long long get_ans(long long n)
{
	long long ans = 0;
	for (long long i=1; i<n; ++i) {
		for (long long j=i+1; j<=n; ++j) {
			ans += a[i][j];
		}
	}
	return ans;
}
/*
long long main()
{
	long long n, m, x, y,l;
	cin >> n >> m;
	for (long long i=1; i<n; ++i) {
		cin >> x >> y >> l;
		a[x][y] = l;
		a[y][x] = l;
	}

	floyd(n);
	for (long long i=0; i<m; ++i) {
		string s;
		cin >> s;
		if (s == "QUERY") {
			cout << get_ans(n) << endl;
		} else {
			cin >> x >> y >> l;
			a[x][y] = l;
			a[y][x] = l;
			floyd(n);
		}
	}
	return 0;
}

*/
