#include<bits/stdc++.h>
#define INF 100000000
using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

int a[101][101];
int sol[101][101],p[101][101];
int e[101];
vector<int> c;

void drum(int i, int j)
{
    //cout<<i<<' '<<j<<'\n';
    if (i!=j)
        drum(i,p[i][j]);
    g<<j<<' ';
}


///nota: am notat cu t=1 cand facem doar floyd-warshall si t=2 cazul in care graful este neorientat si calculam excentricitatea
int main()
{int n,i,j,k,m,x,y,z,emax=INF*-1,emin=INF,t;
bool ok=1,gasit=0;
    f>>t;
    f>>n>>m;
    //initializare
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            if (i==j)
                a[i][j]=0;
            else
                a[i][j]=INF;

    for (i=1;i<=m;i++)
    {
        f>>x>>y>>z;
        a[x][y]=z;
        //pt t=2 facem graful neorientat
        if (t==2)
            a[y][x]=z;
    }
    //initializare matrice distanta si matrice predecesor
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
        {
            sol[i][j]=a[i][j];
            if (sol[i][j]==INF)
                p[i][j]=0;
            else
                p[i][j]=i;

        }
    ///floyd-warshall--->O(n^3)
    for(k=1;k<=n;k++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(sol[i][k]+sol[k][j]<sol[i][j] && sol[i][k]!=INF && sol[k][j]!=INF)
                {
                    sol[i][j]=sol[i][k]+sol[k][j];
                    p[i][j]=p[k][j];
                }

    for (i=1;i<=n;i++)
        if (sol[i][i]<0)
            ok=0;
    if (ok!=0)
        if (t==1)
        {
            for(i=1;i<=n;i++)
            {
                for(j=1;j<=n;j++)
                    if (sol[i][j]==INF)
                        g<<0<<" ";
                    else
                        g<<sol[i][j]<<' ';
                g<<'\n';
            }
        }
        else if (t==2)
        {
            for (i=1;i<=n;i++)
            {
                ///excentricitatea: maximul dintre distantele de la nodul i la oricare nod j!=i
                e[i]=INF*-1;
                for (j=1;j<=n;j++)
                    if (sol[i][j]!=INF && i!=j)
                        e[i]=max(sol[i][j],e[i]);
                //diametru
                emax=max(emax,e[i]);
                //raza
                emin=min(emin,e[i]);
            }
            //calc centru
            for (i=1;i<=n;i++)
                if (e[i]==emin)
                    c.push_back(i);
            g<<"Raza: "<<emin<<'\n';
            g<<"Centru: ";
            for (i=0;i<c.size();i++)
                g<<c[i]<<' ';
            g<<'\n';
            g<<"Diametru: "<<emax<<'\n';
            ///determinarea unui lant diametral: daca distanta de la i la j=diametru-->sol[i][j]=emax => lant diametral intre i si j
            g<<"Lant diametral: ";
            for (i=1;i<=n;i++)
                for (j=1;j<=n;j++)
                    if (sol[i][j]==emax && gasit==0)
                        drum(i,j),gasit=1;
        }

    ///date incorecte
    else
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
                if (sol[i][j]<0 && i!=j && sol[i][i]<0 && sol[j][j]<0)
                    {
                        if (ok==0)
                        {
                             g<<"Ciclu negativ:\n";
                             drum(i,j);
                             ok=1;
                        }


                    }

    return 0;
}
