#include <bits/stdc++.h>

using namespace std;

ifstream f("apm2.in");
ofstream g("apm2.out");

///Idee: Cand adaugam o muchie noua, se inchide un ciclu, deci noi ar trebui sa eliminam muchia cea mai scumpa si sa aplicam
///pretul ei -1 muchiei. Asadar cautam muchia cea mai scumpa din ciclu prin dfs dupa crearea APM-ului

///structura care retine muchia (x,y) cu costul c
struct elem
{
    int x,y,c;
};

elem v[100001];
///arb-->APM-ul finalizat, de forma (x,y) cu costul c
vector <pair<int,int>> arb[10001];

int n,m,dim[100001],tata[100001],q,pmax=-1,maxim[100001];

///functia care realizeaza sortarea crescatoare dupa cost
inline bool cmp(const elem &a, const elem &b)
{
    return a.c<b.c;
}

///returneaza "tatal" unei paduri in O(logN)
int tata_multime(int x)
{
    if (x!=tata[x])
        x=tata_multime(tata[x]);
    return tata[x];
}


///uneste doua paduri intre ele in O(logN) dat de tata_multime
void unire(int x, int y)
{
    x=tata_multime(x); //cauta tatii ambelor multimi
    y=tata_multime(y);
    if (dim[y]>dim[x]) //uneste padurea mai mica de padurea mai mare, tatal padurii nou-formate devenind tatal padurii mari
    {
        tata[x]=y;
        dim[y]+=dim[x];
    }
    else
    {
        tata[y]=x;
        dim[x]+=dim[y];
    }
}

void dfs(int x, int tata, int y)
{
    //daca ajunge la final, atunci salvam valoarea maximului
    if (x==y)
        pmax=maxim[x];
    for (auto fiu: arb[x]) //parcurge fiecare fiu
        if (fiu.first!=tata)
        {
           maxim[fiu.first]=maxim[x]; //pentru a nu avea conflict cu prima parcurgere

           if (fiu.second>maxim[fiu.first]) //salvam costul maxim
                maxim[fiu.first]=fiu.second;
           dfs(fiu.first,x,y);
        }
}
///O(k*n)
int main()
{int i,k=0,x,y;
    f>>n>>m>>q;
    for (i=1;i<=m;i++)
        f>>v[i].x>>v[i].y>>v[i].c;
    sort(v+1,v+m+1,cmp); //sortez muchiile dupa costul lor--->O(mlogm)
    for (i=1;i<=n;i++) //initial, fiecare nod este o componenta conexa, izolata
    {
        dim[i]=1;
        tata[i]=i;
    }
    for (i=1;i<=m && k<n;i++) //pentru fiecare muchie si cat timp nu au fost unite toate nodurile
    {
        if (tata_multime(v[i].x)!=tata_multime(v[i].y)) //daca cele doua noduri din muchie nu formeaza o padure
        {
            unire(v[i].x,v[i].y); //le unesc si construiesc APM-ul
            arb[v[i].x].push_back({v[i].y,v[i].c});
            arb[v[i].y].push_back({v[i].x,v[i].c});
        }
    }///O(m*log^2N)

    for (i=1;i<=q;i++) //pentru fiecare drum, reinitializam costul maxim al drumului pornind din x si incepem parcurgerea dfs
    {
        f>>x>>y;
        maxim[x]=0;
        dfs(x,0,y);
        g<<pmax-1<<'\n';
    }
    return 0;
}
