#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	string s;
	while (getline(cin, s) && s.size()) {
		for (size_t i=0; i<s.size(); ++i){ 
			if (s[i] >= 'A' && s[i] <= 'Z') {
				s[i] = s[i] - 'A' + 'a';
			}
		}
		string::iterator it = s.begin();
		string::iterator ed = s.end();
		while (*it == ' ') {
			++it;
		}
		while (*(ed-1) == ' ') {
			--ed;
		}
		ostringstream sout;
		while (it != ed) {
			while (it != ed && *it >= 'a' && *it <= 'z') {
				sout << *it;
				++it;
			}
			if (it == ed) {
				break;
			}
			while (it != ed && *it == ' ') {
				++it;
			}
			if (it == ed) {
				break;
			}
			if (*it >= 'a' && *it <= 'z') {
				sout << ' ';
			} else {
				sout << *it;
				if (it != ed - 1) {
					sout << ' ';
				}
				++it;
			}
			while (it != ed && *it == ' ') {
				++it;
			}
		}
		string ans = sout.str();
		ans[0] = ans[0] - 'a' + 'A';
		for (size_t i=1; i<ans.size()-2; ++i) {
			if (ans[i] == '.' && ans[i+2] >= 'a' && ans[i+2] <= 'z') {
				ans[i+2] = ans[i+2] - 'a' + 'A';
			}
		}
		cout << ans << endl;
	}
	return 0;
}
