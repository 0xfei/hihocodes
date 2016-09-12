#include <iostream>
using namespace std;

typedef int Array[101];
Array v;
Array w;

int q, n;

int main()
{
        cin >> q;
        while (q--) {
                cin >> n;
                int ans = 0;
                for (int i=0; i<n; ++i) {
                        double k;
                        cin >> k >> v[i];
                        w[i] = k*10;
                }
                for (int i=0; i<n; ++i) {
                        int vv = v[i];
                        int ww = w[i];
                        if (ww % 50 == 0 && vv > ans) {
                                ans = vv;
                        }
                        for (int j=i+1; j<n; ++j) {
                                vv = v[i] + v[j];
                                ww = w[i] + w[j];
                                if (ww % 50 == 0 && vv > ans) {
                                        ans = vv;
                                }
                                for (int k=j+1; k<n; ++k) {
                                        vv = v[i] + v[j] + v[k];
                                        ww = w[i] + w[j] + w[k];
                                        if (ww%50 == 0 && vv > ans) {
                                                ans = vv;
                                        }
                                }
                        }
                }
                cout << ans << endl;
        }
        return 0;
}
