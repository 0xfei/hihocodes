#include <iostream>

using namespace std;

#define n 9
#define N 10

inline int get_block(int x, int y) { return (x/3)*3 + y/3; }

bool find_ans(int x, int y, int (&a)[n][n], bool (&v)[3][N][N])
{
	if (x == n) {
		return true;
	}
	if (a[x][y] > 0) {
		if (y == n-1) {
			return find_ans(x + 1, 0, a, v);
		} else {
			return find_ans(x, y + 1, a, v);
		}
	}

	for (int i=1; i<=9; ++i) {
		if (!v[0][x][i] && !v[1][y][i] && !v[2][get_block(x,y)][i]) {
			a[x][y] = i;
			v[0][x][i] = true;
			v[1][y][i] = true;
			v[2][get_block(x,y)][i] = true;
			bool result = false;
			if (y == n-1) {
				result = find_ans(x + 1, 0, a, v);
			} else {
				result = find_ans(x, y + 1, a, v);
			}
			if (result) {
				return true;
			}
			a[x][y] = 0;
			v[0][x][i] = false;
			v[1][y][i] = false;
			v[2][get_block(x,y)][i] = false;
		}
	}
	return false;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int a[n][n] = {0}, k;
		bool v[3][N][N] = {0};
		for (int i=0; i<n; ++i) {
			for (int j=0; j<n; ++j) {
				cin >> k;
				v[0][i][k] = true;
				v[1][j][k] = true;
				v[2][get_block(i, j)][k] = true;
				a[i][j] = k;
			}
		}
		find_ans(0, 0, a, v);
		for (int i=0; i<n; ++i) {
			for (int j=0; j<n-1; ++j) {
				cout << a[i][j] << ' ';
			}
			cout << a[i][n-1] << endl;
		}
	}
	return 0;
}
