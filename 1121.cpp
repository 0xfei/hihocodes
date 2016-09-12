#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

static vector<int> edge[10001];
static bool v[10001];
static bool color[10001];

bool colored(int s, int n)
{
	queue<int> q;
	
	if (s == 0) {
		return true;
	}

	memset(v, 0, sizeof(v));
	memset(color, 0, sizeof(color));

	q.push(s);
	v[s] = 1;
	color[s] = 1;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (size_t i=0; i<edge[now].size(); ++i) {
			int next = edge[now][i];
			if (!v[next]) {
				v[next] = true;
				color[next] = !color[now];
				q.push(next);
			} else {
				if (color[next] == color[now]) {
					return false;
				}
			}
		}
	}
	/*
	for (int i=1; i<=n; ++i) {
		if (!v[i]) {
			return false;
		}
	}
	*/
	return true;
}

int t1121()
{
	int T;
	cin >> T;
	while (T--) {
		int n, m, s = 0;
		cin >> n >> m;
		for (int i=1; i<=n; ++i) {
			edge[i].clear();
		}
		for (int i=0; i<m; ++i){
			int x, y;
			cin >> x >> y;
			edge[x].push_back(y);
			edge[y].push_back(x);
			s = x;
		}
		if (colored(s, n)) {
			cout << "Correct" << endl;
		} else {
			cout << "Wrong" << endl;
		}
	}
	return 0;
}
