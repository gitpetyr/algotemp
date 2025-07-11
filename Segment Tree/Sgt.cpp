#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

using ll = long long;
using db = double;
using T = ll;

constexpr ll inf = 1e18;
constexpr ll mod = 1e9 + 7;
constexpr ll rt = 1;

namespace sgt {
    int n;
    struct node{
        T sum,tag;
    };
    node merge(node l,node r){
        return node{l.sum+r.sum,0};
    }
    node init(T x){
        return node{x,0};
    }
    vector<node>tr;
    void push_down(int id,int cl,int cr){
        int lc=id*2,rc=id*2+1,mid=(cl+cr)/2;
        tr[lc].tag+=tr[id].tag;
        tr[rc].tag+=tr[id].tag;
        tr[lc].sum+=tr[id].tag*(mid-cl+1);
        tr[rc].sum+=tr[id].tag*(cr-(mid+1)+1);
        tr[id].tag=0;
        return;
    }
    void build(const vector<T>&a,int id=1,int l=1,int r=n){
		if(l==r){
            tr[id]=init(a[l]);
			return ;
        }
        int lc=id*2,rc=id*2+1,mid=(l+r)/2;
        build(a,lc,l,mid);
        build(a,rc,mid+1,r);
        tr[id]=merge(tr[lc],tr[rc]);
        return;
    }
    void sgt(const vector<T>&a){
		n=a.size()-1;
        tr.resize((n+1)<<2);
		// cerr<<n<<endl;
        build(a);
        return ;
    }
    void modify(int l,int r,T v,int id=1,int px=1,int py=n){
        if(py<l||px>r){
            return ;
        }
        if(l<=px&&py<=r){
            tr[id].tag+=v;
            tr[id].sum+=v*(py-px+1);
            // cerr<<px<<" "<<py<<" "<<tr[id].tag<<endl;
            return;
        }
        int lc=id*2,rc=id*2+1,mid=(px+py)/2;
        push_down(id,px,py);
        modify(l,r,v,lc,px,mid);modify(l,r,v,rc,mid+1,py);
        tr[id]=merge(tr[lc],tr[rc]);
        return ;
    }
    node qry(int l,int r,int id=1,int px=1,int py=n){
        if(py<l||px>r){
            return init(0);
        }
        if(l<=px&&py<=r){
            // cerr<<px<<" "<<py<<" "<<tr[id].sum<<endl;
            return tr[id];
        }
        int lc=id*2,rc=id*2+1,mid=(px+py)/2;
        push_down(id,px,py);
        return merge(qry(l,r,lc,px,mid),qry(l,r,rc,mid+1,py));
    }
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
	vector<T>a(n+1);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	// cerr<<1<<endl;
	sgt::sgt(a);
	// cerr<<sgt::qry(2,2).sum<<endl;
	for(int i=1;i<=m;i++){
		int opt;
		cin>>opt;
		if(opt==1){
			int l,r;
			T x;
			cin>>l>>r>>x;
			sgt::modify(l,r,x);
		}
		else{
			int l,r;
			cin>>l>>r;
			cout<<sgt::qry(l,r).sum<<endl;
		}
	}
}