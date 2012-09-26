/**
 * @brief adt defs
 * @file adt.h
 *
 * @author  niujin
 * @date    2012-09-20
 */

/*
 * adt see nothing about columns, it only see key,value
 */

#ifndef _SSTORE_ADT_H_
#define _SSTORE_ADT_H_

#include "common.h"
#include "keyspace.h"
#include "adtvalue.h"
#include "key.h"

/*
 typedef struct _record
 {
 __u8* bytes;
 int len;
 }record;
 */

typedef struct _mainadtoperation
{
	void* (*initop)(void* cfg);
	int (*setop)(void* data, keyspace* ks, key* k, adtvalue* v);
	adtvalue* (*getop)(void* data, keyspace* ks, key* k);

	/*ks ops*/

} mainadtoperation;

typedef enum _mainadttype
{
	ADT_ATDDTREE, ADT_BTREE, ADT_CDHT
} mainadttype;

/**
 @name main adt interface methods: chainedhashtable
 @{
 */

/*
 * main adt requirement:
 * key - only string
 * value - system-wide
 * keyspace - only string
 */

mainadtoperation* cdht_getmainadtops();
int* cdht_mainadt_initop(void* cfg);
int cdht_mainadt_set(void* data, keyspace* ks, key* k, adtvalue* v);
adtvalue* cdht_mainadt_get(void* data, keyspace* ks, key* k);
/**
 @}
 */

mainadtoperation* atddtree_getmainadtops();
/**
 @name main adt interface methods: atddtree
 @{
 */
typedef struct _atddtree_mainadt_cfg
{
	key* kmin;
	key* kmax;
} atddtree_mainadt_cfg;
void* atddtree_mainadt_init(void* cfg);
int atddtree_mainadt_set(void* data, keyspace* ks, key* k, adtvalue* v);
adtvalue* atddtree_mainadt_get(void* data, keyspace* ks, key* k);
/**
 @}
 */

#endif /* ADT_H_ */
