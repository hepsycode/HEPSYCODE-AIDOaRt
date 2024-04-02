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

#include "stim_gen.h"

#include <systemc.h>
#include <cstdlib>   // rand and srand
#include <ctime>     // For the time function
#include "datatype.h"

extern bool stop_concurrency_sampling;

void stim_gen::main()
{
	// init CODE
	unsigned int i=1;

	stimulus_system_payload stim_system_payload_var;

	/*
	//implementation
	while(i <= NUMBER_OF_INPUTS){
		
		// content

		srand((unsigned int)time(NULL));   // Initialization, should only be called once.
		unsigned int r = rand() % 3;      // Returns a pseudo-random integer between 0 and RAND_MAX.

		if(r == 1){
			stim_system_payload_var.Id = EVENT_A;
		}else if(r == 2){
			stim_system_payload_var.Id = EVENT_B;
		}else if(r == 0){
			stim_system_payload_var.Id = EVENT_0;
		}

		wait(1, SC_MS);
		stimulus_system_port_out->write(stim_system_payload_var);
		cout << "Stimulus-"<<i<<": \t" << "\t at time \t" << sc_time_stamp() << "\t Process_" << stim_system_payload_var.Id << endl;

		// Check for stop
		/*if(i >= 10) return;
			else i++; //
		i++;
	}
	*/

	while(1){

		// content

		wait(10, SC_MS);
		stim_system_payload_var.example = i-1;
		stimulus_system_port_out->write(stim_system_payload_var);
		cout << "Stimulus-"<< i <<": \t" << "\t at time \t" << sc_time_stamp() << endl;

		// Check for stop
		if(i >= 100){
			stop_concurrency_sampling = true;
			return;
		}else{ i++;}
	}
}
//END
