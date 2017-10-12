#include <iostream>
#include "Graph.h"
#include <list>
#include <algorithm>
#include <set>
#include <vector>
#include <limits>
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
    list<int> v, u, w;
    int _v, _u, _w, max = 0, aux, m = 0;
    char eater;
    cin >>_v >> eater >> _u >> eater >> _w;
    while ((_v!=0) || (_u!=0) || (_w!=0)){
        v.push_back(_v);
        u.push_back(_u);
        w.push_back(_w);
        m++;

        aux = MAX(_v,_u);
        max = MAX(max,aux);
        cin >>_v >> eater >> _u >> eater >> _w;
    }
//Making Graph
    Graph myGraph(max+1);

    for (int i = 0; i < m; i++){
        myGraph.addEdge(v.front(), u.front(), 100-w.front());
        v.pop_front(); u.pop_front(); w.pop_front();
    }

//Testing SimDij

    vector<Pair> inf(myGraph.n);
    for (int i = 0; i < myGraph.n; i++){
        inf[i].id = i;
        inf[i].influence = 0;
    }

    for (int i = 0; i < myGraph.n; i++){
        if(myGraph.V[i]->connected)
            simDij(myGraph, i, inf);
    }

    sort(inf.begin(), inf.end(), Pair::compare);
    for (auto i: inf)
        if(myGraph.V[i.id]->connected)
            cout << i.id << ':' << i.influence << ",";
    cout << endl;

    return 0;
}

void simDij(Graph& G, int source, vector<Pair> &inf){

    struct SimVertex
    {
        int id, prev;
        float dist;
    };
    struct pVertexComp
    {
        bool operator() (SimVertex* a, SimVertex* b){
            if(a->dist==b->dist)
                return a->id < b->id;
            return a->dist < b->dist;
        }
    };
    set<SimVertex*, pVertexComp> distanceQ;
    vector<SimVertex> nodes(G.n);
    SimVertex* first;
    int v, dest_id, dest_dist;
    float aux =  std::numeric_limits<float>::infinity();

    for (int i = 0; i < G.n; i++){
        if (i!=source){
            nodes[i].id = i;
            nodes[i].dist = aux;
            nodes[i].prev = -1;
        } else{
            nodes[i].id = i;
            nodes[i].dist = 0;
            nodes[i].prev = -1;
        }
        distanceQ.insert(distanceQ.end(), &nodes[i]);
    }

//Dijkstra
    while(!distanceQ.empty()){
    //Finding min dist element
        first = *distanceQ.begin();
        dest_id = first->id;
        dest_dist = first->dist;
    //Removing from the "not reached yet"
        distanceQ.erase(distanceQ.begin());
    //Updating neighbors best similarity
        for (pEdge e : G.V[dest_id]->adj){
        //Getting neighbor id
            v = (e->u->id == dest_id)?e->v->id:e->u->id;
        //If element still in Q
            set<SimVertex*, pVertexComp>::iterator nei = distanceQ.find(&nodes[v]);
            if(nei != distanceQ.end()){
                aux = dest_dist + e->w;
            //Updating distanceQ and node.dist
                if(aux < nodes[v].dist){
                //Removing from set
                    distanceQ.erase(nei);
                //Updating values
                    nodes[v].dist = aux;
                    nodes[v].prev = dest_id;
                //Re-Inserting on set
                    distanceQ.insert(&nodes[v]);
                }
            }
        }
    }

//Paths computation
    for (int i = 0; i < G.n; i++){
        if(G.V[i]->connected){
            int j = i;
            while (j != source){
                inf[j].influence++;
                j = nodes[j].prev;
            }
            inf[source].influence++;
        }
    }

}