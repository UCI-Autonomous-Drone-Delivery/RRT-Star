#include "Graph.hpp"
#include <stack>

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

std::vector<Node*> Graph::nearestNeighbors(Node* node, float r) {
	Coord* coord = node->coord;
	std::vector<Node*> neighbors;
	for(auto& i : adj_list) {

		if (node->parent == i) {
			std::cout << "Dont need to add parent as neighbor" << endl;
			continue;
		}
		if (node == i) {
			std::cout << "Cant be your own neighbor" << endl;
			continue;
		}
		//if distance between node in adj_list and node param < radius
		if(findDistance(coord,i->coord)<=r) {
			neighbors.push_back(i);
		}
	}
	std::cout << "Neighbors are: ";
	for (auto& iter : neighbors) {
		std::cout << iter->node_number << " ";
	}
	std::cout << endl;
	return neighbors;
}

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

void Graph::addEdge(Node* node_src, Node* node_dest, float weight)
{
	//update weight
	float total_weight = weight + node_src->weight;
	node_dest->weight = total_weight;
	std::cout << "Total weight from src: " << total_weight << endl;
	//add node_dest to connectedNodes list of node_src
	adj_list[node_src->node_number]->connectedNodes.push_back(node_dest);
	node_dest->parent = node_src;
	std::cout << "Parent of " << node_dest->node_number << " is " << node_src->node_number << endl;

}

void Graph::addNode(Node* node) {
	adj_list.push_back(node);		//add new node to adj list

	//get cell coordinates, add cell coords to node and add node to the appropriate cell
	Coord* cellCoord=getCellCoords(node);
	node->cell_coord=cellCoord;

	printNode(node);

	cells[(int)cellCoord->x][(int)cellCoord->y][(int)cellCoord->z].push_back(node);

	
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

// Debug Functions

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
	for (int i = 0; i < NUMCELLSX; i++) {
		for (int j = 0; j < NUMCELLSY; j++) {
			for (int k = 0; k < NUMCELLSZ; k++) {
				cout << "cell[" << i << "][" << j << "][" << k << "] population = " << cells[i][j][k].size() << "\n";

			}
		}
	}
}

void Graph::printNode(Node* node) {
	cout << "Node: " << node->node_number << endl;
	cout << "Coord(X,Y,Z) = (" << node->coord->x << "," << node->coord->y << "," << node->coord->z << ")\n";
	cout << "Cell (X,Y,Z) = (" << node->cell_coord->x << "," << node->cell_coord->y << "," << node->cell_coord->z << ")\n" << endl;
}

// End Debug Functions

void getPath(std::stack<Node*> &path) {
	Node* curr = path.top()->parent;
	while (curr) {
		//std::cout << "Current Node is " << curr->node_number << endl;
		path.push(curr);
		curr = curr->parent;
	}
}

void printPath(std::stack<Node*>& path) {
	// Print path
	std::cout << "Path is: ";
	while (!path.empty()) {
		Node* current = path.top();
		std::cout << current->node_number << " ";
		path.pop();
	}
	std::cout << endl;
}

void rrtStar() { // Right now its RRT
	
	// Randomize each run
	srand(time(NULL));

	// Stack for path to destination
	std::stack<Node*> path;

	// Random starting point initialized to 0,10,29 for now
	Coord* startingCoord=new Coord(60,10,29);

	// Choosing the goal coordinates
	Coord* goalCoord = new Coord(35, 25, 42);

	// Creating the start of graph
	Graph graph(NUMNODES,startingCoord);
	
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
		std::vector<Node*> neighbors = graph.nearestNeighbors(new_node, RADIUS);


		// FOR RRT*
		for (auto& node_neighbor : neighbors) {
			std::cout << "Node Neighbor is: " << node_neighbor->node_number << endl;
			float dist = graph.findDistance(new_node->coord, node_neighbor->coord);
			float cost_new = dist;
			std::cout << "Distance between neighbor = " << dist << std::cout.precision() << endl;
			std::cout << "Optimized Cost = " << cost_new << std::cout.precision() << endl;
			std::cout << "Original Cost = " << new_node->weight << endl;
			if ( cost_new < new_node->weight) {

				std::cout << "Optimizing!" << endl;
				graph.addEdge(
					node_neighbor,
					new_node,
					cost_new
				);
			}

		}

		// Find if node is in raidus of desired destination
		float nodeDistanceFromGoal = graph.findDistance(new_node->coord, goalCoord);
		if (nodeDistanceFromGoal < GOALRADIUS) {
			std::cout << "Node that found Goal: " << new_node->node_number << std::endl;
			path.push(new_node);
			break;

		} else { std::cout << "No Node found Goal!\n" << std::endl; }

		i++;
	}

	// Path from src to dest
	if (!path.empty()) {
		getPath(path);
		printPath(path);
	}
	
	
	graph.printGraph();
	//graph.printCellPop();
	
	cin.get();
}

// Drone stuff

// Only works with airsim library

