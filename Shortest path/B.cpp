#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> e[50010];
vector<int> dis(100010, 1e9);
vector<int> inq(100010, 0);
vector<int> pre(100010, 0);

void solve()
{
    int n, m;
    auto spfa = [&](int s) {
        dis[s] = 0;
        queue<int> q;
        q.push(s);
        vector<int> cnt(50010, 0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (pair<int, int> t : e[u]) {
                if (dis[u] + t.second < dis[t.first]) {
                    dis[t.first] = dis[u] + t.second;
                    cnt[t.first] = cnt[u] + 1;
                    pre[t.first] = u;
                    if (!inq[t.first]) {
                        inq[t.first] = 1, q.push(t.first);
                    }
                }
                if (cnt[t.first] > n + 1) {
                    return 1;
                }
            }
        }
        return 0;
    };
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            e[a].push_back(make_pair(b, -c));
        } else if (opt == 2) {
            int a, b, c;
            cin >> a >> b >> c;
            e[b].push_back(make_pair(a, c));
        } else if (opt == 3) {
            int a, b;
            cin >> a >> b;
            e[a].push_back(make_pair(b, 0));
            e[b].push_back(make_pair(a, 0));
        }
    }
    for (int i = 1; i <= n; i++) {
        e[0].push_back(make_pair(i, 0));
    }
    int ok = spfa(0);
    if (ok) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    int T;
    //    cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
}
/*
a-b>=c
a-b<=c
a-b=0
*/