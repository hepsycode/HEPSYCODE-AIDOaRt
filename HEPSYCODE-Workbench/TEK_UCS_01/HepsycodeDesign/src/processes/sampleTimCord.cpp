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


//-----------------------------------------------------------------------------
// Physical constants
//-----------------------------------------------------------------------------
static double sTC_I_0 = 77.3 ;				// [A]		Nominal current
//static double sTC_T_0 = 298.15 ;			// [K]		Ambient temperature
//static double sTC_R_0 = 0.01 ;				// [Ω]		Data-sheet R_DS_On (Drain-Source resistance in the On State)
static double sTC_V_0 = 47.2 ;				// [V]		Nominal voltage

//static double sTC_Alpha = 0.002 ;			// [Ω/K]	Temperature coefficient of Drain-Source resistance in the On State
//static double sTC_ThermalConstant = 0.75 ;
//static double sTC_Tau = 0.02 ;				// [s]		Sampling period

//-----------------------------------------------------------------------------
// Simulation related data
//-----------------------------------------------------------------------------
//#define N_CYCLES	1000	// Change by command line option -n<number>
#define sTC_NOISE 0.2			// Measurement noise = 10%

static double sTC_time_Ex = 0 ;	// Simple time simulation


//-----------------------------------------------------------------------------
// Mnemonics to access the array that contains the sampled data
//-----------------------------------------------------------------------------
#define sTC_SAMPLE_LEN	3			// Array of SAMPLE_LEN elements
#define sTC_I_INDEX		0			// Current
#define sTC_V_INDEX		1			// Voltage
#define sTC_TIME_INDEX	2			// Time



///-----------------------------------------------------------------------------
// Forward references
//-----------------------------------------------------------------------------
//static int sTC_initDescriptors(void) ;
static void sTC_getSample(int index, double sample[sTC_SAMPLE_LEN]) ;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void sTC_getSample(int index, double sample[sTC_SAMPLE_LEN])
{
	// the parameter "index" is needed as device identifier

	sample[sTC_TIME_INDEX] = sTC_time_Ex ;

	// Random generation of i (current)

	double i; double v ; double noise ;

	// Random i
	i = (double)rand() / (double)RAND_MAX ;		// 0.0 <= i <= 1.0
	i *= 2.0 ;									// 0.0 <= i <= 2.0
	i *= sTC_I_0 ;									// 0.0 <= i <= 2.0*I_0
	// Postcondition: (0 <= i <= 2.0*I_0)

	// Add some noise every 3 samples
	noise = rand() % 3 == 0 ? 1.0 : 0.0 ;
	noise *= (double)rand() / (double)RAND_MAX ;
	noise *= 2.0 ;
	noise -= 1.0 ;
	noise *= (sTC_NOISE * sTC_I_0 ) ;					// NOISE as % of I_0
	i += noise ;
	// Postcondition: (-NOISE*I_0 <= i <= (2.0+NOISE)*I_0 )

	// Random v
	v = (double)rand() / (double)RAND_MAX ;		// 0.0 <= i <= 1.0
	v *= 2.0 ;									// 0.0 <= i <= 2.0
	v *= sTC_V_0 ;									// 0.0 <= i <= 2.0*I_0
	// Postcondition: (0 <= i <= 2.0*I_0)

	// Add some noise every 3 samples
	noise = rand() % 3 == 0 ? 1.0 : 0.0 ;
	noise *= (double)rand() / (double)RAND_MAX ;
	noise *= 2.0 ;
	noise -= 1.0 ;
	noise *= (sTC_NOISE * sTC_V_0 ) ;					// NOISE as % of I_0
	v += noise ;
	// Postcondition: (-NOISE*V_0 <= v <= (2.0+NOISE)*V_0 )

	sample[sTC_I_INDEX] = i ;
	sample[sTC_V_INDEX] = v ;
}


