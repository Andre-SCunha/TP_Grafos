#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <set>

struct Node;
struct Edge;
struct Graph;

//Node
struct Node {
    int id;
    std::list<Edge*> adj;

    Node(int _id) {id = _id};
};

//Edge
struct Edge {
    float w;
    Node* u, v;

    Edge(Node* _u, Node* _v, float _w): u(_u), v(_v), w(_w) {};
};

//Graph
struct Graph {
    int n, m;
    std::vector<Node*> V;
    std::vector<Edge*> E;

    Graph() {};
    Graph(int _n);
    void addEdge(Edge* e);
};
#endif //GRAPH_H