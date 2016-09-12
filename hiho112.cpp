// 最大的误解——以为一定是个链，其实只是个普通的树就行！！！居然忘了这么重要的事情，实在是练习太少了。
// 全换成了longlong试试

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Edge{
	long long x;
	long long y;
	long long l;
};

vector<Edge> edges[100005];
vector<long long> connected[100005];

long long father[100005];
long long sons[100005];

bool v[100005];
long long ans = 0;

void swap(long long &a, long long &b)
{
	long long t = a;
	a = b;
	b = t;
}

long long build_tree(long long x)
{
	long long sum = 1;
	v[x] = true;
	for (size_t i = 0; i < connected[x].size(); ++i) {
		long long y = connected[x][i];
		if (v[y]) continue;
		v[y] = true;
		father[y] = x;
		sum += build_tree(y);
	}
	sons[x] = sum;
	return sum;
}

long long get_ans(long long x, long long n)
{
	long long result = 0;
	// 这里没有初始化 似乎出了大问题
	ans = 0;
	for (size_t i=0; i<edges[x].size(); ++i) {
		long long y = edges[x][i].y;
		if (father[y] != x) {
			continue;
		}
		long long l = edges[x][i].l;
		result += get_ans(y, n);
		result += (n - sons[y])*sons[y]*l;
	}
	return result;
}

void update_ans(long long x, long long y, long long l, long long n)
{
	if (father[y] != x) {
		swap(x, y);
	}
	for (size_t i=0; i<edges[x].size(); ++i) {
		if (edges[x][i].y == y) {
			long long step = l - edges[x][i].l;
			ans += step*sons[y]*(n-sons[y]);
			edges[x][i].l = l;
			break;
		}
	}
}

int main()
{
	long long n, m, x, y;
	long long l;
	cin >> n >> m;
	for (long long i=1; i<n; ++i) {
		Edge e = {0};
		cin >> x >> y >> l;
		connected[x].push_back(y);
		connected[y].push_back(x);
		e.x = x, e.y = y, e.l = l;
		edges[e.x].push_back(e);
		e.x = y, e.y = x, e.l = l;
		edges[e.x].push_back(e);
	}

	build_tree(1);
	ans = get_ans(1, n);

	for (long long i=0; i<m; ++i) {
		string s;
		cin >> s;
		if (s == "QUERY") {
			cout << ans << endl;
		} else {
			cin >> x >> y >> l;
			update_ans(x, y, l, n);
		}
	}
	return 0;
}
