#ifndef RRTSTAR_HPP
#define RRTSTAR_HPP

#include "Graph.hpp"

Graph* rrtStarSingle(Coord homeCoord, Coord endCoord);
Graph* rrtStarMany(std::vector<Coord> start_coords, std::vector<Coord> end_coords);

#endif