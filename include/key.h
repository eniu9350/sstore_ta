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

#define KEYCMP(k1, k2) ((k1)==(k2)?0:( (k1)>(k2)?1:-1) )
#define KEYCPY(k1, k2) ((k1)=(k2))

#define KEYADD(k1, k2) ((k1)+(k2))
#define KEYMINUS(k1, k2) ((k1)-(k2))
#define KEYDIV(k, d) ((k)/(d))


key* key_create_fromint(int i);
key* key_create_fromlong(long l);
key* key_create_fromdouble(double d);

#endif /* KEY_H_ */
