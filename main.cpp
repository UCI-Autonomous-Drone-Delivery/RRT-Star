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


void testMany() {
	std::vector<Coord> startCoords;
	std::vector<Coord> goalCoords;
	Coord startCoord = Coord(-140, -140, 10);		
	Coord goalCoord = Coord(140, -140, 10); 
	startCoords.push_back(startCoord);
	goalCoords.push_back(goalCoord);

	//startCoord = Coord(100.f, -100.f, 10);
	//goalCoord = Coord(-100.f, 100.f, 10);
	//startCoords.push_back(startCoord);
	//goalCoords.push_back(goalCoord);

	startCoord = Coord(140, 140, 10);
	goalCoord = Coord(-140, 140, 10);
	startCoords.push_back(startCoord);
	goalCoords.push_back(goalCoord);

	//for (int i = 0; i < NUMDRONES; i++) {
	//	float offset = i * 10;
	//	Coord startCoord = Coord(-100.f + offset, -100.f, 10);				
	//	Coord goalCoord = Coord(100.f + offset, -100.f, 10); 
	//	startCoords.push_back(startCoord);
	//	goalCoords.push_back(goalCoord);
	//}

	Graph* graph = rrtStar(startCoords, goalCoords);
	if (graph) {
		//graph->printGraph();
		for (int i = 0; i < NUMDRONES; i++) {
			graph->printPath(i);
		}
	}
	// If we want to save graph we don't delete and write it to file LATER
	delete graph;
}

void testSingle() {
	Coord startCoord = Coord(0, 0, 0);
	Coord goalCoord = Coord(23.12f, -45.37f, 23.5f);

	Graph* graph = rrtStarOne(startCoord, goalCoord);
	if (graph) {
		graph->printGraph();
		graph->printPath(0);
	}
	delete graph;
}

int main()
{
	//srand((unsigned)time(NULL));
	srand(SEED);

	testMany();
	//testSingle();

	_CrtDumpMemoryLeaks();
	return 0;
}