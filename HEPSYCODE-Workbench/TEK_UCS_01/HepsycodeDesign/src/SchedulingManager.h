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

#ifndef __SCHEDULINGMANAGER__
#define __SCHEDULINGMANAGER__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>

#include <systemc.h>
#include "SystemManager.h"
#include "tl.h"

extern SystemManager *pSystemManager;

#include "define.h"
#include "macros.h"

SC_MODULE(SchedulingManager)
{
	public:

	// Data structure to manage scheduling and analysis

	state process_state[NPS]; // Status of processes: ready (waiting for PU), run, waiting (when a process is waiting to complete a communication over a channel)
	state channel_state[NCH]; // Status of channels: ready (1 process is arrived), run (data transfer), waiting (0 processes)
	state scheduler_state[NBB]; // Status of schedulers: run (scheduler is performing ContextSwitch activities), ready (waiting for token from a process), waiting (if BB suspended)

	unsigned int matrixCOM[NPS][NPS]; //Communication Matrix

	// Check READY&RUN - Potential concurrency
	unsigned int matrixCONC_PS_RR[NPS][NPS]; //Processes Concurrency matrix
	float matrixCONC_PS_RR_N[NPS][NPS]; //Normalized Processes Concurrency matrix (with respect to the number of tests)
	unsigned int matrixCONC_CH_RR[NCH][NCH]; //Channels Concurrency matrix
	float matrixCONC_CH_RR_N[NCH][NCH]; //Normalized Channels Concurrency matrix (with respect to the number of tests)

	void checkStatesProcessesRR(); // Check processes pairs
	void checkStatesChannelsRR(); // Check channels pairs

	// Check only RUN - Actual concurrency
	unsigned int matrixCONC_PS_R[NPS][NPS]; //Processes Concurrency matrix
	float matrixCONC_PS_R_N[NPS][NPS]; //Normalized Processes Concurrency matrix (with respect to the number of tests)
	unsigned int matrixCONC_CH_R[NCH][NCH]; //Channels Concurrency matrix
	float matrixCONC_CH_R_N[NCH][NCH]; //Normalized Channels Concurrency matrix (with respect to the number of tests)

	void checkStatesProcessesR(); // Check processes pairs
	void checkStatesChannelsR(); // Check channels pairs

	// Check BB (actual) concurrency
	unsigned int matrixCONC_BB[NBB][NBB]; //BB Concurrency matrix
	float matrixCONC_BB_N[NBB][NBB]; //Normalized BB Concurrency matrix (number of tests?)
	unsigned int vectorCONC_BB[NBB+1]; //Number of BBs concurrenty active
	float vectorCONC_BB_N[NBB+1]; //Normalized number of BBs concurrenty active (number of tests?)

	void checkStatesBB(); // Check BB pairs

	//Number of concurrency tests: used to normalize the concurrency matrixes
	unsigned int num_tests_CONC_PS_RR;
	unsigned int num_tests_CONC_PS_R;
	unsigned int num_tests_CONC_CH_RR;
	unsigned int num_tests_CONC_CH_R;
	unsigned int num_tests_CONC_BB;

	// Events exchanged by scheduler and processes on the base of process IDs
	sc_event schedule[NPS], release[NPS];

	// Functional Analyzer
	sc_event unblock;
    bool blocked;
	bool process_status_changed[NBB]; // Used to avoid the block of schedulers if some changes in the processes state happened

	// Items used to manage state of BB/PU
	mode BB_mode[NBB]; // Mode of BB (suspended, active)
	sc_event activate[NBB];

	// Data structure to keep track of scheduler timing overhead (the array is of NBB elements, the one related to SPP will not be used)
	sc_time sched_oh[NBB];

	// Data structure to keep track of scheduler energy consumption (the array is of NBB elements, the one related to SPP will not be used)
	double sched_en[NBB];

	// Data structure to keep track of the number of scheduler executions (i.e., scheduler SC_THREAD loops)
	unsigned int sched_loops[NBB]; // (the array is of NBB elements, the one related to SPP will not be used)
	// Data structure to keep track of the number of Context Switches
	unsigned int sched_CS[NBB]; // (the array is of NBB elements, the one related to SPP will not be used)

	ofstream LOG; // File to log each stat change (PSs, CHs, BBs, and schedulers)

	//Scheduler instances assigned to SC_THREADs, one for each possible instance of of SW-PU (see instanceTL.xml)
	void scheduler_8051_0();
	void scheduler_8051_1();
	void scheduler_leon3_2();
	void scheduler_leon3_3();
	void functional_analyzer();

	// Timing concurrency analysis
	void concurrency_sampling();

	//Scheduling policies that can be used by scheduler instances
	// pinstance: ID of BB/SW-PU
	// full_oh: weight for context switch time (normally 1)
	// part_oh: weight for activities of the scheduler that doesn't imply a context switch (normally 0.25)

	void policy_SCHED_RR(int pinstance, float full_oh, float part_oh);
	void policy_SCHED_FCFS(int pinstance, float full_oh, float part_oh);
	void policy_SCHED_FP(int pinstance, float full_oh, float part_oh);

	SC_CTOR(SchedulingManager)
	{
	    LOG.open("LOG.csv"); // Open file (closed in the destructor)

		// Creation of a scheduler instance for each possible instance of of SW-PU (as listed in instanceTL.xml) 
		// The NOT needed ones (i.e., no processes alocated on them) will self-quit

		#if defined(_TIMING_ENERGY_)

			SC_THREAD(scheduler_8051_0);
			SC_THREAD(scheduler_8051_1);
	    	SC_THREAD(scheduler_leon3_2);
			SC_THREAD(scheduler_leon3_3);

		#else

			SC_THREAD(functional_analyzer);

		#endif

		#if defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_)

			// Thread for concurrency analysis (if activated)
			SC_THREAD(concurrency_sampling);

		#endif

		LOG << "sep=;" << endl; // LP: ???

		// Init

		for(unsigned int j=0; j<NBB; j++)
		{
			scheduler_state[j] = undefined;
			if(pSystemManager->VBB[j].getProcessors()[0].getProcessorType() != "SPP")
			{
				HEPSY_TRACE_SCHED_STATE(j)																\
			}

			sched_oh[j]=sc_time(0, SC_MS);
			sched_en[j]=0;
			sched_loops[j]=0;
			sched_CS[j]=0;

			BB_mode[j]=off;
			HEPSY_TRACE_BB_STATE_THIS(j)

			process_status_changed[j]=false;
		}

		for (unsigned int j = 0; j<NBB+1; j++)
		{
			vectorCONC_BB[j] = 0;
			vectorCONC_BB_N[j] = 0;
		}

		// Init
		for(unsigned int j=0; j<pSystemManager->VPS.size(); j++)
		{
			if (pSystemManager->checkSPP(j)==true) process_state[j]=running;
			else if (j==0) process_state[j]=running;
			else if (j==1) process_state[j]=running;
			else process_state[j]=ready;
			HEPSY_TRACE_PS_STATE_THIS(j)

			// BB with processes are activated
			if (BB_mode[pSystemManager->allocationPS_BB[j]]!=active)
			{
				BB_mode[pSystemManager->allocationPS_BB[j]]=active;				
				HEPSY_TRACE_BB_STATE_THIS(j)
			}
		}

		for (int i=0; i<NPS; i++)
		{
			for (int j=0; j<NPS; j++)
			{
				matrixCONC_PS_RR[i][j]=0;
				matrixCONC_PS_RR_N[i][j]=0;
				matrixCONC_PS_R[i][j]=0;
				matrixCONC_PS_R_N[i][j]=0;
				matrixCOM[i][j]=0;
			}
		}

		for (int i=0; i<NBB; i++)
		{
			for (int j=0; j<NBB; j++)
			{
				matrixCONC_BB[i][j]=0;
			}
		}

		for (int i=0; i<NCH; i++)
		{
			channel_state[i]=waiting;
			HEPSY_TRACE_CH_STATE_THIS(i)

			for (int j=0; j<NCH; j++)
			{
				matrixCONC_CH_RR[i][j]=0;
				matrixCONC_CH_RR_N[i][j]=0;
				matrixCONC_CH_R[i][j]=0;
				matrixCONC_CH_R_N[i][j]=0;
			}
		}

		blocked = false;
		num_tests_CONC_PS_RR=0;
		num_tests_CONC_CH_RR=0;
		num_tests_CONC_PS_R=0;
		num_tests_CONC_CH_R=0;
		num_tests_CONC_BB=0;

	}  

	~SchedulingManager()
	{
		LOG.close(); // Close file
	}

};

#endif
