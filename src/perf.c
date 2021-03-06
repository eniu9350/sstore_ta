/*
 * perf.c
 *
 *  Created on: 2012-9-25
 *      Author: realjin
 */

#include <stdlib.h>
#include <gsl_rng.h>
#include <gsl_randist.h>
#include <time.h>
#include <unistd.h>

#include "adt.h"
#include "key.h"
#include "adt_atddtree.h"
#include "adt_avltree.h"

static key** perf_generate_keys(int nkeys)
{
	key** keys; // = MALLOC(nkeys, key*);

	//-------------
	gsl_rng *r;
	const gsl_rng_type *T;
	int n = 5;
	double u;
	int i;
	double mean_ia = 205;	//mmm

	T = gsl_rng_ranlxs0;

	//gen arrival
	gsl_rng_default_seed = ((unsigned long) (time(NULL )));
	r = gsl_rng_alloc(T);
	double* exp_sample_ir = MALLOC(nkeys, double);
	double abstemp = 0;
	for (i = 0; i < nkeys; i++)
	{
		exp_sample_ir[i] = gsl_ran_exponential(r, mean_ia);
		//exp_sample_ir[i] =  2+(i%10000)*0.3;
#ifdef LOGISTIC
		abstemp = gsl_ran_logistic(r, 1);
		if(abstemp<0)
		{
			abstemp=0-abstemp;
		}
		exp_sample_ir[i] = abstemp;
#endif
		//exp_sample_ir[i] = 5*gsl_ran_beta(r, 5, 1);
		//exp_sample_ir[i] = 5*gsl_ran_lognormal(r, 5, 0.25);
		//printf("exp: %f\n", exp_sample_ir[i]);
	}

	double* arrival_real = MALLOC(nkeys, double);
	arrival_real[0] = 1.0;
	for (i = 1; i < nkeys; i++)
	{
		arrival_real[i] = arrival_real[i - 1] + exp_sample_ir[i - 1];
		//printf("arrival_real: %f\n", arrival_real[i]);
	}

	keys = MALLOC(nkeys, key*);
	for (i = 0; i < nkeys; i++)
	{
		keys[i] = key_create_fromint((int) arrival_real[i]);
		//printf("arrival: %ld\n", arrival[i]);
	}
	//------------- end

	return keys;
}

void test(mainadtoperation* adtops)
{
	void* data;
	int nkeys = 1024*1024 - 1;
	int i;
	struct timespec ts1, ts2;

	key** keys = perf_generate_keys(nkeys);
	atddtree_mainadt_cfg* cfg = MALLOC(1, atddtree_mainadt_cfg);
	cfg->kmin = key_create_fromlong(1);
	key* kmax;
	kmax = keys[0];
	for (i = 0; i < nkeys; i++)
	{
		if (key_cmp(keys[i], kmax) > 0)
		{
			kmax = keys[i];
		}
		//printf("arrival: %ld\n", arrival[i]);
	}
	cfg->kmax = kmax;
	data = adtops->initop((void*) cfg);

	//insert keys
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts1);
	for (i = 0; i < nkeys; i++)
	{
//		key_print(keys[i]);
		adtops->setop(data, NULL, keys[i], NULL );	//mmm: ks
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts2);

//	printf("sec = %d, nsec=%ld\n", ts1.tv_sec, ts1.tv_nsec);
//	printf("sec = %d, nsec=%ld\n", ts2.tv_sec, ts2.tv_nsec);

//	printf("height=%d, sizeof void*=%d, sizeof long=%d\n",
//			((atddtree*) data)->h, sizeof(void*), sizeof(long));
	double tcost = (ts2.tv_sec - ts1.tv_sec)
			+ (ts2.tv_nsec - ts1.tv_nsec) / 1000000000.0;
	printf("time=%f\n", tcost);
	adtops->printinfo(data);
//	printf("height=%d, time=%f\n", ((atddtree*) data)->h, tcost);
}

int main()
{
	mainadtoperation* adtops;
//	adtops = atddtree_getmainadtops();
	adtops = avltree_getmainadtops();
	test(adtops);
}
