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

#include "display.h"

#include <systemc.h>

void display::main()
{
	int i = 1;

	system_display_payload system_display_payload_var;

	/*
	//implementation
	while(1)
	{
		system_display_payload_var = system_display_port_in->read();
		cout << "Display-" << i << "\t at time \t" << sc_time_stamp().to_seconds() << endl;										
		i++;
	}
	*/
	//implementation
	while(i <= 100)
	{

		system_display_payload_var = system_display_port_in->read();
		cout << "Display-" << i <<": \t" << "\t at time \t" << sc_time_stamp().to_seconds() << endl;
		i++;
	}
	sc_stop();
}
