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

#include <systemc.h>
#include "../mainsystem.h"
#include <math.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef PATH_MAX
	#define dC_MAX_PATH_LEN PATH_MAX
#endif
#ifdef MAX_PATH
	#define dC_MAX_PATH_LEN MAX_PATH
#endif

//-----------------------------------------------------------------------------
// Status descriptors
//-----------------------------------------------------------------------------
typedef struct dC_DEVICE		// Descriptor of the state of the device
{
	double t ;				// Operating temperature
	double r ;				// Operating Drain-Source resistance in the On State
	double i ;				// Operating current
	double v ;				// Operating voltage
	double time_Ex ;
	int fault ;

} dC_DEVICE ;

static dC_DEVICE dC_device;

///-----------------------------------------------------------------------------
// Log
//-----------------------------------------------------------------------------
static char dC_szOutFile[dC_MAX_PATH_LEN] ;		// Change by command line option -f<filename> MAX_PATH
static char dC_szWorkingDir[dC_MAX_PATH_LEN] ;
static char dC_szHeader[] = "Stp\tDv\tTime\tTemp\tR_DS_On\tDevI\tDevV\tFault\n" ;
FILE * dC_file = NULL ;


/*
 * dC_writeLog(step, Device index, device)
 */
void dC_writeLog(int u, int index, dC_DEVICE device)
{HEPSY_S(dataCollector_id)
	HEPSY_S(dataCollector_id) if( dC_file != NULL )
	{HEPSY_S(dataCollector_id)
		HEPSY_S(dataCollector_id) int w ;
		HEPSY_S(dataCollector_id) w = fprintf	(dC_file, "%u\t%d\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%d\n",
							u,						// Step
							index,					// Device index
							device.time_Ex,		// Time of sampling
							device.t,		// Temperature
							device.r,		// Resistance
							device.i,		// Current
							device.v,		// Voltage
							device.fault		//
						) ;
		HEPSY_S(dataCollector_id) if	( w <= 0 )
		{HEPSY_S(dataCollector_id)
			HEPSY_S(dataCollector_id) fclose(dC_file) ;
			HEPSY_S(dataCollector_id) dC_file = NULL ;
			HEPSY_S(dataCollector_id) printf("Write file record error.\n") ;
		HEPSY_S(dataCollector_id) }
	HEPSY_S(dataCollector_id) }
}

