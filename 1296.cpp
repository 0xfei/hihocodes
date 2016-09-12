#include <iostream>

using namespace std;

int Josephus(int n, int k)
{
	if (n == 1) {
		return 0;
	}
	if (n < k) {
		int ret = 0;
		for (int i=2; i<=n; ++i) {
			ret = (ret + k)%i;
		}
		return ret;
	}
	int ret = Josephus(n - n/k, k);
	if (ret < n%k) {
		ret = ret - n%k + n;
	} else {
		ret = ret - n%k + (ret - n%k)/(k-1);
	}
	return ret;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		cout << Josephus(n, k) << endl;
	}
}