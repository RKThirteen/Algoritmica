#include <bits/stdc++.h>
#define INF 1000000000
using namespace std;


///structura care retine muchia (x,y) cu costul c
struct elem
{
    int x,y,c;
};

elem v[10001];


int n,m,dim[101],tata[101],q,pmax=-1,muchie[101],k;

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

int kruskall_muchii()
{int sol=0,i;
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
            sol+=v[i].c;
            k++;
            muchie[k]=i;
        }
    }///O(m*logN)
    return sol;
}

int kruskall(int rep)
{int sol=0,i;
//cout<<rep<<' ';
    for (i=1;i<=n;i++) //initial, fiecare nod este o componenta conexa, izolata
    {
        dim[i]=1;
        tata[i]=i;
    }

    for (i=1;i<=m;i++) //pentru fiecare muchie si cat timp nu au fost unite toate nodurile
    {
        if (tata_multime(v[i].x)!=tata_multime(v[i].y) && i!=rep) //daca cele doua noduri din muchie nu formeaza o padure
        {
            unire(v[i].x,v[i].y); //le unesc si construiesc APM-ul
            sol+=v[i].c;
        }
    }///O(m*logN)
    //cout<<sol<<'\n';
    for (i=2;i<=n;i++)
        if (tata_multime(i)!=tata_multime(1))
            return INF;
    return sol;
}

int main()
{int i,rez1,rez2=INF;
    cin>>n>>m;
    for (i=1;i<=m;i++)
        cin>>v[i].x>>v[i].y>>v[i].c;
    sort(v+1,v+m+1,cmp); //sortez muchiile dupa costul lor--->O(mlogm)

    rez1=kruskall_muchii(); //APM
    for (i=1;i<=k;i++)
        rez2=min(rez2,kruskall(muchie[i]));

    cout<<rez1<<' '<<rez2;
    return 0;
}
