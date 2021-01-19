#include "RRTStar.hpp"
#include "Graph.hpp"


Graph* rrtStarSingle(Coord homeCoord, Coord endCoord) {
	//Initializes obstacles here


	Obstacles o = Obstacles(MAPMINX,MAPMINY,MAPMINZ,MAPMAXX,MAPMAXY,MAPMAXZ);
	o.initObstacles();
	Graph* graph = new Graph(homeCoord, endCoord);
	int i = 1;
	while (i < NUMNODES + 1) {

		Coord random_coord = Coord();	// Random Position
		Node* nearest_node = graph->nearestNode(&random_coord); // Nearest Node from the random point

		// STILL NEED TO FINISH CHECKOBSTACLE

		if (o.collisionCheck(nearest_node->coord, &random_coord)) { // If obstacle is in between two nodes return true
			std::cout << "collision here!\n";
			nearest_node->printNode();
			random_coord.printCoord();
			continue;
		}


		// Creating coordinate and node step size away from the nearest coord
		Coord step = graph->stepNode(nearest_node->coord, &random_coord, STEPSIZE);
		//Checking if coord is in map Using obstacle checkMap() but not the function
		if (step.x >= MAPMAXX - MINOBSTDIST || step.x < MAPMINX + MINOBSTDIST ||
			step.y >= MAPMAXY - MINOBSTDIST || step.y < MAPMINY + MINOBSTDIST ||
			step.z >= MAPMAXZ - MINOBSTDIST || step.z < MAPMINZ + MINOBSTDIST)
		{
			nearest_node->coord->printCoord();
			step.printCoord();
			std::cout << "Node out of bounds" << std::endl;
			continue;
		}
		if (graph->findDistance(nearest_node->coord, &step) > graph->findDistance(nearest_node->coord, &random_coord)) {
			continue;
		}

		Node* new_node = new Node(i, step);
		graph->addToGraph(nearest_node, new_node);
		//if (i % 100 == 0) {
			new_node->printNode();
		//}
		std::vector<Node*> neighbors = graph->nearestNeighbors(new_node, RADIUS);

		// FOR RRT*
		for (auto& node_neighbor : neighbors) {
			float cost_new = graph->findDistance(new_node->coord, node_neighbor->coord);
			if (cost_new + node_neighbor->weight < new_node->weight) {
				graph->rewireEdge(
					node_neighbor,
					new_node,
					cost_new
				);
			}
		}

		// Check if node found goal
		if (graph->inGoalRadiusSingle(new_node->coord)) {
			//std::cout << "Node that found Goal: " << new_node->node_number << std::endl;
			graph->generatePathSingle(new_node);
			return graph;
		}
		i++;
	}
	std::cout << "Goal was not found" << std::endl;
	delete graph;
		
	// Return NULL if no path found
	return NULL;
}

Graph* rrtStarMany(std::vector<Coord> start_coords, std::vector<Coord> end_coords) {

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
	Graph* graph = new Graph(start_coords, end_coords);

	// Start at ith number after initializing start nodes
	// Only create NUMNODES nodes
	int i = int(NUMDRONES);
	while (i < NUMNODES + NUMDRONES) {

		Coord random_coord = Coord();	// Random Position
		Node* nearest_node = graph->nearestNode(&random_coord); // Nearest Node from the random point
		if (nearest_node->in_use) {
			//std::cout << nearest_node->node_number << " is in Use" << std::endl;
			continue;
		}

		// Creating coordinate and node step size away from the nearest coord
		Coord step = graph->stepNode(nearest_node->coord, &random_coord, STEPSIZE);

		//Checking if coord is in map Using obstacle checkMap() but not the function
		if (step.x >= MAPMAXX - MINOBSTDIST || step.x < MAPMINX + MINOBSTDIST ||
			step.y >= MAPMAXY - MINOBSTDIST || step.y < MAPMINY + MINOBSTDIST ||
			step.z >= MAPMAXZ - MINOBSTDIST || step.z < MAPMINZ + MINOBSTDIST)
		{
			nearest_node->coord->printCoord();
			step.printCoord();
			std::cout << "Node out of bounds" << std::endl;
			continue;
		}
		
		// Random Coord is not a node but the coord that determines the direction the new node is made. Should we be checking nearest_node and the step_node????
		if (o.collisionCheck(nearest_node->coord, &random_coord)) { // if obstacle is in between two nodes return true
			std::cout << "collision here!\n";
			nearest_node->printNode();
			random_coord.printCoord();
			continue;
		}


		if (graph->findDistance(nearest_node->coord, &step) > graph->findDistance(nearest_node->coord, &random_coord)) {
			continue;
		}

		Node* new_node = new Node(i, step);
		graph->addToGraph(nearest_node, new_node);
		if (i % 100 == 0) {
			new_node->printNode();
		}

		// FOR RRT*
		std::vector<Node*> neighbors = graph->nearestNeighbors(new_node, RADIUS);
		for (auto& node_neighbor : neighbors) {
			if (node_neighbor->in_use) {
				continue;
			}
			float cost_new = graph->findDistance(new_node->coord, node_neighbor->coord);
			if (cost_new + node_neighbor->weight < new_node->weight) {
				graph->rewireEdge(
					node_neighbor,
					new_node,
					cost_new
				);
			}
		}

		// Check if node found goal
		// IN USE NOT BEING CALLED HERE. DOUBLE CHECK IN_USE
		for (int j = 0; j < NUMDRONES; j++) {  // PROBLEM
			if (graph->isPathFound(j)) {
				//std::cout << "Found Path: " << j << std::endl;
				continue;
			}
			// Check if node found goal
			if (graph->inGoalRadiusMany(new_node->coord, j)) {
				//Check that path corresponds to correct drone
				Node* curr = new_node->parent;
				bool correct_drone = false;
				while (curr) {
					if (curr->node_number == j) {
						correct_drone = true;
						break;
					}
					curr = curr->parent;
				}
				if (!correct_drone) {
					break;
				}
				//std::cout << "Node that found Goal: " << new_node->node_number << std::endl;
				graph->generatePathMany(new_node, j);
				break;
			}	
		}
		if (graph->allTrue()) {
			return graph;
		}
		// While i++
		i++;
	}
	for (int i = 0; i < NUMDRONES; i++) {
		if (graph->isPathFound(i)) {
			std::cout << "Goal " << i + 1 << " was found!" << std::endl;
		}
		else {
			std::cout << "Goal " << i + 1 << " was not found!" << std::endl;
		}
	}
	return graph;

}