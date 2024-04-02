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
 * mainsystem.h : FirFirGCD mainsystem.
 *
 * Mainsystem: Main SystemC HEPSIM2 header file
 *
********************************************************************************/

/*! \file mainsystem.h
    \brief Mainsystem Documented file.

    Details.
*/

/** @defgroup firfirgcd_mainsystem_group FirFirGCD Mainsystem.
 *
 *  Mainsystem Implementation
 *
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start firfirgcd_mainsystem_group

#ifndef __MYSYSTEM__
#define __MYSYSTEM__

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include "define.h"
#include "sc_csp_channel_ifs.h"
#include "sc_csp_channel.h"
#include "datatype.h"
#include "SystemManager.h"

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

////////////////////////////
// SBM DEPENDENT
////////////////////////////

SC_MODULE(mainsystem)
{
	// Ports for testbench connections
	sc_port< sc_csp_channel_in_if< sc_uint<8> > > stim1_channel_port;
	sc_port< sc_csp_channel_in_if< sc_uint<8> > > stim2_channel_port;
	sc_port< sc_csp_channel_out_if< sc_uint<8> > > result_channel_port;

	// PROCESSES

	void fir8_main();
	void fir8_evaluation();
	void fir8_shifting();

	void fir16_main();
	void fir16_evaluation();
	void fir16_shifting();

	// Process
	void gcd_main();
	void gcd_evaluation();

	// CHANNELS

	// fir8
	sc_csp_channel< fir8e_parameters > *fir8e_parameters_channel;
	sc_csp_channel< fir8e_results > *fir8e_results_channel;
	sc_csp_channel< fir8s_parameters > *fir8s_parameters_channel;
	sc_csp_channel< fir8s_results > *fir8s_results_channel;

	// fir16
	sc_csp_channel< fir16e_parameters > *fir16e_parameters_channel;
	sc_csp_channel< fir16e_results > *fir16e_results_channel;
	sc_csp_channel< fir16s_parameters > *fir16s_parameters_channel;
	sc_csp_channel< fir16s_results > *fir16s_results_channel;

	// gcd
	sc_csp_channel< gcde_parameters > *gcde_parameters_channel;
	sc_csp_channel< gcde_results > *gcde_results_channel;

	// Inter-process connections
	sc_csp_channel< sc_uint<8> > *results8_channel;
	sc_csp_channel< sc_uint<8> >   *results16_channel;

	SC_CTOR(mainsystem)
	{
		fir8e_parameters_channel= new sc_csp_channel< fir8e_parameters > (0);
		fir8e_results_channel= new sc_csp_channel< fir8e_results > (1);
		fir8s_parameters_channel= new sc_csp_channel< fir8s_parameters > (2);
		fir8s_results_channel= new sc_csp_channel< fir8s_results > (3);

		fir16e_parameters_channel= new sc_csp_channel< fir16e_parameters > (4);
		fir16e_results_channel= new sc_csp_channel< fir16e_results > (5);
		fir16s_parameters_channel= new sc_csp_channel< fir16s_parameters > (6);
		fir16s_results_channel= new sc_csp_channel< fir16s_results > (7);

		gcde_parameters_channel = new sc_csp_channel< gcde_parameters > (10);
		gcde_results_channel = new sc_csp_channel< gcde_results > (11);

		results8_channel= new sc_csp_channel< sc_uint<8> > (8);
		results16_channel= new sc_csp_channel< sc_uint<8> > (9);

		SC_THREAD(fir8_main);
		SC_THREAD(fir8_evaluation);
		SC_THREAD(fir8_shifting);

		SC_THREAD(fir16_main);
		SC_THREAD(fir16_evaluation);
		SC_THREAD(fir16_shifting);

		SC_THREAD(gcd_main);
		SC_THREAD(gcd_evaluation);
	}
};

/** @} */ // end of firfirgcd_mainsystem_group

#endif

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
