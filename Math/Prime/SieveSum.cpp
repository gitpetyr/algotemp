#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;

#define endl '\n'

constexpr int N = 1e6 + 5;

vector<int> pri;
bool not_prime[N];
int g[N], f[N];

void pre(int n)
{
    g[1] = f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
            pri.push_back(i);
            g[i] = i + 1;
            f[i] = i + 1;
        }
        for (int pri_j : pri) {
            if (i * pri_j > n)
                break;
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) {
                g[i * pri_j] = g[i] * pri_j + 1;
                f[i * pri_j] = f[i] / g[i] * g[i * pri_j];
                break;
            }
            f[i * pri_j] = f[i] * f[pri_j];
            g[i * pri_j] = 1 + pri_j;
        }
    }
}