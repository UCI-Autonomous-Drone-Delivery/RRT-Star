#include "RRTStar.hpp"
#include "Graph.hpp"

int main() {

	// Random starting point initialized to 0,10,29 for now
	Coord* startingCoord = new Coord(60, 10, 29);
	// Choosing the goal coordinates
	Coord* goalCoord = new Coord(35, 25, 42);

	Graph g = rrtStar(startingCoord, goalCoord);

	g.printGraph();
	g.printPath();
	
	std::cin.get();
	return 0;
}