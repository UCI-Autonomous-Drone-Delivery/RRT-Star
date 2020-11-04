#include "RRTStar.hpp"
#include "Graph.hpp"

Graph* rrtStar(Coord* startingCoord, Coord* goalCoord) {
	// Creating the start of graph
	Graph* graph = new Graph(NUMNODES, startingCoord);

	int i = 1;
	while (i < NUMNODES) {

		Coord* random_coord = new Coord();	// Random Position
		Node* nearest_node = graph->nearestNode(random_coord); // Nearest Node from the random point

		// STILL NEED TO FINISH CHECKOBSTACLE
		if (graph->checkObstacle(nearest_node->coord, random_coord)) { // If obstacle is in between two nodes return true
			delete random_coord;
			continue;
		}

		// Creating coordinate and node step size away from the nearest coord
		Coord* step = graph->stepNode(nearest_node->coord, random_coord, STEPSIZE);
		if (graph->findDistance(nearest_node->coord, step) > graph->findDistance(nearest_node->coord, random_coord)) {
			delete step;
			delete random_coord;
			continue;
		}

		Node* new_node = new Node(i, step);
		graph->addToGraph(nearest_node, new_node);
		std::vector<Node*> neighbors = graph->nearestNeighbors(new_node, RADIUS);


		//// FOR RRT*
		for (auto& node_neighbor : neighbors) {
			//std::cout << "Node Neighbor is: " << node_neighbor->node_number << std::endl;
			//node_neighbor->coord->printCoord();
			float cost_new = graph->findDistance(new_node->coord, node_neighbor->coord);
			//std::cout << "New Cost = " << cost_new + node_neighbor->weight << std::endl;
			//std::cout << "Original Cost = " << new_node->weight << std::endl;
			if (cost_new + node_neighbor->weight < new_node->weight) {

				//std::cout << "Optimizing!" << std::endl;
				graph->removeEdge(new_node->parent, new_node);
				graph->addEdge(
					node_neighbor,
					new_node,
					cost_new
				);
			}
			//std::cout << std::endl;
		}
			
		delete random_coord;

		// Check if node found goal
		float nodeDistanceFromGoal = graph->findDistance(new_node->coord, goalCoord);
		if (nodeDistanceFromGoal < GOALRADIUS) {
			std::cout << "Node that found Goal: " << new_node->node_number << std::endl;
			Node* goal_node = new Node(i + 1, goalCoord);
			graph->addToGraph(new_node, goal_node);
			graph->addNodeStack(goal_node);
			graph->addNodeStack(new_node);
			graph->setPath();
			return graph;
		}
		i++;
	}
	std::cout << "Goal was not found" << std::endl;
	delete graph;
	delete goalCoord;
		
	// Return NULL if no path found
	return NULL;
}