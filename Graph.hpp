#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdlib.h>
#include <vector>
#include <time.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <cuda.h>
typedef std::chrono::high_resolution_clock Clock;

#include "Constants.hpp"

struct Coord {  //For 2d coordinatses, z=-1
    float x, y ,z;

    Coord()
    {
        x = rand() % MAPSIZE;
        y = rand() % MAPSIZE;
        z = rand() % MAPSIZE;
    }

    Coord(float x_new, float y_new, float z_new)
    {
        x = x_new;
        y = y_new;
        z = z_new;
    }
};

//struct Cell {
//    std::vector<Node> contained_nodes;
//};

struct Node {
    int node_number;
    std::vector<Node*> connectedNodes;  //previously node_list
    float weight;
    Coord* coord;
    Coord* cell_coord;
    
    Node() // Base Constructor
    {
        node_number = 0;
        // Temp random coord
        Coord* new_coord;
        new_coord->x = ((float) rand()) / (float) MAPSIZE;
        new_coord->y = ((float) rand()) / (float) MAPSIZE;
        new_coord->z = ((float) rand()) / (float) MAPSIZE;

        coord = new_coord;
        weight = 0; // Temp value
    }

    Node(int node_num, Coord* new_coord) // Constructor for every other new point
    {
        node_number = node_num;
        coord = new_coord;
    }
};

class Graph {   
    int num_nodes; 
    std::vector <Node*> cells[NUMCELLSX][NUMCELLSY][NUMCELLSZ];
    std::vector <Node*> adj_list;
    

public:
    Graph(int total_nodes, Coord* coord);
    Coord* getCellCoords(Node* node);
    Coord* stepNode(Coord* coord, Coord* random_coord, float step_size);
    Node* nearestNode(Coord* random_coord);
    bool checkObstacle(Coord* coord_src, Coord* coord_dest);
    float findDistance(Coord* coord_src, Coord* coord_dest);
    void addNode(Node* node);
    void addEdge(Node* node_src, Node* node_dest, float weight);
    std::vector<Node*> nearestNeighbors(Node* node, float r);
    std::vector<Node*> nearestNeighborsGPU(Node* node, float r);
    //Debugging Functions
    void printCellPop();
    void printGraph();
    void printNode(Node* node);
}; 


#endif
