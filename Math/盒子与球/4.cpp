/*
不同的球 相同的盒子 盒子不能为空
5
3 2
7 3
5 8
6 3
246 135

3
301
0
90
679296
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

constexpr ll N = 2010, Mod = 1e6 + 7;

ll dp[N][N];
ll fact[N];

void init()
{
    dp[0][0] = 1;
    for (ll i = 1; i <= N - 1; i++) {
        for (ll j = 1; j <= i; j++) {
            dp[i][j] = (j * dp[i - 1][j] + dp[i - 1][j - 1]) % Mod;
        }
    }
}

void solve()
{
    ll n, m;
    cin >> n >> m;
    cout << dp[n][m] << endl;
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