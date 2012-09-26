/*
 AVL Tree
 */

#ifndef _SSTORE_ADT_AVLTREE_H_
#define _SSTORE_ADT_AVLTREE_H_

#include "common.h"
#include "key.h"
#include "column.h"
#include "adt.h"

typedef struct _avltree_node
{
	key* k;
	adtvalue* v;
	struct _avltree_node* lchild;
	struct _avltree_node* rchild;
	int subh;	//height of the subtree
} avltree_node;

typedef struct _avltree
{
	avltree_node* root;
	int h;	//height
} avltree;

#endif /* _SSTORE_ADT_AVLTREE_H_ */
