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
#include <math.h>


#define cD_02_ANN_INPUTS			2		// Number of inputs
#define cD_02_ANN_OUTPUTS			1		// Number of outputs

//-----------------------------------------------------------------------------
// Physical constants
//-----------------------------------------------------------------------------
static double cD_02_I_0 = 77.3 ;				// [A]		Nominal current
static double cD_02_T_0 = 298.15 ;			// [K]		Ambient temperature
static double cD_02_R_0 = 0.01 ;				// [Ω]		Data-sheet R_DS_On (Drain-Source resistance in the On State)
static double cD_02_V_0 = 47.2 ;				// [V]		Nominal voltage

static double cD_02_Alpha = 0.002 ;			// [Ω/K]	Temperature coefficient of Drain-Source resistance in the On State
static double cD_02_ThermalConstant = 0.75 ;
static double cD_02_Tau = 0.02 ;				// [s]		Sampling period



//-----------------------------------------------------------------------------
// Status descriptors
//-----------------------------------------------------------------------------
typedef struct cD_02_DEVICE		// Descriptor of the state of the device
{
	double t ;				// Operating temperature
	double r ;				// Operating Drain-Source resistance in the On State
	double i ;				// Operating current
	double v ;				// Operating voltage
	double time_Ex ;
	int fault ;

} cD_02_DEVICE ;

static cD_02_DEVICE cD_02_device;

//-----------------------------------------------------------------------------
// Mnemonics to access the array that contains the sampled data
//-----------------------------------------------------------------------------
#define cD_02_SAMPLE_LEN	3			// Array of SAMPLE_LEN elements
#define cD_02_I_INDEX		0			// Current
#define cD_02_V_INDEX		1			// Voltage
#define cD_02_TIME_INDEX	2			// Time



///-----------------------------------------------------------------------------
// Forward references
//-----------------------------------------------------------------------------
static int cD_02_initDescriptors(cD_02_DEVICE device) ;
//static void getSample(int index, double sample[SAMPLE_LEN]) ;
static void cD_02_cleanData(int index, double sample[cD_02_SAMPLE_LEN]) ;
static double cD_02_extractFeatures(double tPrev, double iPrev, double iNow, double rPrev) ;
static void cD_02_normalize(int index, double x[cD_02_ANN_INPUTS]) ;
static double cD_02_degradationModel(double tNow) ;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
int cD_02_initDescriptors(cD_02_DEVICE device)
{HEPSY_S(cleanData_02_id)
//	for	(int i = 0; i < NUM_DEV; i++)
//	{
	HEPSY_S(cleanData_02_id) device.t = cD_02_T_0 ;		// Operating temperature = Ambient temperature
	HEPSY_S(cleanData_02_id) device.r = cD_02_R_0 ;		// Operating R_DS_On = Data-sheet R_DS_On
		// printf("Init %d \n",i);
//	}

	HEPSY_S(cleanData_02_id) return( EXIT_SUCCESS );
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void cD_02_cleanData(int index, double sample[cD_02_SAMPLE_LEN])
{
	// the parameter "index" could be useful to retrieve the characteristics of the device

	HEPSY_S(cleanData_02_id) if	( sample[cD_02_I_INDEX] < 0 )
	{HEPSY_S(cleanData_02_id)
		HEPSY_S(cleanData_02_id) sample[cD_02_I_INDEX] = 0 ;
	HEPSY_S(cleanData_02_id)}
	else if ( sample[cD_02_I_INDEX] > (2.0 * cD_02_I_0) )
	{HEPSY_S(cleanData_02_id)
		HEPSY_S(cleanData_02_id) sample[cD_02_I_INDEX] = (2.0 * cD_02_I_0) ;
	// Postcondition: (0 <= sample[I_INDEX] <= 2.0*I_0)
	HEPSY_S(cleanData_02_id)}

	HEPSY_S(cleanData_02_id) if	( sample[cD_02_V_INDEX] < 0 )
	{HEPSY_S(cleanData_02_id)
		HEPSY_S(cleanData_02_id) sample[cD_02_V_INDEX] = 0 ;
	HEPSY_S(cleanData_02_id)}
	else if ( sample[cD_02_V_INDEX] > (2.0 * cD_02_V_0 ) )
	{HEPSY_S(cleanData_02_id)
		HEPSY_S(cleanData_02_id) sample[cD_02_V_INDEX] = (2.0 * cD_02_V_0) ;
	// Postcondition: (0 <= sample[V_INDEX] <= 2.0*V_0)
	HEPSY_S(cleanData_02_id)}
}

//-----------------------------------------------------------------------------
// Input:
// - tPrev = temperature at previous step
// - iPrev = current at previous step
// - iNow = current at this step
// - rPrev = resistance at the previous step
// Return:
// - The new temperature
// Very simple model:
// - one constant for dissipation and heat capacity
// - temperature considered constant during the step
//-----------------------------------------------------------------------------
double cD_02_extractFeatures(double tPrev, double iPrev, double iNow, double rPrev)
{HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id) double t ;								// Temperature
	HEPSY_S(cleanData_02_id) double i = 0.5*(iPrev + iNow);			// Average current
	//printf("cD_02_extractFeatures tPrev=%f\n",tPrev);

	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id) t =	tPrev +										// Previous temperature
	    rPrev * (i * i) * cD_02_Tau -						// Heat generated: P = I·R^2
		cD_02_ThermalConstant * (tPrev - cD_02_T_0) * cD_02_Tau ;		// Dissipation and heat capacity

	HEPSY_S(cleanData_02_id) return( t );
}

