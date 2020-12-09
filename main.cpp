#include "RRTStar.hpp"
#include "Graph.hpp"
// Memory Leak Check
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

// Drone stuff
// Only works with airsim library

#include "common/common_utils/StrictMode.hpp"
STRICT_MODE_OFF
#ifndef RPCLIB_MSGPACK
#define RPCLIB_MSGPACK clmdep_msgpack
#endif // !RPCLIB_MSGPACK
#include "rpc/rpc_error.h"
STRICT_MODE_ON

#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"
#include "common/common_utils/FileSystem.hpp"
#include <iostream>
#include <chrono>
#include <thread> 
#include <future>

using namespace msr::airlib;
using namespace std;

//struct DroneRRTSTAR {
//	msr::airlib::MultirotorRpcLibClient* client;
//	Graph* graph;
//
//	DroneRRTSTAR() {
//		client = NULL;
//		graph = NULL;
//	}
//	~DroneRRTSTAR() {
//		delete graph;
//	}
//};
//
//
//void droneTest() {
//	
//
//	// Array of Drones
//	const int droneAmount = 3;
//	msr::airlib::MultirotorRpcLibClient* clients = new msr::airlib::MultirotorRpcLibClient[droneAmount];
//	DroneRRTSTAR* drones = new DroneRRTSTAR[droneAmount];
//	std::thread droneThreads[droneAmount];
//
//	try {
//		for (int i = 0; i < droneAmount; i++) {
//			drones[i].client = &clients[i];
//			drones[i].client->confirmConnection();
//		}
//
//		std::cout << "Press Enter to arm the drone" << std::endl; std::cin.get();
//		int x = 4;
//		for (int i = 0; i < droneAmount; i++) {
//			string droneName = "Drone" + to_string(i + 1);
//			//msr::airlib::Pose pose = drones[i].client->simGetVehiclePose(droneName);
//			//pose.position = Vector3r(x, 0, -2);
//			drones[i].client->enableApiControl(true, droneName);
//			drones[i].client->armDisarm(true, droneName);
//			//drones[i].client->simSetVehiclePose(pose, true, droneName);
//			//x += 4;
//		}
//
//		std::cout << "Press Enter to takeoff" << std::endl; std::cin.get();
//		float takeoffTimeout = 20;
//		for (int i = 0; i < droneAmount; i++) {
//			string droneName = "Drone" + to_string(i + 1);
//			droneThreads[i] = std::thread(&MultirotorRpcLibClient::takeoffAsync, drones[i].client, takeoffTimeout, droneName);
//		}
//		for (int i = 0; i < droneAmount; i++) {
//			droneThreads[i].join();
//		}
//
//		std::cout << "Press Enter to calculate RRTStar" << std::endl; std::cin.get();
//		std::vector<std::future<Graph*>> futureResults;
//		for (int i = 0; i < droneAmount; i++) {
//			auto pos = drones[i].client->getMultirotorState().getPosition();
//			Coord startingCoord = Coord(pos.x(), pos.y(), pos.z());
//			Coord goalCoord = Coord(23.12f, -58.37f, 23.5f);
//			futureResults.emplace_back(std::async(std::launch::async, rrtStar, startingCoord, goalCoord));
//		}
//		for (int i = 0; i < droneAmount; i++) {
//			drones[i].graph = futureResults.at(i).get();
//		}
//		for (int i = 0; i < droneAmount; i++) {
//			std::cout << "Graph " << i + 1 << std::endl;
//			if (drones[i].graph) {
//				drones[i].graph->printGraph();
//				drones[i].graph->printPath();
//			}
//		}
//
//		std::cout << "Press Enter to move drones" << std::endl; std::cin.get();
//		DrivetrainType driveTrain = DrivetrainType::MaxDegreeOfFreedom;
//		YawMode yaw_mode(true, 0);
//		float moveTimeout = 30.0f;
//		float lookahead = -1.0f;
//		float adaptive_lookahead = 1.0f;
//		for (int i = 0; i < droneAmount; i++) {
//			string droneName = "Drone" + to_string(i + 1);
//			droneThreads[i] = std::thread(&MultirotorRpcLibClient::moveToPositionAsync, drones[i].client, -5, 5, -10, 5, moveTimeout, driveTrain, yaw_mode, lookahead, adaptive_lookahead, droneName);
//		}
//		for (int i = 0; i < droneAmount; i++) {
//			droneThreads[i].join();
//		}
//
//		std::cout << "Press Enter to disarm" << std::endl; std::cin.get();
//		for (int i = 0; i < droneAmount; i++) {
//			string droneName = "Drone" + to_string(i + 1);
//			drones[i].client->armDisarm(false, droneName);
//			drones[i].client->enableApiControl(false, droneName);
//			drones[i].client->reset();
//		}
//
//		// Garbage Collection
//		delete[] clients;
//		delete[] drones;
//	}
//	catch (rpc::rpc_error& e) {
//		std::string msg = e.get_error().as<std::string>();
//		std::cout << "Exception raised by the API, something went wrong." << std::endl << msg << std::endl;
//	}
//}


void testMany() {
	std::vector<Coord> startCoords;
	std::vector<Coord> goalCoords;
	for (int i = 0; i < 2; i++) {
		float offset = i * 20;
		Coord startCoord = Coord(0 + offset, 0 + offset, 0 + offset);
		Coord goalCoord = Coord(23.12f + offset, -45.37f + offset, 23.5f + offset);
		startCoords.push_back(startCoord);
		goalCoords.push_back(goalCoord);
	}

	Graph* graph = rrtStar(startCoords, goalCoords);
	if (graph) {
		graph->printGraph();
		for (int i = 0; i < startCoords.size(); i++) {
			graph->printPath(i);
		}
	}
	delete graph;
}

void testSingle() {
	Coord startCoord = Coord(0, 0, 0);
	Coord goalCoord = Coord(23.12f, -45.37f, 23.5f);

	Graph* graph = rrtStar(startCoord, goalCoord);
	if (graph) {
		graph->printGraph();
		graph->printPath(0);
	}
	delete graph;
}


#include <vector>
#include <stack>
int main()
{
	//srand((unsigned)time(SEED));
	srand(SEED);
	//droneTest();

	//testMany();
	testSingle();
	//std::vector <std::stack<int>> paths;
	//paths.resize(3);
	//for (int i = 0; i < 3; i++) {
	//	std::stack<int> path;
	//	paths.push_back(path);
	//}
	//for (int i = 0; i < 3; i++) {
	//	paths.at(i).push(i);
	//}
	//for (int i = 0; i < 3; i++) {
	//	std::stack<int> curr = paths.at(i);
	//	std::cout << curr.top() << std::endl;
	//	curr.pop();
	//	
	//}
	_CrtDumpMemoryLeaks();
	return 0;
}