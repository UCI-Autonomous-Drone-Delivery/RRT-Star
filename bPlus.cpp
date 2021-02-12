#include "bPlus.hpp"




bPlus::bPlus() {
		treeSize = 0;
		treeHead = NULL;
		treeNum = 0;
}

void bPlus::insert(Node* node) {
	TreeNode* root;

	if (treeHead == NULL) {
		root = new TreeNode(true,NULL, treeNum++);
		root->key[0] = node;
		root->size = 1;
		treeSize = 1;
		treeHead = root;
		return;
	}


	TreeNode* cursor;
	TreeNode* parentTemp;
	cursor = traverse(node);

	if (cursor->size < BRANCHSIZE) {
		int i;

		//make room in the key to place our new node
		for (i = 0; i < cursor->size; i++) {
			//if our x value is less than the keys x value, continue
			if (cursor->key[i]->coord->x < node->coord->x) {
				continue;
			}
			else {
				break;
			}
		}
		for (int j = cursor->size-1; j >= i; j--) {
			cursor->key[j+1] = cursor->key[j];
		}
		cursor->key[i] = node;
		cursor->size++;
	}
	else {
		//cout << "split insert" << endl;
		TreeNode* newTreeNode = new TreeNode(true, NULL, treeNum++);
		Node* tempTreeNodeKey[BRANCHSIZE + 1];


		for (int i = 0; i < BRANCHSIZE; i++) {
			tempTreeNodeKey[i] = cursor->key[i];
		}

		//find index in tempTreeNodeKey for our new value 
		int i;
		for (i = 0; i<BRANCHSIZE; i++) {
			if (tempTreeNodeKey[i]->coord->x < node->coord->x) {
				continue;
			}
			else {
				break;
			}
		}
		cout << i << endl;
		//shift all right of i to the right
		for (int j = BRANCHSIZE; j > i; j--) {
			tempTreeNodeKey[j] = tempTreeNodeKey[j - 1];
		}

		tempTreeNodeKey[i] = node;

		//place everything before (BRANCHSIZE+1)/2 in newTreeNode key
		for (int j = 0; j < (BRANCHSIZE+1)/2; j++) {
			cursor->key[j] = tempTreeNodeKey[j];
		}
		//Place everything after (BRANCHSIZE+1)/2 newTreeNode in cursor key
		for (int j = (BRANCHSIZE + 1) / 2; j < BRANCHSIZE+1; j++) {
			newTreeNode->key[j - (BRANCHSIZE + 1) / 2] = tempTreeNodeKey[j];
		}
		cursor->size = (BRANCHSIZE + 1) / 2;
		newTreeNode->size = BRANCHSIZE + 1 - ((BRANCHSIZE + 1) / 2);

		//Cursor childArray[cursor->size] should point to newTreeNode
		cursor->childArray[cursor->size] = newTreeNode;
		//newTreeNode’s childNode[newTreeNode->size] equals to last item in cursor’s childArray
		newTreeNode->childArray[newTreeNode->size] = cursor->childArray[BRANCHSIZE];
		cursor->childArray[BRANCHSIZE] = NULL;



		if (cursor == treeHead) {
			TreeNode* newRoot = new TreeNode(false, NULL, treeNum++);
			newRoot->key[0] = newTreeNode->key[0];
			newRoot->childArray[0] = cursor;
			newRoot->childArray[1] = newTreeNode;
			newRoot->size = 1;
			treeHead = newRoot;
		}
		else {
			//CHECK THIS LINE IDK IF ITS RIGHT
			//cout << " split 2 internal" << endl;
			insertInternal(newTreeNode->key[0], cursor, newTreeNode);
		}
	}
	treeSize++;
	cout << "Root Size is: " << treeHead->size << endl;
}


//This traverses the tree and returns the location of where the input node is/should go
TreeNode* bPlus::traverse(Node* node) {
	TreeNode* cursor=treeHead;
	while (cursor->isLeaf == false) {
		//find the location of the index in which node is/would go
		for (int i = 0; i < cursor->size; i++) {
			//if the x value of node is smaller than the x value in the key
			if (cursor->key[i]->coord->x > node->coord->x) {
				cursor = cursor->childArray[i];
				break;
			}
			//if on the last value in our key
			if (i == cursor->size - 1) {
				cursor = cursor->childArray[i + 1];
				break;
			}
		}
	}
	return cursor;
}

void bPlus::printTree() {
	TreeNode* cursor = treeHead;
	if (cursor->isLeaf == true) {
		printKeys(cursor);
		return;
	}
	for (int i = 0; i < BRANCHSIZE + 1; i++) {
		if(cursor->childArray[i] != NULL)
			printTreeInternal(cursor->childArray[i]);
	}
}

