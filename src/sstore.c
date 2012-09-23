/*
 * sstore.c
 *
 *  Created on: 2012-9-20
 *      Author: realjin
 */

#include "sstore.h"

sstore* sstore_create(mainadttype type, void* cfg)
{
	sstore* ss = MALLOC(1, sstore);
	if (type == ADT_CDHT)
	{
		ss->mainadtops = cdht_getadtops();
		//parse config data
	}

	ss->mainadtdata = ss->mainadtops->initop(cfg);

	//init ks
//	ss->kss = MALLOC(SSTORE_KS_DEFAULTSIZE, keyspace);
//	ss->nkss = SSTORE_KS_DEFAULTSIZE;

	return ss;
}

int sstore_insert(sstore*ss, keyspace* ks, key* k, colvalpair* cvpairs,
		int ncvpairs, long ts)
{
	//1. insert to main adt
	mainadtoperation mainadtops = ss->mainadtops;
	adtvalue* v = cvpair2adtvalue(cvpairs, ncvpairs);
	mainadtops->setop(ss->mainadtdata, ks, k, v);

	//2. update time index

}

int sstore_update(sstore*ss, keyspace* ks, key* k, colvalpair* cvpairs,
		int ncvpairs)
{
	adtvalue* r = ss->mainadtops->getop(ss->mainadtdata, k);
	if (r == NULL )
	{
		//error
	}
	else
	{		//modify, time ignored

	}
}

value* sstore_get(sstore* ss, key* k, column* c)
{
	record* r = ss->adtops->findop(ss->adtdata, k);
}

int main()
{
	printf("aaa");
}
