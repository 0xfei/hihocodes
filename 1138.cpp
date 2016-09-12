#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


struct Point {
	Point(int a, int b, int c): x(a), y(b), i(c) {}
	int i;
	long long x;
	long long y;
};

bool xLess(const Point &a, const Point &b) {
	return a.x < b.x;
}
bool yLess(const Point &a, const Point &b) {
	return a.y < b.y;
}
bool iLess(const Point &a, const Point &b) {
	return a.i < b.i;
}
long long dist(const Point& p, const Point& q) { 
	return min(abs(q.x-p.x), abs(q.y-p.y)); 
}

const int MAX_POINT	= 100001;
vector<Point> points;

queue<int> q;
vector<int> edges[MAX_POINT];
bool v[MAX_POINT];
long long d[MAX_POINT];

long long findShortestPath(int s, int e)
{
	q.push(s);
	v[s] = true;
	d[s] = 0;
	
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		v[now] = false;

		for (size_t i = 0; i < edges[now].size(); ++i) {
			int next = edges[now][i];
			if (d[next] > d[now] + dist(points[now], points[next])) {
				d[next] = d[now] + dist(points[now], points[next]);
				if (!v[next]) {
					v[next] = true;
					q.push(next);
				}
			}
		}
	}
	return d[e];;
}

int slow_spfa()
{
	int n;
	cin >> n;
	for (int i=0; i<n; ++i) {
		long long x, y;
		d[i] = 2100000000;
		cin >> x >> y;
		points.push_back(Point(x, y, i));
	}

	if (n < 2) {
		cout << 0 << endl;
		return 0;
	}

	std::sort(points.begin(), points.end(), xLess);
	for (vector<Point>::iterator it = points.begin(); it != points.end()-1; ++it) {
		edges[it->i].push_back((it+1)->i);
		edges[(it+1)->i].push_back(it->i);
	}

	std::sort(points.begin(), points.end(), yLess);
	for (vector<Point>::iterator it = points.begin(); it != points.end()-1; ++it) {
		edges[it->i].push_back((it+1)->i);
		edges[(it+1)->i].push_back(it->i);
	}

	std::sort(points.begin(), points.end(), iLess);

	cout << findShortestPath(0, n-1) << endl;
	return 0;
}
