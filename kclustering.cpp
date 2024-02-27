#include <bits/stdc++.h>

using namespace std;

///ideea de baza: construim graful complet cu nodurile fiind cuvinte, iar muchiile fiind distantele Levehnstein dintre cuvinte(O(n^2)), unde n=nr. cuv
///Apoi aplicam APM pana cand avem k clase(Kruskall-->O(m*logN)
///Cplx. Finala: O(m*logN) (m=n*(n-1)/2)

ifstream f("cuvinte.in");
ofstream g("cuvinte.out");

char cuv[1001][1001];
int tata[1001],dim[1001];
int dp[101][101];

struct elem
{
    int x,y,c;
};

elem v[1001];

inline bool cmp(const elem &a, const elem &b)
{
    return a.c<b.c;
}

///returneaza "tatal" unei paduri in O(logN)
int tata_multime(int x)
{
    if (x!=tata[x])
        tata[x]=tata_multime(tata[x]);
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

//Distanta levenstein folosind programare dinamica
int lev(string a,string b)
{int i,j;
//initializare
int n=a.size(),m=b.size();
    for (i=1;i<=n;i++)
        dp[i][0]=i;
    for (j=1;j<=m;j++)
        dp[0][j]=j;
//recurenta
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            if (a[i-1]==b[j-1])
                dp[i][j]=dp[i-1][j-1];
            else
                dp[i][j]=min(dp[i][j-1],min(dp[i-1][j],dp[i-1][j-1]))+1;
//solutie
    return dp[n][m];
}

int main()
{int k,n,m=0,i,j;
char c[1001];
    cin>>k;
    while (f>>c) //citim cuvantul si initializam nodul sau ca la kruskall
    {
        n++;
        strcpy(cuv[n],c);
        tata[n]=n;
        dim[n]=1;
    }
    //construim graful complet ponderat
    for (i=1;i<n;i++)
    {
         for(j=i+1;j<=n;j++)
        {
            m++;
            v[m].x=i;
            v[m].y=j;
            v[m].c=lev(cuv[i],cuv[j]);
            //cout<<v[m].c<<' ';
        }
        //cout<<'\n';
    }
    //cout<<m<<'\n';
    sort(v+1,v+m+1,cmp); //sortez muchiile dupa costul lor--->O(mlogm)
    for (i=1;i<=m && k<n;i++) //pentru fiecare muchie si cat timp nu avem k clustere(facem n-k pasi)
    {
        if (tata_multime(v[i].x)!=tata_multime(v[i].y)) //daca cele doua noduri din muchie nu formeaza o padure
        {
            unire(v[i].x,v[i].y); //le unesc si construiesc clusterele
            k++;
            //cout<<v[i].c<<' ';
        }
    }///O(m*logN)
    //uniformizez clusterele
    for (i=1;i<=n;i++)
        tata[i]=tata_multime(i),cout<<tata_multime(i)<<' ';

    k=0;
    int aux=-1;
    //afisarea clusterelor: iau cate un grup cu acelasi reprez, il afisez, apoi trec la urmatorul
    while (k<n) //O(n*k)-->cel mai rau O(n^2)-->nu e mai mare decat complexitatea finala data de Kruskall
    {
        i=1;
        aux=0;
        while (tata[i]==0 && i<=n)
            i++;
        aux=tata[i];
        while (i<=n)
        {
            if (tata[i]==aux)
                g<<cuv[i]<<' ',tata[i]=0,k++;
            i++;
        }
        g<<'\n';
    }
    //urmatoarea muchie care ar fi trebuit adaugata va reprezenta gradul de separare maxim
    ///de ce? pt ca ea uneste 2 clustere, luand muchia cea mai "ieftina", iar gradul de separare maxim este distanta MINIMA
    if (k==1)
        g<<0; //o singura clasa
    else
        g<<v[i].c;
}
