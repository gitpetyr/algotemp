#include <bits/stdc++.h>
using namespace std;

using ll = long long;

namespace trie {

vector<map<int, int>> tr(2);
map<int, int> ised;
map<int, int> cnt;

void insert(string s)
{
    int now = 1;
    for (auto i : s) {
        if (!tr[now].count(i - 'a')) {
            tr.push_back(map<int, int>());
            int nxt = tr.size() - 1;
            tr[now][i - 'a'] = nxt;
        }
        now = tr[now][i - 'a'];
    }
    ised[now] = 1;
}

int lookup(string s)
{
    int now = 1;
    for (auto i : s) {
        // cerr << now << endl;
        if (!tr[now].count(i - 'a')) {
            return 0;
        }
        now = tr[now][i - 'a'];
        // cerr << i << " " << now << endl;
    }
    if (!ised[now]) {
        return 0;
    }
    cnt[now]++;
    if (cnt[now] > 1) {
        return 2;
    }
    return 1;
}

}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        trie::insert(s);
    }
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        int ok = trie::lookup(s);
        if (ok == 0) {
            cout << "WRONG" << endl;
        } else if (ok == 1) {
            cout << "OK" << endl;
        } else if (ok == 2) {
            cout << "REPEAT" << endl;
        }
    }
}