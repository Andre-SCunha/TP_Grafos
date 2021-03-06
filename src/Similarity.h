#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <vector>
#include <list>
#include "Graph.h"

using namespace std;

struct NodeInfluence;
struct DistVertex;
struct VertexComp;
struct Similarity;
typedef DistVertex* pDistVertex;

//Influence cell
struct NodeInfluence{
    int id;
    int influence;

    static bool compare (NodeInfluence a, NodeInfluence b);
};

//Dijkstra Vertex
struct DistVertex{
    int id, prev, num_sons, num_paths;
    float dist;
};

//Vertex Comparison
struct VertexComp{
    bool operator() (pDistVertex a, pDistVertex b);
};

//Similarity
struct Similarity{
    int n;
    vector<NodeInfluence> inf;

    Similarity (int _n);
    void SimPathsComp(Graph& G);
    void SortAndPrint(Graph myGraph);

    private:
        void SimDijikstra(Graph& G, int source);
};

#endif //SIMILARITY_H