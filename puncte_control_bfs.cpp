#include <bits/stdc++.h>
#define INF 999999999
using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

vector <int> v[100001];
int viz[100001],sol[100001],n,m,stramos[100001]; //sol retine distanta minima de la un nod la oricare punct de control, iar ctrl daca un nod este pct de control
queue <int> pq;

void bfs() //O(m)
{int aux,l;

while (!pq.empty()) {aux=pq.front();
                    pq.pop();
                    //cout<<aux<<' ';
                    l=v[aux].size(); //iau fiecare vecin al sau in parte
                    for (int i=0;i<l;i++)
                        if (viz[v[aux][i]]==0) //daca vecinul NU a fost vizitat
                        {
                            viz[v[aux][i]]=1; //il vizitez si il adaug in coada pt urm parcurgere
                            pq.push(v[aux][i]);
                            stramos[v[aux][i]]=stramos[aux]; //marchez stramosul fiului ca fiind stramosul tatalui
                            sol[v[aux][i]]=sol[aux]+1; //actualizez distanta minima cu distanta de la tatal sau+1
                        }

                    }
}

///idee: pentru un punct de control putem afla distanta de la el la oricare nod prin BFS. Deci, facem BFS pentru punctele de control in acelasi timp
///cum? adaugandu-le in coada, intai va parcurge vecinii primului de control, apoi vecinii celui de-al doilea etc.
///retinem pentru fiecare nod punctul de control care este cel mai apropiat de el si distanta pana la acesta
///Complexitate finala: O(n+m)


int main()
{int x,y,i;
    f>>n>>m;
    for (i=1;i<=m;i++) //citirea muchiilor
    {
        f>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    while (f>>x) //pentru fiecare punct critic
    {
        pq.push(x); //adaugam in coada toate punctele de control si le marchez ca fiind proprii lor stramosi si noduri vizitate
        stramos[x]=x;
        viz[x]=1;

    }
    bfs();
    //afisari: O(m)
    for (i=1;i<=n;i++) //afisarea distantei minime
        g<<sol[i]<<' ';
    g<<'\n';
    for (i=1;i<=n;i++) //afisarea celui mai apropiat punct de control pt fiecare
        g<<stramos[i]<<' ';
}

