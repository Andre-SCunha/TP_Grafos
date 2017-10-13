#include <iostream>
#include "Graph.h"
#include "Similarity.h"
#include <list>
#define MAX(a,b) (((a)>(b))?(a):(b))

using namespace std;

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
//Calculating similarity paths and sorting the most influential nodes
    Similarity Sim(myGraph.n);
    Sim.SimPathsComp(myGraph);
    Sim.SortAndPrint(myGraph);

    return 0;
}