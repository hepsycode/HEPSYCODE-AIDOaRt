/********************************************************************************
 * University of L'Aquila - HEPSYCODE Source Code License                       *
 *                                                                            	*
 *                                                                            	*
 * (c) 2018-2019 Centre of Excellence DEWS All rights reserved                	*
 ********************************************************************************
 * <one line to give the program's name and a brief idea of what it does.>      *
 * Copyright (C) 2022  Vittoriano Muttillo, Luigi Pomante                       *                                    *
 *                                                                              *
 * This program is free software: you can redistribute it and/or modify         *
 * it under the terms of the GNU General Public License as published by         *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * This program is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 * GNU General Public License for more details.                                 *
 *                                                                              *
 ********************************************************************************
 *                                                                              *
 * Created on: 09/May/2023                                                      *
 * Authors: Vittoriano Muttillo, Marco Santic, Luigi Pomante                    *
 *                                                                              *
 * email: vittoriano.muttillo@guest.univaq.it                                   *
 *        marco.santic@guest.univaq.it                                          *
 *        luigi.pomante@univaq.it                                               *
 *                                                                              *
 ********************************************************************************
 * This code has been developed from an HEPSYCODE model used as demonstrator by	*
 * University of L'Aquila.                                                      *
 *******************************************************************************/

#include <systemc.h>
#include "../mainsystem.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


////////////////////////////// GENANN //////////////////

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ann_01_GENANN_RANDOM
/* We use the following for uniform random numbers between 0 and 1.
 * If you have a better function, redefine this macro. */
#define ann_01_GENANN_RANDOM() (((double)rand())/RAND_MAX)
#endif

struct ann_01_genann;

typedef double (*ann_01_genann_actfun)(const struct ann_01_genann *ann, double a);

typedef struct ann_01_genann {
    /* How many inputs, outputs, and hidden neurons. */
    int inputs, hidden_layers, hidden, outputs;

    /* Which activation function to use for hidden neurons. Default: gennann_act_sigmoid_cached*/
    ann_01_genann_actfun activation_hidden;

    /* Which activation function to use for output. Default: gennann_act_sigmoid_cached*/
    ann_01_genann_actfun activation_output;

    /* Total number of weights, and size of weights buffer. */
    int total_weights;

    /* Total number of neurons + inputs and size of output buffer. */
    int total_neurons;

    /* All weights (total_weights long). */
    double *weight;

    /* Stores input array and output of each neuron (total_neurons long). */
    double *output;

    /* Stores delta of each hidden and output neuron (total_neurons - inputs long). */
    double *delta;

} ann_01_genann;

#ifdef __cplusplus
}
#endif



///////////////////////////////////// GENANN ///////////////////////////

#ifndef ann_01_genann_act
#define ann_01_genann_act_hidden ann_01_genann_act_hidden_indirect
#define ann_01_genann_act_output ann_01_genann_act_output_indirect
#else
#define ann_01_genann_act_hidden ann_01_genann_act
#define ann_01_genann_act_output ann_01_genann_act
#endif

#define ann_01_LOOKUP_SIZE 4096

double ann_01_genann_act_hidden_indirect(const struct ann_01_genann *ann, double a)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) return ann->activation_hidden(ann, a);
}

double ann_01_genann_act_output_indirect(const struct ann_01_genann *ann, double a)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) return ann->activation_output(ann, a);
}

const double ann_01_sigmoid_dom_min = -15.0;
const double ann_01_sigmoid_dom_max = 15.0;
double ann_01_interval;
double ann_01_lookup[ann_01_LOOKUP_SIZE];

#ifdef __GNUC__
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
#define unused          __attribute__((unused))
#else
#define likely(x)       x
#define unlikely(x)     x
#define unused
#pragma warning(disable : 4996) /* For fscanf */
#endif


double ann_01_genann_act_sigmoid(const ann_01_genann *ann unused, double a)
{HEPSY_S(ann_01_id)

	HEPSY_S(ann_01_id) if (a < -45.0)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return 0;
	}

	HEPSY_S(ann_01_id) if (a > 45.0)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return 1;
	}

	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) return 1.0 / (1 + exp(-a));
}

