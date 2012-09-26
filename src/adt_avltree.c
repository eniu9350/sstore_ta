/*
 * adt_avltree.c
 *
 *  Created on: 2012-9-26
 *      Author: realjin
 */

#include "adt_avltree.h"

mainadtoperation* avltree_getmainadtops()
{
	mainadtoperation* ops = MALLOC(1, mainadtoperation);
	ops->setop = &avltree_mainadt_set;
	ops->getop = &avltree_mainadt_get;
	ops->initop = &avltree_mainadt_init;
	return ops;
}

void* avltree_mainadt_init(void* cfg)
{
	printf(
			"avltree_mainadt_init not implemented!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	return NULL ;
}

int avltree_mainadt_set(void* data, keyspace* ks, key* k, adtvalue* v)
{
	avltree* t = (avltree*) data;
	avltree_insert(t, k, v);
	return 0;
}

adtvalue* avltree_mainadt_get(void* data, keyspace* ks, key* k)
{
	return NULL ;
}

//----------------------------------------------------------- private
avltree_node* avltree_node_create(avltree* t, key* k, adtvalue* v)
{
	avltree_node* n = MALLOC(1, avltree_node);
	n->k = k;
	n->v = v;
	n->lchild = NULL;
	n->rchild = NULL;
	return n;
}

avltree* avltree_create(key* kmin, key* kmax)
{
	avltree* t;
	t = MALLOC(1, avltree);
	t->root = NULL;
	t->h = 0;
	return t;
}

int avltree_find(avltree* t, key* k, avltree_node** n, int* d)
{
	avltree_node* p;
	avltree_node* prev;
	int l;
	int cmp;
	int flag = 0;	// -1: lchild, -2: rchild
	p = t->root;
	l = 1;
	while (p != NULL )
	{
		cmp = key_cmp(p->k, k);
		if (cmp == 0)
		{
			*n = p;
			*d = l;
			return 1;
		}
		else
		{
			if (cmp > 0)
			{
				prev = p;
				p = p->rchild;
				flag = -2;
			}
			else
			{	//cmp<0
				prev = p;
				p = p->lchild;
				flag = -1;
			}
			l++;
		}
	}
	*n = prev;
	*d = l;
	return flag;
}

int avltree_insert(avltree* t, key* k, adtvalue* v)
{
	avltree_node* n = NULL;
	avltree_node* nnew = avltree_node_create(t, k, v);
	int d = 0;
	int find;
	if (t->root == NULL )
	{
		t->root = nnew;
		t->h = 1;
	}
	else
	{
		find = avltree_find(t, k, &n, &d);
		if(find==1){
			printf("avltree_insert: k exist already.\n");
			return 0;
		}else	{
			if(find==-1){

			}else	{

			}
		}
	}

	return 0;
}