//-----------------------------------------------------------------------------
// Input:
// - tNow: temperature at this step
// Return:
// - the resistance
// The model isn't realistic because the even the simpler law is exponential
//-----------------------------------------------------------------------------
double cD_02_degradationModel(double tNow)
{HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id) double r ;

	//r = R_0 + Alpha * tNow ;
	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id) r = cD_02_R_0 * ( 2 - exp(-cD_02_Alpha*tNow) );

	HEPSY_S(cleanData_02_id) return( r );
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void cD_02_normalize(int index, double sample[cD_02_ANN_INPUTS])
{HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id) double i ;	double v ;

	// Precondition: (0 <= sample[I_INDEX] <= 2*I_0) && (0 <= sample[V_INDEX] <= 2*V_0)
	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id) i = sample[cD_02_I_INDEX] <= cD_02_I_0 ? 0.0 : 1.0;
	HEPSY_S(cleanData_02_id)

	HEPSY_S(cleanData_02_id)
	HEPSY_S(cleanData_02_id) v = sample[cD_02_V_INDEX] <= cD_02_V_0 ? 0.0 : 1.0;
	HEPSY_S(cleanData_02_id)
	// Postcondition: (i in {0.0, 1.0}) and (v in {0.0, 1.0})

	HEPSY_S(cleanData_02_id) sample[cD_02_I_INDEX] = i ;
	HEPSY_S(cleanData_02_id) sample[cD_02_V_INDEX] = v ;
}


