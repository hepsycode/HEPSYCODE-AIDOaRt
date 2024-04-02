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
 * fir8_shifting : FirFirGCD FIR8 Shifting process.
 *
 * FIR_8 Shifting process: CSP Process specifying the functionality of
 * the FIR8 Shifting component
 *
********************************************************************************/

/*! \file fir8_shifting.cpp
    \brief FIR8 Shifting Documented file.

    FIR_8 Shifting process: CSP Process specifying the functionality of
    the FIR8 Shifting component
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

//f8s
void mainsystem::fir8_shifting()
{
	// datatype for channels
	fir8s_parameters fir8s_p;
	fir8s_results fir8s_r;

	// local variables
	sc_uint<8> sample_tmp;
	sc_uint<8> shift[8];

	HEPSY_S(fir8s_id) while(1)
	{HEPSY_S(fir8s_id)

		// read parameters from channel
		HEPSY_S(fir8s_id) fir8s_p=fir8s_parameters_channel->read();

		// fill local variables
		HEPSY_S(fir8s_id) sample_tmp=fir8s_p.sample_tmp;

		HEPSY_S(fir8s_id) for (unsigned j = 0; j < TAP8; j++)
		{HEPSY_S(fir8s_id)
			HEPSY_S(fir8s_id) shift[j] = fir8s_p.shift[j];
		HEPSY_S(fir8s_id)}

		// process

		HEPSY_S(fir8s_id) for(int i=TAP8-2; i>=0; i--)
		{HEPSY_S(fir8s_id)
			HEPSY_S(fir8s_id) shift[i+1] = shift[i];
		HEPSY_S(fir8s_id)}

		HEPSY_S(fir8s_id) shift[0]=sample_tmp;

		// fill datatype
		HEPSY_S(fir8s_id) for( unsigned j=0; j<TAP8; j++) fir8s_p.shift[j]=shift[j];

		// send results by channel
		HEPSY_S(fir8s_id) fir8s_results_channel->write(fir8s_r);

		// Profiling
		HEPSY_P(fir8s_id)
	}
}

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
