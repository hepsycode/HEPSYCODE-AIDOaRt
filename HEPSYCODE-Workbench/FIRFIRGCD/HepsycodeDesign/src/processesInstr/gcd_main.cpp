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
 * Created on: 09/May/2022                                                      *
 * Authors: Vittoriano Muttillo, Luigi Pomante                                  *
 *                                                                              *
 * email: vittoriano.muttillo@guest.univaq.it                                   *
 *        luigi.pomante@univaq.it                                               *
 *                                                                              *
 ********************************************************************************
 * This code has been developed from an HEPSYCODE model used as demonstrator by	*
 * University of L'Aquila.                                                      *
 *                                                                              *
 * The code is used as a working example in the 'Embedded Systems' course of    *
 * the Master in Conputer Science Engineering offered by the                    *
 * University of L'Aquila                                                       *
 *******************************************************************************/

/********************************************************************************
 * gcd_main : FirFirGCD GCD process.
 *
 * GCD process: CSP Process specifying the functionality of the GCD component
 *
********************************************************************************/

/*! \file gcd_main.cpp
    \brief GCD Documented file.

    GCD process: CSP Process specifying the functionality of the GCD component.
*/

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include "../mainsystem.h"

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//gcdm
void mainsystem::gcd_main()
{

	// datatype for channels
	gcde_parameters gcde_p;
	gcde_results gcde_r;

	// local variables
	sc_uint<8> sample1;
	sc_uint<8> sample2;
	sc_uint<8> result;
	bool err;

	// init
	HEPSY_S(gcdm_id) err=false;

	HEPSY_S(gcdm_id) while(1)
	{HEPSY_S(gcdm_id)

		// main functionality

		// Main input from channel

		HEPSY_S(gcdm_id) sample1=results8_channel->read();
		HEPSY_S(gcdm_id) if (sample1==0) err=true;

		HEPSY_S(gcdm_id) sample2=results16_channel->read();
		HEPSY_S(gcdm_id) if (sample2==0) err=true;

		//cout<<"sample1: "<<sample1_tmp<<" sample2: "<<sample2_tmp<<endl;

		HEPSY_S(gcdm_id) if (err==false)
		{HEPSY_S(gcdm_id)  
			// fill datatype
			HEPSY_S(gcdm_id) gcde_p.sample1=sample1;
			HEPSY_S(gcdm_id) gcde_p.sample2=sample2;

			// send parameters and receive results
			HEPSY_S(gcdm_id) gcde_parameters_channel->write(gcde_p);
			HEPSY_S(gcdm_id) gcde_r=gcde_results_channel->read();

			// fill local variables
			HEPSY_S(gcdm_id) result=gcde_r.result;
		HEPSY_S(gcdm_id)}	
		else
		{HEPSY_S(gcdm_id) 
			HEPSY_S(gcdm_id) result=0;
			HEPSY_S(gcdm_id) err=false;
		HEPSY_S(gcdm_id)}

		HEPSY_S(gcdm_id) result_channel_port->write(result);

		#if defined(_DEBUG_)
			cout << "GCD: \t\t" << result << "\t at time \t" << sc_time_stamp() << endl;
		#endif

		HEPSY_P(gcdm_id)
	}
}

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