void mainsystem::dataCollector_main()
{
	// datatype for channels

	system_display_payload system_display_payload_var;

	ann_xx_dataCollector_payload ann_01_dataCollector_payload_var;

	ann_xx_dataCollector_payload ann_02_dataCollector_payload_var;

	ann_xx_dataCollector_payload ann_03_dataCollector_payload_var;

	ann_xx_dataCollector_payload ann_04_dataCollector_payload_var;

	//prepare file for the log...
	HEPSY_S(dataCollector_id) strcpy(dC_szOutFile, "log_dC.txt") ;
	// Open log file
	HEPSY_S(dataCollector_id) if( dC_szOutFile[0] != 0 )
	{HEPSY_S(dataCollector_id)
		HEPSY_S(dataCollector_id) dC_file = fopen(dC_szOutFile, "w") ;							// Warning: if the file already exists it is truncated to zero length
		if ( dC_file == NULL )
		{HEPSY_S(dataCollector_id)
			HEPSY_S(dataCollector_id) printf("Open file error.\n") ;
		HEPSY_S(dataCollector_id) }
		else if( fprintf(dC_file, "%s", dC_szHeader) <= 0 )
		{HEPSY_S(dataCollector_id)
			HEPSY_S(dataCollector_id) fclose(dC_file) ;
			HEPSY_S(dataCollector_id) dC_file = NULL ;
			HEPSY_S(dataCollector_id) printf("Write file header error.\n") ;
			HEPSY_S(dataCollector_id) }
		else
		{HEPSY_S(dataCollector_id)
			HEPSY_S(dataCollector_id) printf("W O R K I N G   D I R E C T O R Y : %s\n", getcwd(dC_szWorkingDir, dC_MAX_PATH_LEN)) ;
			HEPSY_S(dataCollector_id) printf("L O G   F I L E : %s\n", dC_szOutFile) ;
			HEPSY_S(dataCollector_id) }
	HEPSY_S(dataCollector_id) }

	HEPSY_S(dataCollector_id) if( dC_file != NULL )
	{HEPSY_S(dataCollector_id)
		HEPSY_S(dataCollector_id) fclose(dC_file);			// Error should be checked
	HEPSY_S(dataCollector_id) }

	HEPSY_S(dataCollector_id) int dev;
	HEPSY_S(dataCollector_id) int step;

	//implementation
	HEPSY_S(dataCollector_id) while(1)
	{HEPSY_S(dataCollector_id)

		// content
		HEPSY_S(dataCollector_id) dC_file = fopen(dC_szOutFile, "a") ;

		// read data
		HEPSY_S(dataCollector_id) ann_01_dataCollector_payload_var = ann_01_dataCollector_channel->read();

		// encap in data_structure
		HEPSY_S(dataCollector_id) dev = ann_01_dataCollector_payload_var.dev;
		HEPSY_S(dataCollector_id) step = ann_01_dataCollector_payload_var.step;
		HEPSY_S(dataCollector_id) dC_device.time_Ex = ann_01_dataCollector_payload_var.ex_time;
		HEPSY_S(dataCollector_id) dC_device.i = ann_01_dataCollector_payload_var.device_i;
		HEPSY_S(dataCollector_id) dC_device.v = ann_01_dataCollector_payload_var.device_v;
		HEPSY_S(dataCollector_id) dC_device.t = ann_01_dataCollector_payload_var.device_t;
		HEPSY_S(dataCollector_id) dC_device.r = ann_01_dataCollector_payload_var.device_r;
		HEPSY_S(dataCollector_id) dC_device.fault = ann_01_dataCollector_payload_var.fault;

		// ###   W R I T E   L O G
		HEPSY_S(dataCollector_id) dC_writeLog(step, dev, dC_device);

		// read data
		HEPSY_S(dataCollector_id) ann_02_dataCollector_payload_var = ann_02_dataCollector_channel->read();

		// encap in data_structure
		HEPSY_S(dataCollector_id) dev = ann_02_dataCollector_payload_var.dev;
		HEPSY_S(dataCollector_id) step = ann_02_dataCollector_payload_var.step;
		HEPSY_S(dataCollector_id) dC_device.time_Ex = ann_02_dataCollector_payload_var.ex_time;
		HEPSY_S(dataCollector_id) dC_device.i = ann_02_dataCollector_payload_var.device_i;
		HEPSY_S(dataCollector_id) dC_device.v = ann_02_dataCollector_payload_var.device_v;
		HEPSY_S(dataCollector_id) dC_device.t = ann_02_dataCollector_payload_var.device_t;
		HEPSY_S(dataCollector_id) dC_device.r = ann_02_dataCollector_payload_var.device_r;
		HEPSY_S(dataCollector_id) dC_device.fault = ann_02_dataCollector_payload_var.fault;

		// ###   W R I T E   L O G
		HEPSY_S(dataCollector_id) dC_writeLog(step, dev, dC_device);

		// read data
		HEPSY_S(dataCollector_id) ann_03_dataCollector_payload_var = ann_03_dataCollector_channel->read();

		// encap in data_structure
		HEPSY_S(dataCollector_id) dev = ann_03_dataCollector_payload_var.dev;
		HEPSY_S(dataCollector_id) step = ann_03_dataCollector_payload_var.step;
		HEPSY_S(dataCollector_id) dC_device.time_Ex = ann_03_dataCollector_payload_var.ex_time;
		HEPSY_S(dataCollector_id) dC_device.i = ann_03_dataCollector_payload_var.device_i;
		HEPSY_S(dataCollector_id) dC_device.v = ann_03_dataCollector_payload_var.device_v;
		HEPSY_S(dataCollector_id) dC_device.t = ann_03_dataCollector_payload_var.device_t;
		HEPSY_S(dataCollector_id) dC_device.r = ann_03_dataCollector_payload_var.device_r;
		HEPSY_S(dataCollector_id) dC_device.fault = ann_03_dataCollector_payload_var.fault;

		// ###   W R I T E   L O G
		HEPSY_S(dataCollector_id) dC_writeLog(step, dev, dC_device);

		// read data
		HEPSY_S(dataCollector_id) ann_04_dataCollector_payload_var = ann_04_dataCollector_channel->read();

		// encap in data_structure
		HEPSY_S(dataCollector_id) dev = ann_04_dataCollector_payload_var.dev;
		HEPSY_S(dataCollector_id) step = ann_04_dataCollector_payload_var.step;
		HEPSY_S(dataCollector_id) dC_device.time_Ex = ann_04_dataCollector_payload_var.ex_time;
		HEPSY_S(dataCollector_id) dC_device.i = ann_04_dataCollector_payload_var.device_i;
		HEPSY_S(dataCollector_id) dC_device.v = ann_04_dataCollector_payload_var.device_v;
		HEPSY_S(dataCollector_id) dC_device.t = ann_04_dataCollector_payload_var.device_t;
		HEPSY_S(dataCollector_id) dC_device.r = ann_04_dataCollector_payload_var.device_r;
		HEPSY_S(dataCollector_id) dC_device.fault = ann_04_dataCollector_payload_var.fault;

		// ###   W R I T E   L O G
		HEPSY_S(dataCollector_id) dC_writeLog(step, dev, dC_device);

		HEPSY_S(dataCollector_id) if( dC_file != NULL )
		{HEPSY_S(dataCollector_id)
			HEPSY_S(dataCollector_id) fclose(dC_file);			// Error should be checked
		}

		//sending to display the last step
		HEPSY_S(dataCollector_id) system_display_payload_var.example = step;

		HEPSY_S(dataCollector_id) system_display_port_in->write(system_display_payload_var);

		HEPSY_P(dataCollector_id)
	
	}
}
//END
