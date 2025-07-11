#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;

namespace Dsu {

vector<int> fa, sizes;

void Dsu(int sz)
{
    fa.resize(sz + 1);
    sizes.resize(sz + 1);
    fill(fa.begin(), fa.end(), 0);
    fill(sizes.begin(), sizes.end(), 1);
    iota(fa.begin(), fa.end(), 0);
}

int find(int x)
{
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

void merge(int u, int v)
{
    u = find(u);
    v = find(v);
    if (sizes[u] < sizes[v])
        swap(u, v);
    fa[v] = u;
    sizes[u] += sizes[v];
    return;
}

};

int main()
{
    int n, m;
    cin >> n >> m;
    Dsu::Dsu(n+1);
    for (int i = 1; i <= m; i++) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            Dsu::merge(x, y);
        }
        if (opt == 2) {
            cout << (Dsu::find(x) == Dsu::find(y) ? "Y" : "N") << endl;
        }
    }
}