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

#ifndef __SYSTEMMANAGER__
#define __SYSTEMMANAGER__

#include <systemc.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "tl.h"

#include "define.h"

using namespace std;

////////////////////////////
// SBM INDEPENDENT
////////////////////////////

class SystemManager
{

	public:

		// Vector of processes
		vector<Process> VPS;

		// Vector of channels
		vector<Channel> VCH; 

		// Vector of basic blocks
		vector<BasicBlock> VBB; 

		// Vector of physical link
		vector<PhysicalLink> VPL; 

		// Allocation of PS to BB instances
		// (IDs of BB and PUs instances are possibly different by construction)
		vector<int> allocationPS_BB;

		// Allocation of CH to physical inks instances
		vector<int> allocationCH_PL; 

		// Constructor
		SystemManager();

		// Used to fill VPS by reading application.xml
		//(process IDs are supposed to be incremental from 0 to NPS-1 where 0 is for stimulus and 1 is for display)
		vector<Process> generateProcessInstances(); 
		
		// Used to fill VCH by reading application.xml
		//(channel IDs, called logical links in the xml, are supposed to be incremental from 0 to NCH-1)
		vector<Channel> generateChannelInstances();

		// Update the profiling of a process
		void PS_Profiling(int processId);

		// Check if a process is allocated on a SPP
		bool checkSPP(int processId);

		// Delete XML concurrency and communication instances
		void deleteConcXmlConCom();

		// Update XML concurrency and communication instances
		void updateXmlConCom(float matrixCONC_PS_N[NPS][NPS], unsigned int matrixCOM[NPS][NPS], float matrixCONC_CH_N[NCH][NCH]);

		// Return a subset of allocationPS_BB by considering only processes mapped to BB with ID equal to bb_id
		vector<int> getAllocationPS_BB(int bb_id);

		// Evaluate the simulated time for the execution of a statement
		sc_time updateSimulatedTime(int processId);

		// Increase time for each statement
		void increaseSimulatedTime(int processId);

		// Increase processTime for the wait of the timers
		void increaseTimer(int processId, sc_time delta);

		// Evaluate the energy for the execution of a statement
		float updateEstimatedEnergy(int processId);

		// Increase Energy for each statement
		void increaseEstimatedEnergy(int processId);

		// Delete XML Energy instances
		void deleteConcXmlEnergy();

		// Update XML Energy instances
		void updateXmlEnergy();

		// Used to fill VBB by reading instancesTL.xml
		vector<BasicBlock> generateBBInstances();

		// Used to fill VPL by reading instancesTL.xml
		vector<PhysicalLink> generatePhysicalLinkInstances();  

		// Fill allocationPS_BB by reading mappingPS.xml
		void mappingPS();

		// Fill allocationCH_PL by reading mappingCH.xml
		void mappingCH();

		// Free Running Load for Processes
		float FRL[NPS];

		//Free Running Time
		sc_time FRT;

		// Get Free Running Time
		sc_time getFRT();
		// Set Free Running Time
		void setFRT(sc_time x);

		//TODO: check float*
		// Load Estimation
		float* loadEst(sc_time FRT_n);
		//TODO: check float*
		// Get Free Running Load
		float* getFRL();

		// Delete XML Load instances
		void deleteConcXmlLoad();
		// Update XML Load instances
		void updateXmlLoad();
};

#endif
