#include <bits/stdc++.h>

using namespace std;

ifstream f("lcs.in");
ofstream g("lcs.out");

int dp[1025][1025];
char a[1025],b[1025],sol[1025];


///LCS: dp[i][j]=cate caractere sunt egale pana la pozitia i a stringului a si pozitia j a stringului b
///Vedem unde sunt caracterele egale si actualizam dp[i][j] accordingly
///dp[i][j]=1+dp[i-1][j-1] daca a[i]==b[j]
///altfel cautam maximul dintre dp[i-1][j] si dp[i][j-1](ca vom merge cu el in continuare)
///Complexitate: O(n*m)

int main()
{int n,m,i=0,j=0,k,x=0;
char c;
    f.getline(a,1025);
    f.getline(b,1025);
    n=strlen(a);
    m=strlen(b);
    ///fac a.i sirurile sa inceapa de la 1, nu de la 0
    for (i=n;i>=1;i--)
    {
        a[i]=a[i-1];
    }

    for (i=m;i>=1;i--)
    {
        b[i]=b[i-1];
    }
    ///determinam nr maxim de caractere egale din ambele subsiruri
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            if (a[i]==b[j])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);

    cout<<dp[n][m]<<'\n';
    ///reconstituire: cand gasim pozitii in care caracterele sunt egale, adaugam caracterul in stringul solutie
    k=dp[n][m];
    i=n;
    j=m;
    while (k>0 && (i>0 || j>0))
    {
        if (a[i]==b[j])
        {
            k--;
            sol[++x]=a[i];
            i--;
            j--;
        }
        else
            if (dp[i-1][j]>dp[i][j-1])
                i--;
            else
                j--;
    }
    for (i=x;i>=1;i--)
        g<<sol[i];
}
