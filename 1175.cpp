#include <iostream>
#include <vector>
#include <queue>

const int Limit = 142857;

using namespace std;

typedef struct _P{
	_P(): value(0), In(0) {}
	int value;
	int In;
	vector<int> Next;
} P;

P a[100002];
queue<int> q;

void topur()
{
	while (!q.empty()) {
		int now = q.front();
		int v = a[now].value;
		q.pop();
		for (size_t i=0; i<a[now].Next.size(); ++i) {
			int next = a[now].Next[i];
			a[next].value += v;
			a[next].value %= Limit;
			--a[next].In;
			if (a[next].In == 0) {
				q.push(next);
			}
		}
	}
}

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	for (int i=0; i<k; ++i) {
		int x;
		cin >> x;
		a[x].value = (a[x].value + 1) % Limit;
	}
	for (int i=0; i<m; ++i) {
		int x, y;
		cin >> x >> y;
		a[x].Next.push_back(y);
		++a[y].In;
	}
	for (int i=1; i<=n; ++i) {
		// 这个地方可能是个坑，不能只考虑有价值的，因为边和value实际上没关系
		// if (a[i].value && a[i].In == 0) {
		if (a[i].In == 0) {
			q.push(i);
		}
	}
	topur();
	int ans = 0;
	for (int i=1; i<=n; ++i) {
		ans = (ans + a[i].value) % Limit;
	}
	cout << ans << endl;
}