//#include "common/common_utils/StrictMode.hpp"
//STRICT_MODE_OFF
//#ifndef RPCLIB_MSGPACK
//#define RPCLIB_MSGPACK clmdep_msgpack
//#endif // !RPCLIB_MSGPACK
//#include "rpc/rpc_error.h"
//STRICT_MODE_ON
//
//#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"
//#include "common/common_utils/FileSystem.hpp"
//#include <iostream>
//#include <chrono>
//
//void flyBox(msr::airlib::MultirotorRpcLibClient& client) {
//	std::cout << "Press Enter to fly in a 10m box pattern at 3 m/s velocity" << std::endl; std::cin.get();
//	// moveByVelocityZ is an offboard operation, so we need to set offboard mode.
//	client.enableApiControl(true);
//	auto position = client.getMultirotorState().getPosition();
//	float z = position.z(); // current position (NED coordinate system).  
//	const float speed = 3.0f;
//	const float size = 10.0f;
//	const float duration = size / speed;
//	DrivetrainType driveTrain = DrivetrainType::ForwardOnly;
//	YawMode yaw_mode(true, 0);
//	std::cout << "moveByVelocityZ(" << speed << ", 0, " << z << "," << duration << ")" << std::endl;
//	client.moveByVelocityZAsync(speed, 0, z, duration, driveTrain, yaw_mode);
//	std::this_thread::sleep_for(std::chrono::duration<double>(duration));
//	std::cout << "moveByVelocityZ(0, " << speed << "," << z << "," << duration << ")" << std::endl;
//	client.moveByVelocityZAsync(0, speed, z, duration, driveTrain, yaw_mode);
//	std::this_thread::sleep_for(std::chrono::duration<double>(duration));
//	std::cout << "moveByVelocityZ(" << -speed << ", 0, " << z << "," << duration << ")" << std::endl;
//	client.moveByVelocityZAsync(-speed, 0, z, duration, driveTrain, yaw_mode);
//	std::this_thread::sleep_for(std::chrono::duration<double>(duration));
//	std::cout << "moveByVelocityZ(0, " << -speed << "," << z << "," << duration << ")" << std::endl;
//	client.moveByVelocityZAsync(0, -speed, z, duration, driveTrain, yaw_mode);
//	std::this_thread::sleep_for(std::chrono::duration<double>(duration));
//
//	client.hoverAsync()->waitOnLastTask();
//}
//
//void movepath(msr::airlib::MultirotorRpcLibClient& client) {
//	std::cout << "Press Enter to fly on a path" << std::endl; std::cin.get();
//	client.enableApiControl(true);
//	auto position = client.getMultirotorState().getPosition();
//	float z = position.z(); // current position (NED coordinate system).  
//	const float speed = 3.0f;
//	const float size = 10.0f;
//	const float duration = size / speed;
//	DrivetrainType driveTrain = DrivetrainType::MaxDegreeOfFreedom;
//	YawMode yaw_mode(true, 0);
//	std::vector<Vector3r> path;
//	float x = position.x();
//	float y = position.y();
//
//	std::cout << "Starting Location: (" << x << ", " << y << ", " << z << ")\n";
//
//	//int points = 3;
//	//for (int i = 0; i < points; i++) {
//	//	x += 5;
//	//	
//	//	std::cout << "Points Location: (" << x << ", " << y << ", " << z << ")\n";
//	//}
//
//	path.push_back(Vector3r(x+size, y, z));
//	path.push_back(Vector3r(x, y+size, z));
//	path.push_back(Vector3r(x-size, y, z));
//	path.push_back(Vector3r(x, y-size, z));
//	
//	client.moveOnPathAsync(path, speed, 4*duration);
//	std::this_thread::sleep_for(std::chrono::duration<double>(4*duration));
//	client.hoverAsync()->waitOnLastTask();
//}
//
//void droneTest() {
//	using namespace msr::airlib;
//
//	msr::airlib::MultirotorRpcLibClient client;
//	typedef ImageCaptureBase::ImageRequest ImageRequest;
//	typedef ImageCaptureBase::ImageResponse ImageResponse;
//	typedef ImageCaptureBase::ImageType ImageType;
//	typedef common_utils::FileSystem FileSystem;
//
//	try {
//		client.confirmConnection();
//
//		std::cout << "Press Enter to arm the drone" << std::endl; std::cin.get();
//		client.enableApiControl(true);
//		client.armDisarm(true);
//
//		auto gps_data = client.getGpsData();
//		std::cout << "GPS data \n"
//			<< "gps_data.time_stamp \t" << gps_data.time_stamp << std::endl
//			<< "gps_data.gnss.time_utc \t" << gps_data.gnss.time_utc << std::endl
//			<< "gps_data.gnss.geo_point \t" << gps_data.gnss.geo_point << std::endl
//			<< "gps_data.gnss.eph \t" << gps_data.gnss.eph << std::endl
//			<< "gps_data.gnss.epv \t" << gps_data.gnss.epv << std::endl
//			<< "gps_data.gnss.velocity \t" << gps_data.gnss.velocity << std::endl
//			<< "gps_data.gnss.fix_type \t" << gps_data.gnss.fix_type << std::endl;
//
//		std::cout << "Press Enter to takeoff" << std::endl; std::cin.get();
//		float takeoffTimeout = 5;
//		client.takeoffAsync(takeoffTimeout)->waitOnLastTask();
//
//		// switch to explicit hover mode so that this is the fall back when 
//		// move* commands are finished.
//		std::this_thread::sleep_for(std::chrono::duration<double>(5));
//		client.hoverAsync()->waitOnLastTask();
//
//		//flyBox(client);
//		movepath(client);
//
//		std::cout << "Press Enter to land" << std::endl; std::cin.get();
//		client.landAsync()->waitOnLastTask();
//
//		std::cout << "Press Enter to disarm" << std::endl; std::cin.get();
//		client.armDisarm(false);
//
//	}
//	catch (rpc::rpc_error& e) {
//		std::string msg = e.get_error().as<std::string>();
//		std::cout << "Exception raised by the API, something went wrong." << std::endl << msg << std::endl;
//	}
//}



// End Drone Stuff

int main() {
	rrtStar();
	//droneTest();
	return 0;
}
