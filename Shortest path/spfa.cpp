#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	vector<pair<int, int>> e[110];
	vector<int> dis(10010, 1e9);
	vector<int> inq(10010, 0);
	vector<int> pre(10010, 0);
	auto spfa = [&](int s) -> bool{
    	dis[s] = 0;
	    queue<int> q;
	    q.push(s);
	    map<int, int> cnt;
	    while (!q.empty()) {
	        int u = q.front();
	        q.pop();
	        inq[u] = 0;
	        int i = -1;
	        for (pair<int, int> t : e[u]) {
	            i++;
	            if (dis[u] + t.second < dis[t.first]) {
	                dis[t.first] = dis[u] + t.second;
	                cnt[t.first] = cnt[u] + 1;
	                pre[t.first] = u;
	                if (!inq[t.first])
	                    inq[t.first] = 1, q.push(t.first);
	            }
	            if (cnt[t.first] >= n)
	                return 1;
	        }
	    }
	    return 0;
	};
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back(make_pair(v, w));
    }
    if (spfa(1))
        cout << "-1" << endl;
    else {
    	for(int i=1;i<=n;i++){
            if(dis[i]==(int(1e9))){
                cout<<"30000 ";
                continue;
            }
    		cout<<dis[i]<<" ";
		}
		cout<<endl;
    }
}