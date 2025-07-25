/*
不同的球 不同的盒子 盒子允许为空
5
3 2
7 3
5 8
6 3
246 135

8
2187
32768
729
289511
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll Mod = 1e6 + 7;

ll qpow(ll a, ll b, ll m)
{
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        ll n, r;
        cin >> n >> r;
        cout << qpow(r, n, Mod)<<endl;
    }
}