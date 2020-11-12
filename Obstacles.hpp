#ifndef OBSTACLES_HPP
#define OBSTACLES_HPP


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
	//f=front, b=back, l=left, r=right, u=up, d=down
	//vertices
	Coord* ful;
	Coord* fur;
	Coord* fdl;
	Coord* fdr;
	Coord* bul;
	Coord* bur;
	Coord* bdl;
	Coord* bdr;

    Obstacle(Coord* a, Coord* b, Coord* c, Coord* d, Coord* e, Coord* f, Coord* g, Coord* h)
    {
		ful = a;
		fur = b;
		fdl = c;
		fdr = d;
		bul = e;
		bur = f;
		bdl = g;
		bdr = h;
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
	Coord* crossProduct(Coord* A, Coord* B);


};


#endif
