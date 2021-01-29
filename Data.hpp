#include <cmath>
#include "Constants.hpp"

using namespace std;

struct Coord {
    float x, y, z;

    Coord()
    {
        x = float((rand() % MAPSIZEX) - abs(MAPMINX));
        y = float((rand() % MAPSIZEY) - abs(MAPMINY));
        z = float((rand() % MAPSIZEZ));
    }

    Coord(float x_new, float y_new, float z_new)
    {
        x = x_new;
        y = y_new;
        z = z_new;
    }

    void printCoord() {
        using namespace std;
        cout << "Coord (X,Y,Z) = (" << x << "," << y << "," << z << ")\n" << endl;
    }
};


struct Node {
    int node_number;
    float weight;
    bool visited;
    bool in_use;

    Coord* coord;
    //Coord* cell_coord;
    Node* parent;

    Node()
    {
        node_number = 0;
        coord = new Coord();
        weight = 0; // Temp value
        visited = false;
        in_use = false;
        parent = NULL;

        //cell_coord = NULL;
    }

    Node(Coord new_coord)
    {
        node_number = 0;
        weight = 0;
        coord = new Coord(new_coord.x, new_coord.y, new_coord.z);
        visited = false;
        in_use = false;
        parent = NULL;

        //cell_coord = NULL;
    }

    Node(int node_num, Coord new_coord)
    {
        node_number = node_num;
        weight = 0;
        coord = new Coord(new_coord.x, new_coord.y, new_coord.z);
        visited = false;
        in_use = false;
        parent = NULL;

        //cell_coord = NULL;
    }

    ~Node()
    {
        delete coord;
        //delete cell_coord;
        parent = NULL;
    }

    void printNode() {
        using namespace std;
        cout << "Node: " << node_number << endl;
        cout << "Coord(X,Y,Z) = (" << coord->x << "," << coord->y << "," << coord->z << ")\n\n";
        //if(cell_coord != NULL)
            //cout << "Cell (X,Y,Z) = (" << cell_coord->x << "," << cell_coord->y << "," << cell_coord->z << ")\n" << endl;
    }


};