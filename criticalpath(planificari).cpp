#include <bits/stdc++.h>
#define INF 1000000000

using namespace std;

ifstream f("activitati.in");
ofstream g("activitati.out");


struct timp
{
    int st,dr;
};

timp interval[100001];

int n,m,ct=0;
vector <int> v[100001], ciclu,sol_ciclu;
int sol[100001],gr[100001],viz[100001],d[100001],tata[100001],durata[100001];
queue <int> pq,q;
bool final=0;

///Complexitate BFS: O(m)
void bfs() //parcurgere BFS deoarece scapam de toate dependentele de la un curs x la "fii" sai
{int aux,l;
while (!pq.empty()) {aux=pq.front(); //iau primul element din coada si il scot din aceasta pentru utilizare
                    pq.pop();
                    l=v[aux].size();
                    for (int i=0;i<l;i++) //parcurgem toate muchiile de la el la un fiu
                    {
                        gr[v[aux][i]]--; //am invatat cursul 'aux', deci de la cursurile care trebuie rezolvate dupa putem "scapa" de o dependenta
                        if (gr[v[aux][i]]==0) //daca un curs, acum, poate fi invatat(nu mai are dependente)
                        {
                            pq.push(v[aux][i]); //il adaugam in coada pentru ca devine un curs prioritar si il adaugam in vectorul final
                            //cout<<v[aux][i]<<'\n';
                            sol[++ct]=v[aux][i];
                        }

                    }
                    }
}


void dfs_circuit(int x)
{
    //cout<<"DFS"<<' '<<x<<'\n';
    viz[x]=1;
    ciclu.push_back(x); //il retine ca vizitat si il adauga intr-un vector care va arata dependenta circulara
    for (auto y: v[x])
    {

        if (viz[y]==0 && gr[y]>0) //daca un nod adiacent este inclus intr-o dependenta circulara si nu a fost inca vizitat
            dfs_circuit(y);
        else if (viz[y]==1 && final==0) //daca nodul a fost deja vizitat si nu s-a afisat inca dependenta(nu se mai verifica gr[y]>0 pt ca un nod vizitat are indeplinita automat conditia)
        {
            final=1; //se arata ca s-a afisat dependenta

            sol_ciclu.push_back(y); //se adauga in vectorul solutiei
            while (!ciclu.empty()) //cat timp vectorul nu e gol
            {
                int auxx=ciclu.back();
                ciclu.pop_back();
                sol_ciclu.push_back(auxx); //adaugam in vectorul solutie nodul din capatul ciclului si il scoatem din vector
                if (auxx==y)  //in cazul in care ajunge la un nod care nu este x, dar este egal cu capatul ciclului->ciclu mai mic, deci nu mai avem nev de ciclu mare
                    break;
            }
            cout<<'\n';
            ciclu.clear(); //golire pentru a evita alte probleme la executie
        }
    }
    if (!ciclu.empty()) //pop back pt a evita pb la executie
        ciclu.pop_back();
}


///determinarea intervalelor "cursurilor" (O(m))
///e BFS asemanator cu sortarea topologica
void det_interval()
{int aux,l,i;
    while (!q.empty())
    {
        aux=q.front();
        q.pop();
        l=v[aux].size();
        for (i=0;i<l;i++)
        {
            ///daca are mai multe dependente, va incepe dupa ce se termina cel mai lung curs dependent
            interval[v[aux][i]].st=max(interval[v[aux][i]].st,interval[aux].dr);
            gr[v[aux][i]]--;
            ///cand toate cursurile de dinainte s-au terminat, ii fixam capatul dreapta
            if (gr[v[aux][i]]==0)
            {
                q.push(v[aux][i]);
                interval[v[aux][i]].dr=interval[v[aux][i]].st+durata[v[aux][i]];
            }
        }
    }
}

void drum(int s)
{
    if (tata[s]!=0)
        drum(tata[s]);
    g<<s<<' ';
}


int main()
{int i,x,y,dmax=INF*-1,j;
bool ok=1;
    f>>n;
    for (i=1;i<=n;i++)
    {
        f>>durata[i];
        d[i]=INF*-1;
    }
    f>>m;
    for (i=1;i<=m;i++) //citirea datelor (O(m))
    {
        f>>x>>y;
        v[x].push_back(y);
        gr[y]++; //retin gradul INTERN al nodurilor
    }

    ///modificare: adaug d[nod]=durata respectiva si creez o noua coada pentru determinarea intervalelor in cadrul drumurilor critice
    for (i=1;i<=n;i++) ///O(n)
        if (gr[i]==0) //daca gradul intern este 0, este un curs care trebuie completat prima data
        {
            pq.push(i); //deci il adaugam intr-o coada si il adaugam in vectorul final, care reprezinta sortarea topologica
            sol[++ct]=i;
            d[i]=durata[i];
            q.push(i);
        }

    ///sortare topologica
    bfs();

    for (i=1;i<=n;i++) ///O(n)
        if (gr[i]>0) //daca exista vreun curs care mai are dependente(in cazul in care exista circuit, orice element din el nu va putea intra in coada)
        {
            ok=0; //sortare topologica imposibila
            dfs_circuit(i); //ii fac dfs-ul care determina un circuit(punctul b)
            break;

        }

    if (ok==0)
    {
        cout<<"IMPOSSIBLE"<<'\n';
        for (i=sol_ciclu.size()-1;i>0;i--)
            cout<<sol_ciclu[i]<<' '; //afisarea dependentei(punctul b, invers pt ca am adaugat in ordine inversa ciclul)
    }

    ///modificarea: identificarea unui drum critic folosind sortare topologica
    else
    {
        for (i=1;i<=ct;i++)
            cout<<sol[i]<<' ';
        ///determin drumurile critice folosing alg de drumuri minime in DAG-->drumuri maxime in DAG
        //cout<<'\n';
        //pentru fiecare vecin, verific daca exista un drum mai costisitor de la nodul selectat la vecin
        for (i=1;i<=ct;i++)
            for (j=0;j<v[sol[i]].size();j++)
            {
                int aux=sol[i];
                //cout<<aux<<' '<<v[aux][j]<<'\n';
                if (d[v[aux][j]]<d[aux]+durata[v[aux][j]])
                {
                    d[v[aux][j]]=d[aux]+durata[v[aux][j]];
                    tata[v[aux][j]]=aux;
                }
            }

        //cout<<'\n';
        for (i=1;i<=n;i++)
            dmax=max(dmax,d[i]);
        g<<"Timp minim "<<dmax<<'\n';
        g<<"Activitati critice: ";
        for (i=1;i<=n;i++)
            if (d[i]==dmax)
            {
                drum(i);
                break;
            }

        g<<'\n';
        //reconstituirea gradelor pentru salvare de memorie: O(m)
        for (i=1;i<=n;i++)
            for (j=0;j<v[i].size();j++)
                gr[v[i][j]]++;

        //fixam in o(n) cursurile de inceput, care nu au dependenta
        for (i=1;i<=n;i++)
            if (gr[i]==0)
                interval[i].dr=durata[i],interval[i].st=0;
        det_interval();
        for (i=1;i<=n;i++)
            g<<i<<": "<<interval[i].st<<' '<<interval[i].dr<<'\n';
    }


}

