#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define endl '\n'

const int N = 2e6;

namespace sgt {
struct node {
    ll cnt, len;
} tr[N << 2];

ll n;
vector<ll> mp;

void push_up(node& rt, node& a, node& b, ll cl, ll cr)
{
    if (!rt.cnt)
        rt.len = a.len + b.len;
    else
        rt.len = mp[cr + 1] - mp[cl];
}

void modify(ll l, ll r, ll x, ll rt = 1, ll cl = 0, ll cr = n - 1)
{
    if (l > cr || r < cl)
        return;
    if (cl == cr) {
        tr[rt].cnt += x;
        tr[rt].len = (tr[rt].cnt != 0) * (mp[cr + 1] - mp[cl]);
        return;
    }

    ll mid = (cl + cr) >> 1;
    if (cl >= l && cr <= r) {
        tr[rt].cnt += x;
        push_up(tr[rt], tr[rt << 1], tr[rt << 1 | 1], cl, cr);
        return;
    }

    modify(l, r, x, rt << 1, cl, mid);
    modify(l, r, x, rt << 1 | 1, mid + 1, cr);
    push_up(tr[rt], tr[rt << 1], tr[rt << 1 | 1], cl, cr);
}
}

struct node {
    ll y, bg, ed, v;
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> a(1, 1e18);
    vector<node> sg;
    for (int i = 1; i <= n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a.push_back(x1);
        a.push_back(x2);
        sg.push_back({ y1, x1, x2, 1 });
        sg.push_back({ y2, x1, x2, -1 });
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    sort(sg.begin(), sg.end(), [&](node x, node y) {
        return x.y < y.y;
    });
    for (auto& u : sg) {
        u.bg = lower_bound(a.begin(), a.end(), u.bg) - a.begin();
        u.ed = lower_bound(a.begin(), a.end(), u.ed) - a.begin();
    }
    sgt::n = a.size();
    sgt::mp = move(a);
    ll lst = 0, ans = 0;
    for (auto& u : sg) {
        ans += (u.y - lst) * sgt::tr[1].len;
        sgt::modify(u.bg, u.ed - 1, u.v);
        lst = u.y;
    }
    cout << ans;
    return 0;
}