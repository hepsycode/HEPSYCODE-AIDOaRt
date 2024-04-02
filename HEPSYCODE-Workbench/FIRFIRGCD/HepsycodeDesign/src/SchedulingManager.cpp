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
 * SchedulingManager : Scheduling Manager file.
 *
 * Scheduling Manager: HEPSIM Scheduling Manager
 *
********************************************************************************/

/*! \file SchedulingManager.cpp
    \brief Scheduling Manager Documented file.

    Scheduling Manager: HEPSIM Scheduling Manager.
*/

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "SchedulingManager.h"
#include "SystemManager.h"

extern SystemManager *pSystemManager;
extern bool stop_concurrency_sampling;
extern unsigned int sampling_period;

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

// Link among scheduler instances and scheduler policies

#if defined(_TIMING_ENERGY_) && defined(_LOAD_)

	void SchedulingManager::scheduler_8051_0()
	{
		policy_SCHED_FCFS(BB8051_0_id, 0.0F, 0.0F);
	}

	void SchedulingManager::scheduler_8051_1()
	{
		policy_SCHED_FCFS(BB8051_1_id, 0.0F, 0.0F);
	}

	void SchedulingManager::scheduler_leon3_2()
	{
		policy_SCHED_FCFS(BBleon3_0_id, 0.0F, 0.0F);
	}

	void SchedulingManager::scheduler_leon3_3()
	{
		policy_SCHED_FCFS(BBleon3_1_id, 0.0F, 0.0F);
	}

#endif

#if defined(_TIMING_ENERGY_) && !defined(_LOAD_)

	void SchedulingManager::scheduler_8051_0()
	{
		policy_SCHED_FCFS(BB8051_0_id, 1.0F, 0.25F);
	}

	void SchedulingManager::scheduler_8051_1()
	{
		policy_SCHED_FCFS(BB8051_1_id, 1.0F, 0.25F);
	}

	void SchedulingManager::scheduler_leon3_2()
	{
		policy_SCHED_FCFS(BBleon3_0_id, 1.0F, 0.25F);
	}

	void SchedulingManager::scheduler_leon3_3()
	{
		policy_SCHED_FCFS(BBleon3_1_id, 1.0F, 0.25F);
	}

#endif

#if !defined(_TIMING_ENERGY_) && !defined(_LOAD_)

	void SchedulingManager::functional_analyzer()
	{
		policy_SCHED_RR(0, 0.0F, 0.0F);
	}

#endif