void ann_01_genann_init_sigmoid_lookup(const ann_01_genann *ann)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) const double f = (ann_01_sigmoid_dom_max - ann_01_sigmoid_dom_min) / ann_01_LOOKUP_SIZE;
	HEPSY_S(ann_01_id) int i;

	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) ann_01_interval = ann_01_LOOKUP_SIZE / (ann_01_sigmoid_dom_max - ann_01_sigmoid_dom_min);

	HEPSY_S(ann_01_id) for (i = 0; i < ann_01_LOOKUP_SIZE; ++i)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id)ann_01_lookup[i] = ann_01_genann_act_sigmoid(ann, ann_01_sigmoid_dom_min + f * i);
	HEPSY_S(ann_01_id)}
}

double ann_01_genann_act_sigmoid_cached(const ann_01_genann *ann unused, double a)
{HEPSY_S(ann_01_id)

	HEPSY_S(ann_01_id) assert(!isnan(a));

	HEPSY_S(ann_01_id) if (a < ann_01_sigmoid_dom_min)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return ann_01_lookup[0];
	}

	HEPSY_S(ann_01_id) if (a >= ann_01_sigmoid_dom_max)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return ann_01_lookup[ann_01_LOOKUP_SIZE - 1];
	}

	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) size_t j = (size_t)((a-ann_01_sigmoid_dom_min)*ann_01_interval+0.5);

    /* Because floating point... */
	HEPSY_S(ann_01_id) if (unlikely(j >= ann_01_LOOKUP_SIZE))
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return ann_01_lookup[ann_01_LOOKUP_SIZE - 1];
	}

	HEPSY_S(ann_01_id) return ann_01_lookup[j];
}

double ann_01_genann_act_linear(const struct ann_01_genann *ann unused, double a)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) return a;
}

double ann_01_genann_act_threshold(const struct ann_01_genann *ann unused, double a)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) return a > 0;
}

void ann_01_genann_randomize(ann_01_genann *ann)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) int i;
	HEPSY_S(ann_01_id) for (i = 0; i < ann->total_weights; ++i)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) double r = ann_01_GENANN_RANDOM();
        /* Sets weights from -0.5 to 0.5. */
		HEPSY_S(ann_01_id) ann->weight[i] = r - 0.5;
	HEPSY_S(ann_01_id) }
}

ann_01_genann *ann_01_genann_init(int inputs, int hidden_layers, int hidden, int outputs)
{HEPSY_S(ann_01_id)

	HEPSY_S(ann_01_id) if (hidden_layers < 0)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return 0;
	}

	HEPSY_S(ann_01_id) if (inputs < 1)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return 0;
	}

	HEPSY_S(ann_01_id) if (outputs < 1)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return 0;
	}

	HEPSY_S(ann_01_id) if (hidden_layers > 0 && hidden < 1)
    {HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return 0;
    }


	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) const int hidden_weights = hidden_layers ? (inputs+1) * hidden + (hidden_layers-1) * (hidden+1) * hidden : 0;
	HEPSY_S(ann_01_id)

	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) const int output_weights = (hidden_layers ? (hidden+1) : (inputs+1)) * outputs;
	HEPSY_S(ann_01_id)

	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) const int total_weights = (hidden_weights + output_weights);
	HEPSY_S(ann_01_id)

	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) const int total_neurons = (inputs + hidden * hidden_layers + outputs);
	HEPSY_S(ann_01_id)

    /* Allocate extra size for weights, outputs, and deltas. */
	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) const int size = sizeof(ann_01_genann) + sizeof(double) * (total_weights + total_neurons + (total_neurons - inputs));

	HEPSY_S(ann_01_id) ann_01_genann *ret = (ann_01_genann *)malloc(size);

	HEPSY_S(ann_01_id) if (!ret)
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return 0;
	}

	HEPSY_S(ann_01_id) ret->inputs = inputs;
	HEPSY_S(ann_01_id) ret->hidden_layers = hidden_layers;
	HEPSY_S(ann_01_id) ret->hidden = hidden;
	HEPSY_S(ann_01_id) ret->outputs = outputs;

	HEPSY_S(ann_01_id) ret->total_weights = total_weights;
	HEPSY_S(ann_01_id) ret->total_neurons = total_neurons;

    /* Set pointers. */
	HEPSY_S(ann_01_id) ret->weight = (double*)((char*)ret + sizeof(ann_01_genann));
	HEPSY_S(ann_01_id) ret->output = ret->weight + ret->total_weights;
	HEPSY_S(ann_01_id) ret->delta = ret->output + ret->total_neurons;

	HEPSY_S(ann_01_id) ann_01_genann_randomize(ret);

	HEPSY_S(ann_01_id) ret->activation_hidden = ann_01_genann_act_sigmoid_cached;
	HEPSY_S(ann_01_id) ret->activation_output = ann_01_genann_act_sigmoid_cached;

	HEPSY_S(ann_01_id) ann_01_genann_init_sigmoid_lookup(ret);

	HEPSY_S(ann_01_id) return ret;
}

