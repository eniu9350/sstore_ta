/**
 * @brief hashtable defs
 * @file key.h
 *
 * @author  niujin
 * @date    2012-09-20
 */

#ifndef _SSTORE_KEY_H_
#define _SSTORE_KEY_H_

#include "common.h"

#define KEYTYPE_INT 1
#define KEYTYPE_DOUBLE 3

//typedef __u32 key;
/*
 * key used both by sstore and adt;
 * ref: redis robj implementation in 2.x
 */
typedef struct _key
{
	unsigned type:4;
	void* ptr;
} key;



key* key_create_fromint(int i);
key* key_create_fromlong(long l);
key* key_create_fromdouble(double d);
key* key_cpy(key* k);

long key_getlong(key* k);
int key_cmp(key* k1, key* k2);

void key_print(key* k);

#endif /* KEY_H_ */
