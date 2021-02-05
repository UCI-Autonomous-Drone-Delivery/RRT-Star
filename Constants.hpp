#ifndef CONSTANTS_H
#define CONSTANTS_H

// WORLD SEED
const int SEED = 69;

// Number of drones
const int NUMDRONES = 3;

//Size of search radius for nearest neighbors
const int RADIUS = 15;

//Goal Radius
const float GOALRADIUS = 40.f;

//Number of Nodes to be created
const int NUMNODES = 10000;
const float STEPSIZE = 7.5; // Remember to set stepsize corresponding to how big the map is

//assume map is a cube for now, this will be changed later

// Assuming center of room is (0,0,0) Z at 0 is ground level
// Let us use cm for our sizes 1m = 100cm
// 3.00m X 3.00m X 3.00m

const int MAPMINX = -150;
const int MAPMINY = -150;
const int MAPMINZ = 0;

const int MAPMAXX = 150;
const int MAPMAXY = 150;
const int MAPMAXZ = 200;

const int MAPSIZEX = abs(MAPMAXX - MAPMINX);
const int MAPSIZEY = abs(MAPMAXY - MAPMINY);
const int MAPSIZEZ = abs(MAPMAXZ - MAPMINZ);

//Number of meters per cell
const int CELLSIZE=50;

//Number of Cells in each Direction (Make sure to update CELLSIZE Accordingly.
//It might be better if we calculate CELLSIZE in xyz directions so that you dont have to manually adjust CELLSIZE)
//WILL OVERFLOW IF NUM OF CELLS IS TOO HIGH
const int NUMCELLSX=2;
const int NUMCELLSY=2;
const int NUMCELLSZ=2;

const float DRONESIZE = 0.1;
const float MINOBSTDIST = DRONESIZE * 1.5;



#endif