#include "Graph.hpp"


//const int TOTAL_NODES = 10;

/*
	BUGS

	-Currently, if our stepSize+coord is greater than the random point, it overshoots the random point
	-Our code is adding invalid points (out of map boundary to the adjlist)
	-If node exists it shouldn't add a new one 

*/

using namespace std;

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


//Double check this idk if it works
Coord* Graph::getCellCoords(Node* node) {		
	Coord* cellCoord=new Coord;
	cellCoord->x=(int)node->coord->x/CELLSIZE;
	cellCoord->y=(int)node->coord->y/CELLSIZE;
	cellCoord->z=(int)node->coord->z/CELLSIZE;

	return cellCoord;
}


float Graph::findDistance(Coord* coord_src, Coord* coord_dest)
{
	float dist_x = pow((coord_dest->x - coord_src->x), 2);
	float dist_y = pow((coord_dest->y - coord_src->y), 2);
	float dist_z = pow((coord_dest->z - coord_src->z), 2);

	float total_distance = sqrt((dist_x + dist_y + dist_z));
	return total_distance;
}

Node* Graph::nearestNode(Coord* random_coord)
{

	//NOTE: Needs to be optimized by using the nearestNeigbors function (using cells)
	Node* nearest_node = adj_list[0];
	for (auto& it : adj_list) {
		if (findDistance(random_coord, nearest_node->coord) > findDistance(random_coord, it->coord))
		{
			nearest_node = it;
		}
	}
	return nearest_node;

}

// Creates a new coordinate step size away from the selected Node
Coord* Graph::stepNode(Coord* coord, float step_size) 
{
	//Need to handle case when coord+step_size is greater than random point
	float x_new, y_new, z_new, hypotonouse;
	z_new = ((step_size)*sqrt(2.0f)) / 2.0f;
	hypotonouse = ((step_size)*sqrt(2.0f)) / 2.0f;
	x_new = ((hypotonouse)*sqrt(2.0f)) / 2.0f;
	y_new = ((hypotonouse)*sqrt(2.0f)) / 2.0f;

	Coord* newCoord = new Coord(coord->x + x_new, coord->y + y_new, coord->z + z_new);

	return newCoord;
}

void Graph::addEdge(Node* node_src, Node* node_dest, float weight)
{
	//update weight
	node_dest->weight = weight;

	//add node_dest to connectedNodes list of node_src
	adj_list[node_src->node_number]->connectedNodes.push_back(node_dest);

}

void Graph::printGraph()
{
	cout << "Size of Graph vector: " << adj_list.size() << endl;
	cout << "Adjacency List" << endl;
	for (auto& it : adj_list)
	{
		for (auto& iter : it->connectedNodes)
		{
			cout << "(" << it->node_number << ", " << iter->node_number << ", " << iter->weight << ") " << endl;
		}
	}
}

void Graph::printCellPop() {
	for(int i=0;i<NUMCELLSX;i++) {
		for(int j=0;j<NUMCELLSY;j++) {
			for(int k=0;k<NUMCELLSZ;k++) {
				cout << "cell[" << i << "][" << j << "][" << k << "] population = " << cells[i][j][k].size() << "\n";

			}
		}
	}
}

void Graph::addNode(Node* node) {
	adj_list.push_back(node);		//add new node to adj list

	//get cell coordinates, add cell coords to node and add node to the appropriate cell
	Coord* cellCoord=getCellCoords(node);
	node->cell_coord=cellCoord;
	cells[(int)cellCoord->x][(int)cellCoord->y][(int)cellCoord->z].push_back(node);

	printNode(node);
}

void Graph::printNode(Node* node) {
	cout<< "(X,Y,Z) = (" << node->coord->x << "," << node->coord->y << "," << node->coord->z<< ")\n";
}


int main() {
	
	srand(time(NULL));
	//Random starting point initialized to 0,10,29 for now
	Coord* startingCoord=new Coord(60,10,29);
	Graph graph(NUMNODES,startingCoord);

	int i = 1;
	while (i <= NUMNODES) {
		Coord* random_coord = new Coord();	// Random Position
		Node* nearest_node = graph.nearestNode(random_coord); // Nearest Node from the random point
		Node* new_node =new Node(i, graph.stepNode(nearest_node->coord, STEPSIZE)); // Create a new node step size away from the nearest node towards the random point

		//if (obstacle between new_node and nearest_node) {
		
		if(false) {
			continue;
		} 
		else {
			graph.addNode(new_node);
			graph.addEdge(nearest_node, new_node, graph.findDistance(nearest_node->coord, new_node->coord));
			i++;
		}
	}
	
	//graph.printGraph();
	graph.printCellPop();
	

	cin.get();
}