void ann_01_genann_free(ann_01_genann *ann)
{HEPSY_S(ann_01_id)
    /* The weight, output, and delta pointers go to the same buffer. */
	HEPSY_S(ann_01_id) free(ann);
}

//genann *genann_read(FILE *in)
//genann *genann_copy(genann const *ann)

double const *ann_01_genann_run(ann_01_genann const *ann, double const *inputs)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) double const *w = ann->weight;
	HEPSY_S(ann_01_id) double *o = ann->output + ann->inputs;
	HEPSY_S(ann_01_id) double const *i = ann->output;

    /* Copy the inputs to the scratch area, where we also store each neuron's
     * output, for consistency. This way the first layer isn't a special case. */
	HEPSY_S(ann_01_id) memcpy(ann->output, inputs, sizeof(double) * ann->inputs);

	HEPSY_S(ann_01_id) int h, j, k;

	HEPSY_S(ann_01_id) if (!ann->hidden_layers)
    {HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) double *ret = o;
    	HEPSY_S(ann_01_id) for (j = 0; j < ann->outputs; ++j)
        {HEPSY_S(ann_01_id)
    		HEPSY_S(ann_01_id)
    		HEPSY_S(ann_01_id) double sum = *w++ * -1.0;
        	HEPSY_S(ann_01_id) for (k = 0; k < ann->inputs; ++k)
            {HEPSY_S(ann_01_id)
        		HEPSY_S(ann_01_id)
        		HEPSY_S(ann_01_id) sum += *w++ * i[k];
            HEPSY_S(ann_01_id) }
        	HEPSY_S(ann_01_id) *o++ = ann_01_genann_act_output(ann, sum);
        	HEPSY_S(ann_01_id) }
    	HEPSY_S(ann_01_id) return ret;
    }

    /* Figure input layer */
	HEPSY_S(ann_01_id) for (j = 0; j < ann->hidden; ++j)
    {HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) double sum = *w++ * -1.0;
    	HEPSY_S(ann_01_id) for (k = 0; k < ann->inputs; ++k)
        {HEPSY_S(ann_01_id)
    		HEPSY_S(ann_01_id)
    		HEPSY_S(ann_01_id) sum += *w++ * i[k];
        HEPSY_S(ann_01_id) }
    	HEPSY_S(ann_01_id) *o++ = ann_01_genann_act_hidden(ann, sum);
    HEPSY_S(ann_01_id) }

	HEPSY_S(ann_01_id) i += ann->inputs;

    /* Figure hidden layers, if any. */
	HEPSY_S(ann_01_id) for (h = 1; h < ann->hidden_layers; ++h)
    {HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) for (j = 0; j < ann->hidden; ++j)
        {HEPSY_S(ann_01_id)
			HEPSY_S(ann_01_id)
			HEPSY_S(ann_01_id) double sum = *w++ * -1.0;
        	HEPSY_S(ann_01_id) for (k = 0; k < ann->hidden; ++k)
            {HEPSY_S(ann_01_id)
        		HEPSY_S(ann_01_id)
        		HEPSY_S(ann_01_id) sum += *w++ * i[k];
            HEPSY_S(ann_01_id) }
        	HEPSY_S(ann_01_id) *o++ = ann_01_genann_act_hidden(ann, sum);
        HEPSY_S(ann_01_id) }

    	HEPSY_S(ann_01_id) i += ann->hidden;
    HEPSY_S(ann_01_id) }

	HEPSY_S(ann_01_id) double const *ret = o;

    /* Figure output layer. */
	HEPSY_S(ann_01_id) for (j = 0; j < ann->outputs; ++j)
    {HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) double sum = *w++ * -1.0;
    	HEPSY_S(ann_01_id) for (k = 0; k < ann->hidden; ++k)
        {HEPSY_S(ann_01_id)
    		HEPSY_S(ann_01_id)
    		HEPSY_S(ann_01_id) sum += *w++ * i[k];
        HEPSY_S(ann_01_id) }
    	HEPSY_S(ann_01_id) *o++ = ann_01_genann_act_output(ann, sum);
    HEPSY_S(ann_01_id) }

    /* Sanity check that we used all weights and wrote all outputs. */
	HEPSY_S(ann_01_id) assert(w - ann->weight == ann->total_weights);
	HEPSY_S(ann_01_id) assert(o - ann->output == ann->total_neurons);

	HEPSY_S(ann_01_id) return ret;
}

