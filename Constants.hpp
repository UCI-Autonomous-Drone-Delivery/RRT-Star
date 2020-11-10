#ifndef CONSTANTS_H
#define CONSTANTS_H

//Size of search radius for nearest neighbors
const int RADIUS=100;

//Goal Radius
const float GOALRADIUS = 150;

//assume map is a cube for now, this will be changed later
const int MAPSIZE=1000; 

const int MAPMINX = -500;
const int MAPMINY = -500;
const int MAPMINZ = 0;

const int MAPMAXX = 500;
const int MAPMAXY = 500;
const int MAPMAXZ = 1000;


//Number of Nodes to be created
const int NUMNODES=200;
const float STEPSIZE=50.f;

//Number of meters per cell
const int CELLSIZE=50;

//Number of Cells in each Direction (Make sure to update CELLSIZE Accordingly.
//It might be better if we calculate CELLSIZE in xyz directions so that you dont have to manually adjust CELLSIZE)
//WILL OVERFLOW IF NUM OF CELLS IS TOO HIGH
const int NUMCELLSX=2;
const int NUMCELLSY=2;
const int NUMCELLSZ=2;

const int DRONESIZE = 0.1;
const int MINOBSTDIST = DRONESIZE * 1.5;



#endif
