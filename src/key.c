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
	k->ptr = (void*) i;
	return k;
}

key* key_create_fromlong(long l)
{
	key* k = MALLOC(1, key);
	k->type = KEYTYPE_INT;
	k->ptr = (void*) l;
	return k;
}

key* key_create_fromdouble(double d)
{
	printf(
			"key_create_fromdouble not implemented!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	return NULL ;
}

long key_getlong(key* k)
{
	if (k->type != KEYTYPE_INT)
	{
		perror("key_getlong: key value not long");
		return -1;
	}

	return (long) k->ptr;
}

int key_cmp(key* k1, key* k2)
{
	int result;
	if (k1->type != k2->type)
	{
		perror("key cmp type not compatible!\n");
		return 0;
	}
	switch (k1->type)
	{
	case KEYTYPE_INT:
		result = ((int) k1->ptr) - ((int) k2->ptr);
		break;
	}

	return result;
}

key* key_cpy(key* k)
{
	key* kcpy = MALLOC(1, key);
	kcpy->type = k->type;
	kcpy->ptr = k->ptr;
	return kcpy;
}

void key_print(key* k)
{
	switch (k->type)
	{
	case KEYTYPE_INT:
		printf("key=%ld\n", ((int) k->ptr));
		break;
	}
}
