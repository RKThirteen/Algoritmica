#include <bits/stdc++.h>

using namespace std;

ifstream f("graf.in");

int intra[1001],iese[1001],tata[1001],viz[1001],r[1001][1001];
int n,m,sol;
bool ok=1;
vector<int> a[1001];
vector<int> rez[1001];
vector<int> taietura;
///Complexitate: O(nm^2)
///se fol ford-fulkerson cu graf rezidual
///actualizari pe baza grafului rezidual

queue<int> q;


///Complexitate totala: O(m*n)

//o(m)
///construirea unui lant nesaturat
bool bfs_lant_nesat(int s, int t)
{//cout<<"IN bfs"<<'\n';
int l,nod_curent,i;
    for (i=1;i<=2*n+1;i++)
        tata[i]=viz[i]=0;
    q.push(s);
    viz[s]=1;
    while (!q.empty())
    {
        nod_curent=q.front();
        q.pop();
        //cout<<nod_curent<<' ';
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
    //cout<<'\n';
    ///cand nu mai exista lant nesaturat, nodurile vizitate sunt accesibile din s, cele nevizitate accesibile din t
    if (viz[t]==0)
    {
        for (i=1;i<=n;i++)
            if (viz[i]==1)
                taietura.push_back(i);
    }
    //cout<<viz[t]<<'\n';
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

                path_flow=min(path_flow,r[tata[j]][j]);
                if(path_flow==0)
                    break;
            }

            ///actualizam graful rezidual
            if(path_flow!=0)
            {//cout<<"OK";

                //cout<<'\n'<<path_flow<<'\n';
                r[a[t][i]][t]-=path_flow;
                r[t][a[t][i]]+=path_flow;
                ///cand reconstitui un drum, se realizeaza automat un cuplaj intre 2 noduri
                for(j=a[t][i];j!=s;j=tata[j])
                {
                    //cout<<j<<' ';
                    r[tata[j]][j]-=path_flow;
                    r[j][tata[j]]+=path_flow;
                }
                sol+=path_flow;
                //cout<<'\n';
            }

        }

    }

}



int main()
{int s,t,x,y,z,w,j,l,i,sum=0,sum2=0;
    f>>n;
    for (i=1;i<=n;i++)
        f>>intra[i],sum+=intra[i];
    for (i=1;i<=n;i++)
        f>>iese[i];

    ///dublez nr de varfuri
    s=0;
    t=2*n+1;
    ///adaugam muchii de la s la nodurile normale si muchii de la nodurile "dublate" la t
    for (i=1;i<=n;i++)
    {
        a[s].push_back(i);
        a[i].push_back(s);
        rez[s].push_back(i);
        a[t].push_back(i+n);
        a[i+n].push_back(t);
        rez[i+1].push_back(t);
        ///muchiile de la s la nodurile 1..n au capacitatea intra[i]
        r[s][i]=intra[i];
        r[i+n][t]=iese[i];
    }
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            if (i!=j)
            {
                a[i].push_back(j+n);
                a[j+n].push_back(i);
                rez[i].push_back(j+n);
                ///muchiile au capacitatea 1
                r[i][j+n]=1;
            }
    ///tratam ca la cuplaj bipartit
    ford_fulkerson(s,t);
    ///daca flux maxim!=suma gradelor de intrare, NU
    if (sol!=sum)
        cout<<"NU"<<'\n';
    else
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
                if (i!=j)
                {
                    if (r[i][j+n]==0)
                        cout<<i<<' '<<j<<'\n';
                }


}
