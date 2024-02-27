#include <bits/stdc++.h>

using namespace std;

int timp,n,m,desc[100001],fin[100001],viz[100001];
vector <int> v[100001];
///desc-->cand a fost descoperit nodul
///fin-->cand s-a terminat explorarea sa

void dfs(int x)
{
    //cout<<"In nodul "<<x<<'\n';
    timp++;
    viz[x]=1;
    desc[x]=timp;
    for (auto y:v[x])
        if (viz[y]==0)
            dfs(y);
        else
        {
            if (desc[x]<fin[y] && desc[x]<desc[y]) ///in muchia(x,y), nodul x a fost descoperit inaintea lui y si e finalizata explorarea sa
                cout<<"Muchia "<<x<<' '<<y<<" este muchie de avansare"<<'\n';

            else if (desc[y]<desc[x] && fin[y]==0) ///in muchia (x,y), daca y a fost descoperit inaintea lui x, iar y mai poate fi explorat
                cout<<"Muchia "<<x<<' '<<y<<" este muchie de intoarcere"<<'\n';

            else if (desc[x]>desc[y] && fin[y]!=0) ///daca y a fost descoperit inaintea lui x, iar y este finalizat, adica face parte dintr-un alt subarbore
                cout<<"Muchia "<<x<<' '<<y<<" este muchie de traversare"<<'\n';
        }
    fin[x]=timp;
}

int main()
{int x,y,i,start;
    cin>>n>>m;
    for (i=1;i<=m;i++)
    {
        cin>>x>>y;
        v[x].push_back(y);
    }
    cin>>start;
    dfs(start);
}

/*
9 13
1 3
1 5
1 9
2 5
3 1
3 2
3 6
4 8
4 9
7 4
9 6
9 7
9 8
1
*/
