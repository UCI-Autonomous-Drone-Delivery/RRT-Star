#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdlib.h>
#include <vector>
#include <stack>
#include <list>
#include <time.h>
#include <cmath>
#include <iostream>
#include <assert.h>

#include "Constants.hpp"
#include "Obstacles.hpp"

class Graph {   
    int num_nodes; 

    // true if init 
    // false if goal
    bool init;
    std::vector<Node*> adj_list;

    // For if we return to cells
    //std::vector <Node*> cells[NUMCELLSX][NUMCELLSY][NUMCELLSZ];
public:
    Graph(Node* start_node);
    ~Graph();

    /* Tree functions */

    // Connect two nodes together
    void addEdge(Node* node_src, Node* node_dest, float weight);

    // Rewire node to new parent
    void rewireEdge(Node* node_src, Node* node_dest);

    /**********************************/
    /**********************************/

    // Getter Functions
    
    int getNumNodes();
    bool isInit();
    std::vector<Node*> getAdjList();

    //Coord* getCellCoords(Node* node);

    /**********************************/
    /**********************************/

    //Debugging Functions
    
    void printGraph();
    void printPathSingle();
    void printPathMany();
    //void printCellPop();
}; 

#endif
