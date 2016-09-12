#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Kmp_compare {
public:
    Kmp_compare(string a): pattern(a) { build(); }
    int find(string a);
private:
    void build();
    string pattern;
    vector<string::size_type> p;
};

void Kmp_compare::build()
{
    p.push_back(-1);
    string::size_type j = -1;
    for (string::size_type i = 1; i < pattern.size(); ++i) {
        while (j != -1 && pattern[j+1] != pattern[i]) j = p[j];
        if (pattern[j+1] == pattern[i]) ++j;
        p.push_back(j);
    }
}

int Kmp_compare::find(string a)
{
    int count = 0;
    string::size_type j = -1;
    for (string::size_type i = 0; i < a.size(); ++i) {
        while (j != -1 && pattern[j+1] != a[i]) j = p[j];
        if (pattern[j+1] == a[i]) ++j;
        if (j == pattern.size()-1) {
            ++count;
            j = p[j];
        }
    }
    return count;
}

int kmp_test()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        Kmp_compare kmp(s);
        cin >> s;
        cout << kmp.find(s) << endl;
    }
    return 0;
}
