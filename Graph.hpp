#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Constants.hpp"

struct Coord {  //For 2d coordinates, z=-1
    float x, y ,z;
};

struct Node {
    Coord* coord;
    struct NodeList* connectedNodes;
    float weight;
};

struct NodeList {
    std::vector<Node*> list;
}; 

//Can we just replace cells with NodeList??
struct Cell {
    std::vector<Node*> containedNodes;
};


class Graph {   
    public:
        Graph(Coord* startCoord);
        void addEdge(Node* startNode, Node* endNode, float weight);
        Coord* getCellCoords(Node* node);

    private:
        int numNodes; 
        std::vector<Node*> adjList;
        //3d vector of cells below
        Cell* cells[NUMCELLSX][NUMCELLSY][NUMCELLSZ];
}; 


#endif