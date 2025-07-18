#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

ll qpow(ll a, ll b, ll m)
{
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

namespace Hash {
using ull = unsigned long long;
static constexpr ull base = 131;
static constexpr ull mod1 = 1000001011, mod2 = 3145769;

int maxn = 0;

vector<ull> b1(1, 1ull), b2(1, 1ull);

void facinit(int n)
{
    for (int i = maxn + 1; i <= n; i++) {
        b1.push_back((b1[i - 1] * base) % mod1);
        b2.push_back((b2[i - 1] * base) % mod2);
    }
    maxn = n;
}

class hash_string {
public:
    vector<ull> hash1, hash2;
    int n;
    hash_string(const string& s)
    {
        init(s);
    }
    hash_string() : n(0) {}
    void init(const string& s)
    {
        n = s.size();
        if (n > maxn) {
            facinit(n);
        }
        hash1.resize(n + 1);
        hash2.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            hash1[i] = (hash1[i - 1] * base + s[i - 1]) % mod1;
            hash2[i] = (hash2[i - 1] * base + s[i - 1]) % mod2;
        }
    }
    pair<ull, ull> computhash(int l, int r)
    {
        return { (hash1[r] - (hash1[l - 1] * b1[r - l + 1]) % mod1 + mod1) % mod1, (hash2[r] - (hash2[l - 1] * b2[r - l + 1]) % mod2 + mod2) % mod2 };
    }
};
}

int main()
{
    string s, t;
    cin >> s >> t;
    Hash::hash_string s1(s), s2(t);
    int ans = 0;
    int len1 = s.size(), len2 = t.size();
    for (int i = len2; i <= len1; i++) {
        // cerr << s1.computhash(i - len2 + 1, i) << " " << s2.computhash(1, len2) << endl;
        if (s1.computhash(i - len2 + 1, i) == s2.computhash(1, len2)) {
            ans++;
        }
    }
    cout << ans << endl;
}
