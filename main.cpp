#include "RRTStar.hpp"
#include "Graph.hpp"
// Memory Leak Check
//#include <crtdbg.h>

int main() {

	// Randomize each run
	srand((unsigned)time(NULL));


	Graph* graph;

	// Loop until path is found
	while (true) {
		// Random starting point initialized to 0,10,29 for now
		Coord* startingCoord = new Coord(0, 0, 0);
		// Choosing the goal coordinates
		Coord* goalCoord = new Coord(400, 325, -150);
		graph = rrtStar(startingCoord, goalCoord);

		// If path is found
		if (graph) {
			graph->printGraph();
			graph->printPath();
			break;
		}

	}

	// Memory Leak Check
	delete graph;
	//_CrtDumpMemoryLeaks();
	std::cin.get();
	return 0;
}