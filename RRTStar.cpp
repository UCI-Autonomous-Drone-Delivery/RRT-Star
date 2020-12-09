#include "RRTStar.hpp"
#include "Graph.hpp"



Graph* rrtStar(Coord homeCoord, Coord endCoord) {
	//Initializes obstacles here
	Coord* ful = new Coord(50, 50, 75);
	Coord* fur = new Coord(75, 50, 75);
	Coord* fdl = new Coord(50, 50, 50);
	Coord* fdr = new Coord(75, 50, 50);
	Coord* bul = new Coord(50, 75, 75);
	Coord* bur = new Coord(75, 75, 75);
	Coord* bdl = new Coord(50, 75, 50);
	Coord* bdr = new Coord(75, 75, 50);

	Obstacles o = Obstacles(MAPMINX,MAPMINY,MAPMINZ,MAPMAXX,MAPMAXY,MAPMAXZ);

	// Creating the start of graph
	Coord startingCoord = Coord(homeCoord.x, homeCoord.y, homeCoord.z);
	Coord goalCoord = Coord(endCoord.x, endCoord.y, endCoord.z);
	Graph* graph = new Graph(NUMNODES, startingCoord);

	int i = 1;
	while (i < NUMNODES + 1) {

		Coord random_coord = Coord();	// Random Position
		Node* nearest_node = graph->nearestNode(&random_coord); // Nearest Node from the random point

		// STILL NEED TO FINISH CHECKOBSTACLE
		//if (o.collisionCheck(nearest_node->coord, &random_coord)) { // If obstacle is in between two nodes return true
		//	std::cout << "collision here!\n";
		//	nearest_node->printNode();
		//	random_coord.printCoord();
		//	continue;
		//}

		// Creating coordinate and node step size away from the nearest coord
		Coord step = graph->stepNode(nearest_node->coord, &random_coord, STEPSIZE);
		if (graph->findDistance(nearest_node->coord, &step) > graph->findDistance(nearest_node->coord, &random_coord)) {
			continue;
		}

		Node* new_node = new Node(i, step);
		graph->addToGraph(nearest_node, new_node);
		std::vector<Node*> neighbors = graph->nearestNeighbors(new_node, RADIUS);


		//// FOR RRT*
		for (auto& node_neighbor : neighbors) {
			float cost_new = graph->findDistance(new_node->coord, node_neighbor->coord);
			if (cost_new + node_neighbor->weight < new_node->weight) {
				graph->removeEdge(new_node->parent, new_node);
				graph->addEdge(
					node_neighbor,
					new_node,
					cost_new
				);
			}
		}

		// Check if node found goal
		float nodeDistanceFromGoal = graph->findDistance(new_node->coord, &goalCoord);
		if (nodeDistanceFromGoal < GOALRADIUS) {
			std::cout << "Node that found Goal: " << new_node->node_number << std::endl;
			Node* goal_node = new Node(i + 1, goalCoord);
			graph->addToGraph(new_node, goal_node);
			graph->addNodeStack(goal_node, 0);
			graph->addNodeStack(new_node, 0);
			graph->setPath(0);
			return graph;
		}
		i++;
	}
	std::cout << "Goal was not found" << std::endl;
	delete graph;
		
	// Return NULL if no path found
	return NULL;
}

Graph* rrtStar(std::vector<Coord> homeCoords, std::vector<Coord> endCoords) {

	Coord* ful = new Coord(50, 50, 75);
	Coord* fur = new Coord(75, 50, 75);
	Coord* fdl = new Coord(50, 50, 50);
	Coord* fdr = new Coord(75, 50, 50);
	Coord* bul = new Coord(50, 75, 75);
	Coord* bur = new Coord(75, 75, 75);
	Coord* bdl = new Coord(50, 75, 50);
	Coord* bdr = new Coord(75, 75, 50);

	Obstacles o = Obstacles(MAPMINX, MAPMINY, MAPMINZ, MAPMAXX, MAPMAXY, MAPMAXZ);

	// Creating the start of graph
	Graph* graph = new Graph(NUMNODES, homeCoords);

	// Start at ith number after initializing start nodes
	// Only create NUMNODES nodes
	int i = int(homeCoords.size());
	while (i < NUMNODES + homeCoords.size()) {

		Coord random_coord = Coord();	// Random Position
		Node* nearest_node = graph->nearestNode(&random_coord); // Nearest Node from the random point
		
		// STILL NEED TO FINISH CHECKOBSTACLE
		//if (o.collisionCheck(nearest_node->coord, &random_coord)) { // If obstacle is in between two nodes return true
		//	std::cout << "collision here!\n";
		//	nearest_node->printNode();
		//	random_coord.printCoord();
		//	continue;
		//}

		// Creating coordinate and node step size away from the nearest coord
		Coord step = graph->stepNode(nearest_node->coord, &random_coord, STEPSIZE);
		if (graph->findDistance(nearest_node->coord, &step) > graph->findDistance(nearest_node->coord, &random_coord)) {
			continue;
		}

		Node* new_node = new Node(i, step);
		graph->addToGraph(nearest_node, new_node);
		std::vector<Node*> neighbors = graph->nearestNeighbors(new_node, RADIUS);


		//// FOR RRT*
		for (auto& node_neighbor : neighbors) {
			if (node_neighbor->in_use) {
				continue;
			}
			float cost_new = graph->findDistance(new_node->coord, node_neighbor->coord);
			if (cost_new + node_neighbor->weight < new_node->weight) {
				graph->removeEdge(new_node->parent, new_node);
				graph->addEdge(
					node_neighbor,
					new_node,
					cost_new
				);
			}
		}

		// Check if node found goal
		// IN USE NOT BEING CALLED HERE. DOUBLE CHECK IN_USE
		for (int j = 0; j < endCoords.size(); j++) {  // PROBLEM
			if (graph->getFoundPath(j)) {
				continue;
			}
			Coord drone_end = endCoords.at(j);

			float nodeDistanceFromGoal = graph->findDistance(new_node->coord, &drone_end);

			if (nodeDistanceFromGoal < GOALRADIUS) {
				std::cout << "Node that found Goal " << i+1 << ": " << new_node->node_number << std::endl;
				Node* goal_node = new Node(i + 1, drone_end);
				goal_node->in_use = true;
				graph->addToGraph(new_node, goal_node);
				graph->addNodeStack(goal_node, j);
				graph->addNodeStack(new_node, j);
				graph->setPath(j);
				break;
			}
		}
		i++;
	}
	for (int i = 0; i < endCoords.size(); i++) {
		if (graph->getFoundPath(i)) {
			std::cout << "Goal " << i + 1 << " was found!" << std::endl;
		}
		else {
			std::cout << "Goal " << i + 1 << " was not found!" << std::endl;
		}
	}
	return graph;

}