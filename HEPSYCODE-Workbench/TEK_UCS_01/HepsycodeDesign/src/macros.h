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

#ifndef __MACROS__
#define __MACROS__

//////// MAIN MACROS /////////////

// Macro S for managing the inyercation with the scheduler and the increase of simulated time and estimated energy

#if defined(_TIMING_ENERGY_)

	#define HEPSY_S(X) 																\
		pSystemManager->increaseSimulatedTime(X);											\
		pSystemManager->increaseEstimatedEnergy(X);										\
		if(!pSystemManager->checkSPP(X)) wait(pSchedulingManager->schedule[X]); \
		wait(pSystemManager->updateSimulatedTime(X));										\
		if(!pSystemManager->checkSPP(X)) pSchedulingManager->release[X].notify(SC_ZERO_TIME);
#else

	#define HEPSY_S(X) 																\
		wait(pSchedulingManager->schedule[X]);					\
		pSchedulingManager->release[X].notify(SC_ZERO_TIME);

#endif

// Macro P for Profiling (to be used at the end of while(1))
#define HEPSY_P(X) pSystemManager->PS_Profiling(X);

// Macro HEPSY_SCHED_CS for managing the Overhead introduced by the scheduler ContextSwitch activities and the energy for CS
#define HEPSY_SCHED_CS(X, i)									\
		wait(pSystemManager->VBB[X].getProcessors()[0].getOverheadCS()*i);   			 \
		this->sched_oh[X] += pSystemManager->VBB[X].getProcessors()[0].getOverheadCS()*i;      \
		this->sched_en[X]+= ((pSystemManager->VBB[X].getProcessors()[0].getOverheadCS().to_seconds() * pSystemManager->VBB[X].getProcessors()[0].getPower())*1000000);

// Macro PRE_WAIT to support the use of explicit wait (for ALT or timers) in the model
// Since we are going to call a wait (without involving channels) we need to explicitly change the process status
#define PRE_WAIT(X)									\
	pSchedulingManager->process_state[X]=waiting;	\
	HEPSY_TRACE_PS_STATE(X)

// Macro POST_WAIT to support the use of explicit wait (for ALT or timers) in the model
// Since we call a wait (without involving channels) we need to explicitly check BB mode
// Since we call a wait (without involving channels) we need to explicitly change the process status
// We nee also to avoid the block of schedulers if some changes in the processes state happened
#define POST_WAIT(X)																				\
	if (pSchedulingManager->BB_mode[pSystemManager->allocationPS_BB[X]]==suspended)					\
	{																								\
		if (pSystemManager->checkSPP(X)==true)														\
		{																							\
			pSchedulingManager->BB_mode[pSystemManager->allocationPS_BB[X]]=active;					\
			HEPSY_TRACE_BB_STATE(X)																				\
		}																							\
		else pSchedulingManager->activate[pSystemManager->allocationPS_BB[X]].notify(SC_ZERO_TIME);	\
	}																								\
																									\
if (pSystemManager->checkSPP(X)==true) pSchedulingManager->process_state[X]=running;				\
	else pSchedulingManager->process_state[X]=ready;												\
	HEPSY_TRACE_PS_STATE(X)																						\
																									\
if (pSystemManager->checkSPP(X)==false)																\
	pSchedulingManager->process_status_changed[pSystemManager->allocationPS_BB[X]]=true;

// Macro S for managing the increase of simulated time while also interacting with the scheduler
// in case of explicit wait (timers)
#define HEPSY_S_TIMER(X,Y) 																		\
		pSystemManager->increaseTimer(X,Y);														\
		if(!pSystemManager->checkSPP(X)) wait(pSchedulingManager->schedule[X]);					\
		PRE_WAIT(X)																				\
		wait(Y);																				\
		POST_WAIT(X)																			\
		if(!pSystemManager->checkSPP(X)) pSchedulingManager->release[X].notify(SC_ZERO_TIME);

//////// MACROS FOR LOG /////////////

// Macro for tracing of processes states
#define HEPSY_TRACE_PS_STATE(X)																\
		pSchedulingManager->LOG << "Execution Time;" << sc_time_stamp().to_seconds() << "; Energy;" << pSystemManager->VPS[X].getEnergy() << "; Process;" << X << "; State;" << pSchedulingManager->process_state[X] << endl;

// The same but used inside the scheduler
#define HEPSY_TRACE_PS_STATE_THIS(X)																\
		this->LOG << "Execution Time;" << sc_time_stamp().to_seconds() << "; Energy;" << pSystemManager->VPS[X].getEnergy() << "; Process;" << X << "; State;" << this->process_state[X] << endl;

// Macro for tracing of channels states
#define HEPSY_TRACE_CH_STATE(X)																\
		pSchedulingManager->LOG << "Execution Time;" << sc_time_stamp().to_seconds() << "; Energy;" << pSystemManager->VCH[X].working_energy << "; Channel;" << X << "; State;" << pSchedulingManager->channel_state[X] << endl;

// The same but used inside the scheduler
#define HEPSY_TRACE_CH_STATE_THIS(X)																\
		this->LOG << "Execution Time;" << sc_time_stamp().to_seconds() << "; Energy;" << pSystemManager->VCH[X].working_energy << "; Channel;" << X << "; State;" << this->channel_state[X] << endl;

// Macro for tracing of BB states
#define HEPSY_TRACE_BB_STATE(X)																\
		pSchedulingManager->LOG << "Execution Time;" << sc_time_stamp().to_seconds() << "; Energy;" << 0 << "; BB;" << X << "; Mode;" << pSchedulingManager->BB_mode[X] << endl;

// The same but used inside the scheduler
#define HEPSY_TRACE_BB_STATE_THIS(X)																\
		this->LOG << "Execution Time;" << sc_time_stamp().to_seconds() << "; Energy;" << 0 << "; BB;" << X << "; Mode;" << this->BB_mode[X] << endl;

// Macro for tracing of schedulers states
#define HEPSY_TRACE_SCHED_STATE(X)																\
		this->LOG << "Execution Time;" << sc_time_stamp().to_seconds() << "; Energy;" << this->sched_en[X] << "; Scheduler;" << X << "; State;" << this->scheduler_state[X] << endl;

#endif
