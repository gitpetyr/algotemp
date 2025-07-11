#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr i64 inf = 1e18 + 7;

void solve()
{
    i64 n, m;
    cin >> n >> m;
    // cerr<<n<<" "<<m<<"\n";
    vector<pair<i64, pair<i64, i64>>> e(m + 1);
    for (i64 i = 1; i <= m; i++) {
        i64 u, v, w;
        cin >> u >> v >> w;
        e[i] = { u, { v, w } };
    }
    vector<i64> dis(n + 1, 0), pre(n + 1);
    iota(pre.begin(), pre.end(), 0);
    for (i64 i = 1; i < n; i++) {
        for (i64 j = 1; j <= m; j++) {
            if (dis[e[j].first] + e[j].second.second < dis[e[j].second.first] && dis[e[j].first] != inf) {
                dis[e[j].second.first] = dis[e[j].first] + e[j].second.second;
                pre[e[j].second.first] = e[j].first;
            }
        }
    }
    i64 Flag = 0;
    vector<i64> ans;
    for (i64 j = 1; j <= m; j++) {
        if (dis[e[j].first] + e[j].second.second < dis[e[j].second.first] && dis[e[j].first] != inf) {
            Flag = 1;
            i64 x = e[j].second.first, y = e[j].second.first;
            int flag = 0;
            while (pre[y] != x) {
                ans.push_back(y);
                y = pre[y];
                if ((int)ans.size() > n) {
                    flag = 1;
                    break;
                }
            }
            ans.push_back(y);
            y = pre[y];
            // cerr<<flag<<"\n";
            if (flag) {
                ans.clear();
            } else {
                break;
            }
        }
    }
    cout << (Flag ? "YES\n" : "NO\n");
    if (Flag) {
        reverse(ans.begin(), ans.end());
        // cerr<<ans[0]<<" "<<ans.size()<<"\n";
        for (auto u : ans) {
            cout << u << " ";
        }
        cout << ans[0] << "\n";
    }

    // cerr<<"\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin>>T;
    while (T--)
        solve();
}
/*
13 9 18 5
*/