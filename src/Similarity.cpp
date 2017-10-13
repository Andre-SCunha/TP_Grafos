#include "Similarity.h"
#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;

//Influence
bool NodeInfluence::compare (NodeInfluence a, NodeInfluence b){

    if(a.influence==b.influence)
        return a.id<b.id;
    return a.influence>b.influence;

}

//Vertex Comparison
bool VertexComp::operator() (pDistVertex a, pDistVertex b){

    if(a->dist==b->dist)
        return a->id < b->id;
    return a->dist < b->dist;

}

//Similarity
Similarity::Similarity (int _n): n(_n), inf(_n){

    for (int i = 0; i < n; i++){
        inf[i].id = i;
        inf[i].influence = 0;
    }

}

void Similarity::SimPathsComp(Graph& G){

    for (int i = 0; i < n; i++)
        SimDijikstra(G, i);

}

void Similarity::SimDijikstra(Graph& G, int source){

    //Check if node has edges
    if(!G.V[source]->connected)
        return;
        
    //Structures
    set<pDistVertex, VertexComp> distanceQ;
    vector<DistVertex> nodes(G.n);
    pDistVertex first;
    int v, dest_id, dest_dist;
    float aux =  std::numeric_limits<float>::infinity();

    for (int i = 0; i < G.n; i++){
        nodes[i].id = i;
        nodes[i].dist = (i!=source)?aux:0;
        nodes[i].prev = -1;
        nodes[i].num_sons = 0;
        nodes[i].num_paths = 1;
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

        //Updating min_tree
        if(dest_id!=source)
            nodes[nodes[dest_id].prev].num_sons ++;

        //Updating neighbours best similarity path
        for (pEdge e : G.V[dest_id]->adj){
            //Getting neighbour id
            v = (e->u->id == dest_id)?e->v->id:e->u->id;
            //If element still in Q
            set<pDistVertex, VertexComp>::iterator nei = distanceQ.find(&nodes[v]);
            if(nei != distanceQ.end()){
                aux = dest_dist + e->w;
                //Updating distanceQ and node distance
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

    //Nodes influence computation
    list<int> queue;

    //Queueing leaf nodes
    for (int i = 0; i < G.n; i++)
        if(G.V[i]->connected && nodes[i].num_sons == 0)
            queue.push_back(i);

    //Paths computation
    while (!queue.empty()){
        int n = queue.front();
        if(n != source){
            nodes[nodes[n].prev].num_paths += nodes[n].num_paths;
            nodes[nodes[n].prev].num_sons --;
            if(nodes[nodes[n].prev].num_sons == 0)
                queue.push_back(nodes[n].prev);
        }
        inf[n].influence += nodes[n].num_paths;
        queue.pop_front();
    }

}


void Similarity::SortAndPrint(Graph myGraph){

    sort(inf.begin(), inf.end(), NodeInfluence::compare);
    int j = 0;
    while(!myGraph.V[inf[j].id]->connected)
        j++;
    cout << inf[j].id;
    for (int i = j+1; i < n; i ++)
        if(myGraph.V[inf[i].id]->connected)
            cout << ","<< inf[i].id;
    cout << endl;

}