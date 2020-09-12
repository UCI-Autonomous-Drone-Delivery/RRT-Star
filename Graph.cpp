#include "Graph.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <cmath>
#include <vector>


//const int TOTAL_NODES = 10;

using namespace std;

Graph::Graph(int total_nodes)
{
	this->num_nodes = total_nodes;
	//adj_list.resize(this->num_nodes);
};

float Graph::findDistance(Coord coord_src, Coord coord_dest)
{
	float dist_x = pow((coord_dest.x - coord_src.x), 2);
	float dist_y = pow((coord_dest.y - coord_src.y), 2);
	float dist_z = pow((coord_dest.z - coord_src.z), 2);

	float total_distance = sqrt((dist_x + dist_y + dist_z));
	return total_distance;
}

Node Graph::nearestNode(Coord random_coord)
{
	Node nearest_node = adj_list[0];
	for (auto& it : adj_list) {
		if (findDistance(random_coord, nearest_node.coord) > findDistance(random_coord, it.coord))
		{
			nearest_node = it;
		}
	}
	return nearest_node;

}

// Creates a new coordinate step size away from the selected Node
Coord Graph::stepNode(Coord coord, float step_size) 
{
	float x_new, y_new, z_new, hypotonouse;
	z_new = ((step_size)*sqrt(2.0f)) / 2.0f;
	hypotonouse = ((step_size)*sqrt(2.0f)) / 2.0f;
	x_new = ((hypotonouse)*sqrt(2.0f)) / 2.0f;
	y_new = ((hypotonouse)*sqrt(2.0f)) / 2.0f;

	Coord newCoord = Coord(coord.x + x_new, coord.y + y_new, coord.z + z_new);

	return newCoord;
}

void Graph::addEdge(Node node_src, Node node_dest, float weight)
{
	node_dest.weight = weight;
	adj_list[node_src.node_number].node_list.push_back(node_dest);
}

void Graph::printGraph()
{
	cout << "Size of Graph vector: " << adj_list.size() << endl;
	cout << "Adjacency List" << endl;
	for (auto& it : adj_list)
	{
		for (auto& iter : it.node_list)
		{
			cout << "(" << it.node_number << ", " << iter.node_number << ", " << iter.weight << ") " << endl;
		}
	}
}

int main() {
	
	srand(time(NULL));
	int total_nodes = 20;
	float step_size = 5.0f;
	Graph graph(total_nodes);

	// Starting Location
	graph.adj_list.push_back(Node());


	int i = 1;
	while (i < total_nodes) {
		Coord random_coord = Coord();	// Random Position
		// if (obstacle) == True , continue;
		Node nearest_node = graph.nearestNode(random_coord); // Nearest Node from the random point
		Node new_node = Node(i, graph.stepNode(nearest_node.coord, step_size)); // Create a new node step size away from the nearest node towards the random point
		graph.adj_list.push_back(new_node);
		graph.addEdge(nearest_node, new_node, graph.findDistance(nearest_node.coord, new_node.coord));


		i++;
	}
	
	graph.printGraph();
	

	cin.get();
}
