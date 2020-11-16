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



//Check the plane equations and make sure we're using the right vectors for each face. I haven't checked those yet
void Obstacles::addObstacle(Coord* a, Coord* b, Coord* c, Coord* d, Coord* e, Coord* f, Coord* g, Coord* h) {
	Obstacle* obstacle = new Obstacle(a,b,c,d,e,f,g,h);
	
	numObstacles++;


	//calculate plane equations
	Coord* ful = a;
	Coord* fur = b;
	Coord* fdl = c;
	Coord* fdr = d;
	Coord* bul = e;
	Coord* bur = f;
	Coord* bdl = g;
	Coord* bdr = h;

	Coord* dispVect1;
	Coord* directVect1;
	Coord* directVect2;

	float xo, yo, zo, a1, b1, c1, d1;
	Coord* face;
	Coord* vector1 = new Coord();
	Coord * vector2 = new Coord();

	//----------------------------------------up face plane equation------------------------------------------//
	xo = ful->x;
	yo = ful->y;
	zo = ful->z;

	//line1 eqn (ful -> fur)
	directVect1 = new Coord(ful->x - fur->x, ful->y - fur->y, ful->z - fur->z);

	//line2 eqn (ful -> bul)
	directVect2 = new Coord(bul->x - ful->x, bul->y - ful->y, bul->z - ful->z);

	face = crossProduct(directVect1, directVect2);	//creates normal vector of two vectors
	a1 = face->x;
	b1 = face->y;
	c1 = face->z;
	d1 = a1 * xo + b1 * yo + c1 * zo;		//Double checck this line
	Plane* plane = new Plane(a1, b1, c1, d1);
	obstacle->pUp = plane;


	//----------------------------------------down face plane equation------------------------------------------//
	xo = fdl->x;
	yo = fdl->y;
	zo = fdl->z;

	//line1 eqn (fdl -> fdr)
	directVect1 = new Coord(fdr->x - fdl->x, fdr->y - fdl->y, fdr->z - fdl->z);

	//line2 eqn (fdl -> bdl)
	directVect2 = new Coord(bdl->x - fdl->x, bdl->y - fdl->y, bdl->z - fdl->z);

	face = crossProduct(directVect1, directVect2);	//creates normal vector of two vectors
	a1 = face->x;
	b1 = face->y;
	c1 = face->z;
	d1 = a1 * xo + b1 * yo + c1 * zo;		//Double check this line
	plane = new Plane(a1, b1, c1, d1);
	obstacle->pDown = plane;


	//----------------------------------------left face plane equation------------------------------------------//
	xo = fdl->x;
	yo = fdl->y;
	zo = fdl->z;

	//line1 eqn (fdl -> bdl)
	directVect1 = new Coord(bdl->x - fdl->x, bdl->y - fdl->y, bdl->z - fdl->z);

	//line5 eqn (fdl -> ful)
	directVect2 = new Coord(ful->x - fdl->x, ful->y - fdl->y, ful->z - fdl->z);

	face = crossProduct(directVect1, directVect2);	//creates normal vector of two vectors
	a1 = face->x;
	b1 = face->y;
	c1 = face->z;
	d1 = a1 * xo + b1 * yo + c1 * zo;		//Double check this line
	plane = new Plane(a1, b1, c1, d1);
	obstacle->pLeft = plane;


	//----------------------------------------right face plane equation------------------------------------------//
	xo = fdr->x;
	yo = fdr->y;
	zo = fdr->z;

	//line1 eqn (fdr -> bdr)
	directVect1 = new Coord(bdr->x - fdr->x, bdr->y - fdr->y, bdr->z - fdr->z);

	//line2 eqn (fdr -> fur)
	directVect2 = new Coord(fur->x - fdr->x, fur->y - fdr->y, fur->z - fdr->z);

	face = crossProduct(directVect1, directVect2);	//creates normal vector of two vectors
	a1 = face->x;
	b1 = face->y;
	c1 = face->z;
	d1 = a1 * xo + b1 * yo + c1 * zo;		//Double check this line
	plane = new Plane(a1, b1, c1, d1);
	obstacle->pRight = plane;

	//----------------------------------------front face plane equation------------------------------------------//
	xo = fdl->x;
	yo = fdl->y;
	zo = fdl->z;

	//line1 eqn (fdl -> fdr)
	directVect1 = new Coord(fdr->x - fdl->x, fdr->y - fdl->y, fdr->z - fdl->z);

	//line2 eqn (fdl -> ful)
	directVect2 = new Coord(ful->x - fdl->x, ful->y - fdl->y, ful->z - fdl->z);

	face = crossProduct(directVect1, directVect2);	//creates normal vector of two vectors
	a1 = face->x;
	b1 = face->y;
	c1 = face->z;
	d1 = a1 * xo + b1 * yo + c1 * zo;		//Double check this line
	plane = new Plane(a1, b1, c1, d1);
	obstacle->pFront = plane;


	//----------------------------------------back face plane equation------------------------------------------//
	xo = bdl->x;
	yo = bdl->y;
	zo = bdl->z;

	//line1 eqn (bdl -> bdr)
	directVect1 = new Coord(bdr->x - bdl->x, bdr->y - bdl->y, bdr->z - bdl->z);

	//line2 eqn (bdl -> bul)
	directVect2 = new Coord(bul->x - bdl->x, bul->y - bdl->y, bul->z - bdl->z);

	face = crossProduct(directVect1, directVect2);	//creates normal vector of two vectors
	a1 = face->x;
	b1 = face->y;
	c1 = face->z;
	d1 = a1 * xo + b1 * yo + c1 * zo;		//Double check this line
	plane = new Plane(a1, b1, c1, d1);
	obstacle->pBack = plane;


	obstacleList.push_back(obstacle);
}

