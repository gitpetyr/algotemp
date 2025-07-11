#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;

constexpr ll maxn = 150010;
constexpr ll inf = 1e18;

vector<pair<ll, ll>> e[maxn];
vector<ll> dis(maxn, inf);
vector<ll> vis(maxn, 0);
map<ll,ll>pre;

void dij(ll s) {
    fill(dis.begin(), dis.end(), inf);
    dis[s] = 0;
    fill(vis.begin(), vis.end(), 0);
    // pair<long long,long long> => <w,v>
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>,
                   greater<pair<ll, ll>>>
        pq;

    pq.emplace(0, s);
    while (!pq.empty()) {
        auto u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto edg : e[u]) {
            auto v = edg.first, w = edg.second;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pre[v] = u;
                pq.emplace(dis[v], v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    ll n, m, s;
    cin >> n >> m >> s;
    for (ll i = 1; i <= m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({ v, w });
    }
    dij(s);
    for(ll i=1;i<=n;i++){
    	cout<<dis[i]<<" ";
	}
	cout<<endl;
}