#include "Obstacles.hpp"
#include "Graph.hpp"


Obstacles::Obstacles(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
	xMapMin = xMin;
	yMapMin = yMin;
	zMapMin = zMin;

	xMapMax = xMax;
	yMapMax = yMax;
	zMapMax = zMax;

	numObstacles = 0;
}

void Obstacles::addObstacle(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	Obstacle* obstacle = new Obstacle(minX, minY, minZ, maxX, maxY, maxZ);
	obstacleList.push_back(obstacle);
	numObstacles++;
}

//equivalent to A x B
void Obstacles::crossProduct(float a[], float b[], float out[]) {
	out[0] = a[1] * b[2] - a[2] * b[1];
	out[1] = -(a[0] * b[2] - a[2] * b[0]);
	out[2] = a[0] * b[1] - a[1] * b[0];
}

//returns true if in object
bool Obstacles::checkInObstacle(Coord* c) {
	//if outside map, return true
	if (c->x >= MAPMAXX - MINOBSTDIST || c->x <= MAPMINX + MINOBSTDIST ||
		c->y >= MAPMAXY - MINOBSTDIST || c->y <= MAPMINY + MINOBSTDIST ||
		c->z >= MAPMAXZ - MINOBSTDIST || c->z <= MAPMINZ + MINOBSTDIST)
	{
		return true;
	}

	for (int i = 0; i < numObstacles; i++)
	{
		Obstacle* ob = obstacleList.at(i);
		//if in object, return true
		if (c->x <= ob->xMax + MINOBSTDIST && c->x >= ob->xMin - MINOBSTDIST &&
			c->y <= ob->yMax + MINOBSTDIST && c->y >= ob->yMin - MINOBSTDIST &&
			c->z <= ob->zMax + MINOBSTDIST && c->z >= ob->zMin - MINOBSTDIST)
		{
			return true;
		}
	}
	return false;
}

bool Obstacles::checkIntersectObstacle(Coord* A, Coord* B) {
	//loop through obstacles
		//loop through faces
			//get equation for plane of face
			//check where AB intersects this plane
			//if the intersection point is within the face, we have a collision (return true)

	return false;
}


