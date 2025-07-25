/*
相同的球 相同的盒子 盒子不能为空
5
3 2
7 3
5 8
6 3
246 135

1
4
0
3
898450
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

constexpr ll N = 4010, Mod = 1e6 + 7;

ll c[N][N];

void init()
{
    for (ll i = 1; i < N; i++) {
        c[i][1] = 1;
    }
    for (ll i = 0; i < N; i++) {
        c[0][i] = 1;
    }
    for (ll i = 1; i < N; i++) {
        for (ll j = 2; j < N; j++) {
            if (i >= j) {
                c[i][j] = (c[i - j][j] + c[i][j - 1]) % Mod;
            } else {
                c[i][j] = c[i][j - 1] % Mod;
            }
        }
    }
}

void solve()
{
    ll n, m;
    cin >> n >> m;
    if (n < m) {
        cout << 0 << endl;
        return;
    }
    cout << c[n - m][m] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    ll T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}