#include <bits/stdc++.h>
#define INF -1
using namespace std;

///pentru viitor: in loc de operatii, mai bine logaritmezi si folosesti adunare ca la dijkstra normal (e 2^n deci log-ul e n)

ifstream f("retea.in");

int n,m;
struct elem
{int nod;
double c;
 bool operator < (const elem &a) const
    {
        return c>a.c;
    }
};

vector<elem>a[50002];
priority_queue<elem>pq;
double sol[50002];
int tata[5002];
int vv[10001][10001];
///plecand de la nodul start, el va avea sol[i]=1, restul vor fi INF, care arata ca nu sunt parcurse
///de ce 1? pentru ca probabilitatile sunt mai mici sau egale cu 1, deci nu va intra niciodata inapoi in nodul de start
void dijkstra(int start, int finish) ///o(mlogn)
{int i,nod;
elem p;
double cost;
    for (i=1;i<=n;i++)
        if (i!=start)
            sol[i]=INF;
        else
            sol[i]=1;
    pq.push({start,1});

    while (!pq.empty())
    {
        p=pq.top();
        pq.pop();
        nod=p.nod;
        cost=p.c;
        //cout<<nod<<' '<<cost<<' '<<tata[nod]<<'\n';
        if (cost==sol[nod]) ///in coada poate aparea acelasi nod de mai multe ori in cazul in care sunt mai multe drumuri pana la el
        {int l=a[nod].size();
            for (i=0;i<l;i++)
                //daca e INF, se va intra pentru prima data in el cu o solutie care apartine (0,1). Daca nu, incearca sa gaseasca un drum mai sigur
                if (sol[a[nod][i].nod]==INF || (sol[a[nod][i].nod]!=INF && sol[nod]*a[nod][i].c>sol[a[nod][i].nod]))
                {
                    sol[a[nod][i].nod]=sol[nod]*a[nod][i].c;
                    pq.push({a[nod][i].nod,sol[a[nod][i].nod]});
                    tata[a[nod][i].nod]=nod;
                }
        }
    }
}

vector<int> drum;
void dfs(int s, int t)
{
    drum.push_back(t);
    if (s!=t)
        dfs(s,tata[t]);

}

int main()
{int s,t,i,x,y;
double z;
    cin>>s>>t;
    f>>n>>m;
    for (i=1;i<=m;i++)
    {
        f>>x>>y>>z;
        a[x].push_back({y,z});
    }

    dijkstra(s,t);
    cout<<sol[t]<<'\n';
    dfs(s,t);
    for (i=drum.size()-1;i>=0;i--)
        cout<<drum[i]<<' ';
}