////////////////////////////////////////////////////////////////
// Implementation of scheduling policies
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Round Robin (RR) (used, without OVH, also for the functional analyzer)
// The running process is changed after the execution of each statement wihthe next ready one (in a circular way)
void SchedulingManager::policy_SCHED_RR(int pinstance, float full_oh, float part_oh)
{
	//// MAIN VARIABLES

	// Used to manage processes and processing unit
	Process ps;
	BasicBlock bb;
	ProcessingUnit pu;

	// Get BB/PU with ID equal to pinstance
	bb = pSystemManager->VBB[pinstance];
	pu = pSystemManager->VBB[pinstance].getProcessors()[0];  // Mono-core

	// Get the processes allocated on the BB/PU
	vector<int> local_PS = pSystemManager->getAllocationPS_BB(pinstance);

	#if defined(_DEBUG_)
		//// PRINT INFO (for debug)
		if (local_PS.size() != 0)
		{
			cout << endl << "Scheduler for BB: " << bb.getName() << "[" << pinstance << "] - PU: " << pu.getName() << "[" << pu.getId() << "]" << endl;
			cout << "Processes[" << local_PS.size() << "]: ";
			for (unsigned int i = 0; i < local_PS.size(); i++) cout << local_PS[i] << " ";
			cout << endl;
			cout << "Policy: Round-Robin" << endl << endl;
		}
		else cout << "No processes on BB: " << bb.getName() << "[" << pinstance << "] - PU: " << pu.getName() << "[" << pu.getId() << "] - Scheduler terminated" << endl << endl;

		#if _WIN32
			system("pause");
		#endif
	#endif

	//// MAIN BEHAVIOUR

	unsigned int current_local_ps_id = 0;
	unsigned int last_served_local_ps_id = 0;

	// If no processes for this processing unit the scheduler self-quit
	if (local_PS.size() == 0) return;
	else
	{
		// Get the current process
		ps = pSystemManager->VPS[local_PS[current_local_ps_id]];

		do
		{
			#if !defined(_TIMING_ENERGY_) // Only if functional analizer (only RR)
				// Concurrency check at each loop (i.e., current_local_ps_id == 0)
				if (current_local_ps_id == 0)
				{
					checkStatesProcessesRR();
					checkStatesChannelsRR();
				}
			#endif

			// Change scheduler state
			scheduler_state[pinstance] = running;
			HEPSY_TRACE_SCHED_STATE(pinstance)

			// Partial overhead to get info about the current process
			HEPSY_SCHED_CS(pinstance, part_oh)

			if (process_state[ps.id] == ready)
			{

				if (current_local_ps_id != last_served_local_ps_id)
				{
					// OVH to complete context switch
					HEPSY_SCHED_CS(pinstance, full_oh)
					last_served_local_ps_id = current_local_ps_id;

					sched_CS[pinstance]++; // Number of CS
				}

				// Exchange token with the current ready process and change its state in run
				schedule[ps.id].notify(SC_ZERO_TIME);
				process_state[ps.id] = running;
				HEPSY_TRACE_PS_STATE_THIS(ps.id)

				// Change scheduler state
				scheduler_state[pinstance] = ready;
				HEPSY_TRACE_SCHED_STATE(pinstance)

				wait(release[ps.id]);

				// Manage process state: if no blocked go in ready state
				if (process_state[ps.id] == running) process_state[ps.id] = ready;
				HEPSY_TRACE_PS_STATE_THIS(ps.id)
			}

			//Move to next process in the round
			current_local_ps_id = (current_local_ps_id + 1) % (local_PS.size());
			// Get the new current process
			ps = pSystemManager->VPS[local_PS[current_local_ps_id]];

			// if a "loop" on the allocated processes is completed without serving any process (and the new current is still waiting)
			// then check if it is possible to block the scheduler
			if ((current_local_ps_id == last_served_local_ps_id) && (process_state[ps.id] == waiting))
			{
				if (process_status_changed[pSystemManager->allocationPS_BB[ps.id]] == false)
				{
					scheduler_state[pinstance] = waiting;
					HEPSY_TRACE_SCHED_STATE(pinstance)

					// If no changes during explicit wait, it is safe to block the sceduler
					BB_mode[pSystemManager->allocationPS_BB[ps.id]] = suspended;
					HEPSY_TRACE_BB_STATE_THIS(ps.id)

					wait(activate[pSystemManager->allocationPS_BB[ps.id]]);

					// Reactivate BB/PU (scheduler is reactivated at the beginning of the while loop)
					BB_mode[pSystemManager->allocationPS_BB[ps.id]] = active;
					HEPSY_TRACE_BB_STATE_THIS(ps.id)

				}
				// Otherwise, it is NOT safe to block the sceduler, reset process_status_changed to false
				else
				{
					process_status_changed[pSystemManager->allocationPS_BB[ps.id]] = false;
				}
			}

			// Increase the number of scheduler executions for the scheduler instance
			// associated to the processing unit with id = pinstance
			sched_loops[pinstance]++;

		}while (1);
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Fist Come First Served (FCFS)
// A process run without preemption until it is ready
// It is blocked only when it start using a channel (i.e., a kind of system call)
void SchedulingManager::policy_SCHED_FCFS(int pinstance, float full_oh, float part_oh)
{

	//// MAIN VARIABLES

	// Used to manage processes and processing unit
	Process ps;
	BasicBlock bb;
	ProcessingUnit pu;

	// Get BB/PU with ID equal to pinstance
	bb = pSystemManager->VBB[pinstance];
	pu = pSystemManager->VBB[pinstance].getProcessors()[0];  // Mono-core

	// Get the processes allocated on the BB/PU
	vector<int> local_PS = pSystemManager->getAllocationPS_BB(pinstance);

	#if defined(_DEBUG_)
		//// PRINT INFO (for debug)
		if (local_PS.size() != 0)
		{
			cout << endl << "Scheduler for BB: " << bb.getName() << "[" << pinstance << "] - PU: " << pu.getName() << "[" << pu.getId() << "]" << endl;
			cout << "Processes[" << local_PS.size() << "]: ";
			for (unsigned int i = 0; i < local_PS.size(); i++) cout << local_PS[i] << " ";
			cout << endl;
			cout << "Policy: FCFS" << endl << endl;
		}
		else cout << "No processes on BB: " << bb.getName() << "[" << pinstance << "] - PU: " << pu.getName() << "[" << pu.getId() << "] - Scheduler terminated" << endl << endl;

		#if _WIN32
			system("pause");
		#endif
	#endif

	//// MAIN BEHAVIOUR

	// Working variables
	unsigned int current_local_ps_id = 0; // Index of local processes
	unsigned int last_served_local_ps_id = 0; // Keep the ID of the process tha has been run the last time

	// If no processes for this processing unit the scheduler self-quit
	if (local_PS.size()==0)	return;
	else
	// If there is at least one process execute selected one until is ready (by looping on current_local_ps_id, index of local processes)
	{

		// Get the current process
		ps = pSystemManager->VPS[local_PS[current_local_ps_id]];

		do{

			// Change scheduler state in running
			scheduler_state[pinstance] = running;
			HEPSY_TRACE_SCHED_STATE(pinstance)
			
			// Partial overhead to get info about the current process
			HEPSY_SCHED_CS(pinstance, part_oh)

			// FCFS: Until the considerd local process is ready it will run without scheduling overhead
			while(process_state[ps.id]==ready)
			{

				// If the local process is different from the last one that has been run
				// there is the need for a context switch so we need to pay an overhead
				if (current_local_ps_id != last_served_local_ps_id)
				{
					HEPSY_SCHED_CS(pinstance, full_oh)
					last_served_local_ps_id = current_local_ps_id;

					sched_CS[pinstance]++; // Number of CS
				}

				// Exchange token with the current ready process and change state in running
				schedule[ps.id].notify(SC_ZERO_TIME);
				process_state[ps.id]=running;
				HEPSY_TRACE_PS_STATE_THIS(ps.id)

				// Change scheduler state in ready
				scheduler_state[pinstance] = ready;
				HEPSY_TRACE_SCHED_STATE(pinstance)

				wait(release[ps.id]);

				// If no blocked go in ready state
				if (process_state[ps.id]==running) process_state[ps.id]=ready;
				HEPSY_TRACE_PS_STATE_THIS(ps.id)
			}

			//Move to next process
			current_local_ps_id = (current_local_ps_id + 1) % (local_PS.size());
			// Get the new current process
			ps = pSystemManager->VPS[local_PS[current_local_ps_id]];

			// if a "loop" on the allocated processes is completed without serving any process
			// then check if it is possible to block the scheduler
			if ((current_local_ps_id == last_served_local_ps_id) && (process_state[ps.id] == waiting))
			{
				if (process_status_changed[pSystemManager->allocationPS_BB[ps.id]]==false)
				{
					scheduler_state[pinstance]=waiting;
					HEPSY_TRACE_SCHED_STATE(pinstance)

					// If no changes from explicit wait, it is safe to block the sceduler
					BB_mode[pSystemManager->allocationPS_BB[ps.id]]=suspended;
					HEPSY_TRACE_BB_STATE_THIS(ps.id)

					wait(activate[pSystemManager->allocationPS_BB[ps.id]]);

					// Reactivate BB/PU (scheduler is reactivated at the beginning of the while loop)
					BB_mode[pSystemManager->allocationPS_BB[ps.id]] = active;
					HEPSY_TRACE_BB_STATE_THIS(ps.id)
				}
				// Otherwise, it is NOT safe to block the sceduler, reset process_status_changed to false
				else
				{
					process_status_changed[pSystemManager->allocationPS_BB[ps.id]]=false;
				}
			}

			// Increase the number of scheduler executions for the scheduler instance
			// associated to the processing unit with id = pinstance
			sched_loops[pinstance]++;

		}while(1);
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Fixed Priority (FP)
// It is run the ready process with max priority
void SchedulingManager::policy_SCHED_FP(int pinstance, float full_oh, float part_oh)
{
	//// MAIN VARIABLES

	// Used to manage processes and processing unit
	Process ps;
	BasicBlock bb;
	ProcessingUnit pu;

	// Get BB/PU with ID equal to pinstance
	bb = pSystemManager->VBB[pinstance];
	pu = pSystemManager->VBB[pinstance].getProcessors()[0];  // Mono-core

	// Get the processes allocated on the BB/PU
	vector<int> local_PS = pSystemManager->getAllocationPS_BB(pinstance);

	#if defined(_DEBUG_)
		//// PRINT INFO (for debug)
		if (local_PS.size() != 0)
		{
			cout << endl << "Scheduler for BB: " << bb.getName() << "[" << pinstance << "] - PU: " << pu.getName() << "[" << pu.getId() << "]" << endl;
			cout << "Processes[" << local_PS.size() << "]: ";
			for (unsigned int i = 0; i < local_PS.size(); i++) cout << local_PS[i] << " ";
			cout << endl;
			cout << "Policy: FP" << endl << endl;
		}
		else cout << "No processes on BB: " << bb.getName() << "[" << pinstance << "] - PU: " << pu.getName() << "[" << pu.getId() << "] - Scheduler terminated" << endl << endl;

		#if _WIN32
			system("pause");
		#endif
	#endif

	//// MAIN BEHAVIOUR

	// Working variables
	unsigned int current_local_ps_id = 0; // Index of local processes
	unsigned int last_served_local_ps_id = 0; // Keep the ID of the process tha has been run the last time

	unsigned int max_pri_ready_ps=0;
	unsigned int max_pri_ready_ps_id=0;
	bool ready_ps_found;

	// If no processes for this processing unit the scheduler self-quit
	if (local_PS.size()==0) return;
	else
	{

		do
		{
			// Change scheduler state in running
			scheduler_state[pinstance] = running;
			HEPSY_TRACE_SCHED_STATE(pinstance)

			max_pri_ready_ps = 0;
			ready_ps_found=false;

			// Partial overhead to get info about the current process
			HEPSY_SCHED_CS(pinstance, part_oh)

			for (current_local_ps_id = 0; current_local_ps_id<local_PS.size(); current_local_ps_id++)
			{
				// Get the current process
				ps = pSystemManager->VPS[local_PS[current_local_ps_id]];

				if ((process_state[ps.id] == ready) && (ps.priority >= max_pri_ready_ps))
				{
					max_pri_ready_ps = ps.priority;
					max_pri_ready_ps_id = current_local_ps_id;
					ready_ps_found=true;
				}
			}
			
			if (ready_ps_found==true)
			{

				ps = pSystemManager->VPS[local_PS[max_pri_ready_ps_id]];
				current_local_ps_id = max_pri_ready_ps_id;

				//OH x CS
				if (current_local_ps_id != last_served_local_ps_id)
				{
					HEPSY_SCHED_CS(pinstance, full_oh)
					last_served_local_ps_id = current_local_ps_id;

					sched_CS[pinstance]++; // Number of CS
				}

				// Exchange token with the current ready process and change state in run
				schedule[ps.id].notify(SC_ZERO_TIME);
				process_state[ps.id]=running;
				HEPSY_TRACE_PS_STATE_THIS(ps.id)

				// Change scheduler state in ready
				scheduler_state[pinstance] = ready;
				HEPSY_TRACE_SCHED_STATE(pinstance)

				wait(release[ps.id]);

				// If no blocked go in ready state
				if (process_state[ps.id]==running) process_state[ps.id]=ready;
				HEPSY_TRACE_PS_STATE_THIS(ps.id)
			}
			else
			{
				if (process_status_changed[pSystemManager->allocationPS_BB[ps.id]] == false)
				{
					scheduler_state[pinstance] = waiting;
					HEPSY_TRACE_SCHED_STATE(pinstance)

					// If no changes from explicit wait, it is safe to block the sceduler
					BB_mode[pSystemManager->allocationPS_BB[ps.id]] = suspended;
					HEPSY_TRACE_BB_STATE_THIS(ps.id)

					wait(activate[pSystemManager->allocationPS_BB[ps.id]]);

					// Reactivate BB/PU (scheduler is reactivated at the beginning of the while loop)
					BB_mode[pSystemManager->allocationPS_BB[ps.id]] = active;
					HEPSY_TRACE_BB_STATE_THIS(ps.id)
				}
				// Otherwise, it is NOT safe to block the sceduler, reset process_status_changed to false
				else
				{
					process_status_changed[pSystemManager->allocationPS_BB[ps.id]] = false;
				}
			}

			// Increase the number of scheduler executions for the scheduler instance
			// associated to the processing unit with id = pinstance
			sched_loops[pinstance]++;

		}while(1);
	}
}

/////// METHODS FOR CONCURRENCHY ANALYSIS //////////

/////////////// ONLY RUN (ACTUAL)

void SchedulingManager:: checkStatesProcessesR()
{
	for (unsigned int i=0; i<NPS; i++)
	{
		if (process_state[i]==running)
		{
			for(unsigned int k=i+1; k<NPS; k++)
			{
				if (process_state[k]==running) matrixCONC_PS_R[i][k]++;
			}
		}
	}
	num_tests_CONC_PS_R++;
}

void SchedulingManager:: checkStatesChannelsR()
{
	for (unsigned int i=0; i<NCH; i++)
	{
		if (channel_state[i]==running)
		{
			for(unsigned int k=i+1; k<NCH; k++)
			{
				if (channel_state[k]==running) matrixCONC_CH_R[i][k]++;
			}
		}
	}
	num_tests_CONC_CH_R++;
}

/////////////// RUN&READY (POTENTIAL)

void SchedulingManager:: checkStatesProcessesRR()
{
	for (unsigned int i=0; i<NPS; i++)
	{
		if ((process_state[i]==ready)||(process_state[i]==running))
		{
			for(unsigned int k=i+1; k<NPS; k++)
			{
				if ((process_state[k]==ready)||(process_state[k]==running)) matrixCONC_PS_RR[i][k]++;
			}
		}
	}
	num_tests_CONC_PS_RR++;
}

void SchedulingManager:: checkStatesChannelsRR()
{
	for (unsigned int i=0; i<NCH; i++)
	{
		if ((channel_state[i]==ready)||(channel_state[i]==running))
		{
			for(unsigned int k=i+1; k<NCH; k++)
			{
				if ((channel_state[k]==ready)||(channel_state[k]==running)) matrixCONC_CH_RR[i][k]++;
			}
		}
	}
	num_tests_CONC_CH_RR++;
}

/////////////// ACTUAL

void SchedulingManager:: checkStatesBB()
{
	for (unsigned int i=0; i<NBB; i++)
	{
		if (BB_mode[i]==active)
		{
			for(unsigned int k=i+1; k<NBB; k++)
			{
				if (BB_mode[k]==active) matrixCONC_BB[i][k]++;
			}
		}
	}

	unsigned int k=0;

	for (unsigned int i=0; i<NBB; i++)
	{
		if (BB_mode[i]==active) k++;
	}

	vectorCONC_BB[k]++;
	num_tests_CONC_BB++;
}

/////////////// CONCURRENCY SAMPLING
void SchedulingManager::concurrency_sampling()
{
	while(stop_concurrency_sampling==false)
	{
		// Concurrency check (ad ogni statement eseguito) - usare apposito sc_thread?
		checkStatesProcessesR();
		checkStatesProcessesRR();
		checkStatesChannelsR();
		checkStatesChannelsRR();
		checkStatesBB();

		// Periodic sampling
		wait(sampling_period, SC_NS);
	}
}

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
