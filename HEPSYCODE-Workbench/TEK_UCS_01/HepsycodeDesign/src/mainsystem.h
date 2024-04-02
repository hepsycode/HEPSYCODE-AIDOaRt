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

#ifndef __MYSYSTEM__

#define __MYSYSTEM__

#include "define.h"
#include "sc_csp_channel_ifs.h"
#include "sc_csp_channel.h"
#include "datatype.h"
#include "SystemManager.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

SC_MODULE(mainsystem)
{
	// Ports for testbench connections
	sc_port< sc_csp_channel_in_if< stimulus_system_payload > > stimulus_system_port_out;
	sc_port< sc_csp_channel_out_if< system_display_payload > > system_display_port_in;

	// PROCESSES
	void sampleTimCord_main();

	void cleanData_01_main();
	void cleanData_02_main();
	void cleanData_03_main();
	void cleanData_04_main();

	void ann_01_main();
	void ann_02_main();
	void ann_03_main();
	void ann_04_main();

	void dataCollector_main();

	// CHANNELS
	sc_csp_channel< sampleTimCord_cleanData_xx_payload > *sampleTimCord_cleanData_01_channel;
	sc_csp_channel< sampleTimCord_cleanData_xx_payload > *sampleTimCord_cleanData_02_channel;
	sc_csp_channel< sampleTimCord_cleanData_xx_payload > *sampleTimCord_cleanData_03_channel;
	sc_csp_channel< sampleTimCord_cleanData_xx_payload > *sampleTimCord_cleanData_04_channel;
	sc_csp_channel< cleanData_xx_ann_xx_payload > *cleanData_01_ann_01_channel;
	sc_csp_channel< cleanData_xx_ann_xx_payload > *cleanData_02_ann_02_channel;
	sc_csp_channel< cleanData_xx_ann_xx_payload > *cleanData_03_ann_03_channel;
	sc_csp_channel< cleanData_xx_ann_xx_payload > *cleanData_04_ann_04_channel;
	sc_csp_channel< ann_xx_dataCollector_payload > *ann_01_dataCollector_channel;
	sc_csp_channel< ann_xx_dataCollector_payload > *ann_02_dataCollector_channel;
	sc_csp_channel< ann_xx_dataCollector_payload > *ann_03_dataCollector_channel;
	sc_csp_channel< ann_xx_dataCollector_payload > *ann_04_dataCollector_channel;

	SC_CTOR(mainsystem)
	{

		sampleTimCord_cleanData_01_channel = new sc_csp_channel< sampleTimCord_cleanData_xx_payload >(2);
		sampleTimCord_cleanData_02_channel = new sc_csp_channel< sampleTimCord_cleanData_xx_payload >(3);
		sampleTimCord_cleanData_03_channel = new sc_csp_channel< sampleTimCord_cleanData_xx_payload >(4);
		sampleTimCord_cleanData_04_channel = new sc_csp_channel< sampleTimCord_cleanData_xx_payload >(5);

		cleanData_01_ann_01_channel = new sc_csp_channel< cleanData_xx_ann_xx_payload >(6);
		cleanData_02_ann_02_channel = new sc_csp_channel< cleanData_xx_ann_xx_payload >(7);
		cleanData_03_ann_03_channel = new sc_csp_channel< cleanData_xx_ann_xx_payload >(8);
		cleanData_04_ann_04_channel = new sc_csp_channel< cleanData_xx_ann_xx_payload >(9);

		ann_01_dataCollector_channel = new sc_csp_channel< ann_xx_dataCollector_payload >(10);
		ann_02_dataCollector_channel = new sc_csp_channel< ann_xx_dataCollector_payload >(11);
		ann_03_dataCollector_channel = new sc_csp_channel< ann_xx_dataCollector_payload >(12);
		ann_04_dataCollector_channel = new sc_csp_channel< ann_xx_dataCollector_payload >(13);

		// SC_THREAD(TekneProcess_main);
		SC_THREAD(sampleTimCord_main);

		SC_THREAD(cleanData_01_main);
		SC_THREAD(cleanData_02_main);
		SC_THREAD(cleanData_03_main);
		SC_THREAD(cleanData_04_main);

		SC_THREAD(ann_01_main);
		SC_THREAD(ann_02_main);
		SC_THREAD(ann_03_main);
		SC_THREAD(ann_04_main);

		SC_THREAD(dataCollector_main);
	}
};

#endif
