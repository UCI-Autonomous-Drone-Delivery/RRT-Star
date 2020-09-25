#include <stdlib.h>
#include <vector>
#include <time.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <cuda.h>

#include "Graph.hpp"
using namespace std;

__global__ void checkIfNeighbor(float r,int n,float x, float y,float z, float* xArr,float* yArr,float* zArr,bool* output) {
	int i=threadIdx.x;
	if(i<n) {

		if(5<=r) {
			output[i]=true;
		}
		else {
			output[i]=false;
		}
	}

}

__global__
void initializeArr(float* x,float* y,float* z,Node* node) {

}

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}


vector<Node*> nearestNeighborsGPU(Node* node, float r,int n) {
	Coord* coord=node->coord;

	//arrays of info to pass to gpu
	float *xArr;
	float *yArr;
	float *zArr;
	float x,y,z;
	bool *output;
	x=coord->x;
	y=coord->y;
	z=coord->z;
	gpuErrchk(cudaMallocManaged(&xArr, n*sizeof(float)));
	cudaMallocManaged(&yArr, n*sizeof(float));
	cudaMallocManaged(&zArr, n*sizeof(float));
	//cudaMallocManaged(&output, n*sizeof(bool));

	for(int i=0;i<n;i++) {
		cout<< "made it here\n";
		xArr[i]=5.0f;//adj_list.at(i)->coord->x;
		yArr[i]=5.0f;//adj_list.at(i)->coord->y;
		zArr[i]=5.0f;//adj_list.at(i)->coord->z;
	}

	//checkIfNeighbor<<<1,256>>>(r,num_nodes,x,y,z,xArr,yArr,zArr,output);
	cudaDeviceSynchronize();
	vector<Node*> neighbors;
	
	return neighbors;
}

int main() {
	Coord* startingCoord=new Coord(60,10,29);

	//Graph graph(NUMNODES,startingCoord);

	Coord* c=new Coord(50,50,50);
	Node* n=new Node(-1,c);

	auto t1 = Clock::now();

	vector<Node*> neighbors=nearestNeighborsGPU(n,50,256);
    auto t2 = Clock::now();

	cout << "Delta t2-t1: " 
    	 << std::chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count()
    	 << " nanoseconds" <<endl;

	cin.get();

}