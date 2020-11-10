#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdlib.h>
#include <vector>
#include <stack>
#include <list>
#include <time.h>
#include <cmath>
#include <iostream>
#include <assert.h>

#include "Graph.hpp"

struct Obstacle {
	float xMin;
	float yMin;
	float zMin;

	float xMax;
	float yMax;
	float zMax;

    Obstacle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
    {
		xMin = minX;
		yMin = minY;
		zMin = minZ;

		xMax = maxX;
		yMax = maxY;
		zMax = maxZ;
    }
};

class Obstacles {
	float xMapMin;
	float yMapMin;
	float zMapMin;

	float xMapMax;
	float yMapMax;
	float zMapMax;

	int numObstacles;
	std::vector<Obstacle*> obstacleList;
public:
	Obstacles(float xMin,float xMax,float yMin, float yMax, float zMin, float zMax);
	void addObstacle(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	bool checkInObstacle(Coord* coord);
	bool checkIntersectObstacle(Coord* A, Coord* B);
};


#endif
