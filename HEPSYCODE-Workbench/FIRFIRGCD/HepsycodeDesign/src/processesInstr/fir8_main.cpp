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
 * fir8_main : FirFirGCD FIR8 process.
 *
 * FIR_8 process: CSP Process specifying the functionality of the FIR8 component
 *
********************************************************************************/

/*! \file fir8_main.cpp
    \brief FIR8 Documented file.

    FIR_8 process: CSP Process specifying the functionality of the FIR8 component.
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

//f8m
void mainsystem::fir8_main()
{
	// datatype for channels
	fir8e_parameters fir8e_p;
	fir8e_results fir8e_r;
	fir8s_parameters fir8s_p;
	fir8s_results fir8s_r;

	// local variables
	sc_uint<8>  sample_tmp;
	sc_uint<19> acc;
	sc_uint<9> coef[8];
	sc_uint<8> shift[8];

	// init
	HEPSY_S(fir8m_id) coef[0] = 6;
	HEPSY_S(fir8m_id) coef[1] = 4;
	HEPSY_S(fir8m_id) coef[2] = 13;
	HEPSY_S(fir8m_id) coef[3] = 8;
	HEPSY_S(fir8m_id) coef[4] = 18;
	HEPSY_S(fir8m_id) coef[5] = 41;
	HEPSY_S(fir8m_id) coef[6] = 23;
	HEPSY_S(fir8m_id) coef[7] = 154;
	HEPSY_S(fir8m_id) coef[8] = 222;

	HEPSY_S(fir8m_id) for (unsigned int i=0; i<TAP8; i++)
	{HEPSY_S(fir8m_id)
		HEPSY_S(fir8m_id) shift[i] = 0;
	HEPSY_S(fir8m_id)}

	// main functionality

	HEPSY_S(fir8m_id) while (1)
	{
		HEPSY_S(fir8m_id)

			// Main input from channel
			HEPSY_S(fir8m_id) sample_tmp = stim1_channel_port->read();

		//fir8e

		// fill datatype
		HEPSY_S(fir8m_id) fir8e_p.acc = acc;

		HEPSY_S(fir8m_id) for (unsigned j = 0; j < TAP8; j++)
		{
			HEPSY_S(fir8m_id)
				HEPSY_S(fir8m_id) fir8e_p.coef[j] = coef[j];
			HEPSY_S(fir8m_id)
		}

		HEPSY_S(fir8m_id) fir8e_p.sample_tmp = sample_tmp;

		HEPSY_S(fir8m_id) for (unsigned j = 0; j < TAP8; j++)
		{
			HEPSY_S(fir8m_id)
				HEPSY_S(fir8m_id) fir8e_p.shift[j] = shift[j];
			HEPSY_S(fir8m_id)
		}

		// send parameters and receive results
		HEPSY_S(fir8m_id) fir8e_parameters_channel->write(fir8e_p);
		HEPSY_S(fir8m_id) fir8e_r = fir8e_results_channel->read();

		// fill local variables
		HEPSY_S(fir8m_id) acc = fir8e_r.acc;

		//fir8s

		// fill datatype
		HEPSY_S(fir8m_id) fir8s_p.sample_tmp = sample_tmp;

		HEPSY_S(fir8m_id) for (unsigned j = 0; j < TAP8; j++)
		{
			HEPSY_S(fir8m_id)
				HEPSY_S(fir8m_id) fir8s_p.shift[j] = shift[j];
			HEPSY_S(fir8m_id)
		}

		// send parameters and receive results
		HEPSY_S(fir8m_id) fir8s_parameters_channel->write(fir8s_p);
		HEPSY_S(fir8m_id) fir8s_r = fir8s_results_channel->read();

		// fill local variables
		HEPSY_S(fir8m_id) for( unsigned j=0; j<TAP8; j++)
		{HEPSY_S(fir8m_id)
			HEPSY_S(fir8m_id) shift[j] = fir8s_r.shift[j];
		HEPSY_S(fir8m_id)}

		// write output values on channel
		HEPSY_S(fir8m_id) results8_channel->write(acc);

		#if defined(_DEBUG_)
			cout << "FIR8: \t\t" << acc << "\t at time \t" << sc_time_stamp() << endl;
		#endif

		// Profiling
		HEPSY_P(fir8m_id)
	}
}

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
