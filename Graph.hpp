#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdlib.h>
#include <vector>
#include <stack>
#include <list>
#include <time.h>
#include <cmath>
#include <iostream>

#include "Constants.hpp"

struct Coord {
    float x, y, z;

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

struct Node {
    int node_number;
    float weight;
    bool visited;

    Coord* coord;
    Coord* cell_coord;
    Node* parent;

    std::vector<Node*> connectedNodes;  //previously node_list
    
    Node() // Base Constructor
    {
        node_number = 0;
        // Temp random coord
        
        float x = ((float) rand()) / (float) MAPSIZE;
        float y = ((float) rand()) / (float) MAPSIZE;
        float z = ((float) rand()) / (float) MAPSIZE;
        Coord* new_coord = new Coord(x, y, z);

        coord = new_coord;
        weight = 0; // Temp value
        visited = false;
        parent = NULL;

        cell_coord = NULL;
    }

    Node(int node_num, Coord* new_coord) // Constructor for every other new point
    {
        node_number = node_num;
        weight = 0; // Temp value
        coord = new_coord;
        visited = false;
        parent = NULL;

        cell_coord = NULL;
    }

    void printNode() {
        using namespace std;
        cout << "Node: " << node_number << endl;
        cout << "Coord(X,Y,Z) = (" << coord->x << "," << coord->y << "," << coord->z << ")\n";
        if(cell_coord != NULL)
            cout << "Cell (X,Y,Z) = (" << cell_coord->x << "," << cell_coord->y << "," << cell_coord->z << ")\n" << endl;
    }


};

class Graph {   
    int num_nodes; 
    std::vector <Node*> cells[NUMCELLSX][NUMCELLSY][NUMCELLSZ];
    std::vector <Node*> adj_list;
    std::stack<Node*> path;
    

public:
    Graph(int total_nodes, Coord* coord);
    
    // Utility Functions

    Coord* stepNode(Coord* coord, Coord* random_coord, float step_size);
    Node* nearestNode(Coord* random_coord);
    bool checkObstacle(Coord* coord_src, Coord* coord_dest);
    float findDistance(Coord* coord_src, Coord* coord_dest);
    
    std::vector<Node*> nearestNeighbors(Node* new_node, float r);
    
    // Setter Functions
    void addEdge(Node* node_src, Node* node_dest, float weight);
    void addNode(Node* node);
    void addNodeStack(Node* node);

    // Getter Functions
    Coord* getCellCoords(Node* node);
    void getPath();
    std::vector<Node*> getAdjList();

    //Debugging Functions
    void printCellPop();
    void printGraph();
    void printPath();
}; 

#endif
