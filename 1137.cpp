#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

typedef struct _v {
	_v(): value(-100000), cost(0), used(0) {}
	int value;
	int cost;
	bitset<101> used;
} V;

typedef struct _p {
	int value;
	int price;
	int index;
} P;

typedef V Value[1002][102];
typedef P Person[102];

Value f, m;
Person a, b;

void packet(int n, int m, int x, Value &f, Person &a)
{
	f[0][0].value = 0;
	for (int now=1; now<=n; ++now) {
		for (int i=now; i>=1; --i){
			int temp;
			for (int j=m; j>=a[now].price; --j) {
				temp = f[j-a[now].price][i-1].value + a[now].value;
				if (temp >= 0 && temp > f[j][i].value) {
					f[j][i].value = temp;
					f[j][i].used = f[j-a[now].price][i-1].used;
					f[j][i].used.set(a[now].index);
				}
			}
		}
	}
}

int t1137()
{
	int N, X, Y, B;
	int mc = 0, fc = 0;
	
	cin >> N >> X >> Y >> B;
	for (int i=1; i<=N; ++i){
		char s;
		cin >> s;
		if (s == 'M') {
			++fc;
			cin >> a[fc].value >> a[fc].price;
			a[fc].index = i;
		} else {
			++mc;
			cin >> b[mc].value >> b[mc].price;
			b[mc].index = i;
		}
	}
	packet(fc, B, X, f, a);
	packet(mc, B, Y, m, b);

	int Ans = 0, Cost = 0;
	bitset<101> used;
	for (int i=0; i<=B; ++i) {
		for (int j=0; j<=B-i; ++j) {
			if (f[i][X].value + m[j][Y].value > Ans) {
				Ans = f[i][X].value + m[j][Y].value;
				Cost = i + j;
				used = f[i][X].used | m[j][Y].used;
			}
		}
	}
	cout << Ans << ' ' << Cost << endl;

	int e = 0;
	for (int i=N; i>0; --i) {
		if (used.test(i)) {
			e = i;
			break;
		}
	}
	for (int i=1; i<e; ++i) {
		if (used.test(i)) {
			cout << i << ' ';
		}
	}
	if (e) cout << e << endl;
	return 0;
}
