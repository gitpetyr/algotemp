#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 3e4 + 10;

vector<int> G[N];

int dfn[N], low[N];
int dcnt = 0;
vector<pair<int, int>> bri;
void dfs1(int u, int fa)
{
    low[u] = dfn[u] = ++dcnt;
    for (auto v : G[u]) {
        if (!dfn[v]) {
            dfs1(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                bri.push_back({ u, v });
            }
        } else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main()
{
    int n, m;
    while (cin >> n >> m) {
        if(n==0&&m==0){
            break;
        }
        dcnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        bri.clear();
        for (int i = 1; i <= n; i++) {
            G[i].clear();
        }
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs1(1, 1);
        cout << bri.size() << endl;
    }
}