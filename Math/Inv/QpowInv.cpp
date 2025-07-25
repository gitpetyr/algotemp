using ll = long long;

constexpr ll p = 1e9 + 7;

int qpow(ll a, ll b)
{
    int ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1) {
        if (b & 1)
            ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans;
}

ll inv(ll a)
{
    return qpow(a, p - 2);
}