void mainsystem::sampleTimCord_main()
{
	// datatype for channels

	stimulus_system_payload stimulus_system_payload_var;

	sampleTimCord_cleanData_xx_payload sampleTimCord_cleanData_xx_payload_var;

	//step var
	uint16_t step;

	//device var
	int dev;

	// ex_time (for extractFeatures...)
	double ex_time;

	//var for samples, to re-use getSample()
	double sample[sTC_SAMPLE_LEN] ;

	srand(1) ;

	//implementation
	HEPSY_S(sampleTimCord_id) while(1)
	{HEPSY_S(sampleTimCord_id)

		// content
		stimulus_system_payload_var = stimulus_system_port_out->read();

		dev = 0;
		step = stimulus_system_payload_var.example; //step
		ex_time = sc_time_stamp().to_seconds();

		//providing sample to ward device 0 (cleanData_01)
		sTC_getSample(dev, sample);
//		cout << "sampleTimCord \t dev: " << dev
//						<<"\t s0:" << sample[0]
//						<<"\t s1:" << sample[1]
//						<<"\t s3:" << sample[2]
//						<< endl;
		sampleTimCord_cleanData_xx_payload_var.dev = dev++;
		sampleTimCord_cleanData_xx_payload_var.step = step;
		sampleTimCord_cleanData_xx_payload_var.ex_time = ex_time;
		sampleTimCord_cleanData_xx_payload_var.sample_i = sample[sTC_I_INDEX];
		sampleTimCord_cleanData_xx_payload_var.sample_v = sample[sTC_V_INDEX];

		sampleTimCord_cleanData_01_channel->write(sampleTimCord_cleanData_xx_payload_var);
	

		//providing sample to ward device 1 (cleanData_02)
		sTC_getSample(dev, sample);
//		cout << "sampleTimCord \t dev: " << dev
//						<<"\t s0:" << sample[0]
//						<<"\t s1:" << sample[1]
//						<<"\t s3:" << sample[2]
//						<< endl;
		sampleTimCord_cleanData_xx_payload_var.dev = dev++;
		sampleTimCord_cleanData_xx_payload_var.step = step;
		sampleTimCord_cleanData_xx_payload_var.ex_time = ex_time;
		sampleTimCord_cleanData_xx_payload_var.sample_i = sample[sTC_I_INDEX];
		sampleTimCord_cleanData_xx_payload_var.sample_v = sample[sTC_V_INDEX];

		sampleTimCord_cleanData_02_channel->write(sampleTimCord_cleanData_xx_payload_var);
	

		//providing sample to ward device 2 (cleanData_03)
		sTC_getSample(dev, sample);
//		cout << "sampleTimCord \t dev: " << dev
//						<<"\t s0:" << sample[0]
//						<<"\t s1:" << sample[1]
//						<<"\t s3:" << sample[2]
//						<< endl;
		sampleTimCord_cleanData_xx_payload_var.dev = dev++;
		sampleTimCord_cleanData_xx_payload_var.step = step;
		sampleTimCord_cleanData_xx_payload_var.ex_time = ex_time;
		sampleTimCord_cleanData_xx_payload_var.sample_i = sample[sTC_I_INDEX];
		sampleTimCord_cleanData_xx_payload_var.sample_v = sample[sTC_V_INDEX];

		sampleTimCord_cleanData_03_channel->write(sampleTimCord_cleanData_xx_payload_var);


		//providing sample to ward device 3 (cleanData_04)
		sTC_getSample(dev, sample);
//		cout << "sampleTimCord \t dev: " << dev
//						<<"\t s0:" << sample[0]
//						<<"\t s1:" << sample[1]
//						<<"\t s3:" << sample[2]
//						<< endl;
		sampleTimCord_cleanData_xx_payload_var.dev = dev++;
		sampleTimCord_cleanData_xx_payload_var.step = step;
		sampleTimCord_cleanData_xx_payload_var.ex_time = ex_time;
		sampleTimCord_cleanData_xx_payload_var.sample_i = sample[sTC_I_INDEX];
		sampleTimCord_cleanData_xx_payload_var.sample_v = sample[sTC_V_INDEX];

		sampleTimCord_cleanData_04_channel->write(sampleTimCord_cleanData_xx_payload_var);

		HEPSY_P(sampleTimCord_id)
	
	}
}
//END
