/*
 * key.c
 *
 *  Created on: 2012-9-25
 *      Author: realjin
 */

#include "key.h"

key* key_create_fromint(int i)
{
	key* k = MALLOC(1, key);
	k->type = KEYTYPE_INT;
	k->ptr
	return k;
}

key* key_create_fromlong(long l)
{

}

key* key_create_fromdouble(double d)
{

}
