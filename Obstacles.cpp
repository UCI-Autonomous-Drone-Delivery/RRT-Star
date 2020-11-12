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
Coord* Obstacles::crossProduct(Coord* A, Coord* B) {
	Coord* Out = new Coord();
	Out->x = (A->y * B->z) - (A->z * B->y);
	Out->y = -(A->x * B->z) + (A->z * B->x);
	Out->z = (A->x * B->y) - (A->y * B->x);

	return Out;
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
		//----------------------------------------up face equation------------------------------------------//

		//line1 eqn (ful -> fur)
		dispVect1 = new Coord(ob->ful->x, ob->ful->y, ob->ful->z);
		directVect1 = new Coord(ob->ful->x - ob->fur->x, ob->ful->y - ob->fur->y, ob->ful->z - ob->fur->z);

		//line2 eqn (ful -> bul)
		dispVect2 = new Coord(ob->ful->x, ob->ful->y, ob->ful->z);
		directVect2 = new Coord(ob->bul->x - ob->ful->x,ob->bul->y - ob->ful->y, ob->bul->z - ob->ful->z);

		//check intersect, return true if it intersects within face



		//----------------------------------------down face equation------------------------------------------//

		//line1 eqn (fdl -> fdr)
		dispVect1 = new Coord(ob->fdl->x, ob->fdl->y, ob->fdl->z);
		directVect1 = new Coord(ob->fdr->x - ob->fdl->x, ob->fdr->y - ob->fdl->y, ob->fdr->z - ob->fdl->z);

		//line2 eqn (fdl -> bdl)
		dispVect2 = new Coord(ob->fdl->x, ob->fdl->y, ob->fdl->z);
		directVect2 = new Coord(ob->bdl->x - ob->fdl->x, ob->bdl->y - ob->fdl->y, ob->bdl->z - ob->fdl->z);
		//check intersect



		//----------------------------------------left face equation------------------------------------------//

		//line1 eqn (fdl -> bdl)
		dispVect1 = new Coord(ob->fdl->x, ob->fdl->y, ob->fdl->z);
		directVect1 = new Coord(ob->bdl->x - ob->fdl->x, ob->bdl->y - ob->fdl->y, ob->bdl->z - ob->fdl->z);
		
		//line5 eqn (fdl -> ful)
		dispVect2 = new Coord(ob->fdl->x, ob->fdl->y, ob->fdl->z);
		directVect2 = new Coord(ob->ful->x - ob->fdl->x, ob->ful->y - ob->fdl->y, ob->ful->z - ob->fdl->z);
		//check intersect

		
		//----------------------------------------right face equation------------------------------------------//
		
		//line1 eqn (fdr -> bdr)
		dispVect1 = new Coord(ob->fdr->x, ob->fdr->y, ob->fdr->z);
		directVect1 = new Coord(ob->bdr->x - ob->fdr->x, ob->bdr->y - ob->fdr->y, ob->bdr->z - ob->fdr->z);

		//line2 eqn (fdr -> fur)
		dispVect2 = new Coord(ob->fdr->x, ob->fdr->y, ob->fdr->z);
		directVect2 = new Coord(ob->fur->x - ob->fdr->x, ob->fur->y - ob->fdr->y, ob->fur->z - ob->fdr->z);
		//check intersect


		//----------------------------------------front face equation------------------------------------------//

		//line1 eqn (fdl -> fdr)
		dispVect1 = new Coord(ob->fdl->x, ob->fdl->y, ob->fdl->z);
		directVect1 = new Coord(ob->fdr->x - ob->fdl->x, ob->fdr->y - ob->fdl->y, ob->fdr->z - ob->fdl->z);

		//line2 eqn (fdl -> ful)
		dispVect2 = new Coord(ob->fdl->x, ob->fdl->y, ob->fdl->z);
		directVect2 = new Coord(ob->ful->x - ob->fdl->x, ob->ful->y - ob->fdl->y, ob->ful->z - ob->fdl->z);
		//check intersect

		//----------------------------------------back face equation------------------------------------------//
		//line1 eqn (bdl -> bdr)
		dispVect1 = new Coord(ob->bdl->x, ob->bdl->y, ob->bdl->z);
		directVect1 = new Coord(ob->bdr->x - ob->bdl->x, ob->bdr->y - ob->bdl->y, ob->bdr->z - ob->bdl->z);

		//line2 eqn (bdl -> bul)
		dispVect2 = new Coord(ob->bdl->x, ob->bdl->y, ob->bdl->z);
		directVect2 = new Coord(ob->bul->x - ob->bdl->x, ob->bul->y - ob->bdl->y, ob->bul->z - ob->bdl->z);
		//check intersect

	}

	return false;
}


