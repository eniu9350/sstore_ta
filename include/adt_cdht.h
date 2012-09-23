/**
 * @brief hashtable defs
 * @file adt_cdht.h
 *
 * @author  niujin
 * @date    2012-09-20
 */



#ifndef _SSTORE_HASHTABLE_H_
#define _SSTORE_HASHTABLE_H_


#include "key.h"
#include "adtvalue.h"

/**
@name cdht defs
@{
*/

typedef struct _kvpair
{
	key* k;
	adtvalue* v;
	struct _kvpair* next;
} kvpair;

typedef struct _cdhtbucket
{
	kvpair* head;
	int size;
} cdhtbucket;

#define CDHT_DEFAULT_SIZE 1024*1024

/*
 * requirement:
 * key - only string
 * value - system-wide
 */
typedef struct _cdht
{
	cdhtbucket* buckets;
	int size;
	char name[256];
} cdht;

/**
@}
*/

/**
@name cdhtlist defs
@{
*/


#define CDHTLIST_DEFAULT_SIZE 255
#define CDHTLIST_NAMEMAP_NAME "namemap"

typedef struct _cdhtlist	{
	cdht** list;
	int size;
	int capacity;
	/*
	 * <name, position> map
	 */
	cdht* namemap;
}cdhtlist;

/**
@}
*/


typedef struct _htinfo	{
	int usedbucket;
	int nkeys;
	double avgk_valid;
	double avgk_all;
}htinfo;



/**
@name cdht ops
@{
*/
cdht* cdht_new(int size, char* name);
void cdht_put(cdht* h, key* k, adtvalue* v);
adtvalue* cdht_get(cdht* h, key* k);
void cdht_remove(cdht* h, key* k);
void cdht_getinfo(cdht* h, htinfo* hi);
/**
@}
*/

/**
@name cdht list ops
@{
*/
cdhtlist* cdhtlist_new();
/**
@}
*/
#endif /* HASHTABLE_H_ */
