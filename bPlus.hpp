#ifndef BPLUS_HPP
#define BPLUS_HPP

#include <stdlib.h>
#include <vector>
#include <stack>
#include <list>
#include <time.h>
#include <cmath>
#include <iostream>
#include <assert.h>

#include "Data.hpp"


struct TreeNode {
	bool isLeaf;
	Node* key[BRANCHSIZE]; // holds node at same level
	TreeNode* childArray[BRANCHSIZE + 1]; // holds nodes at next level
	TreeNode* parent;
	int size;
	TreeNode(bool isLe, TreeNode* par) {
		isLeaf = isLe;
		parent = par;
		size = 0;

		//initialize arrays to be null
		for (int i = 0; i < BRANCHSIZE; i++) {
			key[i] = NULL;
			childArray[i] = NULL;
		}
		childArray[BRANCHSIZE] = NULL;
	}
};


class bPlus {
public:
	bPlus();
	void insert(Node* node);
	TreeNode* traverse(Node* node);
	TreeNode* search(Node* node);
	void insertInternal(Node* node, TreeNode* cursor, TreeNode* child);
	TreeNode* findParent(TreeNode* cursor, TreeNode* child);

private:
	int treeSize;
	TreeNode* treeHead;

};



#endif