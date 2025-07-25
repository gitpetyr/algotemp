#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;

#define endl '\n'

constexpr int N = 1e6 + 5;

vector<int> pri;
bool not_prime[N];
int d[N], num[N];

void pre(int n)
{
    d[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
            pri.push_back(i);
            d[i] = 2;
            num[i] = 1;
        }
        for (int pri_j : pri) {
            if (i * pri_j > n)
                break;
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) {
                num[i * pri_j] = num[i] + 1;
                d[i * pri_j] = d[i] / num[i * pri_j] * (num[i * pri_j] + 1);
                break;
            }
            num[i * pri_j] = 1;
            d[i * pri_j] = d[i] * 2;
        }
    }
}