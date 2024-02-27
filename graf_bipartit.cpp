#include <bits/stdc++.h>

using namespace std;

int n,m;
vector <int> v[100001];
int team[100001],viz[100001];
queue<int> q;
bool ok=1;

void bfs(int k) //(O(m))
{int aux,l;
q.push(k); ///adaug copilul in coada si prelucram
while (!q.empty()) {aux=q.front();
                    q.pop();
                    l=v[aux].size(); //pentru fiecare prieten al sau
                    for (int i=0;i<l;i++)
                    {
                        if (team[v[aux][i]]==team[aux] && viz[v[aux][i]]==1) //daca prietenul sau a fost deja introdus in aceeasi echipa cu el
                            ok=0; //imposibil pt ca ar strica alternanta
                        else
                            team[v[aux][i]]=1-team[aux]; //daca nu, il introducem in echipa opusa
                        if(viz[v[aux][i]]==0) //apoi, marcam prietenul ca fiind introdus si ii luam prietenii la rand
                        {
                            q.push(v[aux][i]);
                            viz[v[aux][i]]=1;
                        }


                    }

                    }
}
///idee: Pentru o prietenie dintre x si y, trebuie sa ii avem in echipe diferite, deci introducem alternativ prietenii in grupe diferite
///adica: x e prieten cu y si y cu z, deci x in echipa 1, y in echipa 2, z in echipa 1
///Complexitate: O(n+m)
int main()
{int i,x,y;
    cin>>n>>m;
    for (i=1;i<=m;i++) //citirea datelor
    {
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    for (i=1;i<=n;i++) //pentru fiecare copil
        if (viz[i]==0) //daca nu l-am introdus in vreo echipa
        {
            team[i]=0; //il introducem in prima echipa, il marcam ca fiind intr-o echipa si incepem parcurgerea relatiilor de prietenie
            viz[i]=1;
            bfs(i); //O(m)
        }//-->O(n+m) pentru ca nu resetam viz[i];

    if (ok==1)
        for (int i=1;i<=n;i++)
            cout<<team[i]+1<<' ';
    else
        cout<<"IMPOSSIBLE";
}
