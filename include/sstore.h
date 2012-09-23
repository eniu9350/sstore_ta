#ifndef _SSTORE_SSTORE_H_
#define _SSTORE_SSTORE_H_

#include "column.h"
#include "key.h"
#include "value.h"
#include "adt.h"
#include "keyspace.h"

/**
 @name sstore defs
 @{
 */

#define SSTORE_KS_DEFAULTSIZE 255

/*
 * requirement:
 * key - string
 * value - system-wide
 * keyspace - only string
 */

typedef struct _sstore
{
	//---- main adt related
	mainadtoperation* mainadtops;
	void* mainadtdata;
	//---- main adt related end

	//---- key space related
//	keyspace* kss;
//	int nkss;
	//---- key space related end
} sstore;

sstore* sstore_create(mainadttype type, void* cfg);
/*
 * if k not exist:return error
 * if k exist, if column exist, mod, if column not exist, insert;
 */
int sstore_insert(sstore*ss, keyspace* ks, key* k, colvalpair* cvpairs,
		int ncvpairs, long ts);
//int sstore_set(sstore*ss, key* k, column* cn, value* v);
int sstore_update(sstore*ss, keyspace* ks, key* k, colvalpair* cvpairs,
		int ncvpairs);
value* sstore_get(sstore* ss, key* k, column* cn);

/**
 @}
 */

#endif
