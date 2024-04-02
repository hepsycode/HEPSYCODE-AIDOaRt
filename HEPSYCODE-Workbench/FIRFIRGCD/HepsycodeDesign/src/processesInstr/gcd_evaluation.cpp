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
 * gcd_evaluatin : FirFirGCD GCD Evaluation process.
 *
 * GCD Evaluation process: CSP Process specifying the functionality of
 * the GCD Evaluation component
 *
********************************************************************************/

/*! \file gcd_evaluation.cpp
    \brief GCD Evaluation Documented file.

    GCD Evaluation process: CSP Process specifying the functionality of
    the GCD Evaluation component
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

//gcde
void mainsystem::gcd_evaluation()
{
	// datatype for channels
	gcde_parameters gcde_p;
	gcde_results gcde_r;

	// local variables
	sc_uint<8>  sample1;
	sc_uint<8>  sample2;

	HEPSY_S(gcde_id) while(1)
	{HEPSY_S(gcde_id)

		// read parameters from channel
		HEPSY_S(gcde_id) gcde_p=gcde_parameters_channel->read();

		// fill local variables
		HEPSY_S(gcde_id) sample1=gcde_p.sample1;
		HEPSY_S(gcde_id) sample2=gcde_p.sample2;

		HEPSY_S(gcde_id) while(sample1!=sample2)
		{HEPSY_S(gcde_id)

			HEPSY_S(gcde_id) if (sample1>sample2) //HEPSY_S rules: IF like WHILE
			{HEPSY_S(gcde_id)
				HEPSY_S(gcde_id) sample1=sample1-sample2;
			}
			else //HEPSY_S rules: ELSE like WHILE
			{HEPSY_S(gcde_id)
				HEPSY_S(gcde_id) sample2= sample2-sample1;
			}

		}

		// fill datatype
		HEPSY_S(gcde_id) gcde_r.result=sample1;

		// send results to channel
		HEPSY_S(gcde_id) gcde_results_channel->write(gcde_r);

		// Profiling
		HEPSY_P(gcde_id)
	}
}

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
