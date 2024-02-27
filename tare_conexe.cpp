#include<bits/stdc++.h>

using namespace std;

vector <int> a[100001],inv[100001];
int viz[100001],n,m,backwards[100001],k,ct,sol[100001];

void dfs(int x) //parcurgerea dfs obisnuita a grafului
{
    viz[x]=1;
    for (auto y:a[x]) //pentru fiecare nod vecin al grafului:
        if (viz[y]==0) //daca nu a fost vizitat, il parcurge
            dfs(y);
    backwards[++k]=x; //dfs-ul este bottom-up, deci "frunzele" vor fi adaugate primele, apoi tatal lor, etc, alcatuind ordinea parcurgerii, invers
}

void dfs_backwards(int x) //parcurgerea dfs, dar invers
{
    viz[x]=1;
    sol[x]=ct; //adaugam planeta in castelul corespunzator
    for (auto y:inv[x])
        if (viz[y]==0) //daca nu a fost vizitat, parcurge "inapoi"
            dfs_backwards(y);

}

///ideea: cum componentele tare-conexe au un nod final, putem sa parcurgem invers, de la finalul componentei la inceput
///cum ajungem acolo? prin parcurgere dfs obisnuita, obtinand ordinea de parcurgere, apoi pornind invers
///de ce? daca mergem pe un lant in mod obisnuit, trebuie sa vedem si cat putem parcurge din lant, de la coada la cap, iar unde se opreste ->comp tare-con.
int main()
{int x,y;
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        cin>>x>>y;
        a[x].push_back(y);
        inv[y].push_back(x); //memoram si vectorul invers, care retine tatal nodului y
    }

    for (int i=1;i<=n;i++)
        if (viz[i]==0)
            dfs(i); //obtinem vectorul dorit prin dfs

    for (int i=1;i<=n;i++)
        viz[i]=0; //resetam ordinea vizitarii, intrucat toate nodurile sunt acum "gri"/explorate o singura data

    for (int i=n;i>=1;i--)
        if (viz[backwards[i]]==0)
            ct++,dfs_backwards(backwards[i]); //parcurgem acum invers

    cout<<ct<<'\n';    //afisarea nr de regate
    for (int i=1;i<=n;i++)
        cout<<sol[i]<<' '; //afisarea regatului de care apartine planeta

}
