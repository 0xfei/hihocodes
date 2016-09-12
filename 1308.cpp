#include <iostream>
#include <utility>
#include <queue>
#include <map>
using namespace std;

int mov[][2] = {
	{-2, -1},
	{-2, 1},
	{-1, -2},
	{-1, 2},
	{1, -2},
	{1, 2},
	{2, -1},
	{2, 1}
};

inline bool valid(int x, int y)
{
	return (x >= 0 && x < 8 && y >=0 && y < 8);
}

inline bool ok(int status)
{
	return ((status & 077) == ((status >> 6) & 077)) && ((status & 077) == (status >> 12));
}

int find_ans(int start)
{
	queue<int> q;
	map<int, int> path;

	q.push(start);
	path.insert(make_pair(start, 0));

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		int a[] = {now >> 12, (now >> 6) & 077, now & 077};
		int d = path[now];

		if (ok(now)) {
			return d;
		}

		for (int i=0; i<3; ++i) {
			for (int j=0; j<8; ++j) {
				int orig = a[i];
				int x = (orig >> 3) + mov[j][0], y = (orig & 07) + mov[j][1];
				a[i] = x*8 + y;
				int next = (a[0] << 12) + (a[1] << 6) + a[2];
				if (valid(x, y) && path.find(next) == path.end()) {
					if (ok(next)) {
						return d + 1;
					}
					q.push(next);
					path.insert(make_pair(next, d+1));
				}
				a[i] = orig;
			}
		}
	}
	return 1;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int start = 0;
		for (int i=0; i<3; ++i) {
			char a;
			int b;
			cin >> a >> b;
			start = start*8 + a - 'A';
			start = start*8 + b - 1;
		}
		cout << find_ans(start) << endl;
	}
	
	return 0;
}
