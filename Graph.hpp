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
    bool* found_path;

    Obstacles* obs;

    // Single Query // RRT is a single query path planner
    Node* start_node;
    Node* end_node;

    // Multi Query  // We might need to look into multi query algorithms eg. PRM
                    // ours is idk what ours is lol right now
    std::vector<Node*> start_nodes;
    std::vector<Node*> end_nodes;

    std::vector<Node*> adj_list;

    std::vector<Node*> path_single;
    std::vector<std::vector<Node*>> path_many;
    // For if we return to cells
    //std::vector <Node*> cells[NUMCELLSX][NUMCELLSY][NUMCELLSZ];
public:
    Graph(Coord start_coord);
    Graph(Coord start, Coord end);
    Graph(std::vector<Coord>start_coords, std::vector<Coord> end_coords);
    ~Graph();

    /**********************************/
    /**********************************/

    /* Utility Functions */

    // add Obstacles
    void addObstacles(Obstacles* o);

    // Connect
    void connect(Node* node_src, Node* node_dest, Graph* ga);

    // Finds distance between two nodes
    float findDistance(Coord* coord_src, Coord* coord_dest);

    // Returns Coord stepsize away from nearest_node coord
    Coord stepNode(Coord* coord, Coord* random_coord, float step_size);

    // Finds node closest to the coord
    Node* nearestNode(Coord* random_coord);
    
    // Returns vector of nodes closest to node in radius r
    std::vector<Node*> nearestNeighbors(Node* new_node, float r);

    // Returns true if all paths are found
    bool allTrue();

    // Returns true if coord is in goal radius
    bool inGoalRadiusSingle(Coord* node_coord);
    bool inGoalRadiusMany(Coord* node_coord, int number);

    // Generates final path if path is found
    void generatePathSingle(Node* final_node);
    void generatePathMany(Node* final_node, int number);

    /**********************************/
    /**********************************/

    /* Tree functions */

    // Connect two nodes together
    void addEdge(Node* node_src, Node* node_dest, float weight);

    // Rewire node to new parent
    void rewireEdge(Node* node_src, Node* node_dest, float weight);

    // Calls addEdge and adds distance between two nodes to the total weight
    void addToGraph(Node* node_src, Node* node_dest);

    /**********************************/
    /**********************************/

    // Getter Functions
    
    // Returns path found if a path is found
    std::vector<Node*> getPath();
    int getNumNodes();
    bool isPathFound(int path_number);
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