//void genann_train(genann const *ann, double const *inputs, double const *desired_outputs, double learning_rate)
//void genann_write(genann const *ann, FILE *out)

/////////////////////// ANN ////////////////////////

#define ann_01_NUM_DEV		1		// The equipment is composed of NUM_DEV devices ...

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define ann_01_MAX_ANN 			100		// Maximum MAX_ANN ANN

#define ann_01_ANN_INPUTS			2		// Number of inputs
#define ann_01_ANN_HIDDEN_LAYERS	1		// Number of hidden layers
#define ann_01_ANN_HIDDEN_NEURONS	2		// Number of neurons of every hidden layer
#define ann_01_ANN_OUTPUTS			1		// Number of outputs

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define ann_01_ANN_EPOCHS			10000
#define ann_01_ANN_DATASET			6
#define ann_01_ANN_LEARNING_RATE	3		// ...

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define ann_01_MAX_ERROR 0.00756	// 0.009

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
static int ann_01_nANN = -1 ;				// Number of ANN that have been created

static ann_01_genann * ann_01_ann[ann_01_MAX_ANN] ;		// Now up to MAX_ANN ann

//static double ann_01_trainingInput[ann_01_ANN_DATASET][ann_01_ANN_INPUTS] =     { {0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 1}, {0, 0} } ;
//static double ann_01_trainingExpected[ann_01_ANN_DATASET][ann_01_ANN_OUTPUTS] = { {0},    {1},    {1},    {0},    {1},    {0}    } ;

static double ann_01_weights[] =	{
								-3.100438,
								-7.155774,
								-7.437955,
								-8.132828,
								-5.583678,
								-5.327152,
								5.564897,
								-12.201226,
								11.771879
							} ;

// static double input[4][3] = {{0, 0, 1}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}};
// static double output[4] = {0, 1, 1, 0};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
static int ann_01_annCheck(int index);
static int ann_01_annCreate(int n);

//-----------------------------------------------------------------------------
// Check the correctness of the index of the ANN
//-----------------------------------------------------------------------------
int ann_01_annCheck(int index)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) if( (index < 0) || (index >= ann_01_nANN) )
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return( EXIT_FAILURE );
	}

	HEPSY_S(ann_01_id) return( EXIT_SUCCESS );
}

//-----------------------------------------------------------------------------
// Create n ANN
//-----------------------------------------------------------------------------
int ann_01_annCreate(int n)
{HEPSY_S(ann_01_id)
	// If already created, or not legal number, or too many ANN, then error
	HEPSY_S(ann_01_id) if( (ann_01_nANN != -1)  || (n <= 0) || (n > ann_01_MAX_ANN) )
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return( EXIT_FAILURE );
	}

	// Create the ANN's
	HEPSY_S(ann_01_id) for( int i = 0; i < n; i++ )
	{HEPSY_S(ann_01_id)
		// New ANN with ANN_INPUT inputs, ANN_HIDDEN_LAYER hidden layers all with ANN_HIDDEN_NEURON neurons, and ANN_OUTPUT outputs
		HEPSY_S(ann_01_id) ann_01_ann[i] = ann_01_genann_init(ann_01_ANN_INPUTS, ann_01_ANN_HIDDEN_LAYERS, ann_01_ANN_HIDDEN_NEURONS, ann_01_ANN_OUTPUTS);
		HEPSY_S(ann_01_id) if( ann_01_ann[i] == 0 )
		{HEPSY_S(ann_01_id)
			HEPSY_S(ann_01_id) for(int j = 0; j < i; j++)
			{HEPSY_S(ann_01_id)
				HEPSY_S(ann_01_id) ann_01_genann_free(ann_01_ann[j]) ;
			HEPSY_S(ann_01_id) }
			HEPSY_S(ann_01_id) return( EXIT_FAILURE );
		}
	HEPSY_S(ann_01_id) }

	HEPSY_S(ann_01_id) ann_01_nANN = n ;
	HEPSY_S(ann_01_id) return( EXIT_SUCCESS );
}

