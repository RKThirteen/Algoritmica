#include <bits/stdc++.h>
#define INF 1000000000000000000
using namespace std;

///Idee: matricea de coordonate poate fi asemanata cu un graf complet, deci facem Prim in O(m^2)
///Prea multe submisii puse pana sa vad adevarata greseala...

ifstream f("retea2.in");
ofstream g("retea2.out");

///structura care retine coordonatele punctelor
struct coords
{
    long long x,y;
};

coords bloc[2001],centrala[2001];

long double dist_euclidiana(coords a, coords b)
{
    return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

long double d[2001];
bool viz[2001];


int main()
{long long i,j,k=0,nod_selectat,n,m;
long double sol=0,dmin;
    f>>n>>m;
    for (i=1;i<=n;i++)
        f>>centrala[i].x>>centrala[i].y;
    for (i=1;i<=m;i++)
    {
        f>>bloc[i].x>>bloc[i].y;
        d[i]=INF; //setam distanta minima ca fiind infinit
    }
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            d[j]=min(d[j],dist_euclidiana(centrala[i],bloc[j])); //calculam distanta minima de la un bloc la oricare centrala in O(m*n)
    //Prim: O(m^2)
    while (k<m) //cat timp nu avem toate blocurile in APM
    {
        dmin=INF;
        for (i=1;i<=m;i++) //selectam blocul care e cel mai apropiat de o centrala sau un alt bloc
            if (viz[i]==0 && d[i]<dmin)
            {
                dmin=d[i];
                nod_selectat=i;
            }
        sol+=dmin; //adaugam distanta la solutie si il adaugam in coada finala
        viz[nod_selectat]=1;
        k++;
        for (i=1;i<=m;i++) //actulizam distantele celorlalte blocuri comparand cu distanta optima selectata anterior
            if (viz[i]==0)
                d[i]=min(d[i],dist_euclidiana(bloc[i],bloc[nod_selectat]));
    }
    g<<fixed<<setprecision(8)<<sol;
    return 0;

}
