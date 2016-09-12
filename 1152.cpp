/*
	一定要好好审题！！！！
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

int fib[12] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};

bool check(int (&a)[27])
{
	int k = 0;
	for (int i=0; i<27; ++i) {
		if (a[i]) {
			++k;
		}
	}
	for (int i=0; i<12; ++i) {
		if (k == fib[i]) {
			return true;
		}
	}

	return false;
}

int main()
{
	int count[27];
	vector<string> hash;
	string s;
	cin >> s;
	for (string::iterator it = s.begin(); it != s.end(); ++it) {
		memset(count, 0, sizeof(count));
		for (string::iterator next=it; next != s.end(); ++next) {
			++count[*next-'a'];
			if (check(count)) {
				string s(it, next+1);
				bool has = false;
				for (size_t i=0; i<hash.size(); ++i) {
					if (hash[i] == s) {
						has = true;
						break;
					}
				}
				if (!has) {
					hash.push_back(s);
				}
			}
		}
	}
	std::sort(hash.begin(), hash.end());
	for (size_t i=0; i<hash.size(); ++i) {
		cout << hash[i] << endl;
	}
	return 0;
}
