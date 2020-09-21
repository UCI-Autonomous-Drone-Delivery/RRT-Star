#ifndef CONSTANTS_H
#define CONSTANTS_H

//assume map is a cube for now, this will be changed later
const int MAPSIZE=100; 

//Number of Nodes to be created
const int NUMNODES=20;
const float STEPSIZE=10.0f;

//Number of meters per cell
const int CELLSIZE=50;

//Number of Cells in each Direction (Make sure to update CELLSIZE Accordingly.
//It might be better if we calculate CELLSIZE in xyz directions so that you dont have to manually adjust CELLSIZE)
const int NUMCELLSX=2;
const int NUMCELLSY=2;
const int NUMCELLSZ=2;


#endif
