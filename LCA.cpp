#include <bits/stdc++.h>
using namespace std;
namespace LCA{
	const int maxn=500010;
	vector<int> e[maxn];
	int f[__lg(maxn) + 1][maxn], dep[maxn], n, lim;
	
	void dfs(int u, int fa) {
	    f[0][u] = fa; dep[u] = dep[fa] + 1;
	    for (auto v: e[u]) 
	        if (v != fa) dfs(v, u);
	}
	void init(int sz, int rt) {
	    n = sz; lim = __lg(n);
	    dep[rt] = 1; dfs(rt, 0);
	    for (int i = 1; i <= lim; i++) 
	        for (int u = 1; u <= n; u++) f[i][u] = f[i - 1][f[i - 1][u]];
	}
	int lca(int u,int v){
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		for(int i=lim;i>=0;i--){
			if(dep[u]-(1<<i)>=dep[v])u=f[i][u];
		} 
		if(u==v){
			return u;
		}
		for(int i=lim;i>=0;i--){
			if(!f[i][u])continue;
			if(f[i][u]!=f[i][v]){
				u=f[i][u];
				v=f[i][v];
			}
		}
		return f[0][u];
	}
}

int main() {
    int n, q, m; cin >> n >> q >> m;
    for (int i = 2; i <= n; i++) {
        int u; cin >> u;
        LCA::e[u].push_back(i);
    }

    LCA::init(n, m);

    while (q--){
        int u, k; cin >> u >> k;
        cout<<LCA::lca(u,k)<<endl;
    }
}