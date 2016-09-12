#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
        char a[5][5];
        int len = 0;
        vector<bool> v(26);
        string s;
        cin >> s;
        for (int i=0; i<s.size(); ++i) {
                if (s[i] == 'J') {
                        s[i] = 'I';
                }
                int ch = s[i] - 'A';
                if (v[ch] == true) continue;
                v[ch] = true;
                a[len/5][len%5] = ch+'A';
                ++len;
        }
        for (int i=0; i<26; ++i) {
                if (v[i] || i == 'J' - 'A') {
                        continue;
                }
                v[i] = true;
                a[len/5][len%5] = 'A' + i;
                ++len;
        }
        for (int i=0; i<5; ++i) {
                for (int j=0; j<5; ++j) {
                        cout << a[i][j];
                }
                cout << endl;
        }
        return 0;
}
