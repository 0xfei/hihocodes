#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void sort(int &a, int &b, int &c)
{
        int t;
        if (a < b) {
                t = a, a = b, b = t;
        }
        if (b < c) {
                t = b, b = c, c = t;
        }
        if (a < b) {
                t = a, a = b, b = t;
        }
}

bool check(int a, int b, int c, int x, int y, int z)
{
        sort(a, b, c);
        sort(x, y, z);
        if (x-z == a && x-y == b && y-z == c) return true;
        if (x-z == a && y-z == b && x-y == c) return true;
        if (y-z == a && x-z == b && x-y == c) return true;
        return false;
}

int main()
{
        string s;
        int a, b, c;
        int red=0, blue=0, yellow=0;
        int ans=0;
        cin >> a >> b >> c;
        cin >> s;
        for (int i=0; i<s.size(); ++i) {
                switch (s[i]) {
                        case 'R':
                                ++red;
                                break;
                        case 'B':
                                ++blue;
                                break;
                        case 'Y':
                                ++yellow;
                                break;
                }
                if (red + yellow + blue > ans) {
                        ans = red + yellow + blue;
                }
                if (check(a, b, c, red, yellow, blue))
                        red = yellow = blue = 0;
        }
        cout << ans << endl;
        return 0;
}