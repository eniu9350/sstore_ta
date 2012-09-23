/*
 * adtvalue.h
 *
 *  Created on: 2012-9-20
 *      Author: realjin
 */

#ifndef _SSTORE_ADTVALUE_H_
#define _SSTORE_ADTVALUE_H_

/*
 value used by adt
 */
typedef struct _adtvalue
{
	__u8* bytes;
	int len;
}adtvalue;

int adtvalue2int(value* v);
value* value_create_byint(int v);
int adtvalue_free(adtvalue* v);

#endif /* ADTVALUE_H_ */
