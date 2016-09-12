#include <iostream>
#include <string>

using namespace std;

bool isR(int year)
{
        return (((year%100)&&!(year%4))||!(year%400));
}

int getM(string& s)
{
        static string m[] = {
                "January", "February", "March", "April", 
                "May", "June", "July", "August", 
                "September", "October", "November" , "December"
        };
        for (int i=0; i<12; ++i) {
                if (s == m[i]) return i+1;
        }
        return 0;
}

bool lessT229(int m, int d)
{
        if (m < 2) return true;
        if (m > 2) return false;
        return d <= 29;
}

bool largerT229(int m, int d)
{
        if (m < 2) return false;
        if (m > 2) return true;
        return d >= 29;
}

int main()
{

        int n;
        cin >> n;
        for (int i=0; i<n; ++i) {
                string ts;
                char t;
                int m1, m2, d1, d2, y1, y2;
                cin >> ts >> d1 >> t >> y1;
                m1 = getM(ts);
                cin >> ts >> d2 >> t >> y2;
                m2 = getM(ts);
                int ans = 0;
                if (y1 == y2) {
                        // and m2.d2 >= 2.29 !!!!!!!
                        // ans = isR(y1) && lessT229(m1,d1;)
                        // !lessT229 != largerT229!!!!!!!!!
                        ans = isR(y1) && lessT229(m1,d1) && largerT229(m2,d2);
                } else {
                // I'm wrong here,should not be (y1 != y2) 
                //if (y1 != y2) {
                        ans = isR(y1) && (++y1) && lessT229(m1,d1);
                        ans += isR(y2) && (--y2) && largerT229(m2, d2);
                        while (!isR(y1)) ++y1;
                        while (!isR(y2)) --y2;
                        // there should be this, not simple /4!!!!!!!
                        // if (y1 <= y2) ans += (y2-y1)/4 - (y2-y1)/100 + (y2-y1)/400 + 1;
                        if (y1 <= y2) {
                                ans += (y2/4-y2/100+y2/400) - (y1/4-y1/100+y1/400) + 1;
                        }
                }
                // fuck the output
                // this is fucking fool
                //cout << ans << endl;
                cout << "Case #" << i+1 << ": " << ans << endl;
        }
        return 0;
}