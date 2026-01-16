#include <bits/stdc++.h>
using namespace std;
const int N = 2.3e7 + 10;

int p[N];

int main()
{
    string t;
    cin >> t;
    string s = "&#";
    for (int i = 0; i < (int)t.size(); i++) {
        s += t[i];
        s += '#';
    }
    s += '*';
    // cerr << s << endl;
    int r = 0, c = 0;
    int ans = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (i < r) {
            p[i] = min(p[c * 2 - i], r - i);
        } else {
            p[i] = 1;
        }
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            r = i + p[i];
            c = i;
        }
        ans = max(ans, p[i] - 1);
    }
    cout << ans << endl;
}