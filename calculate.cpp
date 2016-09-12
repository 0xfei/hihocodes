#include <iostream>
#include <cctype>
#include <string>
#include <deque>
#include <stack>

using namespace std;

#define LIMIT	0x80000000

int f(char fl)
{
	switch (fl) {
		case '+':
		case '-':
			return 0;
		case '*':
		case '/':
			return 1;
		case '(':
			return -1;
		default:
			return 2;
	}
}

int main()
{
	string s;
	deque<int> t;
	stack<int> q;
	stack<int> v;
	cin >> s;
	for (size_t i=0; i<s.size();) {
		if (isspace(s[i])) {
			++i;
			continue;
		}
		if (isdigit(s[i])) {
			int k = 0;
			while (i < s.size() && isdigit(s[i])) {
				k = k*10 + s[i] - '0';
				++i;
			}
			t.push_back(k);
			continue;
		}
		if (q.empty()) {
			q.push(s[i++]);
			continue;
		}

		if (s[i] == '(') {
			q.push(s[i++]);
			continue;
		}

		char tp;
		if (s[i] == ')') {
			while ((tp = q.top()) != '(') {
				t.push_back(tp | LIMIT);
				q.pop();
			}
			q.pop();
			++i;
			continue;
		}

		while (!q.empty() && f(q.top()) >= f(s[i])) {
			t.push_back(q.top() | LIMIT);
			q.pop();
		}
		q.push(s[i++]);
	}
	while (!q.empty()) {
		t.push_back(q.top() | LIMIT);
		q.pop();
	}

	for (size_t i=0; i<t.size(); ++i) {
		if (t[i] & LIMIT) {
			char c = static_cast<char>(t[i] & ~LIMIT);
			cout << c << ' ';
			
			int a, b;
			b = v.top();
			v.pop();
			if (v.empty()) {
				a = 0;
			} else {
				a = v.top();
				v.pop();
			}
			switch (c) {
				case '+':
					v.push(a+b);
					break;
				case '-':
					v.push(a-b);
					break;
				case '*':
					v.push(a*b);
					break;
				case '/':
					v.push(a/b);
					break;
				default:
					break;
			}
		} else {
			cout << t[i] << ' ';
			v.push(t[i]);
		}
	}
	cout << endl << v.top() << endl;
	return 0;
}