////-----------------------------------------------------------------------------
//// Create and train n identical ANN
////-----------------------------------------------------------------------------
//int annCreateAndTrain(int n)
//{
//	if	( annCreate(n) != EXIT_SUCCESS )
//		return( EXIT_FAILURE );
//
//    // Train the ANN's
//	for	( int index = 0; index < nANN; index++ )
//		for ( int i = 0; i < ANN_EPOCHS; i++ )
//			for ( int j = 0; j < ANN_DATASET; j++ )
//				genann_train(ann[index], trainingInput[j], trainingExpected[j], ANN_LEARNING_RATE) ;
//
//    return( EXIT_SUCCESS );
//}

//-----------------------------------------------------------------------------
// Create n identical ANN and set their weight
//-----------------------------------------------------------------------------
int ann_01_annCreateAndSetWeights(int n)
{
	HEPSY_S(ann_01_id) if( ann_01_annCreate(n) != EXIT_SUCCESS )
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return( EXIT_FAILURE );
	}

    // Set weights
	HEPSY_S(ann_01_id) for( int index = 0; index < ann_01_nANN; index++ )
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) for	( int i = 0; i < ann_01_ann[index]->total_weights; ++i )
		{HEPSY_S(ann_01_id)
			HEPSY_S(ann_01_id) ann_01_ann[index]->weight[i] = ann_01_weights[i] ;
		HEPSY_S(ann_01_id)}
	HEPSY_S(ann_01_id)}

	HEPSY_S(ann_01_id) return( EXIT_SUCCESS );
}

//-----------------------------------------------------------------------------
// x[2] = x[0] XOR x[1]
//-----------------------------------------------------------------------------
int ann_01_annRun(int index, double x[ann_01_ANN_INPUTS + ann_01_ANN_OUTPUTS])
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) if( ann_01_annCheck(index) != EXIT_SUCCESS )
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) return( EXIT_FAILURE ) ;
	}

	HEPSY_S(ann_01_id) x[2] = * ann_01_genann_run(ann_01_ann[index], x) ;

	HEPSY_S(ann_01_id) return( EXIT_SUCCESS );
}

////-----------------------------------------------------------------------------
////
////-----------------------------------------------------------------------------
//int annPrintWeights(int index)
//{
//	if	( annCheck(index) != EXIT_SUCCESS )
//		return( EXIT_FAILURE ) ;
//
//
//	printf("\n*** ANN index = %d\n", index) ;
//	for	( int i = 0; i < ann[index]->total_weights; ++i )
//		printf("*** w%d = %f\n", i, ann[index]->weight[i]) ;
//
//	return( EXIT_SUCCESS );
//}

