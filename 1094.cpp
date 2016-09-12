#include <iostream>
#include <string>
using namespace std;

int n, m;
char a[201][201];
char b[4][4];

bool check(int x, int y)
{
        if (a[x][y]==b[0][0] && a[x][y+1]==b[0][1] && a[x][y+2]==b[0][2] &&
                a[x+1][y]==b[1][0] && a[x+1][y+1]==b[1][1] && a[x+1][y+2]==b[1][2] &&
                a[x+2][y]==b[2][0] && a[x+2][y+1]==b[2][1] && a[x+2][y+2]==b[2][2])
                return true;

        if (a[x][y]==b[2][0] && a[x][y+1]==b[1][0] && a[x][y+2]==b[0][0] &&
                a[x+1][y]==b[2][1] && a[x+1][y+1]==b[1][1] && a[x+1][y+2]==b[0][1] &&
                a[x+2][y]==b[2][2] && a[x+2][y+1]==b[1][2] && a[x+2][y+2]==b[0][2])
                return true;

        if (a[x][y]==b[2][2] && a[x][y+1]==b[2][1] && a[x][y+2]==b[2][0] &&
                a[x+1][y]==b[1][2] && a[x+1][y+1]==b[1][1] && a[x+1][y+2]==b[1][0] &&
                a[x+2][y]==b[0][2] && a[x+2][y+1]==b[0][1] && a[x+2][y+2]==b[0][0])
                return true;

        if (a[x][y]==b[0][2] && a[x][y+1]==b[1][2] && a[x][y+2]==b[2][2] &&
                a[x+1][y]==b[0][1] && a[x+1][y+1]==b[1][1] && a[x+1][y+2]==b[2][1] &&
                a[x+2][y]==b[0][0] && a[x+2][y+1]==b[1][0] && a[x+2][y+2]==b[2][0])
                return true;

        return false;
}
int main()
{
        cin >> n >> m;
        for (int i=0; i<n; ++i) {
                for (int j=0; j<m; ++j) {
                        cin >> a[i][j];
                }
        }
        for (int i=0; i<3; ++i) {
                for (int j=0; j<3; ++j) {
                        cin >> b[i][j];
                }
        }
        for (int i=0; i<n-2; ++i) {
                for (int j=0; j<m-2; ++j) {
                        if (check(i, j)) {
                                cout << i+2 << ' ' << j+2 << endl;
                                //return 0;
                        }
                }
        }
        return 0;
}
