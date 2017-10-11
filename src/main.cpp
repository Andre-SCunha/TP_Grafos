#include <iostream>
#include "Graph.h"
#include <list>
#include <algorithm>
#include <set>
#include <vector>
#define MAX(a,b) (((a)>(b))?(a):(b))

using namespace std;
struct Pair
{
    int id;
    int influence;

    static bool compare (Pair a, Pair b){
        if(a.influence==b.influence)
            return a.id<b.id;
        return a.influence>b.influence;};
    };
void simDij(Graph& G, int source, vector<Pair> &inf);

int main(){

//Reading input
    list<int> v, u;
    int _v, _u, max = 0, aux, m = 0;
    list<float> w;
    float _w;
    char c;
    cin >>_v >> c >> _u >> c >> _w;
    while (_v!=0 || _u!=0 || _w!=0){
        v.push_back(_v);
        u.push_back(_u);
        w.push_back(_w);
        m++;

        aux = MAX(_v,_u);
        max = MAX(max,aux);
        cin >>_v >> c >> _u >> c >> _w;
    }

//Making Graph
    Graph myGraph(max+1);

    for (int i = 0; i < m; i++){
        myGraph.addEdge(v.front(), u.front(), w.front()/100);
        v.pop_front(); u.pop_front(); w.pop_front();
    }

//Testing SimDij

    vector<Pair> inf(myGraph.n);
    for (int i = 0; i < myGraph.n; i++){
        inf[i].id = i;
        inf[i].influence = 0;
    }
    for (int i = 0; i < myGraph.n; i++){
        simDij(myGraph, i, inf);
    }
    sort(inf.begin(), inf.end(), Pair::compare);
    for (auto i: inf)
        cout << i.id << ',';
    cout << "\b\n" << endl;

//Printing Graph
/*    cout << myGraph.n << " " << myGraph.m << endl;
    for (int i=0; i<myGraph.n; i++){
        cout << myGraph.V[i]->id;
        for (pEdge e : myGraph.V[i]->adj){
            cout << endl << "\t" << e->w << "," << e->u->id << "," << e->v->id;
        }
        cout << endl;
    }*/

    return 0;
}

void simDij(Graph& G, int source, vector<Pair> &inf){

    set<int> Q;
    vector<float> dist(G.n), prev(G.n);
    int max, v;
    float aux;

    for (int i = 0; i < G.n; i++){
        dist[i] = -1;
        prev[i] = -1;
        Q.insert(Q.end(), i);
    }

    dist[source] = 1;

//Modified Dijkstra
    while(!Q.empty()){
    //Finding max dist element
        max = *Q.begin();
        for (set<int>::iterator it=Q.begin(); it!=Q.end(); ++it){
            if(dist[*it] > dist[max])
                max = *it;
        }
    //Removing from the "not reached yet"
        Q.erase(max);
    //Updating neighbors best similarity
        for (pEdge e : G.V[max]->adj){
            v = (e->u->id == max)?e->v->id:e->u->id;
        //If element still in Q
            if(Q.find(v) != Q.end()){
                aux = dist[max] * e->w;
                if(aux > dist[v]){
                    dist[v] = aux;
                    prev[v] = max;
                }
            }
        }
    }

//Printing Solution
    for (int i = 0; i < G.n; i++){
        int j = i;
        while (j != source){
            inf[j].influence++;//cout << j << " ";
            j = prev[j];
        }
        inf[source].influence++;//cout << source << endl;
    }

}