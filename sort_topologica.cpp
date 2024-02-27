#include <bits/stdc++.h>

using namespace std;

int n,m,ct=0;
vector <int> v[100001],ciclu,sol_ciclu;
int sol[100001],gr[100001],viz[100001];
queue <int> pq;
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


///idee subpunctul b: dupa BFS, orice curs inclus intr-o dependenta circulara va avea gradul intern>0, deci un DFS pe nodurile care au grad intern>0 va duce
///la realizarea unui ciclu in DFS->retinem intr-un vector nodurile parcurse
///nu va merge pe noduri cu grad intern 0, deci nu va intra intr-un lant care are final, care ar strica circuitul
///oricum ar merge pe noduri, va ajunge garantat intr-un punct vizitat anterior, deci mergand inapoi vom gasi un ciclu corect
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

///ideea: primele cursuri studiate sunt cele care nu au niciun alt curs care trebuie invatat inainte, deci nu exista nod catre ele
///deci->parcurgem ordinea prioritatilor de la fiecare curs in parte care are gradul intern 0
///Complexitate finala: O(n+m)


int main()
{int i,x,y;
bool ok=1;
    cin>>n>>m;
    for (i=1;i<=m;i++) //citirea datelor (O(m))
    {
        cin>>x>>y;
        v[x].push_back(y);
        gr[y]++; //retin gradul INTERN al nodurilor
    }

    for (i=1;i<=n;i++) ///O(n)
        if (gr[i]==0) //daca gradul intern este 0, este un curs care trebuie completat prima data
        {
            pq.push(i); //deci il adaugam intr-o coada si il adaugam in vectorul final, care reprezinta sortarea topologica
            sol[++ct]=i;
        }

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

    else
        for (i=1;i<=ct;i++)
            cout<<sol[i]<<' ';

}
