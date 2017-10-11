#include <iostream>
#include "Graph.h"
#define MAX(a,b) (((a)>(b))?(a):(b))

using namespace std;

int main(){

    Graph myGraph(10);
    cout << myGraph.n << " " << myGraph.m << endl;
    myGraph.addEdge(0,1,0);
    myGraph.addEdge(9,1,7);
    myGraph.addEdge(2,5,6);
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