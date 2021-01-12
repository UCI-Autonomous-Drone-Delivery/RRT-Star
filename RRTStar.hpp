#ifndef RRTSTAR_HPP
#define RRTSTAR_HPP

#include "Graph.hpp"
#include "Obstacles.hpp"


Graph* rrtStarOne(Coord homeCoord, Coord endCoord);
Graph* rrtStar(std::vector<Coord> homeCoords, std::vector<Coord> endCoords);

#endif