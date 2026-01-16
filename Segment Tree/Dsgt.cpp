#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define endl '\n'

template <typename T>
struct sgt
{
private:
    int sz;

    struct node
    {
        int cl, cr;
        T sum, tag;
        node()
            : cl(0), cr(0), sum(0), tag(-1)
        {
        }
    };

    vector<node> tr;

    int newnode()
    {
        tr.push_back(node());
        return (int)tr.size() - 1;
    }

    void mkson(int id)
    {
        if (!tr[id].cl)
        {
            tr[id].cl = newnode();
        }
        if (!tr[id].cr)
        {
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
        if (tr[id].tag == -1)
        {
            return;
        }
        int cl = tr[id].cl, cr = tr[id].cr, mid = (px + py) / 2;

        tr[cl].tag = tr[id].tag;
        tr[cl].sum = tr[id].tag * (mid - px + 1);

        tr[cr].tag = tr[id].tag;
        tr[cr].sum = tr[id].tag * (py - (mid + 1) + 1);

        tr[id].tag = -1;
        return;
    }

    void modify(int L, int R, T val, int id, int px, int py)
    {
        if (L <= px && py <= R)
        {
            tr[id].sum = val * (py - px + 1);
            tr[id].tag = val;
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

    T query_sum(int L, int R, int id, int px, int py)
    {
        if (L > py || R < px)
        {
            return 0;
        }
        if (L <= px && py <= R)
        {
            return tr[id].sum;
        }
        mkson(id);
        int cl = tr[id].cl, cr = tr[id].cr, mid = (px + py) / 2;
        push_down(id, px, py);
        return query_sum(L, R, cl, px, mid) + query_sum(L, R, cr, mid + 1, py);
    }

public:
    sgt() : tr()
    {
        sz = 1e9 + 10;
        tr.reserve(16651005);
        tr.push_back(node());
        tr.push_back(node());
    }
    T query_sum(int L, int R)
    {
        return query_sum(L, R, 1, 1, sz);
    }
    void modify(int L, int R, T val)
    {
        modify(L, R, val, 1, 1, sz);
    }
};

static sgt<int> t;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    t.modify(1, n, 1);
    while (q--)
    {
        // cout << t.query_sum(1, n) << endl;
        int l, r, opt;
        cin >> l >> r >> opt;
        if (opt == 1)
        {
            t.modify(l, r, 0);
        }
        else
        {
            t.modify(l, r, 1);
        }
        cout << t.query_sum(1, n) << endl;
    }
    return 0;
}
