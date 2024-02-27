#include<bits/stdc++.h>


using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

///retine nodul adiacent si nr muchiei
struct elem
{
    int x,muchie;
};


///Alg Hierzholer-->O(m)

vector<elem>a[100002];
stack<int>st;
int sol[500002],k,p[100002],viz[500002];

int main()
{
    int n,m,i,x,y,l,ok=1;
    f>>n>>m;
    ///a retine nodul adiacent si nr muchiei
    for(i=1;i<=m;i++)
    {
        f>>x>>y;
        a[x].push_back({y,i});
        a[y].push_back({x,i});
    }

    ///graf neorientat==>a[i] trebuie sa aiba nr par de vecini pentru a face parte dintr-un ciclu eulerian
    ///in caz de nr impar, se va omite o muchie in parcurgere
    for(i=1;i<=n;i++)
    if(a[i].size()%2==1)
    {
        ok=0;
        break;
    }
    ///hierzholler: reuniune de cicluri disjuncte(O(m))
    ///daca muchia de la x nu apartine unui ciclu, adauga nodul adiacent pe stiva si marcheaza muchia
    ///p[x]:al catelea nod il viziteaza(grad curent al lui x: grad_initial[x]-p[x])
    if(ok==1)
    {
        st.push(1);
        while(!st.empty())
        {
            x=st.top();

            l=a[x].size();
            //cout<<x<<' '<<p[x]<<' '<<l<<' '<<a[x][p[x]].x<<'\n';
            if(p[x]<l)
            {
                if(viz[a[x][p[x]].muchie]==0)
                {
                    st.push(a[x][p[x]].x);
                    viz[a[x][p[x]].muchie]=1;
                }

                p[x]++;
            }
            else
            {
                sol[++k]=x;
                st.pop();
            }
        }
        for(i=k;i>=2;i--)
            g<<sol[i]<<" ";
    }
    else
        g<<-1;
    return 0;
}
