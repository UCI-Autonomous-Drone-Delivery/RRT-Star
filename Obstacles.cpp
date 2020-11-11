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

	//handle diagonal objects

	return false;
}

bool Obstacles::checkIntersectObstacle(Coord* A, Coord* B) {
	//loop through obstacles
		//loop through faces
			//get equation for plane of face
			//check where AB intersects this plane
			//if the intersection point is within the face, we have a collision (return true)
	Coord* dispVect1;
	Coord* directVect1;
	Coord* dispVect2;
	Coord* directVect2;
	
	for (int i = 0; i < numObstacles; i++) {
		Obstacle* ob = obstacleList.at(i);
		//get top face eqn

		//line1 eqn (ful-fur)
		dispVect1 = new Coord(ob->ful->x, ob->ful->y, ob->ful->z);
		directVect1 = new Coord(ob->ful->x - ob->fur->x, ob->ful->y - ob->fur->y, ob->ful->z - ob->fur->z);

		//line2 eqn (ful-bul)
		dispVect2 = new Coord(ob->ful->x, ob->ful->y, ob->ful->z);
		directVect2 = new Coord(ob->ful->x - ob->bul->x, ob->ful->y - ob->bul->y, ob->ful->z - ob->bul->z);

		//check intersect, return true if it intersects within face




		//get down face eqn
		dispVect1 = new Coord(ob->fdl->x, ob->fdl->y, ob->fdl->z);
		directVect1 = new Coord(ob->fdl->x - ob->fdr->x, ob->fdl->y - ob->fdr->y, ob->fdl->z - ob->fdr->z);

		//line2 eqn (ful-bul)
		dispVect2 = new Coord(ob->fdl->x, ob->fdl->y, ob->fdl->z);
		directVect2 = new Coord(ob->fdl->x - ob->bdl->x, ob->fdl->y - ob->bdl->y, ob->fdl->z - ob->bdl->z);
		//check intersect

		//get left face eqn
		//check intersect

		//get right face eqn
		//check intersect

		//get front face eqn
		//check intersect

		//get back face eqn
		//check intersect

	}

	return false;
}


