#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

template <typename T>
struct sgt {
private:
    struct Node {
        int l, r;
        T val;
    };

    vector<Node> tr;
    vector<int> roots;
    int n;

    int newnode()
    {
        tr.push_back({});
        return (int)tr.size() - 1;
    }

    int newnode(int cp)
    {
        tr.push_back(tr[cp]);
        return (int)tr.size() - 1;
    }

    int build(int l, int r, const vector<T>& a)
    {
        int id = newnode();
        if (l == r) {
            tr[id].val = a[l];
            return id;
        }
        int mid = l + (r - l) / 2;
        tr[id].l = build(l, mid, a);
        tr[id].r = build(mid + 1, r, a);
        return id;
    }

    int modify(int prev, int l, int r, int pos, T val)
    {
        int id = newnode(prev);
        if (l == r) {
            tr[id].val = val;
            return id;
        }
        int mid = l + (r - l) / 2;
        if (pos <= mid)
            tr[id].l = modify(tr[prev].l, l, mid, pos, val);
        else
            tr[id].r = modify(tr[prev].r, mid + 1, r, pos, val);
        return id;
    }

    T query(int id, int l, int r, int pos)
    {
        if (l == r) {
            return tr[id].val;
        }
        int mid = l + (r - l) / 2;
        if (pos <= mid)
            return query(tr[id].l, l, mid, pos);
        else
            return query(tr[id].r, mid + 1, r, pos);
    }

public:
    sgt(int _sz, int opt)
        : n(_sz)
    {

        tr.reserve(_sz * 2 + opt * 25);
        roots.reserve(opt + 1);
        tr.push_back({ 0, 0, 0 });
    }

    void init(const vector<T>& arr) // v0
    {
        roots.push_back(build(1, n, arr));
    }

    void update(int bver, int pos, T val)
    {
        int nrt = modify(roots[bver], 1, n, pos, val);
        roots.push_back(nrt);
    }

    T query_and_copy(int bver, int pos)
    {

        roots.push_back(roots[bver]);
        return query(roots[bver], 1, n, pos);
    }

    T query_only(int ver, int pos)
    {
        return query(roots[ver], 1, n, pos);
    }
};

int main()
{

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sgt<int> pa(n, m);
    pa.init(a);

    for (int i = 1; i <= m; i++) {
        int v, opt, loc;
        cin >> v >> opt >> loc;

        if (opt == 1) {
            int val;
            cin >> val;

            pa.update(v, loc, val);
        } else {

            cout << pa.query_and_copy(v, loc) << endl;
        }
    }

    return 0;
}
