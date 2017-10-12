#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct TreeNode{
	int value;
	struct TreeNode *parent;
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct TreeNode TreeNode;

TreeNode *findNode(int number, TreeNode *Tree);
TreeNode *createNode(int number, TreeNode *node, TreeNode *parent);
TreeNode *addNode(int number, TreeNode *tree);
TreeNode *removeNode(int number, TreeNode *tree);
void *freeNode(TreeNode *node);
int readFile(char *filename);

#endif //_NODE_H_
