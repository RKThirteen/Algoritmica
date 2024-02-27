#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

///Kruskal

ifstream f("apm.in");
ofstream g("apm.out");

///structura care retine muchia (x,y) cu costul c
struct elem
{
    int x,y,c;
};

elem v[200001],sol[200001];

int n,m,dim[200001],tata[200001];

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

int main()
{int i,rez=0,k=0;
    f>>n>>m;
    //citire (O(m))
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
            unire(v[i].x,v[i].y); //le unesc-->padure, se adauga costul muchiei la costul total si se adauga muchia in arborele final
            rez+=v[i].c;
            sol[++k]=v[i];
        }
    }///O(m*logn)

    g<<rez<<'\n'<<k<<'\n';
    for (i=1;i<=k;i++) g<<sol[i].x<<' '<<sol[i].y<<'\n';
    return 0;
}
