#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
// #define int long long
const int N = 2e6 + 10;

struct node {
    int cl, cr;
    ll sum, tag;
    node()
        : cl(0)
        , cr(0)
        , sum(0)
        , tag(0)
    {
    }
};

struct sgt {

    vector<node> tr;

private:
    int sz;

    int newnode()
    {
        tr.push_back(node());
        return (int)tr.size() - 1;
    }

    void mkson(int id)
    {
        if (!tr[id].cl) {
            tr[id].cl = newnode();
        }
        if (!tr[id].cr) {
            tr[id].cr = newnode();
        }
    }

    void push_up(int id)
    {
        int cl = tr[id].cl, cr = tr[id].cr;
        tr[id].sum = tr[cl].sum + tr[cr].sum;
        return;
    }

    void push_down(int id, int px, int py)
    {
        if (tr[id].tag == 0)
            return;
        int cl = tr[id].cl, cr = tr[id].cr, mid = (px + py) / 2;

        tr[cl].tag += tr[id].tag;
        tr[cl].sum += tr[id].tag * (mid - px + 1);

        tr[cr].tag += tr[id].tag;
        tr[cr].sum += tr[id].tag * (py - mid);

        tr[id].tag = 0;
        return;
    }

    void modify(int L, int R, ll val, int id, int px, int py)
    {
        if (L <= px && py <= R) {
            tr[id].sum += val * (py - px + 1);
            tr[id].tag += val;
            return;
        }
        mkson(id);
        int cl = tr[id].cl, cr = tr[id].cr, mid = (px + py) / 2;
        push_down(id, px, py);
        if (L <= mid)
            modify(L, R, val, cl, px, mid);
        if (R > mid)
            modify(L, R, val, cr, mid + 1, py);
        push_up(id);
        return;
    }

    ll query_sum(int L, int R, int id, int px, int py)
    {
        if (L > py || R < px) {
            return 0;
        }
        if (L <= px && py <= R) {
            return tr[id].sum;
        }
        mkson(id);
        int cl = tr[id].cl, cr = tr[id].cr, mid = (px + py) / 2;
        push_down(id, px, py);
        return query_sum(L, R, cl, px, mid) + query_sum(L, R, cr, mid + 1, py);
    }

public:
    sgt()
        : tr()
    {
        sz = 2e6 + 10;
        tr.reserve(4000005);
        tr.push_back(node());
        tr.push_back(node());
    }
    ll query_sum(int L, int R)
    {
        return query_sum(L, R, 1, 1, sz);
    }
    void modify(int L, int R, ll val)
    {
        modify(L, R, val, 1, 1, sz);
    }
};
sgt st;

int f[N], dep[N], top[N], siz[N], hson[N];
int dfn[N], rnk[N];
ll a[N];

vector<int> adj[N];
int idx = 0;

void dfs1(int u, int fa)
{
    f[u] = fa, dep[u] = dep[fa] + 1, siz[u] = 1;
    for (auto v : adj[u]) {
        if (v == fa)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[hson[u]])
            hson[u] = v;
    }
}

void dfs2(int u, int ftop)
{
    top[u] = ftop, dfn[u] = ++idx, rnk[idx] = u;
    if (hson[u])
        dfs2(hson[u], ftop);
    for (auto v : adj[u]) {
        if (v != hson[u] && v != f[u]) {
            dfs2(v, v);
        }
    }
}

void updatesum(int x, int y, ll val)
{
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] >= dep[fy]) {
            st.modify(dfn[fx], dfn[x], val);
            x = f[fx];
        } else {
            st.modify(dfn[fy], dfn[y], val);
            y = f[fy];
        }
        fx = top[x];
        fy = top[y];
    }
    if (dfn[x] <= dfn[y])
        st.modify(dfn[x], dfn[y], val);
    else
        st.modify(dfn[y], dfn[x], val);
}

ll querysum(int x, int y)
{
    ll ret = 0;
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] >= dep[fy])
            ret += st.query_sum(dfn[fx], dfn[x]), x = f[fx];
        else
            ret += st.query_sum(dfn[fy], dfn[y]), y = f[fy];
        fx = top[x];
        fy = top[y];
    }
    if (dfn[x] <= dfn[y])
        ret += st.query_sum(dfn[x], dfn[y]);
    else
        ret += st.query_sum(dfn[y], dfn[x]);
    return ret;
}

signed main()
{
    int n, m, r, p;
    cin >> n >> m >> r >> p;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(r, 0);
    dfs2(r, r);

    for (int i = 1; i <= n; i++) {
        st.modify(dfn[i], dfn[i], a[i] % p);
    }

    for (int i = 1; i <= m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y;
            ll z;
            cin >> x >> y >> z;
            updatesum(x, y, z % p);
        } else if (opt == 2) {
            int x, y;
            cin >> x >> y;
            cout << querysum(x, y) % p << endl;
        } else if (opt == 3) {
            int x;
            ll z;
            cin >> x >> z;
            st.modify(dfn[x], dfn[x] + siz[x] - 1, z % p);
        } else if (opt == 4) {
            int x;
            cin >> x;
            cout << st.query_sum(dfn[x], dfn[x] + siz[x] - 1) % p << endl;
        }
    }
}