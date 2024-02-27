#include <bits/stdc++.h>
#define INF 2000000000
using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

struct elem
{
    int nod,c;
};

vector <elem> a[50001];
queue <int> q;

int d[50001],nr[50001],n,m,inq[50001],tata[50001];
bool ok=1;

void ciclu_negativ(int nod_naspa)
{int x,i;
    for (i=1;i<=n;i++)
        nod_naspa=tata[nod_naspa];
    x=nod_naspa;
    x=tata[x];
    g<<x<<' ';
    while (x!=nod_naspa)
    {
        g<<tata[x]<<' ';
        x=tata[x];
    }

}

vector<int>drum;
void dfs(int s, int t)
{
    drum.push_back(t);
    if (t!=s)
        dfs(s,tata[t]);
}

int main()
{int x,y,z,l,s,nod_naspa,i,j;
    f>>n>>m;
    for (i=1;i<=m;i++)
    {
        f>>x>>y>>z;
        a[x].push_back({y,z});
    }
    f>>s;
    for (i=1;i<=n;i++)
        d[i]=INF;

    //initializare nod start
    d[s]=0;
    q.push(s);
    inq[s]=1;
    nr[s]=1;
    ///bellman-ford: O(m*n)-->pentru fiecare nod in parte, cautam un drum minim, "relaxand" arcul
    ///in plus, daca nu este in coada adaugat, verificam de cate ori a intrat in coada: de n ori-->ciclu
    while (ok==1 && !q.empty())
    {
        x=q.front();
        q.pop();
        inq[x]=0;
        l=a[x].size();
        for (i=0;i<l;i++)
            if (d[a[x][i].nod]>d[x]+a[x][i].c)
            {
                d[a[x][i].nod]=d[x]+a[x][i].c;
                tata[a[x][i].nod]=x;
                if (inq[a[x][i].nod]==0)
                    {
                        q.push(a[x][i].nod);
                        inq[a[x][i].nod]=1;
                        nr[a[x][i].nod]++;
                        //daca este intr-un ciclu, reconstituim drumul pana ajungem inapoi la el
                        if (nr[a[x][i].nod]==n)
                        {
                            ok=0;
                            nod_naspa=a[x][i].nod;
                            break;
                        }

                    }
            }
    }
    if (ok==0)
    {
        g<<"Circuit de cost negativ:"<<'\n';
        ciclu_negativ(nod_naspa);
    }
    else
    {
        for (i=1;i<=n;i++)
            if (i!=s && d[i]!=INF)
            {
                g<<"Drum: ";
                dfs(s,i);
                for (j=drum.size()-1;j>=0;j--)
                    g<<drum[j]<<' ';
                drum.clear();
                g<<"Cost: "<<d[i]<<'\n';
            }
    }
}
