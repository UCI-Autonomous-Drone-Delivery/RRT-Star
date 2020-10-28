#include "Graph.hpp"

using namespace std;

// Constructor

Graph::Graph(int total_nodes, Coord* coord)
{
	this->num_nodes = total_nodes;
	Node* first_node = new Node(0,coord);
	addNode(first_node);

	//create array of cells
	for(int i=0;i<NUMCELLSX;i++) {
		for(int j=0;j<NUMCELLSY;j++) {
			for(int k=0;k<NUMCELLSZ;k++) {
				//create cell and store in cells[i][j][k]
				std::vector<Node*> newCell;
				cells[i][j][k]=newCell;
	
			}
		}
	}
};

std::vector<Node*> Graph::nearestNeighbors(Node* new_node, float r) {
	Coord* coord = new_node->coord;
	std::vector<Node*> neighbors;
	for(auto& node : adj_list) {

		if (new_node->parent == node) {
			std::cout << "Dont need to add parent as neighbor" << endl;
			continue;
		}
		if (new_node == node) {
			std::cout << "Cant be your own neighbor" << endl;
			continue;
		}
		//if distance between node in adj_list and node param < radius
		if(findDistance(coord,node->coord)<=r) {
			neighbors.push_back(node);
		}
	}
	std::cout << "Neighbors are: ";
	for (auto& node : neighbors) {
		std::cout << node->node_number << " ";
	}
	std::cout << endl;
	return neighbors;
}

Node* Graph::nearestNode(Coord* random_coord)
{

	//NOTE: Needs to be optimized by using the nearestNeigbors function (using cells)
	Node* nearest_node = adj_list[0];
	for (auto& node : adj_list) {
		if (findDistance(random_coord, nearest_node->coord) > findDistance(random_coord, node->coord))
		{
			nearest_node = node;
		}
	}
	return nearest_node;

}

// Utility Functions

// Creates a new coordinate step size away from the selected Node
Coord* Graph::stepNode(Coord* coord, Coord* random_coord, float step_size) 
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

	Coord* newCoord = new Coord(coord->x + x_new, coord->y + y_new, coord->z + z_new);

	return newCoord;
}

float Graph::findDistance(Coord* coord_src, Coord* coord_dest)
{
	float dist_x = pow((coord_dest->x - coord_src->x), 2);
	float dist_y = pow((coord_dest->y - coord_src->y), 2);
	float dist_z = pow((coord_dest->z - coord_src->z), 2);

	float total_distance = sqrt((dist_x + dist_y + dist_z));
	return total_distance;
}

bool Graph::checkObstacle(Coord* coord_src, Coord* coord_dest) {

	// Check if coordinate is outside boundaries
	// This is very basic right now
	if (coord_dest->x >= MAPSIZE || coord_dest->y >= MAPSIZE || coord_dest->z >= MAPSIZE) {
		return true;
	}
	else {
		return false;
	}
}

// Setter Functions

void Graph::addEdge(Node* node_src, Node* node_dest, float weight)
{
	//update weight
	float total_weight = weight + node_src->weight;
	node_dest->weight = total_weight;
	//std::cout << "Total weight from src: " << total_weight << endl;
	//add node_dest to connectedNodes list of node_src
	adj_list[node_src->node_number]->connectedNodes.push_back(node_dest);
	node_dest->parent = node_src;
	//std::cout << "Parent of " << node_dest->node_number << " is " << node_src->node_number << endl;

}

void Graph::addNode(Node* node) {
	adj_list.push_back(node);		//add new node to adj list

	//get cell coordinates, add cell coords to node and add node to the appropriate cell
	Coord* cellCoord = getCellCoords(node);
	node->cell_coord = cellCoord;

	node->printNode();

	cells[(int)cellCoord->x][(int)cellCoord->y][(int)cellCoord->z].push_back(node);
}

void Graph::addNodeStack(Node* node) {
	path.push(node);
}

// Getter Functions

//Double check this idk if it works
Coord* Graph::getCellCoords(Node* node) {
	Coord* cellCoord = new Coord;
	cellCoord->x = (int)node->coord->x / CELLSIZE;
	cellCoord->y = (int)node->coord->y / CELLSIZE;
	cellCoord->z = (int)node->coord->z / CELLSIZE;

	return cellCoord;
}

void Graph::getPath() {
	Node* curr = path.top()->parent;
	while (curr) {
		//std::cout << "Current Node is " << curr->node_number << endl;
		path.push(curr);
		curr = curr->parent;
	}
}

std::vector<Node*> Graph::getAdjList() {
	return adj_list;
}

// Debug Functions

void Graph::printGraph()
{
	cout << "Size of Graph vector: " << adj_list.size() << endl;
	cout << "Adjacency List" << endl;
	for (auto& node : adj_list)
	{
		for (auto& nodeChild : node->connectedNodes)
		{
			cout << "(" << node->node_number << ", " << nodeChild->node_number << ", " << nodeChild->weight << ") " << endl;
		}
	}
}

void Graph::printCellPop() {
	for (int i = 0; i < NUMCELLSX; i++) {
		for (int j = 0; j < NUMCELLSY; j++) {
			for (int k = 0; k < NUMCELLSZ; k++) {
				cout << "cell[" << i << "][" << j << "][" << k << "] population = " << cells[i][j][k].size() << "\n";

			}
		}
	}
}

void Graph::printPath() {
	if (path.empty()) {
		std::cout << "No path found!" << std::endl;
		return;
	}

	std::stack<Node*> temp = path;
	std::cout << "Path is: ";
	while (!temp.empty()) {
		Node* current = temp.top();
		std::cout << current->node_number << " ";
		temp.pop();
	}
	std::cout << std::endl;
}

// End Debug Functions
