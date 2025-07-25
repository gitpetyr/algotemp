/*
相同的球 不同的盒子 盒子允许为空
5
3 2
7 3
5 8
6 3
246 135

4
36
792
28
338053
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

constexpr ll N = 4010, Mod = 1e6 + 7;

ll c[N][N];

void init()
{
    for (ll i = 0; i < N; i++) {
        c[i][0] = 1;
    }
    for (ll i = 1; i < N; i++) {
        for (ll j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % Mod;
        }
    }
}

void solve()
{
    ll n, m;
    cin >> n >> m;
    cout << c[n + m - 1][m - 1] << endl;
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