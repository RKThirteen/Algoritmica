#include <bits/stdc++.h>

using namespace std;

ifstream f("graf.in");

int intra[1001],iese[1001],tata[1001],viz[1001],r[1001][1001],team[1001];
int n,m,sol;
bool ok=1;
vector<int> a[1001];
vector<int> rez[1001];
vector<int> taietura;


queue<int> q;


///Complexitate totala: O(m*n)

void bfs(int k) //(O(m))
{int aux,l;
q.push(k); ///adaug copilul in coada si prelucram
while (!q.empty()) {aux=q.front();
                    q.pop();
                    l=a[aux].size(); //pentru fiecare prieten al sau
                    for (int i=0;i<l;i++)
                    {
                        if (team[a[aux][i]]==team[aux] && viz[a[aux][i]]==1) //daca prietenul sau a fost deja introdus in aceeasi echipa cu el
                            {
                                ok=0;
                                while (!q.empty())
                                    q.pop();

                            } //imposibil pt ca ar strica alternanta
                        else
                            team[a[aux][i]]=1-team[aux]; //daca nu, il introducem in echipa opusa

                        if(viz[a[aux][i]]==0) //apoi, marcam prietenul ca fiind introdus si ii luam prietenii la rand
                        {
                            q.push(a[aux][i]);
                            viz[a[aux][i]]=1;
                            tata[a[aux][i]]=aux;
                        }


                    }

                    }
}

void dfs(int x)
{cout<<x<<' ';
    viz[x]=1;
    for (auto y:a[x])
    {
        if (team[y]==team[x] && viz[y]==1)
        {
            cout<<'\n';
            for (int i=x;tata[i]!=y;i=tata[i])
                cout<<i<<' ';
            cout<<'\n';
        }
        else
            team[y]=team[x];
        if (viz[y]==0)
        {
            team[y]=1-team[x];
            tata[y]=x;
            dfs(y);
        }


    }
}

//o(m)
///construirea unui lant nesaturat
bool bfs_lant_nesat(int s, int t)
{//cout<<"IN bfs"<<'\n';
int l,nod_curent,i;
    for (i=1;i<=n+1;i++)
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
                ///de ce?
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
{int s,t,x,y,z,w,j,l,i;
    f>>n>>m;
    for (i=1;i<=m;i++)
    {
        f>>x>>y;
        //de ce ca graf neorientat? pentru ca putem trimite flux inainte, DAR SI INAPOI
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for (i=1;i<=n;i++)
        if (viz[i]==0)
        {
            team[i]=0;
            viz[i]=1;
            bfs(i);
        }//-->O(n+m) pentru ca nu resetam viz[i];
    ///daca e bipartit-->face ford-fulkerson
    /*for (i=1;i<=n;i++)
        cout<<team[i]<<' ';*/
    cout<<'\n';
    if (ok==1)
    {
        s=0;
        t=n+1;
        for (i=1;i<=n;i++)
        {
            ///alcatuirea grafului rezidual si a fluxului
            if (team[i]==0)
            {
                for (j=0;j<a[i].size();j++)
                {
                    if (team[a[i][j]]==1)
                        {
                            rez[i].push_back(a[i][j]);
                            r[i][a[i][j]]=1;
                        }
                }
                a[s].push_back(i);
                a[i].push_back(s);
                rez[s].push_back(i);
                r[s][i]=1;
            }

            else
            {
                a[i].push_back(t);
                a[t].push_back(i);
                r[i][t]=1;
                rez[i].push_back(t);
            }

        }

        ford_fulkerson(s,t);
        cout<<'\n';
        for (i=1;i<=n;i++)
            for (j=0;j<rez[i].size();j++)
                if (r[i][rez[i][j]]==0 && rez[i][j]!=t && rez[i][j]!=s)
                    cout<<i<<' '<<rez[i][j]<<'\n';

    }
    else
    {
        for (i=1;i<=n;i++)
            team[i]=viz[i]=tata[i]=0;
        dfs(1);
    }





}
