#include "Graph.hpp"
using namespace std;

// Constructor


// Singluar Drone
Graph::Graph(Coord startCoord, Coord endCoord)
{
	this->start_node = new Node(0, startCoord);
	this->end_node = new Node(NUMNODES, endCoord);
	adj_list.push_back(start_node);
};

Graph::Graph(std::vector<Coord> start_coords, std::vector<Coord> end_coords)
{
	found_path = new bool[NUMDRONES];
	path_many.resize(NUMDRONES);
	for (int i = 0; i < NUMDRONES; i++) {
		found_path[i] = false;

		Node* start_node = new Node(i, start_coords.at(i));
		Node* end_node = new Node(NUMNODES - (NUMDRONES - i), end_coords.at(i));

		start_nodes.push_back(start_node);
		end_nodes.push_back(end_node);
		adj_list.push_back(start_node);
	}

	// Cell optimization use later

	////create array of cells
	//for(int i=0;i<NUMCELLSX;i++) {
	//	for(int j=0;j<NUMCELLSY;j++) {
	//		for(int k=0;k<NUMCELLSZ;k++) {
	//			//create cell and store in cells[i][j][k]
	//			std::vector<Node*> newCell;
	//			cells[i][j][k]=newCell;
	//
	//		}
	//	}
	//}
};



Graph::~Graph() {
	for (auto& iter : adj_list) {
		delete iter;
	}
	delete[] found_path;
}

std::vector<Node*> Graph::nearestNeighbors(Node* new_node, float r) {
	Coord* coord = new_node->coord;
	std::vector<Node*> neighbors;
	for(auto& node : adj_list) {
		if (!node) { continue; }
		if (new_node->parent == node) {
			//std::cout << "Dont need to add parent as neighbor" << endl;
			continue;
		}
		if (new_node == node) {
			//std::cout << "Cant be your own neighbor" << endl;
			continue;
		}
		//if distance between node in adj_list and node param < radius
		if(findDistance(coord,node->coord)<=r) {
			neighbors.push_back(node);
		}
	}
	//std::cout << "Neighbors are: ";
	//for (auto& node : neighbors) {
	//	if (!node) { continue; }
	//	std::cout << node->node_number << " ";
	//}
	//std::cout << "\n\n";
	return neighbors;
}

bool Graph::allTrue() {
	for (int i = 0; i < NUMDRONES; i++) {
		if (!found_path[i]) {
			return false;
		}
	}
	return true;
}

Node* Graph::nearestNode(Coord* random_coord)
{

	//NOTE: Needs to be optimized by using the nearestNeigbors function (using cells)
	Node* nearest_node = adj_list[0];
	for (auto& node : adj_list) {
		if (!node) { continue; }
		if (findDistance(random_coord, nearest_node->coord) > findDistance(random_coord, node->coord))
		{
			nearest_node = node;
		}
	}
	return nearest_node;

}

// Utility Functions

// Creates a new coordinate step size away from the selected Node
Coord Graph::stepNode(Coord* coord, Coord* random_coord, float step_size) 
{
	//Need to handle case when coord+step_size is greater than random point
	float x_new, y_new, z_new, hypotonouse;
	z_new = ((step_size)*sqrt(2.0f)) / 2.0f;
	hypotonouse = ((step_size)*sqrt(2.0f)) / 2.0f;
	x_new = ((hypotonouse)*sqrt(2.0f)) / 2.0f;
	y_new = ((hypotonouse)*sqrt(2.0f)) / 2.0f;


	// Checks if random coordinate is at a location less than the nearest coordinate
	if (random_coord->x < coord->x) { x_new = -x_new; }
	if (random_coord->y < coord->y) { y_new = -y_new; }
	if (random_coord->z < coord->z) { z_new = -z_new; }

	Coord newCoord = Coord(coord->x + x_new, coord->y + y_new, coord->z + z_new);

	return newCoord;
}

float Graph::findDistance(Coord* coord_src, Coord* coord_dest)
{
	float dist_x = pow((coord_dest->x - coord_src->x), 2);
	float dist_y = pow((coord_dest->y - coord_src->y), 2);
	float dist_z = pow((coord_dest->z - coord_src->z), 2);
	
	float total_distance = sqrt((dist_x + dist_y + dist_z));
	/*std::cout << "dx: " << dist_x << " dy: " << dist_y << " dz: " << dist_z << std::endl;
	std::cout << "Total Distance: " << total_distance << std::endl;*/
	return total_distance;
}

