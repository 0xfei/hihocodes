#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int count(int n)
{
	int k = 0;
	while (n) {
		k += n&1;
		n/=2;
	}
	return k;
}

int main()
{
	int n, a;
	cin >> n;
	for (int i=0; i<24; ++i) {
		a = count(i);
		if (a <= n) {
			for (int j=0; j<60; ++j) {
				if (count(j) == n-a) {
					char s[6]={0};
					sprintf(s, "%02d:%02d", i, j);
					cout << s << endl;
				}
			}
		}
	}
	return 0;
}
