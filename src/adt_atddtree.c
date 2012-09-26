#include "adt_atddtree.h"

mainadtoperation* atddtree_getmainadtops()
{
	mainadtoperation* ops = MALLOC(1, mainadtoperation);
	ops->setop = &atddtree_mainadt_set;
	ops->getop = &atddtree_mainadt_get;
	ops->initop = &atddtree_mainadt_init;
	return ops;
}

void* atddtree_mainadt_init(void* cfg)
{
	atddtree_mainadt_cfg* c = (atddtree_mainadt_cfg*) cfg;
	atddtree* t = atddtree_create(c->kmin, c->kmax);
	return (void*) t;
}

int atddtree_mainadt_set(void* data, keyspace* ks, key* k, adtvalue* v)
{
	atddtree* t = (atddtree*) data;
	atddtree_insert(t, k, v);
	return 0;
}

adtvalue* atddtree_mainadt_get(void* data, keyspace* ks, key* k)
{
	return NULL ;
}


//----------------------------------------------------------- private
atddtree_node* atddtree_node_create(atddtree* t, key* k, adtvalue* v)
{
	atddtree_node* n = MALLOC(1, atddtree_node);
	n->k = k;
	n->v = v;
	n->lchild = NULL;
	n->rchild = NULL;
	return n;
}

atddtree* atddtree_create(key* kmin, key* kmax)
{
	atddtree* t;
	t = MALLOC(1, atddtree);
	t->root = NULL;
	t->kmin = kmin;
	t->kmax = kmax;
	t->h = 0;
	return t;
}

/*
 min: last level min
 max: last level max
 id:

 void atddtree_getrange(int level, int id, key* min, key* max, key* rmin, key* rmax)
 {
 key totalrange = KEYMINUS(max, min);
 *rmin = (id-1)*totalrange/2+1;
 *rmax = id*totalrange/2;
 }
 */

int atddtree_find(atddtree* t, key* k, atddtree_node** n, int* d)
{
	atddtree_node* root = t->root;
	atddtree_node* prev;
	atddtree_node* p;

	prev = p = root;

	int l;	//level
	//int id;	//id in level
	long min;
	long max;
	long range;
	long min1, max1, min2, max2;
	int flag = 0;	// -1: lchild, -2: rchild

	min = key_getlong(t->kmin);
	max = key_getlong(t->kmax);
	l = 1;
	while (p != NULL )
	{
		//id = 1;
		if (key_getlong(p->k) == key_getlong(k))	//mmm
		{
			*n = p;
			*d = l;
			return 1;
		}
		else
		{
//			KEYCPY(range, KEYADD(KEYMINUS(max, min),1));
			range = max - min + 1;

			//choose 
//			KEYCPY( max1, KEYADD(KEYMINUS(min,1), KEYDIV(range, 2)));
			max1 = (min - 1) + range / 2;
//			if (KEYCMP(*k, max1) <= 0)
			if (key_getlong(k) <= max1)
			{	//left
				//min not change
//				KEYCPY( max, max1);
				max = max1;

				prev = p;
				p = p->lchild;
				flag = -1;
			}
			else
			{	//right
//				KEYCPY( min, max1+1);
				min = max1 + 1;
				//max not change				

				prev = p;
				p = p->rchild;
				flag = -2;
			}

			l++;
		}
	}

	*d = l;
	*n = prev;

	return flag;
}

int atddtree_insert(atddtree* t, key* k, adtvalue* v)
{
	//find leaf node that is in charge of the range
	atddtree_node* n = NULL;
//	printf("in insert\n");
	int d = 0;
	int find;
	if (t->root == NULL )
	{
		t->root = atddtree_node_create(t, k, v);
		t->h = 1;
	}
	else
	{
		find = atddtree_find(t, k, &n, &d);
		if (find == 1)
		{	//found
			printf("atddtree_insert: k exist already.\n");
			return 0;	//mmm
		}
		else
		{ // not found , decide whether to create left child or right child
			if (find == -1)
			{	//left
				n->lchild = atddtree_node_create(t, k, v);
			}
			else if (find == -2)
			{	//right
				n->rchild = atddtree_node_create(t, k, v);
			}

			if (d > t->h)
			{
				if (d - t->h != 1)
				{
					printf("atddtree_insert: d-t->h!=1.\n");
				}
				t->h = d;
			}
		}
	}

	return 0;
}

