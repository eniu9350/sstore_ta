/*
 * perf.c
 *
 *  Created on: 2012-9-25
 *      Author: realjin
 */

#include <stdlib.h>
#include <gsl_rng.h>
#include <gsl_randist.h>

#include "adt.h"
#include "key.h"

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

	key** keys = MALLOC(nkeys, key*);
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
	int nkeys = 1000;
	key** keys = perf_generate_keys(nkeys);

	//gen keys
	int i;
	for (i = 0; i < nkeys; i++)
	{
		adtops->setop(data, ks, keys + i, v);

	}
}

int main()
{
	mainadtoperation* adtops;
	adtops = atddtree_getmainadtops();
	test(adtops);
}
