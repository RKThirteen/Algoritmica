#include <bits/stdc++.h>
#define INF 10000000000
using namespace std;

long long c[10001],viz[10001];
vector<pair<int, int>> a[100001];
set<pair<int, int>> s;
long long sol=0;
///Idee: Conectare la mai multe surse: incepem adaugand fiecare sursa in BFS, ce are costul 0-->BFS pe surse
///c-->costul minim pentru a stoca programul in nodul i
///folosim set in loc de coada(merge si priority queue) pentru BFS ca sa ia mereu cel mai ieftin nod prima data
///Complexitate: O(mlogn)

//Prim/BFS :O(mlogn)
//logn vine de la operatiile de insert din set
//Luam cel mai bun nod(initial un nod-sursa)(daca n-a fost parcurs), intram pe vecinii sai
void BFS_Prim()
{
    while(!s.empty())
    {
        auto it=s.begin();
        s.erase(it);
        int cost=(*it).first;
        int nod=(*it).second;
        if(viz[nod]==0)
        {
            ///asemanator cu pb cu puncte critice: pornim de la nodurile sursa, mergem pe vecini->drum optim la ei, apoi pe vecinii lor->drum optim etc
            viz[nod]=1;
            sol+=cost;
            for(auto next : a[nod])
            {
                ///daca exista o muchie cu un cost mai mic decat costul minim deja inregistrat
                if(c[next.first] > next.second)
                {
                    //se adauga in set
                    c[next.first] = next.second;
                    s.insert({c[next.first], next.first});
                }
            }
        }

    }
}


int main()
{
int t,n,m,l,S,i,x,y,z;

    cin>>t;
    //pentru fiecare caz in parte
    while(t)
    {
        cin>>n>>m>>l>>S;

        //initializare
        for(i=1;i<=n;i++)
        {
            c[i]=INF;
            viz[i]=0;
        }

        //adaugare noduri-sursa in set(ele au costul 0 pt ca au deja programul)
        for(i=1;i<=S;i++)
        {
            cin>>x;
            c[x]=0;
            s.insert({0,x});
        }
        //construire graf
        for(i=1;i<=m;i++)
        {
            cin>>x>>y>>z;
            a[x].push_back({y,z});
            a[y].push_back({x,z});
        }
        BFS_Prim();
        //reset
        for(int i=1;i<=n;i++)
        {
            a[i].clear();
        }
        sol+=1LL*(n - S)*l;
        cout<<sol<< '\n';
        t--;
        sol=0;
    }
    return 0;
}
