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
 * display : FirFirGCD Display.
 *
 * Display: Display (feedback) file
 *
********************************************************************************/

/*! \file display.h
    \brief Display Documented file.

    Display: Display (feedback) file
*/

/** @defgroup firfirgcd_display_group FirFirGCD Display.
 *
 *  Display Implementation
 *
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start firfirgcd_display_group

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include <systemc.h>
#include "sc_csp_channel_ifs.h"

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

////////////////////////////
// SBM DEPENDENT
////////////////////////////

////////////////////////////

// DISPLAY: PRINTS TO THE SCREEN DATA FROM THE SYSTEM

////////////////////////////

SC_MODULE(display)
{

	// Port for input by channel
	sc_port< sc_csp_channel_in_if< sc_uint<8> > > result_channel_port;

	SC_CTOR(display)
	{
		SC_THREAD(output);
	}

	// Main method
	void output();
};

/** @} */ // end of firfirgcd_display_group

#endif

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
