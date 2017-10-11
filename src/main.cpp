#include <iostream>
#include "Graph.h"
#include <list>
#define MAX(a,b) (((a)>(b))?(a):(b))

using namespace std;

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
        myGraph.addEdge(v.front(), u.front(), w.front());
        v.pop_front(); u.pop_front(); w.pop_front();
    }

//Printing Graph
    cout << myGraph.n << " " << myGraph.m << endl;
    for (int i=0; i<myGraph.n; i++){
        cout << myGraph.V[i]->id;
        for (pEdge e : myGraph.V[i]->adj){
            cout << endl << "\t" << e->w << "," << e->u->id << "," << e->v->id;
        }
        cout << endl;
    }
    return 0;
}