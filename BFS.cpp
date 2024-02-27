#include<bits/stdc++.h>

using namespace std;

vector<int> v[10001];
queue<int> q;
int viz[10001],niv[10001];

void bfs(int s)
{int aux,i,l;
    q.push(s);
    viz[s]=1;
    while (!q.empty())
    {
        aux=q.front();
        q.pop();
        l=v[aux].size();
        for (i=0;i<l;i++)
        {
            if (viz[v[aux][i]]==0)
            {
                q.push(v[aux][i]);
                viz[v[aux][i]]=1;
                niv[v[aux][i]]=niv[aux]+1;
            }

        }
    }
}

int main()
{int n,m,s,i,x,y;
    cin>>n>>m>>s;
    for (i=1;i<=m;i++)
    {
        cin>>x>>y;
        v[x].push_back(y);
    }
    bfs(s);
    for (i=1;i<=n;i++)
        if (viz[i]==0)
            cout<<-1<<' ';
        else
            cout<<niv[i]<<' ';
}
