#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int N = 2e6 + 10;

int n, m, a[N];
int ans[N];

struct node {
    int x, id, v;
};
vector<node> qrys[N];

int c[N];

inline int lowbit(int x)
{
    return x & (-x);
}

void add(int x, int k)
{
    for (; x < N; x += lowbit(x)) {
        c[x] += k;
    }
}

int qry(int x)
{
    int res = 0;
    for (; x >= 1; x -= lowbit(x)) {
        res += c[x];
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        qrys[l - 1].push_back({ x, i, -1 });
        qrys[r].push_back({ x, i, 1 });
    }
    for (int i = 1; i <= n; i++) {
        add(a[i], 1);
        for (int j = 0; j < (int)qrys[i].size(); j++) {
            int tmp = qrys[i][j].v * qry(qrys[i][j].x);
            ans[qrys[i][j].id] += tmp;
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}