#include <iostream>

using namespace std;

int main()
{
        int n;
        const int m = 19999997;
        long long a=0, b=1, c=1, d=1;
        long long x=1, y=0, z=0, q=1;
        long long t1, t2, t3, t4;
        cin >> n;
        while (n) {
                if (n%2) {
                        t1 = (a*x%m + c*y%m)%m;
                        t2 = (b*x%m + d*y%m)%m; 
                        t3 = (a*z%m + c*q%m)%m;
                        t4 = (b*z%m + d*q%m)%m;
                        x = t1, y = t2, z = t3, q = t4;
                }
                t1 = (a*a%m + b*c%m)%m;
                t2 = (a*b%m + b*d%m)%m;
                t3 = (a*c%m + c*d%m)%m;
                t4 = (b*c%m + d*d%m)%m;
                a = t1, b = t2, c = t3, d = t4;
                n /= 2;
        }
        cout << q << endl;
        return 0;
}
