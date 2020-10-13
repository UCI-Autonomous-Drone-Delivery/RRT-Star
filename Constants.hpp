#ifndef CONSTANTS_H
#define CONSTANTS_H

//Size of search radius for nearest neighbors
const int RADIUS=5;

//Goal Radius
const float GOALRADIUS = 25;

//assume map is a cube for now, this will be changed later
const int MAPSIZE=100; 

//Number of Nodes to be created
const int NUMNODES=30;
const float STEPSIZE=1.f;

//Number of meters per cell
const int CELLSIZE=50;

//Number of Cells in each Direction (Make sure to update CELLSIZE Accordingly.
//It might be better if we calculate CELLSIZE in xyz directions so that you dont have to manually adjust CELLSIZE)
const int NUMCELLSX=2;
const int NUMCELLSY=2;
const int NUMCELLSZ=2;


#endif
