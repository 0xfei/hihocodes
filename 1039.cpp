/*
	�����̸���һ�����صĽ�ѵ����Ҫ�뵱Ȼ����Ҫ��̫�࣡�Ҿ�Ȼ�������Ϊһ��Ҫ��˳����������š�
	��ʵ���Ǳ���ͷ���������ʵ��̫���ˡ�
	AAABA -> ABAABA
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int find(string& s)
{
	int ans = 0;
	string t1(s), t2;
	string::size_type i = 0, len = s.size();

	if (len < 2) {
		return 0;
	}
	for (i = 1; i < len-1; ++i) {
		if (s[i] == s[i-1] || s[i] == s[i+1]) {
			t1[i] = '.';
			++ans;
		}
	}
	if (s[0] == s[1]) {
		t1[0] = '.';
		++ans;
	}
	if (s[len-1] == s[len-2]) {
		t1[len-1] = '.';
		++ans;
	}

	for (i = 0; i < len; ++i) {
		if (t1[i] != '.') {
			t2 += t1[i];
		}
	}

	if (t2 == s) {
		return 0;
	} else {
		return ans + find(t2);
	}
}

int simple_right()
{
	int n;
	cin >> n;

	for (int i=0; i<n; ++i){
		int ans = 0;
		string s;
		cin >> s;
		for (string::size_type i=0; i < s.size(); ++i){
			string t;
			int temp;
			t = s;
			t.insert(i, "A");
			if ((temp = find(t)) > ans) {
				ans = temp;
			}
			t = s;
			t.insert(i, "B");
			if ((temp = find(t)) > ans) {
				ans = temp;
			}
			t = s;
			t.insert(i, "C");
			if ((temp = find(t)) > ans) {
				ans = temp;
			}
		}
		cout << ans << endl;
	}

	return 0;
}
