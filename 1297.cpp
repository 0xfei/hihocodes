#include <iostream>

using namespace std;

typedef long long L;

L gcd(L a, L b)
{
	if (b == 0) {
		return a;
	}
	return gcd(b, a%b);
}

L extend_gcd(L a, L b, L &x, L &y)
{
	if (a % b ==0) {
		x = 0;
		y = 1;
		return b;
	}
	L tx, ty;
	L c = extend_gcd(b, a%b, tx, ty);
	x = ty;
	y = tx - (a/b)*ty;
	return c;
}

L solve(L s1, L s2, L v1, L v2, L m)
{
	long long a = v1 - v2;
	long long b = m;
	long long c = s2 - s1;

	if (a < 0) {
		a += m;
	}

	long long d = gcd(a, b);

	if (c%d) {
		return -1;
	}

	a = a/d;
	b = b/d;
	c = c/d;

	L x, y;
	extend_gcd(a, b, x, y);
	x = (x*c) % b;
	while (x < 0) {
		x += b;
	}
	return x;
}

int main()
{
	long long s1, s2, v1, v2, m;
	cin >> s1 >> s2 >> v1 >> v2 >> m;
	cout << solve(s1, s2, v1, v2, m) << endl;
	return 0;
}