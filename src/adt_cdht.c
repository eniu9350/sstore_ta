/*
 * hashtable.c
 *
 *  Created on: 2012-9-20
 *      Author: realjin
 */

#include <string.h>

#include "adt_cdht.h"
#include "common.h"

//------- main adt interface
mainadtoperation* cdht_getmainadtops()
{
	mainadtoperation* ops = MALLOC(1, mainadtoperation);
	ops->setop = &cdht_mainadt_set;
	ops->getop = &cdht_mainadt_find;
	return ops;
}

int* cdht_mainadt_initop(void* cfg)
{
	cdhtlist* cl = cdhtlist_new();
	return (void*) cl;
}

int cdht_mainadt_set(void* data, keyspace* ks, key* k, adtvalue* v)
{
	cdhtlist* cl = (cdhtlist*) data;
	cdht* h = cdhtlist_getcdht(cl, ks->name);
	if (h == NULL )
	{ //ks not exist, create
		h = cdhtlist_createcdht(cl, ks->name);
	}
	//put k,v in keyspace
	cdht_put(h, k, v);
//cl->namemap =
}

adtvalue* cdht_mainadt_find(void* data, keyspace* ks, key* k)
{
	cdhtlist* cl = (cdhtlist*) data;
	cdht* h = cdhtlist_getcdht(cl, ks->name);
	if (h == NULL )
	{ //not exist
		return NULL ;
	}
	else
	{
		return cdht_get(h, k);
	}
}

//--------ht

cdht* cdht_new(int size, char* name)
{
	int i;
	cdht* h;
	h = MALLOC(1, cdht);
	h->buckets = MALLOC(size, cdhtbucket);
	h->size = size;
	for (i = 0; i < size; i++)
	{
		h->buckets[i].head = NULL;
	}
	strcpy(h->name, name);
	return h;
}

/*
 * 0: exist and put
 * 1: not exist and put
 * -3: not exist and put failure -- size exceeded
 */
static int cdht_bucket_put(cdht* h, int id, key* k, adtvalue* v)
{
	cdhtbucket* b = h->buckets + id;
	kvpair* head;
	kvpair* tail;	//last before tail

	head = b->head;
	tail = head;

	if (head != NULL )
	{
		while (tail->next != NULL )
		{
			if (tail->k equals k)
			{	//found
				adtvalue_free(tail->v);
				//mmm: no copy!
				tail->v = v;
				return 0;
			}
			tail = tail->next;
		}

		if (tail->k equals k)
		{	//found
			adtvalue_free(tail->v);
			//mmm: no copy!
			tail->v = v;
			return 0;
		}
	}

	//not found

	if (id >= h->size)
	{	//
		perror("cdht_bucket_add id>=h->size!");
		return -3;
	}

	kvpair* kvp = kvp_new(k, v);
	tail->next = kvp;

	b->size++;
	return 1;
}

static value* cdht_bucket_get(cdht* h, int id, key* k)
{
	cdhtbucket* b = h->buckets + id;
	kvpair* head;
	kvpair* tail; //tail
	if (id >= h->size)
	{
		perror("cdht_bucket_get id>=h->size!");
		return NULL ;
	}

	head = b->head;

	tail = head;
	while (tail != NULL )
	{
		if (key_cmp(tail->k, k) == 0)
		{
			return tail->v;
		}
		else
		{
			tail = tail->next;
		}
	}

	return NULL ;
}

static void cdht_bucket_remove(cdht* h, int id, key* k)
{
	cdhtbucket* b = h->buckets + id;
	kvpair* head;
	kvpair* p; //tail
	kvpair* prev;
	if (id >= h->size)
	{
		perror("cdht_bucket_remove id>=h->size!");
		return;
	}

	head = b->head;

	prev = p = head;
	while (p != NULL )
	{
		if (key_cmp(p->k, k) == 0)
		{
			//found, remove
			if (p == head)
			{	//set head pointer
				b->head = p->next;
			}
			else
			{
				prev->next = p->next;
			}

			b->size--;
			return;
		}
		else
		{
			prev = p;
			p = p->next;
		}
	}

	printf("cdht_bucket_remove error: not found! k=%s\n", *k);
}

void cdht_put(cdht* h, key* k, value* v)
{
	int hashid = (int) ((hash(*k)) % (h->size));
//printf("hash *k = %ld, h->size=%d\n", hash(*k), h->size);
	//mmm: no check of result
	cdht_bucket_put(h, hashid, k, v);
}

adtvalue* cdht_get(cdht* h, key* k)
{
	int hashid = (int) ((hash(*k)) % (h->size));
//printf("hash *k = %ld, h->size=%d\n", hash(*k), h->size);
	return cdht_bucket_get(h, hashid, k);
}

void cdht_remove(cdht* h, key* k)
{
	int hashid = (int) ((hash(*k)) % (h->size));
//printf("cdht_remove: hash *k = %ld, h->size=%d\n", hash(*k), h->size);
	return cdht_bucket_remove(h, hashid, k);
}

void cdht_getinfo(cdht* h, htinfo* hi)
{

	int i;
	cdhtbucket* b;

	hi->nkeys = 0;
	hi->usedbucket = 0;
	for (i = 0; i < h->size; i++)
	{
		b = h->buckets + i;

		if (b->size != 0)
		{
			hi->nkeys += b->size;
			hi->usedbucket++;
		}
	}

	hi->avgk_valid = hi->nkeys * 1.0 / hi->usedbucket;
	hi->avgk_all = hi->nkeys * 1.0 / h->size;
}

//--------htlist ops

cdhtlist* cdhtlist_new()
{
	cdhtlist* cl = MALLOC(1, cdhtlist);
	cl->list = MALLOC(CDHTLIST_DEFAULT_SIZE, cdht*);
	cl->capacity = CDHTLIST_DEFAULT_SIZE;
	cl->size = 0;
	cl->namemap = cdht_new(CDHTLIST_DEFAULT_SIZE * 2, CDHTLIST_NAMEMAP_NAME);
	return cl;
//xxx
}

cdht* cdhtlist_createcdht(cdhtlist* cl, char* name)
{
	cdht* h;
	int pos = cl->size;
	value* vpos;
	if (pos == cl->capacity)
	{
		perror("cdhtlist_createcdht failed: pos==cl->capacity");
		return NULL ;
	}

	h = cdht_new(CDHT_DEFAULT_SIZE, name);
	cl->list[pos] = h;
	cl->size++;

	vpos = value_create_byint(pos);
	cdht_put(cl->namemap, name, vpos);
	return h;
}

cdht* cdhtlist_getcdht(cdhtlist* cl, char* name)
{
	value* vpos = cdht_get(cl->namemap, name);
	int pos;
	if (vpos == NULL )
	{	//not exist
		return NULL ;
	}
	else
	{
		pos = value2int(vpos);
		return cl->list + pos;
	}
}

