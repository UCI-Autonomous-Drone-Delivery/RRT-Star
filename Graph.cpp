#include "Graph.hpp"

Graph::Graph(Coord* startCoord) {
	//create array of cells
	for(int i=0;i<NUMCELLSX;i++) {
		for(int j=0;j<NUMCELLSY;j++) {
			for(int k=0;k<NUMCELLSZ;k++) {
				//create cell and store in cells[i][j][k]
				struct Cell* newCell=new Cell;
				cells[i][j][k]=newCell;
	
			}
		}
	}

	//create the first node
	struct Node* firstNode=new Node;
	firstNode->coord=startCoord;
	firstNode->weight=0;

	//figure out which cell the node belongs to and add it to the cell
	Coord* cellCoord = getCellCoords(firstNode);
	cells[(int)cellCoord->x][(int)cellCoord->y][(int)cellCoord->z]->containedNodes.push_back(firstNode);

	//add node to a nodeList, and add the nodeList to the Graph's Adjacency list
	struct NodeList* nodeList=new NodeList;
	nodeList->list.push_back(firstNode);
	adjList.push_back(nodeList);
}

Coord* Graph::getCellCoords(Node* node) {
	Coord* cellCoord=new Coord;
	cellCoord->x=(int)node->coord->x/CELLSIZE;
	cellCoord->y=(int)node->coord->y/CELLSIZE;
	cellCoord->z=(int)node->coord->z/CELLSIZE;

	return cellCoord;
}

void Graph::addEdge(Node* startNode, Node* endNode, float weight) {
	//using findNeighbors function will speed up the part where you check if the node exists


	//Check if startNode and endNode already exist
	//add them to the adjacency list if they don't exist
	//add endNode to startNode's connectedNodes list.
}

int main() {
	struct Coord* c=new Coord;
	c->x=15;
	c->y=21;
	c->z=20;


	Graph* g=new Graph(c);
}