void bPlus::printTreeInternal(TreeNode* cursor) {
	if (cursor->isLeaf == false) {
		for (int i = 0; i < BRANCHSIZE + 1; i++) {
			if (cursor->childArray[i] != NULL)
				printTreeInternal(cursor->childArray[i]);
		}
	}
	else {
		printKeys(cursor);
	}
}


void bPlus::insertInternal(Node* node, TreeNode* cursor, TreeNode* child) {
	if (cursor->size < BRANCHSIZE) {
		int i;
		for (i = 0; i < cursor->size; i++) {
			if (cursor->key[i]->coord->x < node->coord->x) {
				continue;
			}
			else {
				break;
			}
		}
		//shift all right of i to the right
		for (int j = BRANCHSIZE; j > i; j--) {
			cursor[j] = cursor[j - 1];
		}
		cursor->key[i] = node;
		cursor->size++;
		cursor->childArray[i + 1] = child;
	}
	else {
		TreeNode* newTreeNode = new TreeNode(true, NULL, treeNum++);
		Node* tempTreeNodeKey[BRANCHSIZE + 1];
		TreeNode* tempTreeNodeChild[BRANCHSIZE + 2];

		for (int i = 0; i < BRANCHSIZE; i++) {
			tempTreeNodeKey[i] = cursor->key[i];
			tempTreeNodeChild[i] = cursor->childArray[i];
		}
		tempTreeNodeChild[BRANCHSIZE] = cursor->childArray[BRANCHSIZE];


		//find index in tempTreeNodeKey for our new value 
		int i;
		for (i = 0; i < BRANCHSIZE; i++) {
			if (tempTreeNodeKey[i]->coord->x < node->coord->x) {
				continue;
			}
			else {
				break;
			}
		}
		//shift all right of i to the right
		for (int j = BRANCHSIZE; j > i; j--) {
			tempTreeNodeKey[j] = tempTreeNodeKey[j - 1];
		}

		tempTreeNodeKey[i] = node;


		//shift all right of i to the right
		for (int j = BRANCHSIZE; j > i+1; j--) {
			tempTreeNodeKey[j] = tempTreeNodeKey[j - 1];
		}

		tempTreeNodeChild[i + 1] = child;

		newTreeNode->isLeaf = false;



		//place everything before (BRANCHSIZE+1)/2 in newTreeNode key
		for (int j = 0; j < (BRANCHSIZE + 1) / 2; j++) {
			cursor->key[j] = tempTreeNodeKey[j];
		}
		//Place everything after (BRANCHSIZE+1)/2 newTreeNode in cursor key
		for (int j = (BRANCHSIZE + 1) / 2; j < BRANCHSIZE + 1; j++) {
			newTreeNode->key[j - (BRANCHSIZE + 1) / 2] = tempTreeNodeKey[j];
		}
		cursor->size = (BRANCHSIZE + 1) / 2;
		newTreeNode->size = BRANCHSIZE + 1 - ((BRANCHSIZE + 1) / 2);


		//place everything before (BRANCHSIZE+2)/2 in newTreeNode key
		for (int j = 0; j < (BRANCHSIZE + 2) / 2; j++) {
			cursor->childArray[j] = tempTreeNodeChild[j];
		}
		//Place everything after (BRANCHSIZE+2)/2 newTreeNode in cursor key
		for (int j = (BRANCHSIZE + 2) / 2; j < BRANCHSIZE + 1; j++) {
			newTreeNode->childArray[j - (BRANCHSIZE + 2) / 2] = tempTreeNodeChild[j];
		}

		if (cursor == treeHead) {
			TreeNode* newRoot = new TreeNode(false, NULL, treeNum++);
			newRoot->key[0] = cursor->key[0];
			newRoot->childArray[0] = cursor;
			newRoot->childArray[1] = newTreeNode;
			newRoot->size = 1;
			treeHead = newRoot;
		}
		else {
			//CHECK THIS LINE IDK IF ITS RIGHT
			insertInternal(newTreeNode->key[0], cursor, newTreeNode);
		}









	}
}

TreeNode* bPlus::search(Node* node) {
	if (treeSize == 0) {
		return NULL;
	}
	TreeNode* destNode = traverse(node);
	for (int i = 0; i < destNode->size; i++) {
		if (destNode->key[i] == node) {
			return destNode;
		}
	}
	return NULL;
}



TreeNode* bPlus::findParent(TreeNode* cursor, TreeNode* child) {
	return NULL;
}

void bPlus::printKeys(TreeNode* input) {
	cout << "Tree Node for Branch: [" << input->treeID << "],  keys are:" << endl;
	for (int i = 0; i < input->size; i++) {
		input->key[i]->printNode();
	}
};