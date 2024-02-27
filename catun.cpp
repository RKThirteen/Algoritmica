#include <bits/stdc++.h>
#define INF 100000000
using namespace std;

ifstream f("catun.in");
ofstream g("catun.out");

int n,m;
struct elem
{int nod,c;
 bool operator < (const elem &a) const
    {
        return c>a.c;
    }
};

vector<elem>a[50002];
priority_queue<elem>pq;
int sol[36002],catune[36002],d[36002];

///O(mlogn)-->log de la pq
void dijkstra()
{elem p;
int l,i;
    while (!pq.empty())
    {
        p=pq.top();
        pq.pop();
        if (p.c==d[p.nod])
        {
            l=a[p.nod].size();
            for (i=0;i<l;i++)
                if (d[p.nod]+a[p.nod][i].c<d[a[p.nod][i].nod])
                {
                    sol[a[p.nod][i].nod]=sol[p.nod];
                    d[a[p.nod][i].nod]=d[p.nod]+a[p.nod][i].c;
                    pq.push({a[p.nod][i].nod,d[a[p.nod][i].nod]});
                }
                ///verificarea pentru drumuri egale, fiindca pb zice sa asignam feude cu nr cat mai mic catunelor in caz de egalitate
                else if (d[p.nod]+a[p.nod][i].c==d[a[p.nod][i].nod] && sol[a[p.nod][i].nod]>sol[p.nod])
                {
                    sol[a[p.nod][i].nod]=sol[p.nod];
                    pq.push({a[p.nod][i].nod,d[a[p.nod][i].nod]});
                }
        }
    }
}
///ideea de baza: aplicand dijkstra, creez drumuri de cost minim de la o feuda la cele mai apropiate catune de ea
///vectorul sol pastreaza pentru fiecare teren feuda de care apartine(0 daca este feuda)
int main()
{int k,i,x,y,z;
    f>>n>>m>>k;
    for (i=1;i<=k;i++)
    {
        f>>catune[i];
        pq.push({catune[i],0});
        sol[catune[i]]=catune[i];
    }
    for (i=1;i<=m;i++)
    {
        f>>x>>y>>z;
        a[x].push_back({y,z});
        a[y].push_back({x,z});
    }
    ///initializare dijkstra
    for (i=1;i<=n;i++)
        d[i]=INF;
    for (i=1;i<=k;i++)
        d[catune[i]]=0;
    dijkstra();

    for (i=1;i<=k;i++)
        sol[catune[i]]=0;
    for (i=1;i<=n;i++)
        g<<sol[i]<<' ';

}
