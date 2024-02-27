#include <bits/stdc++.h>

using namespace std;

int n,m,ct=0;
vector <int> v[100001];
int sol[100001],niv[100001],viz[100001],nma[100001],copii[100001];

void dfs_arbore(int x, int tata)
{
    //cout<<"In dfs "<<x<<' '<<tata<<'\n';
    viz[x]=1; //am parcurs vectorul, ii acordam nivelul corespunzator dar si nivelul minim accesibil
    niv[x]=niv[tata]+1;
    nma[x]=niv[x];
    for (auto y: v[x]) //pentru fiecare nod adiacent, diferit de tatal sau(merge mai jos pe "arbore")
    {
        if (y!=tata)
            if (viz[y]==1) //in caz ca a fost vizitat, inseamna ca muchia (x,y) este de intoarcere, deci actualizam nma-ul lui x cu minimul dintre nma-ul
                nma[x]=min(niv[y],nma[x]);//existent si nivelul efectiv al fiului sau
            else //muchia nu este muchie de intoarcere si face parte din arborele DFS
            {
                copii[x]++; //daca nu a mai fost vizitat, il marcam ca un copil al lui x, apoi il parcurgem
                dfs_arbore(y,x);
                nma[x]=min(nma[x],nma[y]); //revenind, actualizam nivelul minim accesibil al lui x cu nma-ul dintre el insusi si fiul sau
                if ((niv[tata]==0 && copii[x]>1 && sol[x]==0)||(niv[tata]!=0 && sol[x]==0 && niv[x]<=nma[y])) //daca este radacina si are macar 2 copii SAU nu este radacina si exista un fiu care are nivelul minim accesibil mai mare sau egal cu al lui x
                {
                    //cout<<x<<' '<<tata<<'\n';
                    sol[x]=1; //inseamna ca x este punct de articulatie si il retinem, pentru a nu-l adauga accidental de mai multe ori
                    ct++;
                }

            }
    }
}

///Determinarea punctelor de articulatie:
///Idee: Un nod este nod de articulatie daca are un fiu cu nivelul minim accesibil>=nivelul efectiv al nodului?
///Dar ce este nma-ul? nivelul minim de la care se poate ajunge din k mergand numai pe arborele DFS
///nma-ul poate fi: nivelul nodului curent(default), minimul dintre nivelul nodurilor din muchia de intoarcere sau minimul dintre nma-urile fiilor din arborele DFS
///pentru a determina nma-ul cum trebuie, ne trebuie in dfs bottom-up, comparand cu valorile default, apoi cu minimele obtinute pe parcurs
///Complexitate finala: O(m+n) per test

int main()
{int i,x,y;
bool ok=1;
    cin>>n>>m;
    while (n!=0 && m!=0) //citirea testelor pana cand m si n sunt 0
    {
        for (i=1;i<=m;i++) //citirea datelor (O(m))
        {
            cin>>x>>y;
            v[x].push_back(y); //graf neorientat
            v[y].push_back(x);
        }
        dfs_arbore(1,0); //dfs in (O(m))
        cout<<ct<<'\n';
        for (i=1;i<=n;i++) //resetarea tuturor vectorilor si valorii finale pentru a fi folosite in urmatorul test
        {
            viz[i]=0;
            nma[i]=0;
            copii[i]=0;
            sol[i]=0;
            niv[i]=0;
            v[i].clear();
            ct=0;
        }

        cin>>n>>m; //recitirea lui n si m
    }

}
