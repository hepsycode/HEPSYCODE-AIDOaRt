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

/*! \file stim_gen.h
    \brief Stimulus Generation Documented file.

    Details.
*/

/** @defgroup firfirgcd_stim_gen_group FirFirGCD Stimulus.
 *
 *  Stimulus Implementation
 *
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start firfirgcd_stim_gen_group

#ifndef __STIMGEN_H__
#define __STIMGEN_H__

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include <systemc.h>
#include "sc_csp_channel_ifs.h"
#include "define.h"

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

////////////////////////////

// STIMULUS: GENERATES INPUTS FOR THE SYSTEM (SBM DEPENDENT)

////////////////////////////

SC_MODULE(stim_gen)
{
	// Port for outputs to the channels
	sc_port < sc_csp_channel_out_if < sc_uint<8> > > stim1_channel_port;  	    
	sc_port < sc_csp_channel_out_if < sc_uint<8> > > stim2_channel_port;  	    

	// Used to stop concurrency sampling (to allow the simulation to finish), if needed
	bool stop_sampling1, stop_sampling2;

	SC_CTOR(stim_gen)
	{
		SC_THREAD(stimulus1);
		SC_THREAD(stimulus2);

		// Used to stop concurrency sampling (to allow the simulation to finish), if needed
		stop_sampling1=false;
		stop_sampling2=false;
	}  

	// Main methods
	void stimulus1();
	void stimulus2();
};

/** @} */ // end of firfirgcd_stim_gen_group

#endif

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
