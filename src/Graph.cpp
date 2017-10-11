#include <vector>
#include <list>
#include <set>
#include "Graph.h"

//Node
void Node::addAdj(pEdge e){

    adj.push_back(e);
    connected = true;

}

//Graph
Graph::Graph(int _n): m(0), n(_n){

    for(int i = 0; i < n; i++){
        V.push_back(new Node(i));
    }

}

void Graph::addEdge(int _u, int _v, float _w){

    m++;
    E.push_back(new Edge(V[_u], V[_v], _w));

    V[_u]->addAdj(E.back());
    V[_v]->addAdj(E.back());

}