#ifndef _SSTORE_COLUMN_H_
#define _SSTORE_COLUMN_H_

#include "value.h"
#include "adtvalue.h"

typedef struct _column
{
	char* name;
} column;

//column value pair
typedef struct _colvalpair
{
	column* c;
	value* v;
} colvalpair;

adtvalue* cvpair2adtvalue(colvalpair* cvp, int ncvpairs);

#endif
