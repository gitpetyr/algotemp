#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 1e5 + 10;

int a[N];

namespace trie {

vector<map<int, int>> tr(2);

void insert(int num)
{
    int now = 0;
    for (int i = 31; i >= 0; i--) {
        int tmp = (num >> i) & 1;
        if (!tr[now].count(tmp)) {
            tr.push_back(map<int, int>());
            int nxt = tr.size() - 1;
            tr[now][tmp] = nxt;
        }
        now = tr[now][tmp];
        // cerr << i << " " << now << endl;
    }
}

int find(ll num)
{
    int ans = 0, now = 0;
    for (int i = 31; i >= 0; i--) {
        int tmp = (num >> i) & 1;
        if (!tr[now].count(tmp ^ 1)) {
            now = tr[now][tmp];
        } else {
            now = tr[now][tmp ^ 1];
            ans = ans ^ (1 << i);
        }
    }
    return ans;
}

}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        trie::insert(a[i]);
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum = max(sum, trie::find(a[i]));
    }
    cout << sum << endl;
}