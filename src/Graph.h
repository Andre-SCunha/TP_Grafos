#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <set>

struct Node;
struct Edge;
struct Graph;
typedef Node* pNode;
typedef Edge* pEdge;
typedef Graph* pGraph;

//Node
struct Node {
    int id;
    bool connected;
    std::list<pEdge> adj;

    Node(int _id): id(_id), connected(false) {};
    void addAdj(pEdge e);
};

//Edge
struct Edge {
    float w;
    pNode u, v;

    Edge(pNode _u, pNode _v, float _w): u(_u), v(_v), w(_w) {};
};

//Graph
struct Graph {
    int n, m;
    std::vector<pNode> V;
    std::vector<pEdge> E;

    Graph(int _n);
    void addEdge(int _u, int _v, float _w);
    void print();
};
#endif //GRAPH_H