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
 * display : FirFirGCD Display process.
 *
 * Display module: SystemC Module specifying the functionality of
 * the Display component
 *
********************************************************************************/

/*! \file display.cpp
    \brief Display Documented file.

    Display module: SystemC Module specifying the functionality of
    the Display component
*/

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include "display.h"
#include "define.h"

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

////////////////////////////
/// SBM DEPENDENT
////////////////////////////

////////////////////////////

/// DISPLAY: PRINTS TO THE SCREEN DATA FROM THE SYSTEM

////////////////////////////

void display::output()
{

	// Output counter
	int i=1;

	// Temp
	sc_uint<8> tmp1;

	while(1)
	{
		// Read from channel
		tmp1=result_channel_port->read();

		// Write output
		cout << "Display-" << i <<": \t" << tmp1 << " " << "\t at time \t" << sc_time_stamp() << endl;

		// Output counter
		i++;
	}
}

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
