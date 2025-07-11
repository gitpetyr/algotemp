#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 2e5 + 10;

vector<int> G[N];

int dfn[N], low[N];
int dcnt = 0;

int cut[N], rson;

void dfs(int u, int fa)
{
    low[u] = dfn[u] = ++dcnt;
    int chd = 0;
    for (auto v : G[u]) {
        if (!dfn[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            chd++;
            if (low[v] >= dfn[u]) {
                if (fa == -1) {
                    rson++;
                } else {
                    cut[u] = true;
                }
            }
        } else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (chd > 1 && fa == -1) {
        cut[u] = 1;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i, -1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (cut[i]) {
            ans++;
        }
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++) {
        if (cut[i]) {
            ans++;
            cout << i << " ";
        }
    }
    cout << endl;
}