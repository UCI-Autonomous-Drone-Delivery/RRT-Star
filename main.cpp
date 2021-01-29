#define _HAS_STD_BYTE 0
#define _USE_MATH_DEFINES

#include <matplot/matplot.h>
#include <cmath>
#include "RRTStar.hpp"


namespace plt = matplot;

Graph* singleRRT() {
    Coord start = Coord(-110, 130, 10);
    Coord end = Coord(110, -130, 10);
    Graph* rrtTree = rrtStarSingle(start, end);
    if (rrtTree) {
        rrtTree->printPathSingle();
        //rrtTree->printGraph();
        return rrtTree;
    }
    else {
        std::cout << "No paths found :(" << std::endl;
        return NULL;
    }

}

void manyRRT() {
    std::vector<Coord> start_coords;
    std::vector<Coord> goal_coords;

    Coord start_coord = Coord(-140, -140, 10);
    Coord goal_coord = Coord(140, -140, 10);
    start_coords.push_back(start_coord);
    goal_coords.push_back(goal_coord);

    //startCoord = Coord(100.f, -100.f, 10);
    //goalCoord = Coord(-100.f, 100.f, 10);
    //startCoords.push_back(startCoord);
    //goalCoords.push_back(goalCoord);

    start_coord = Coord(140, 140, 10);
    goal_coord = Coord(-140, 140, 10);
    start_coords.push_back(start_coord);
    goal_coords.push_back(goal_coord);

    Graph* rrtTree = rrtStarMany(start_coords, goal_coords);
    if (rrtTree) {
        rrtTree->printPathMany();
        rrtTree->printGraph();
    }
    else {
        std::cout << "No paths found :(" << std::endl;
    }
}

int main()
{
    srand(SEED);
    plt::xlim({ MAPMINX, MAPMAXX });
    plt::ylim({ MAPMINY, MAPMAXY });
    plt::zlim({ MAPMINZ, MAPMAXZ });
    plt::xlabel("x");
    plt::ylabel("y");
    plt::zlabel("z");

    Graph* rrtTree = singleRRT();
    //
    //manyRRT();
    std::vector<float> x, y, z, x1,y1,z1, xob, yob, zob;
    
    // Adds coords to vector to plot
    plt::hold(plt::on);
    for (auto& node : rrtTree->getAdjList()) {
        x.push_back(node->coord->x);
        y.push_back(node->coord->y);
        z.push_back(node->coord->z);
    }
    plt::plot3(x, y, z, "o");
    for (auto& node : rrtTree->getPath()) {
        x1.push_back(node->coord->x);
        y1.push_back(node->coord->y);
        z1.push_back(node->coord->z);
    }
    plt::plot3(x1, y1, z1, "-rs");

    // Shows Obstacle same order as text file
    xob.push_back(-10);     yob.push_back(-100);    zob.push_back(150);
    xob.push_back(10);      yob.push_back(-100);    zob.push_back(150);
    xob.push_back(-10);     yob.push_back(-100);    zob.push_back(0);
    xob.push_back(10);      yob.push_back(-100);    zob.push_back(0);
    xob.push_back(-10);     yob.push_back(100);     zob.push_back(150);
    xob.push_back(10);      yob.push_back(100);     zob.push_back(150);
    xob.push_back(-10);     yob.push_back(100);     zob.push_back(0);
    xob.push_back(10);      yob.push_back(100);     zob.push_back(0);
    plt::plot3(xob, yob, zob, "-mx");
    

    plt::show();
    return 0;
}
