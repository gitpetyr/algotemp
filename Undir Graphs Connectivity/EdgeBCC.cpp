#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 5;

int n, m, dcnt;
int dfn[N], low[N];

struct node {
    int v, id;
};

vector<node> G[N];
vector<vector<int>> ans;
stack<int> st;

void dfs(int u, int id)
{
    low[u] = dfn[u] = ++dcnt;
    st.push(u);
    for (auto e : G[u]) {
        if (e.id == (id ^ 1)) {
            continue;
        }
        if (!dfn[e.v]) {
            dfs(e.v, e.id);
            low[u] = min(low[u], low[e.v]);
        } else {
            low[u] = min(low[u], dfn[e.v]);
        }
    }
    if (dfn[u] == low[u]) {
        vector<int> nds;
        nds.push_back(u);
        while (st.top() != u) {
            nds.push_back(st.top());
            st.pop();
        }
        st.pop();
        ans.push_back(nds);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back({ v, i * 2 });
        G[v].push_back({ u, i * 2 + 1 });
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i, 0);
        }
    }
    cout << ans.size() << endl;
    for (auto nds : ans) {
        cout << nds.size() << ' ';
        for (auto v : nds) {
            cout << v << ' ';
        }
        cout << endl;
    }
    return 0;
}