//equivalent to A x B
Coord* Obstacles::crossProduct(Coord* A, Coord* B) {
	Coord* Out = new Coord();
	Out->x = (A->y * B->z) - (A->z * B->y);
	Out->y = -(A->x * B->z) + (A->z * B->x);
	Out->z = (A->x * B->y) - (A->y * B->x);

	return Out;
}


bool Obstacles::collisionCheck(Coord* A, Coord* B) {
	Coord* intersect;

	//check if points are in map (checkInMap returns true if in map)
	bool status;
	status = checkInMap(A);
	if (status == false) {
		return true;
	}

	status = checkInMap(B);
	if (status == false) {
		return true;
	}

	Coord* line = new Coord(B->x - A->x, B->y - A->y, B->z - A->z);
	
	//loop through obstacles
	for (int i = 0; i < numObstacles; i++) {
		//check if the obstacle is between A and B inclusive
		Obstacle* ob = obstacleList.at(i);
		status = checkObstacleInt(line,ob);
		if(status == true) {
			return true;
		}
	}

	return false;
}



	//creates a plane equation and finds point of intersection
bool Obstacles::checkObstacleInt(Coord* line, Obstacle* ob) {


	//CheckTopFace
		//find intersect of pUp
		//get the 4 vectors formed by top corners 
		//take the determinant of all four vectors  https://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line 
			//0 means it is on the line
			//1 means it is on one side
			//-1 means it is on the other side
			//if the point is on the cube side of all of the vectors then it is inside the object
			//NOTE: THIS CHECKS THE WHOLE LINE, WE NEED TO ACCOUNT FOR WHETHER THE POINT OF INTERSECTION IS BETWEEN THE TWO NODES OR NOT

	//repeat for all faces

	return NULL;
}

//returns true if within map
bool Obstacles::checkInMap(Coord* c) {
	//if outside map, return true
	if (c->x >= MAPMAXX - MINOBSTDIST || c->x <= MAPMINX + MINOBSTDIST ||
		c->y >= MAPMAXY - MINOBSTDIST || c->y <= MAPMINY + MINOBSTDIST ||
		c->z >= MAPMAXZ - MINOBSTDIST || c->z <= MAPMINZ + MINOBSTDIST)
	{
		return false;
	}
	return true;
}