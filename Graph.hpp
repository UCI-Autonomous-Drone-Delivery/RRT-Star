#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdlib.h>
#include <vector>
#include <time.h>
#include <cmath>
#include <iostream>

#include "Constants.hpp"

struct Coord {  //For 2d coordinatses, z=-1
    float x, y ,z;

    Coord()
    {
        x = rand() % 100;
        y = rand() % 100;
        z = rand() % 100;
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

        // Temp Values
        Coord* new_cell_coord;
        new_cell_coord->x = 5;
        new_cell_coord->y = 10;
        new_cell_coord->z = 15;

        coord = new_coord;
        cell_coord = new_cell_coord;
        weight = 200; // Temp value
    }

    Node(int node_num, Coord* new_coord) // Constructor for every other new point
    {
        node_number = node_num;

        // Temp Values
        Coord* new_cell_coord;
        //new_cell_coord.x = 5;
        //new_cell_coord.y = 10;
        //new_cell_coord.z = 15;

        coord = new_coord;
        cell_coord = new_cell_coord;
    }
};

class Graph {   
    int num_nodes; 
    

public:
    Graph(int total_nodes, Coord* coord);
    Coord* getCellCoords(Node* node);
    std::vector<Node*> cells[NUMCELLSX][NUMCELLSY][NUMCELLSZ];
    std::vector <Node*> adj_list;
    void addEdge(int u, int v, float w);
    float findDistance(Coord* coord_src, Coord* coord_dest);
    Node* nearestNode(Coord* random_coord);
    Coord* stepNode(Coord* coord, float step_size);
    void addNode(Node* node);
    void addEdge(Node* node_src, Node* node_dest, float weight);


    //Debugging Functions
    void printCellPop();
    void printGraph();
    void printNode(Node* node);
}; 


#endif
