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
 * fir16_evaluatin : FirFirGCD FIR16 Evaluation process.
 *
 * FIR_16 Evaluation process: CSP Process specifying the functionality of
 * the FIR16 Evaluation component
 *
********************************************************************************/

/*! \file fir16_evaluation.cpp
    \brief FIR16 Evaluation Documented file.

    FIR_16 Evaluation process: CSP Process specifying the functionality of
    the FIR16 Evaluation component
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

//f16e
void mainsystem::fir16_evaluation()
{
	// datatype for channels
	fir16e_parameters fir16e_p;
	fir16e_results fir16e_r;

	// local variables
	sc_int<17> pro;
	sc_uint<19> acc;
	sc_uint<9> coef[16];
	sc_uint<8>  sample_tmp;
	sc_uint<8> shift[16];

	HEPSY_S(fir16e_id) while(1)
	{HEPSY_S(fir16e_id)

		// read parameters from channel
		HEPSY_S(fir16e_id) fir16e_p=fir16e_parameters_channel->read();

		// fill local variables
		HEPSY_S(fir16e_id) sample_tmp=fir16e_p.sample_tmp;

		HEPSY_S(fir16e_id) for (unsigned j = 0; j < TAP16; j++)
		{HEPSY_S(fir16e_id)
			HEPSY_S(fir16e_id) coef[j] = fir16e_p.coef[j];
		HEPSY_S(fir16e_id)}

		HEPSY_S(fir16e_id) for (unsigned j = 0; j < TAP16; j++)
		{HEPSY_S(fir16e_id)
			HEPSY_S(fir16e_id) shift[j] = fir16e_p.shift[j];
		HEPSY_S(fir16e_id)}

		// process
		HEPSY_S(fir16e_id) acc=sample_tmp*coef[0];

		HEPSY_S(fir16e_id) for(int i=TAP16-2; i>=0; i--)
		{HEPSY_S(fir16e_id)
			HEPSY_S(fir16e_id) pro=shift[i]*coef[i+1];
			HEPSY_S(fir16e_id) acc += pro;
		HEPSY_S(fir16e_id)}

		// fill datatype
		HEPSY_S(fir16e_id) fir16e_r.acc=acc;

		// send results by channel
		HEPSY_S(fir16e_id) fir16e_results_channel->write(fir16e_r);

		// Profiling
		HEPSY_P(fir16e_id)
	}
}

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
