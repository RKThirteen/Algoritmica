#include<bits/stdc++.h>

using namespace std;

int a[1001][1001],n,m,ct;

void fill(int ct,int x, int y)
{

    a[x][y]=ct;//coloram camera
    //verificam daca avem o podea NECOLORATA in directiile:
    if (x-1>=1 && a[x-1][y]==0) //nord
        fill(ct,x-1,y);
    if (x+1<=n && a[x+1][y]==0) //sud
        fill(ct,x+1,y);
    if (y+1<=m && a[x][y+1]==0) //est
        fill(ct,x,y+1);
    if (y-1>=1 && a[x][y-1]==0) //vest
        fill(ct,x,y-1);
}

///idee: cand gasim o bucata de podea, incercam sa mergem catre nord, est, sud, vest pana nu mai putem niciunde, pentru a "colora" camera intreaga
///Complexitate finala: O(n*m) pentru ca odata ce descoperim o camera nu ne mai intoarcem in ea

int main()
{
    int i,j;
    char c;
    bool ok=1;
    cin>>n>>m;
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) //citirea datelor si transformarea matricii
        {
            cin>>c;
            if (c=='.') //punem 0 unde e podea si -1 unde este zid
                a[i][j]=0;
            else
                a[i][j]=-1;
        }
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            if (a[i][j]==0) //daca este podea necolorata, inseamna ca incepe o camera noua
            {
                ct++;
                fill(ct,i,j); //pe care o coloram cu o culoare unica, incrementata inainte
            }
    cout<<ct;
}
