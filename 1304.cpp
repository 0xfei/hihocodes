#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define LIMIT 0.01

char opt[] = {'+', '-', '*', '/', '&', '|' };

double o(double a, double b, char op)
{
        switch (op) {
                case '+':
                        return a+b;
                case '-':
                        return a-b;
                case '*':
                        return a*b;
                case '/':
                        if (fabs(b) < LIMIT) return -1;
                        return a/b;
                case '&':
                        return b-a;
                case '|':
                        if (fabs(a) < LIMIT) return -1;
                        return b/a;
        }
        return 0;
}

bool calculate(double* a)
{
        for (int i=0; i<6; ++i) {
                for (int j=0; j<6; ++j) {
                        for (int k=0; k<6; ++k) {
                                double v1 = o(a[0], a[1], opt[i]), v2 = o(a[2], a[3], opt[j]);
                                if (v1 == -1 || v2 == -1) {
                                        goto next;
                                }
                                if (fabs(o(v1, v2, opt[k]) - 24) < LIMIT) {
                                        return true;
                                }
next:
                                v1 = o(a[0], a[1], opt[i]);
                                if (v1 == -1) {
                                        continue;
                                }
                                v2 = o(v1, a[2], opt[j]);
                                if (v2 == -1) {
                                        continue;
                                }
                                if (fabs(o(v2, a[3], opt[k])-24) < LIMIT) {
                                        return true;
                                }
                        }
                }
        }
        return false;
}

bool findans(double* a, double *b, int n, int used)
{
        if (n == 4) {
                if (calculate(b)) {
                        return true;
                } else {
                        return false;
                }
        }

        bool result = false;
        for (int i=0; i<4; ++i) {
                if (!(used & (1<<i))) {
                        b[n] = a[i];
                        result |= findans(a, b, n+1, used | (1<<i));
                        if (result) {
                                break;
                        }
                }
        }
        return result;
}

int main()
{
        int t;
        cin >> t;
        while (t--) {
                double a[4] = {0};
                double b[4] = {0};
                cin >> a[0] >> a[1] >> a[2] >> a[3];
                if (findans(a, b, 0, 0)) {
                        cout << "Yes" << endl;
                } else {
                        cout << "No" << endl;
                }
        }
        return 0;
}