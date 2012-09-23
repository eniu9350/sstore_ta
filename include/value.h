/*
 * value.h
 *
 *  Created on: 2012-9-20
 *      Author: realjin
 */

#ifndef _SSTORE_VALUE_H_
#define _SSTORE_VALUE_H_

#include "common.h"



/*
 * value used by sstore
 */

typedef struct _value
{
	__u8* bytes;
	int len;
} value;



#endif /* VALUE_H_ */
