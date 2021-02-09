#ifndef RRTSTAR_HPP
#define RRTSTAR_HPP

#include "Graph.hpp"

class BiRRTStar {
	bool* found_path;
	Obstacles* obs;

    // Single Query // RRT is a single query path planner
    Node* start_node;
    Node* end_node;

    // Multi Query  // We might need to look into multi query algorithms eg. PRM
                    // ours is idk what ours is lol right now
    std::vector<Node*> start_nodes;
    std::vector<Node*> end_nodes;

    std::vector<Node*> path_single;

    /**********************************/
    /**********************************/
public:
    BiRRTStar(Coord start_coord, Coord end_coord);

    std::vector<Node*> CallRRTStar();

    /* Utility Functions */

    // add Obstacles
    void addObstacles(Obstacles* o);

    // Returns true if all paths are found
    bool allTrue();

    // Returns Coord stepsize away from nearest_node coord
    Coord stepNode(Coord* coord, Coord* random_coord);

    // Finds node closest to the coord
    Node* nearestNode(Coord* random_coord, Graph* graph);

    // Returns vector of nodes closest to node in radius r
    std::vector<Node*> nearestNeighbors(Node* new_node, Graph* graph);

    // Choose best parent with least cost from neighbors
    Node* chooseBestParent(Node* new_node, std::vector<Node*> neighbors);

    // Connect
    void connect(Node* node_src, Node* node_dest, Graph* graph);

    // Returns true if coord is in goal radius
    bool inGoalRadiusSingle(Coord* node_coord);
    bool inGoalRadiusMany(Coord* node_coord, int number);

    // Generates final path if path is found
    void generatePathSingle(Node* final_node);
    std::vector<Node*> makePath(Node* node);
    void generatePathMany(Node* final_node, int number);


    /**********************************/
    /**********************************/

    // Getter Functions

    // Returns path found if a path is found
    std::vector<Node*> getPath();
    std::vector<Node*> getPathMany(int number);
    bool isPathFound(int path_number);

    void printPathSingle();
    void printPathMany();

    /**********************************/
    /**********************************/
};

Graph* rrtStarSingle(Coord homeCoord, Coord endCoord);
Graph* rrtStarMany(std::vector<Coord> start_coords, std::vector<Coord> end_coords);

#endif