#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

using ll = long long;
using T = ll;

namespace BIT {
    int n;
    vector<T> bit;

    void init(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    void update(int idx, T val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    T query(int idx) {
        T res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res += bit[idx];
        }
        return res;
    }
}

int main() {
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<T> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    BIT::init(n);
    for (int i = 1; i <= n; ++i) {
        T diff = a[i] - (i == 1 ? 0 : a[i - 1]);
        BIT::update(i, diff);
    }
    
    for (int i = 1; i <= m; ++i) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            T x;
            cin >> l >> r >> x;
            BIT::update(l, x);
            if (r + 1 <= n) {
                BIT::update(r + 1, -x);
            }
        } else {
            int x;
            cin >> x;
            cout << BIT::query(x) << endl;
        }
    }
    return 0;
}