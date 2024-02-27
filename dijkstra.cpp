#include <bits/stdc++.h>
#define INF 100000000
using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

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
queue<int> p;
int sol[50002];
int tata[50002],stramos[50002],d[50002],viz[50002];

///am considerat ca ponderea nu reprezinta distanta de la un nod la altul, ci un cost(ex. cost de mentinere a acelei legaturi)
///fac ca in lab 1 si aflu fiecare nod de ce punct de control e mai apropiat
void bfs() //O(m)
{int aux,l;

while (!p.empty()) {aux=p.front();
                    p.pop();
                    //cout<<aux<<' ';
                    l=a[aux].size(); //iau fiecare vecin al sau in parte
                    for (int i=0;i<l;i++)
                        if (viz[a[aux][i].nod]==0) //daca vecinul NU a fost vizitat
                        {
                            viz[a[aux][i].nod]=1; //il vizitez si il adaug in coada pt urm parcurgere
                            p.push(a[aux][i].nod);
                            stramos[a[aux][i].nod]=stramos[aux]; //marchez stramosul fiului ca fiind stramosul tatalui
                            d[a[aux][i].nod]=d[aux]+1; //actualizez distanta minima cu distanta de la tatal sau+1
                        }

                    }
}

///O(mlogn), aflu drumul minim de la nodul selectat la fiecare nod in parte
///daca opresc algoritmul cand ajung la punctul de control prima data, posibil sa ratez un drum de cost mai mic, deci mai bine ruleaza pana la capat
///fiindca e neorientat graful, pot porni dijkstra de la punctul din fisier, nu de la punctul de control
void dijkstra(int start)
{int i,nod,cost;
elem p;
    for (i=1;i<=n;i++)
        if (i!=start)
            sol[i]=INF;
        else
            sol[i]=0;
    pq.push({start,0});

    while (!pq.empty())
    {
        p=pq.top();
        pq.pop();
        nod=p.nod;
        cost=p.c;
        cout<<nod<<' '<<cost<<' '<<tata[nod]<<'\n';
        if (cost==sol[nod]) ///in coada poate aparea acelasi nod de mai multe ori in cazul in care sunt mai multe drumuri pana la el
        {int l=a[nod].size();
            for (i=0;i<l;i++)
                if (sol[nod]+a[nod][i].c<sol[a[nod][i].nod])
                {
                    sol[a[nod][i].nod]=sol[nod]+a[nod][i].c;
                    pq.push({a[nod][i].nod,sol[a[nod][i].nod]});
                    //retin tatal nodului pentru a reconstitui drumul mai tarziu
                    tata[a[nod][i].nod]=nod;
                }
        }
    }
}

vector<int> drum,control;
void dfs(int s, int t)
{
    cout<<t<<' ';
    drum.push_back(t);
    if (s!=t)
        dfs(s,tata[t]);

}

int main()
{int s,i,x,y,z,dmin=INF,k;
    f>>n>>m;
    for (i=1;i<=m;i++)
    {
        f>>x>>y>>z;
        a[x].push_back({y,z});
        a[y].push_back({x,z});
    }
    f>>k;
    for (i=1;i<=k;i++)
    {
        f>>x;
        p.push(x);
        stramos[x]=x;
        viz[x]=1;
        control.push_back(x);
    }
    bfs();
    ///observatie: punctele de control 5 si 6 in graful exemplu sunt la o distanta de 2 noduri de nodul 1, deci stramos[1]=5.
    ///ironic, drumul de la 1 la 5 este egal in cost cu drumul de la 1 la 6
    f>>s;
    dijkstra(s);
    g<<stramos[s]<<'\n';
    dfs(s,stramos[s]);
    for (i=drum.size()-1;i>=0;i--)
        g<<drum[i]<<' ';
}
