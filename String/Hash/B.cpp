#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

constexpr ull base1 = 13331, mod1 = 998244353;
constexpr ull base2 = 998244353, mod2 = 1e9 + 7;

map<array<ull, 3>, ull> pcalc;

ull qpow(ull a, ull x, ull m)
{
    if (pcalc.count({ a, x, m })) {
        return pcalc[{ a, x, m }];
    }
    if (x == 0) {
        return pcalc[{ a, x, m }] = 1;
    }
    if (x == 1) {
        return pcalc[{ a, x, m }] = (a % m);
    }
    ull ans = qpow(a * a % m, x / 2, m);
    if (x % 2 == 1) {
        ans = ans * a % m;
    }
    return pcalc[{ a, x, m }] = ans;
}

class Hash {
public:
    vector<ull> hash1, hash2;
    Hash()
    {
        hash1.assign(0, 0);
        hash2.assign(0, 0);
    };
    Hash(string s)
    {
        hash1.assign(s.size() + 1, 0);
        hash2.assign(s.size() + 1, 0);
        for (int i = 0; i < (int)s.size(); i++) {
            hash1[i + 1] = ((hash1[i] * base1 + s[i]) % mod1 + mod1) % mod1;
            hash2[i + 1] = ((hash2[i] * base2 + s[i]) % mod2 + mod2) % mod2;
        }
    };
    pair<ull, ull> computhash(int l, int r)
    {
        return { (hash1[r] - (hash1[l - 1] * qpow(base1, r - l + 1, mod1)) % mod1 + mod1) % mod1, (hash2[r] - (hash2[l - 1] * qpow(base2, r - l + 1, mod2)) % mod2 + mod2) % mod2 };
    }
};

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (s.length() == 0) {
        return 0;
    }
    int len = (int)(s.length() * 2 + 1);
    vector<char> tmp1(len + 1);
    vector<int> cnt(len + 1);
    int idx = 0;
    for (int i = 0; i < len; i++) {
        tmp1[i] = (i & 1) == 0 ? '#' : s[idx++];
    }
    int x = -1;
    int y = -1;
    int ans = 0;
    for (int i = 0; i < len; i++) {
        cnt[i] = x > i ? min(x - i, cnt[2 * y - i]) : 1;
        while (i + cnt[i] < len && i - cnt[i] > -1) {
            if (tmp1[i + cnt[i]] == tmp1[i - cnt[i]]) {
                cnt[i]++;
            } else {
                break;
            }
        }
        if (i + cnt[i] > x) {
            x = i + cnt[i];
            y = i;
        }
        ans = max(ans, cnt[i]);
    }
    cout << ans - 1;
    return 0;
}
