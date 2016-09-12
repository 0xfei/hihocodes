#include <iostream>
#include <string>

using namespace std;

#define S1 "marshtomp"
#define S2 "fjxmlhx"
#define S1L 9

bool iequal(const string& s, string::size_type b, string::size_type e)
{
	int i = 0;
	while (b != e) {
		if ((s[b] == S1[i]) || ((s[b]-'A'+'a') == S1[i])) {
			++b;
			++i;
		} else {
			return false;
		}
	}
	return true;
}

void replace(const string &s)
{
	string t;
	if ( s.size() < S1L) {
		t = s;
	} else {
		for (string::size_type i=0; i<s.size();) {
			if (i < s.size()-S1L+1 && iequal(s, i, i+S1L)) {
				t += S2;
				i += S1L;
			} else {
				t += s[i];
				++i;
			}
		}
	}

	cout << t << endl;
}

int test1082()
{
	string s;
	while (getline(cin, s)) {
		replace(s);
	}
	return 0;
}

