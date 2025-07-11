#include <bits/stdc++.h>
using namespace std;

constexpr double eps = 1e-6;
constexpr int maxn=400+5;

double A[maxn][maxn];
int flag=0;

void Gauss(int n){
    for(int i=1;i<=n;i++){
        int mx=i;
        for(int j=1;j<=n;j++){
            if(j<i&&fabs(A[j][j])>eps)continue;
            if(fabs(A[mx][i])<fabs(A[j][i]))mx=j;
        }
        for(int j=1;j<=n+1;j++){
            swap(A[i][j],A[mx][j]);
        }
        if(fabs(A[i][i])<eps)continue;
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            double rate=A[j][i]/A[i][i];
            for(int k=i;k<=n+1;k++){
                A[j][k]-=rate*A[i][k];
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(fabs(A[i][i])<eps){
            flag=1;
            continue;
        }
        A[i][n+1]/=A[i][i];
        A[i][i]=1.0;
    }
}

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            cin>>A[i][j];
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n+1;j++){
    //         cerr<<A[i][j]<<" ";
    //     }
    //     cerr<<endl;
    // }
    // cerr<<endl;
    Gauss(n);
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n+1;j++){
    //         cerr<<A[i][j]<<" ";
    //     }
    //     cerr<<endl;
    // }
    if(flag){
        cout<<"No Solution"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        cout<<fixed<<setprecision(2)<<A[i][n+1]/A[i][i]<<endl;
    }
}