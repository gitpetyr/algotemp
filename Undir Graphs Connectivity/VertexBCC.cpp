#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 5e5 + 10;

vector<int> G[N];
int dfn[N], low[N];
int dcnt = 0, bcnt = 0;
stack<pair<int, int>> stk;
vector<pair<int, int>> blo[N];

void dfs(int u, int fa)
{
    int son = 0;
    low[u] = dfn[u] = ++dcnt;
    for (auto v : G[u]) {
        if (!dfn[v]) {
            stk.push({ u, v });
            son++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) {
                bcnt++;
                pair<int, int> e;
                do {
                    e = stk.top();
                    stk.pop();
                    blo[bcnt].push_back(e);
                } while (!(e.first == u && e.second == v));
            }
        } else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
            if (dfn[u] > dfn[v]) {
                stk.push({ u, v });
            }
        }
    }
    if (fa == -1 && son == 0) {
        bcnt++;
        blo[bcnt].push_back({ u, u });
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i, -1);
        }
    }
    cout << bcnt << endl;
    for (int i = 1; i <= bcnt; i++) {
        set<int> nodes;
        for (auto j : blo[i]) {
            nodes.insert(j.first);
            nodes.insert(j.second);
        }
        cout << nodes.size() << " ";
        for (auto j : nodes) {
            cout << j << " ";
        }
        cout << endl;
    }
}