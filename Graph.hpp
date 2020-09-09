#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <vector>

struct Coord {  //For 2d coordinatses, z=-1
    float x, y ,z;
};

struct Node {
    Coord* coord;
    struct NodeList* connectedNodes;
    float weight;
};

struct NodeList {
    std::vector<Node> list;
}; 





class Graph {   
    int numNodes; 
    struct NodeList* adjList; 

public:
    Graph();
    void addEdge(int u, int v, float w);

}; 


#endif