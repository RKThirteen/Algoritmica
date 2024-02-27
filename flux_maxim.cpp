#include <bits/stdc++.h>

using namespace std;

ifstream f("retea.in");

int intra[1001],iese[1001],tata[1001],viz[1001],r[1001][1001];
int n,m,sol;
vector<int> a[1001];
vector<int> rez[1001];
vector<int> taietura;
///Complexitate: O(nm^2)
///se fol ford-fulkerson cu graf rezidual
///actualizari pe baza grafului rezidual

queue<int> q;
//o(m)
///construirea unui lant nesaturat
bool bfs_lant_nesat(int s, int t)
{cout<<"IN bfs"<<'\n';
int l,nod_curent,i;
    for (i=1;i<=n;i++)
        tata[i]=viz[i]=0;
    q.push(s);
    viz[s]=1;
    while (!q.empty())
    {
        nod_curent=q.front();
        q.pop();
        cout<<nod_curent<<' ';
        l=a[nod_curent].size();
        for (i=0;i<l;i++)
            //daca pe langa conditia de vizitare, se poate transmite flux de la nod la vecin
            if (viz[a[nod_curent][i]]==0 && r[nod_curent][a[nod_curent][i]]>0)
            {
                viz[a[nod_curent][i]]=1;
                tata[a[nod_curent][i]]=nod_curent;
                q.push(a[nod_curent][i]);

            }
    }
    cout<<'\n';
    ///cand nu mai exista lant nesaturat, nodurile vizitate sunt accesibile din s, cele nevizitate accesibile din t
    if (viz[t]==0)
    {
        for (i=1;i<=n;i++)
            if (viz[i]==1)
                taietura.push_back(i);
    }
    return viz[t];
}


void ford_fulkerson(int s, int t)
{
    int path_flow,i,j,l=a[t].size();
    //cat timp exista drumuri
    while (bfs_lant_nesat(s,t))
    {
        //mergem invers, de la destinatie la sursa
        for (i=0;i<l;i++)
            ///de la fiecare vecin in parte, calculeaza fluxul maxim care poate fi transmis pe lant
            ///se uita la arcele inverse
        if((tata[a[t][i]]!=0||a[t][i]==s) && r[a[t][i]][t]>0)
        {
            path_flow=r[a[t][i]][t];
            ///mergem pe vectorul tata
            for(j=a[t][i];j!=s;j=tata[j])
            {
                cout<<j<<' ';
                path_flow=min(path_flow,r[tata[j]][j]);
                if(path_flow==0)
                    break;
            }
            ///actualizam graful rezidual
            if(path_flow!=0)
            {
                cout<<'\n'<<path_flow<<'\n';
                r[a[t][i]][t]-=path_flow;
                r[t][a[t][i]]+=path_flow;
                for(j=a[t][i];j!=s;j=tata[j])
                {
                    r[tata[j]][j]-=path_flow;
                    r[j][tata[j]]+=path_flow;
                }
                sol+=path_flow;
            }
        }

    }

}
///det arcelor directe: de la un nod vizitat la un nod nevizitat
void det_taietura()
{
    int l=taietura.size(),nod_curent,i,j;
    for (i=0;i<l;i++)
    {
        nod_curent=taietura[i];
        for (j=0;j<rez[nod_curent].size();j++)
            if (viz[rez[nod_curent][j]]==0)
                cout<<nod_curent<<' '<<rez[nod_curent][j]<<'\n';
    }

}


int main()
{int s,t,x,y,z,w,j,l,i;
bool cons=1,marg=1;
    f>>n>>s>>t>>m;
    for (i=1;i<=m;i++)
    {
        f>>x>>y>>z>>w;
        //de ce ca graf neorientat? pentru ca putem trimite flux inainte, DAR SI INAPOI
        a[x].push_back(y);
        a[y].push_back(x);
        rez[x].push_back(y);
        ///daca fluxul>capacitate-->marginire
        if(w>z)
            marg=0;
        iese[x]+=w;
        intra[y]+=w;
        ///intializare graf rezidual
        r[x][y]=z-w;
        r[y][x]=w;
    }
    ///conservare
    for (i=1;i<=n;i++)
        if (iese[x]!=intra[x])
        cons=0;
    if (cons==0)
        cout<<"Nu se respecta conditia de conservare";
    else if (cons==1 && marg==0)
        cout<<"Nu se respecta conditia de marginire";
    else if (cons==0 && marg==0)
        cout<<"Nu se respecta nicio conditie";
    else
    {
        cout<<"DA"<<'\n';
        //adaug fluxul care deja intra in destinatie
        sol+=intra[t];
        //cout<<sol<<'\n';
        ford_fulkerson(s,t);
        ///flux maxim
        cout<<sol<<'\n';
        ///fluxul care trece de la i la j-->r[j][i]=flux_curent de la i la j
        for (i=1;i<=n;i++)
        {
            l=rez[i].size();
            for (j=0;j<l;j++)
                cout<<i<<' '<<rez[i][j]<<' '<<r[rez[i][j]][i]<<'\n';
        }
        ///flux maxim=valoare taietura minima
        cout<<sol<<'\n';
        ///determinarea arcelor directe
        det_taietura();
    }

}
