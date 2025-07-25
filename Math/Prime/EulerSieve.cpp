#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;

#define endl '\n'

constexpr int N = 1e8;
bitset<N> vis;
vector<int> Prime;
int n, m, x;

void init()
{
    vis[0] = vis[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i])
            Prime.push_back(i);
        for (auto j : Prime) {
            if (i * j > n)
                break;
            vis[i * j] = 1;
            if (i % j == 0)
                break;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin >> n;
    init();
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 0; j < Prime.size(); j++) {
            if (i % Prime[j] == 0) {
                cnt++;
            }
            if (cnt > 2)
                break;
        }
        if (cnt == 2) {
            ans++;
        }
    }
    cout << ans << endl;
}