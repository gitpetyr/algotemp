#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define endl '\n'

const int N = 30000;

namespace sgt {
struct node {
    double sum, len, tag;
    double cl, cr;
} tr[N << 2];

void push_up(node& rt, node& a, node& b)
{
    if (rt.tag > 0) {
        rt.sum = rt.cr - rt.cl;
        if (rt.tag > 1) {
            rt.len = rt.sum;
        } else {
            rt.len = a.sum + b.sum;
        }
    } else {
        rt.sum = a.sum + b.sum;
        rt.len = a.len + b.len;
    }
}

void build(ll rt, ll cl, ll cr, double* num)
{
    tr[rt].cl = num[cl];
    tr[rt].cr = num[cr];
    tr[rt].tag = 0;
    if (cr - cl <= 1) {
        tr[rt].sum = 0;
        tr[rt].len = 0;
        return;
    }
    ll mid = (cl + cr) >> 1;
    build(rt << 1, cl, mid, num);
    build(rt << 1 | 1, mid, cr, num);
    push_up(tr[rt], tr[rt << 1], tr[rt << 1 | 1]);
}

void modify(double l, double r, ll x, ll rt)
{
    if (l >= tr[rt].cr || r <= tr[rt].cl)
        return;

    if (l <= tr[rt].cl && r >= tr[rt].cr) {
        tr[rt].tag += x;
        push_up(tr[rt], tr[rt << 1], tr[rt << 1 | 1]);
        return;
    }

    modify(l, r, x, rt << 1);
    modify(l, r, x, rt << 1 | 1);
    push_up(tr[rt], tr[rt << 1], tr[rt << 1 | 1]);
}
}

struct node {
    double x, bg, ed;
    ll v;
} seg[N];
double num[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int TESTCASE = 1;
    cin >> TESTCASE;
    while (TESTCASE--) {
        int n;
        cin >> n;
        if (!n)
            break;
        for (int i = 0; i < n; i++) {
            double x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            seg[i] = { x1, y1, y2, 1 };
            seg[i + n] = { x2, y1, y2, -1 };
            num[i + 1] = y1;
            num[i + n + 1] = y2;
        }
        sort(num + 1, num + (2 * n) + 1);
        sort(seg, seg + n * 2, [](node& a, node& b) {
            return a.x < b.x;
        });
        sgt::build(1, 1, 2 * n, num);
        double ans = 0;
        sgt::modify(seg[0].bg, seg[0].ed, seg[0].v, 1);
        for (int i = 1; i < 2 * n; i++) {
            ans += (seg[i].x - seg[i - 1].x) * sgt::tr[1].len;
            sgt::modify(seg[i].bg, seg[i].ed, seg[i].v, 1);
        }
        cout << fixed << setprecision(2) << (ans + 1e-9) << endl;
    }
    return 0;
}
