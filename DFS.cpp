#include<bits/stdc++.h>
using namespace std;
ifstream f("dfs.in");
ofstream g("dfs.out");
vector<int>a[100002];
bool viz[100002];

void dfs(int x)
{
    viz[x]=1;
    for(auto y:a[x])
    if(viz[y]==0)
        dfs(y);
}

int main()
{
    int n,m,i,x,y,sol=0;
    f>>n>>m;
    for(i=1;i<=m;i++)
    {
        f>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(i=1;i<=n;i++)
    if(viz[i]==0)
    {
        sol++;
        dfs(i);
    }
    g<<sol;
    return 0;
}