bool Graph::inGoalRadiusSingle(Coord* node_coord) {
	if (findDistance(node_coord, end_node->coord) < GOALRADIUS) {
		return true;
	}
	else
		return false;
}

bool Graph::inGoalRadiusMany(Coord* node_coord, int number) {
	if (findDistance(node_coord, end_nodes.at(number)->coord) < GOALRADIUS) {
		return true;
	}
	else
		return false;
}

void Graph::generatePathSingle(Node* final_node) {
	addToGraph(final_node, end_node);
	path_single.push_back(end_node);
	Node* node = final_node;
	while (node->parent) {
		path_single.push_back(node);
		node = node->parent;
	}
	path_single.push_back(node);
}

void Graph::generatePathMany(Node* final_node, int number) {
	addToGraph(final_node, end_nodes.at(number));
	std::vector<Node*> path;
	path.push_back(end_nodes.at(number));
	Node* node = final_node;
	while (node->parent) {
		path.push_back(node);
		node = node->parent;
	}
	path.push_back(node);

	found_path[number] = true;
	path_many.at(number) = path;
}

// Setter Functions

void Graph::addEdge(Node* node_src, Node* node_dest, float weight)
{
	float total_weight = weight + node_src->weight;
	node_dest->weight = total_weight;
	node_dest->parent = node_src;
	adj_list.push_back(node_dest);
}

void Graph::rewireEdge(Node* node_src, Node* node_dest, float weight) {
	float total_weight = weight + node_src->weight;
	node_dest->weight = total_weight;
	node_dest->parent = node_src;
}

void Graph::addToGraph(Node* node_src, Node* node_dest) {
	float cost = findDistance(node_src->coord, node_dest->coord);
	addEdge(node_src, node_dest, cost);
}


// Getter Functions

////Double check this idk if it works
//Coord* Graph::getCellCoords(Node* node) {
//	
//	float x = (int)node->coord->x / CELLSIZE;
//	float y = (int)node->coord->y / CELLSIZE;
//	float z = (int)node->coord->z / CELLSIZE;
//
//	Coord* cellCoord = new Coord(x, y, z);
//
//	return cellCoord;
//}


bool Graph::isPathFound(int path_number) {
	return found_path[path_number];
}

int Graph::getNumNodes() {
	return num_nodes;
}

std::vector<Node*> Graph::getPath() {
	return path_single;
}

std::vector<Node*> Graph::getAdjList() {
	return adj_list;
}

// Debug Functions

void Graph::printGraph()
{
	cout << "Size of Tree: " << adj_list.size() << endl;
	//cout << "Adjacency List" << endl;
	//for (auto& node : adj_list)
	//{
	//	if (!node) { continue; }
	//	cout << "(" << node->node_number << ", " << nodeChild->node_number << ", " << nodeChild->weight << ") " << endl;

	//	//for (auto& nodeChild : node->connectedNodes)
	//	//{
	//	//	if (!nodeChild) { continue; }
	//	//	cout << "(" << node->node_number << ", " << nodeChild->node_number << ", " << nodeChild->weight << ") " << endl;
	//	//}
	//}
}

//void Graph::printCellPop() {
//	for (int i = 0; i < NUMCELLSX; i++) {
//		for (int j = 0; j < NUMCELLSY; j++) {
//			for (int k = 0; k < NUMCELLSZ; k++) {
//				cout << "cell[" << i << "][" << j << "][" << k << "] population = " << cells[i][j][k].size() << "\n";
//
//			}
//		}
//	}
//}


void Graph::printPathSingle() {
	for (auto& node : path_single) {
		std::cout << node->node_number << " ";
	}
	std::cout << std::endl;
	std::cout << "Total Cost: " << end_node->weight << std::endl;
}

void Graph::printPathMany() {
	for (int i = 0; i < NUMDRONES; i++) {
		std::vector<Node*> path = path_many.at(i);
		std::cout << "Path " << i << ": ";
		if (path.empty()) {
			std::cout << "No path found :(" << std::endl;
			continue;
		}
		for (auto& node : path) {
			if (!node) { continue; }
			std::cout << node->node_number << " ";
		}
		std::cout << std::endl;
		std::cout << "Total Cost: " << end_nodes.at(i)->weight << std::endl;
	}
}



// End Debug Functions
