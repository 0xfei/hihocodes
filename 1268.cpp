#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

string start = "04923578160";
vector<string> all;
queue<string> q;

string turn_right(const string &s)
{
        string t = s;
        t[1] = s[7], t[2] = s[4], t[3] = s[1];
        t[4] = s[8], t[5] = s[5], t[6] = s[2];
        //                        t[7] = s[3] fuck!!!!
        t[7] = s[9], t[8] = s[6], t[9] = s[3];
        return t;
}

string left_to_right(const string &s)
{
        string t = s;
        for (int i=1; i<=3; ++i) {
                t[i] = s[i+6];
        }
        for (int i=7; i<=9; ++i) {
                t[i] = s[i-6];
        }
        return t;
}

string up_to_down(const string &s)
{
        string t = s;
        t[1] = s[3], t[3] = s[1];
        t[4] = s[6], t[6] = s[4];
        t[7] = s[9], t[9] = s[7];
        return t;
}

void get_all_format()
{
        string w;
        string t = start;

        for (int i=0; i<4; ++i) {
                all.push_back(t); //1
                w = up_to_down(t);
                all.push_back(w);
                w = left_to_right(t);
                all.push_back(w);
                t = turn_right(t);
        }
        std::sort(all.begin(), all.end());
}

bool ok(const string &a, const string &b)
{
        for (int i=0; i<b.size(); ++i) {
                if (b[i] == '0') continue;
                if (b[i] != a[i]) return false;
        }
        return true;
}

int main()
{
        int a[3][3];
        int ans = 0;
        
        get_all_format();       

        string s, t, prev;
        s.push_back('0');
        for (int i=0; i<3; ++i) {
                for (int j=0; j<3; ++j) {
                        cin >> a[i][j];
                        s.push_back(a[i][j]+'0');
                }
        }
        s.push_back('0');
        for (int i=0; i<all.size(); ++i) {
                if (ok(all[i], s)) {
                        t = all[i];
                        if (t != prev) {
                                ++ans;
                        }
                        prev = t;
                }
        }
        if (ans > 1) {
                cout << "Too Many" << endl;
        } else {
                for (int i=1; i<=9; ++i) {
                        cout << t[i];
                        if (i%3 == 0) cout << endl;
                        else cout << ' ';
                }
        }
        return 0;
}
