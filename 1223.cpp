// C��Ȼ������С������������ȷʵ��ʱ��ûʲô�ջ�ֻ�Ǹ�����ֵ����ƣ������ⲻ˵����
// ������Ҳ˵��ȷʵҪ���ǵĶ�һЩ��

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct edge {
	string s;
	double x;
};

edge a[51];

int main()
{
	int n;
	cin >> n;
	for (int i=0; i<n; ++i) {
		char ch;
		cin >> ch >> a[i].s >> a[i].x;
		a[i].x = a[i].x * 10;
	}

	int ans = 0;
	// �����Ǹ��� ע��߽�ss
	for (int point=-1; point<=10001; ++point) {
		int temp = 0;
		for (int i=0; i<n; ++i) {
			if (a[i].s == "=" && point == a[i].x) temp++;
			if (a[i].s == "<" && point < a[i].x) temp++;
			if (a[i].s == ">" && point > a[i].x) temp++;
			if (a[i].s == "<=" && point <= a[i].x) temp++;
			if (a[i].s == ">=" && point >= a[i].x) temp++;
		}
		if (temp > ans) {
			ans = temp;
		}
	}
	cout << ans << endl;
	return 0;
}