void mainsystem::cleanData_02_main()
{
	// datatype for channels

	sampleTimCord_cleanData_xx_payload sampleTimCord_cleanData_xx_payload_var;

	cleanData_xx_ann_xx_payload cleanData_xx_ann_xx_payload_var;

	//device var
	uint8_t dev;

	//step var
	uint16_t step;

	// ex_time (for extractFeatures...)
	double ex_time;

	//samples i and v
	double sample_i;
	double sample_v;

	//var for samples, to re-use cleanData()
	double cD_02_sample[cD_02_SAMPLE_LEN] ;
	double x[cD_02_ANN_INPUTS + cD_02_ANN_OUTPUTS] ;

	// NOTE: commented, should be changed param by ref...
	//cD_02_initDescriptors(cD_02_device);
	cD_02_device.t = cD_02_T_0 ;		// Operating temperature = Ambient temperature
	cD_02_device.r = cD_02_R_0 ;		// Operating R_DS_On = Data-sheet R_DS_On

	// ### added for time related dynamics
	//static double cD_02_Tau = 0.02 ;				// [s]		Sampling period
	HEPSY_S(cleanData_02_id) double cD_02_last_sample_time = 0;

	//implementation
	HEPSY_S(cleanData_02_id) while(1)
	{HEPSY_S(cleanData_02_id)

		// content

		HEPSY_S(cleanData_02_id) sampleTimCord_cleanData_xx_payload_var = sampleTimCord_cleanData_02_channel->read();

		HEPSY_S(cleanData_02_id) dev = sampleTimCord_cleanData_xx_payload_var.dev;
		HEPSY_S(cleanData_02_id) step = sampleTimCord_cleanData_xx_payload_var.step;
		HEPSY_S(cleanData_02_id) ex_time = sampleTimCord_cleanData_xx_payload_var.ex_time;
		HEPSY_S(cleanData_02_id) sample_i = sampleTimCord_cleanData_xx_payload_var.sample_i;
		HEPSY_S(cleanData_02_id) sample_v = sampleTimCord_cleanData_xx_payload_var.sample_v;

//		cout << "cleanData_02 rcv \t dev: " << dev
//				<<"\t step: " << step
//				<<"\t time_ex:" << ex_time
//				<<"\t i:" << sample_i
//				<<"\t v:" << sample_v
//				<< endl;

		// reconstruct sample
		HEPSY_S(cleanData_02_id) cD_02_sample[cD_02_I_INDEX] = sample_i;
		HEPSY_S(cleanData_02_id) cD_02_sample[cD_02_V_INDEX] = sample_v;
		HEPSY_S(cleanData_02_id) cD_02_sample[cD_02_TIME_INDEX] = ex_time;

		// ###   C L E A N   D A T A   (0 <= I <= 2.0*I_0) and (0 <= V <= 2.0*V_0)
		HEPSY_S(cleanData_02_id) cD_02_cleanData(dev, cD_02_sample) ;
		HEPSY_S(cleanData_02_id) cD_02_device.time_Ex = cD_02_sample[cD_02_TIME_INDEX] ;
		HEPSY_S(cleanData_02_id) cD_02_device.i = cD_02_sample[cD_02_I_INDEX] ;
		HEPSY_S(cleanData_02_id) cD_02_device.v = cD_02_sample[cD_02_V_INDEX] ;

		// ### added for time related dynamics
		//static double cD_02_Tau = 0.02 ;				// [s]		Sampling period
		HEPSY_S(cleanData_02_id) cD_02_Tau = ex_time - cD_02_last_sample_time;
		HEPSY_S(cleanData_02_id) cD_02_last_sample_time = ex_time;

		// ###   F E A T U R E S   E X T R A C T I O N   (compute the temperature)
		HEPSY_S(cleanData_02_id) cD_02_device.t = cD_02_extractFeatures(	cD_02_device.t,	// Previous temperature
												cD_02_device.i, 	// Previous current
												cD_02_sample[cD_02_I_INDEX], 	// Current at this step
												cD_02_device.r) ;	// Previous resistance

		// ###   D E G R A D A T I O N   M O D E L   (compute R_DS_On)
		HEPSY_S(cleanData_02_id) cD_02_device.r = cD_02_degradationModel(cD_02_device.t) ;

		// ###   N O R M A L I Z E:  (x[0] in {0.0, 1.0}) and (x[1] in {0.0, 1.0})
		HEPSY_S(cleanData_02_id) x[0] = cD_02_device.i ;
		HEPSY_S(cleanData_02_id) x[1] = cD_02_device.v ;
		HEPSY_S(cleanData_02_id) cD_02_normalize(dev, x) ;

//		// ###   P R E D I C T   (simple XOR)
//		if	( annRun(index, x) != EXIT_SUCCESS ){

		//prepare out data payload
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.dev = dev;
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.step = step;
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.ex_time = ex_time;
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.device_i = cD_02_device.i;
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.device_v = cD_02_device.v;
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.device_t = cD_02_device.t;
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.device_r = cD_02_device.r;
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.x_0 = x[0];
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.x_1 = x[1];
		HEPSY_S(cleanData_02_id) cleanData_xx_ann_xx_payload_var.x_2 = x[2];

		HEPSY_S(cleanData_02_id) cleanData_02_ann_02_channel->write(cleanData_xx_ann_xx_payload_var);

		HEPSY_P(cleanData_02_id)
	
	}
}
//END
