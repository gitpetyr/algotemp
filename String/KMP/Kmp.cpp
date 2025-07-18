#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 10;

int nxt[N];

int ans = 0;

void getnext(string& s)
{
    int m = s.size();
    nxt[0] = 0;
    int i = 1, len = 0;
    while (i < m) {
        if (s[len] == s[i]) {
            nxt[i] = ++len;
            i++;
        } else {
            if (len == 0) {
                nxt[i] = 0;
                i++;
            } else {
                len = nxt[len - 1];
            }
        }
    }
}

void kmp(string& A, string& B)
{
    getnext(B);
    int i = 0, j = 0;
    int n = A.size();
    int m = B.size();
    while (i < n) {
        if (A[i] == B[j]) {
            i++;
            j++;
        } else {
            if (j > 0) {
                j = nxt[j - 1];
            } else {
                i++;
            }
        }
        if (j == m) {
            ans++;
            cout << i - m + 1 << endl;
            j = nxt[j - 1];
        }
    }
}

int main()
{
    string s, t;
    cin >> s >> t;
    kmp(s, t);
    for (int i = 1; i <= (int)t.size(); i++) {
        cout << nxt[i - 1] << " ";
    }
}