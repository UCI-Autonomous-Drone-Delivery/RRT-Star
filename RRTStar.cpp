#include "RRTStar.hpp"
#include "Graph.hpp"

Graph rrtStar(Coord* startingCoord, Coord* goalCoord) { // Right now its RRT

	// Randomize each run
	srand(time(NULL));

	// Creating the start of graph
	Graph graph(NUMNODES, startingCoord);

	int i = 1;
	while (i <= NUMNODES) {
		Coord* random_coord = new Coord();	// Random Position
		Node* nearest_node = graph.nearestNode(random_coord); // Nearest Node from the random point

		// STILL NEED TO FINISH CHECKOBSTACLE
		if (graph.checkObstacle(nearest_node->coord, random_coord)) { // If obstacle is in between two nodes return true
			continue;
		}

		// Creating coordinate and node step size away from the nearest coord
		Coord* step = graph.stepNode(nearest_node->coord, random_coord, STEPSIZE);
		if (graph.findDistance(nearest_node->coord, step) > graph.findDistance(nearest_node->coord, random_coord)) {
			continue;
		}

		Node* new_node = new Node(i, step);
		float cost = graph.findDistance(nearest_node->coord, new_node->coord);

		graph.addNode(new_node);
		graph.addEdge(nearest_node, new_node, cost);
		//std::vector<Node*> neighbors = graph.nearestNeighbors(new_node, RADIUS);


		//// FOR RRT*
		//for (auto& node_neighbor : neighbors) {
		//	std::cout << "Node Neighbor is: " << node_neighbor->node_number << endl;
		//	float dist = graph.findDistance(new_node->coord, node_neighbor->coord);
		//	float cost_new = dist;
		//	std::cout << "Distance between neighbor = " << dist << std::cout.precision() << endl;
		//	std::cout << "Optimized Cost = " << cost_new << std::cout.precision() << endl;
		//	std::cout << "Original Cost = " << new_node->weight << endl;
		//	if ( cost_new < new_node->weight) {

		//		std::cout << "Optimizing!" << endl;
		//		graph.addEdge(
		//			node_neighbor,
		//			new_node,
		//			cost_new
		//		);
		//	}

		//}

		// Check if node found goal
		float nodeDistanceFromGoal = graph.findDistance(new_node->coord, goalCoord);
		if (nodeDistanceFromGoal < GOALRADIUS) {
			std::cout << "Node that found Goal: " << new_node->node_number << std::endl;
			graph.addNodeStack(new_node);
			graph.getPath();
			break;
		}
		i++;
	}

	return graph;
}
