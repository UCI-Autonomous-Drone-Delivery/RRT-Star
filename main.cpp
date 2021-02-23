#include "RRTStar.hpp"
#include "Graph.hpp"
#include "AirSimTest.hpp"
// Memory Leak Check
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


//void manyRRT() {
//    std::vector<Coord> start_coords;
//    std::vector<Coord> goal_coords;
//
//    Coord start_coord = Coord(-140, -140, 10);
//    Coord goal_coord = Coord(140, -140, 10);
//    start_coords.push_back(start_coord);
//    goal_coords.push_back(goal_coord);
//
//    //startCoord = Coord(100.f, -100.f, 10);
//    //goalCoord = Coord(-100.f, 100.f, 10);
//    //startCoords.push_back(startCoord);
//    //goalCoords.push_back(goalCoord);
//
//    start_coord = Coord(140, 140, 10);
//    goal_coord = Coord(-140, 140, 10);
//    start_coords.push_back(start_coord);
//    goal_coords.push_back(goal_coord);
//
//    Graph* rrtTree = rrtStarMany(start_coords, goal_coords);
//    if (rrtTree) {
//  /*      rrtTree->printPathMany();
//        rrtTree->printGraph();*/
//    }
//    else {
//        std::cout << "No paths found :(" << std::endl;
//    }
//    delete rrtTree;
//}
//
void singleRRT() {
    Coord start = Coord(-130, -110, 2);
    Coord end = Coord(25, 50, 10);
    BiRRTStar brrt = BiRRTStar(start, end);
    brrt.CallRRTStar();

    for (auto& it : brrt.getPath()) {
        it->printNode();
    }
    for (auto& it : brrt.getPath()) {
        std::cout << it->node_number << " ";
    }
    std::cout << std::endl;
}

void obstacleCheck() {
    Obstacles o = Obstacles(MAPMINX, MAPMINY, MAPMINZ, MAPMAXX, MAPMAXY, MAPMAXZ);
    o.initObstacles();
    Coord start = Coord(17.6, 0, 0);
    Coord end = Coord(50, 25, 5);
    if (o.collisionCheck(&start, &end)) {
        std::cout << "Collision\n";
    }
    else {
        std::cout << "No Collision\n";
    }

}

int main()
{
    //srand((unsigned)time(NULL));
    srand(SEED);
    //obstacleCheck();
    //singleRRT();
    //manyRRT();
    singleDrone();
    //droneTest();


    _CrtDumpMemoryLeaks();
    return 0;
}