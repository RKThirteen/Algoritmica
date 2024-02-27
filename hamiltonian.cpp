#include <bits/stdc++.h>
#define INF 2000000000
using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

struct elem
{
    int x,c;
};

vector <elem> a[20];
///dp[i][j]-->costul drumului care se termina in j si contine o multime de noduri reprezentata prin i
///i-->mask pentru noduri, fiecare bit reprezinta nr nodului(ex: nodul 0 e reprezentat de bitul 0)

int dp[262150][20];

///complexitate finala: O(2^n*m)

int main()
{int i,n,m,x,y,z,p=1,l,sol=INF,k,j; //i=stare
    f>>n>>m;
    for (i=1;i<=m;i++)
    {
        f>>x>>y>>z;
        a[x].push_back({y,z});
    }
    //p=2^(n)-1-->toate combinatiile posibile
    for (i=1;i<=n;i++)
    p*=2;
    p--;
    ///setam costul initial al drumurilor ca fiind infinit
    for (i=0;i<=p;i++)
    for (j=0;j<n;j++)
        dp[i][j]=INF;
    ///incepem de la nodul 0, care se termina in el insusi, avand evident costul 0
    dp[1][0]=0;

    ///pe scurt: considerand fiecare combinatie de noduri, se construieste un drum de cost minim
    ///O(2^n*m)
    for (i=0;i<p;i++)
    for (j=0;j<n;j++)
    if(dp[i][j]!=INF)
    {
        l=a[j].size();
        for(k=0;k<l;k++)
        if((i&(1<<a[j][k].x))==0)
            dp[i|(1<<a[j][k].x)][a[j][k].x]=min(dp[i|(1<<a[j][k].x)][a[j][k].x],dp[i][j]+a[j][k].c);
    }
    ///acum cautam ciclul hamiltonian de cost minim
    ///ciclu hamiltonian: ciclu care contine toate nodurile
    for(i=0;i<n;i++)
    if(dp[p][i]!=INF)
    {
        l=a[i].size();
        for(j=0;j<l;j++)
        if(a[i][j].x==0)
            sol=min(sol,dp[p][i]+a[i][j].c);
    }
    if(sol==INF)
        g<<"Nu exista solutie";
    else
        g<<sol;
    return 0;
}
