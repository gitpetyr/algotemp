#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

using ll = long long;
using db = double;
using T = ll;

constexpr int N = 1e6 + 10;
constexpr T inf = 1e9;

namespace Bit{

int n;
vector<T>tr;

int lowbit(int x){
    return x&-x;
}

void build(vector<T>&a){
    for(int i=1;i<=n;i++){
        tr[i]+=a[i];
        int j=i+lowbit(i);
        if(j<=n){
            tr[j]+=tr[i];
        }
    }
}

void Bit(vector<T>&a){
    n=a.size()-1;
    tr.resize(n+1);
    build(a);
}

T qry(int x){
    T res=0;
    while(x>0){
        res=res+tr[x];
        x=x-lowbit(x);
    }
    return res;
}

void modify(int x,T v){
    while(x<=n){
        tr[x]=tr[x]+v;
        x=x+lowbit(x);
    }
}
}

int main()
{
    int n,q;
    cin>>n>>q;
    vector<T>a(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    Bit::Bit(a);
    for(int i=1;i<=q;i++){
        int opt;
        cin>>opt;
        if(opt==1){
            int x;
            T v;
            cin>>x>>v;
            Bit::modify(x,v);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<Bit::qry(r)-Bit::qry(l-1)<<endl;
        }
    }
}