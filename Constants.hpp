#ifndef CONSTANTS_H
#define CONSTANTS_H

// WORLD SEED
const int SEED = 69;

//Size of search radius for nearest neighbors
const int RADIUS=15;

//Goal Radius
const float GOALRADIUS = 30;

//assume map is a cube for now, this will be changed later

const int MAPMINX = -50;
const int MAPMINY = -50;
const int MAPMINZ = 0;

const int MAPMAXX = 50;
const int MAPMAXY = 50;
const int MAPMAXZ = 100;

const int MAPSIZEX = abs(MAPMAXX - MAPMINX);
const int MAPSIZEY = abs(MAPMAXY - MAPMINY);
const int MAPSIZEZ = abs(MAPMAXZ - MAPMINZ);



//Number of Nodes to be created
const int NUMNODES=100;
const float STEPSIZE=10.f;

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