////-----------------------------------------------------------------------------
//// Run the index-th ANN k time on random input and return the number of error
////-----------------------------------------------------------------------------
//int annTest(int index, int k)
//{
//	int x0; int x1; int y;
//	double x[2];
//	double xor_ex;
//	int error = 0;
//
//	if	( annCheck(index) != EXIT_SUCCESS )
//		return( -1 );					// less than zero errors <==> the ANN isn't correctly created
//
//	for	(int i = 0; i < k; i++ )
//	{
//		x0 = rand() % 2;		x[0] = (double)x0;
//		x1 = rand() % 2;		x[1] = (double)x1;
//		y = x0 ^ x1 ;
//
//		xor_ex = * genann_run(ann[index], x);
//		if	( fabs(xor_ex - (double)y) > MAX_ERROR )
//		{
//			error++ ;
//			printf("@@@ Error: ANN = %d, step = %d,  x0 = %d, x1 = %d, y = %d, xor_ex = %f \n", index, i, x0, x1, y, xor_ex) ;
//		}
//	}
//
//	if	( error )
//		printf("@@@ ANN = %d: N� of errors = %d\n", index, error) ;
//	else
//		printf("*** ANN = %d: Test OK\n",index) ;
//	return( error );
//}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ann_01_annDestroy(void)
{HEPSY_S(ann_01_id)
	HEPSY_S(ann_01_id) if( ann_01_nANN == -1 )
		HEPSY_S(ann_01_id) return ;

	HEPSY_S(ann_01_id) for	( int index = 0; index < ann_01_nANN; index++ )
	{HEPSY_S(ann_01_id)
		HEPSY_S(ann_01_id) ann_01_genann_free(ann_01_ann[index]) ;
	HEPSY_S(ann_01_id) }

	HEPSY_S(ann_01_id) ann_01_nANN = -1 ;
}

void mainsystem::ann_01_main()
{
	// datatype for channels

	cleanData_xx_ann_xx_payload cleanData_xx_ann_xx_payload_var;

	ann_xx_dataCollector_payload ann_xx_dataCollector_payload_var;

	double x[ann_01_ANN_INPUTS + ann_01_ANN_OUTPUTS] ;
	//int ann_01_index = 1;

	HEPSY_S(ann_01_id) if	( ann_01_annCreateAndSetWeights(ann_01_NUM_DEV) != EXIT_SUCCESS ){		// Create and init ANN
		HEPSY_S(ann_01_id) printf("Error Weights \n");
	HEPSY_S(ann_01_id)}

	//implementation
	HEPSY_S(ann_01_id) while(1)
	{HEPSY_S(ann_01_id)

		// content

		HEPSY_S(ann_01_id) cleanData_xx_ann_xx_payload_var = cleanData_01_ann_01_channel->read();

		HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.dev = cleanData_xx_ann_xx_payload_var.dev;
		HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.step = cleanData_xx_ann_xx_payload_var.step;
		HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.ex_time = cleanData_xx_ann_xx_payload_var.ex_time;
		HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.device_i = cleanData_xx_ann_xx_payload_var.device_i;
		HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.device_v = cleanData_xx_ann_xx_payload_var.device_v;
		HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.device_t = cleanData_xx_ann_xx_payload_var.device_t;
		HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.device_r = cleanData_xx_ann_xx_payload_var.device_r;
		HEPSY_S(ann_01_id) x[0] = cleanData_xx_ann_xx_payload_var.x_0;
		HEPSY_S(ann_01_id) x[1] = cleanData_xx_ann_xx_payload_var.x_1;
		HEPSY_S(ann_01_id) x[2] = cleanData_xx_ann_xx_payload_var.x_2;
		//u = cleanData_xx_ann_xx_payload_var.step;
		HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.fault = cleanData_xx_ann_xx_payload_var.fault;

		//RUN THE ANN...
		// ###   P R E D I C T   (simple XOR)
//		if	( annRun(index, x) != EXIT_SUCCESS ){
//			printf("Step = %u Index = %d ANN error.\n", u, index) ;
//		}else{
//			device[index].fault = x[2] <= 0.5 ? 0 : 1 ;
//		}
		//u: cycle num
		HEPSY_S(ann_01_id) if	( ann_01_annRun(0, x) != EXIT_SUCCESS )
		{HEPSY_S(ann_01_id)
			HEPSY_S(ann_01_id) printf("Step = %d Index = %d ANN error.\n", (int)ann_xx_dataCollector_payload_var.step, (int)ann_xx_dataCollector_payload_var.dev) ;
		HEPSY_S(ann_01_id)}
		else
		{HEPSY_S(ann_01_id)
			HEPSY_S(ann_01_id) ann_xx_dataCollector_payload_var.fault = x[2] <= 0.5 ? 0 : 1 ;
		}

		HEPSY_S(ann_01_id) ann_01_dataCollector_channel->write(ann_xx_dataCollector_payload_var);

		HEPSY_P(ann_01_id)
	
	}
}

// END

