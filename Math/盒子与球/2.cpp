/*
不同的球 不同的盒子 盒子不能为空
5
3 2
7 3
5 8
6 3
246 135

6
1806
0
540
59392
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll Mod = 1e6 + 7;

inline static ll fact(ll x)
{
    ll ans = 1;
    for (ll i = 1; i <= x; i++) {
        ans *= i;
        ans %= Mod;
    }
    return ans;
}

ll p(ll n, ll m) { return fact(n) / fact(n - m) % Mod; }

ll c(ll n, ll m) { return p(n, m) / p(m, m) % Mod; }

static int s[2010][2010];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    static int T;
    cin >> T;
    s[1][1] = 1;
    for (int j = 1; j <= 2005; j++) {
        for (int i = 1; i <= 2005; i++) {
            if (i == 1 && j == 1)
                continue;
            s[i][j] = s[i - 1][j] * j + s[i - 1][j - 1];
            s[i][j] %= Mod;
        }
    }
    while (T--) {
        static ll n, r;
        cin >> n >> r;
        cout << s[n][r] * fact(r) % Mod << endl;
    }
}