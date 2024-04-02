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
 * Created on: 19/Aug/2019                                                      *
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
 * main.cpp : FirFirGCD main file.                                              *
 *******************************************************************************/

/*! \mainpage HEPSYCODE FirFirGCD Application

\section INTRODUCTION

Hepsycode is a prototypal tool to improve the design time of embedded applications. 
It is based on a System-Level methodology for HW/SW Co-Design of Heterogeneous Parallel 
Dedicated Systems. The whole framework drives the designer from an Electronic System-Level 
(ESL) behavioral model, with related NF requirements, including real-time and 
mixed-criticality ones, to the final HW/SW implementation, considering specific 
HW technologies, scheduling policies and Inter-Process Communication (IPC) mechanisms. 
The system behavior modeling language introduced in Hepsycode, named HML (HEPSY Modeling Language), 
is based on the Communicating Sequential Processes (CSP) Model of Computation (MoC). 
It allows modeling the behavior of the system as a network of processes communicating 
through unidirectional synchronous channels. By means of HML it is possible to specify 
the System Behavior Model (SBM), an executable model of the system behavior, a set of 
Non Functional Constraints (NFC) and a set of Reference Inputs (RI) to be used for 
simulation-based activities. Through the execution of different steps, including a 
system-level Design Space Exploration (DSE) approach that allows the related co-design 
methodology to suggest an HW/SW partitioning of the application specification and a 
mapping of the partitioned entities onto an automatically defined heterogeneous 
multi-processor architecture, it is possible to proceed with system implementation.

Hepsycode uses Eclipse MDE technologies, SystemC custom simulator implementation and 
an evolutionary genetic algorithm for partitioning activities, all integrated 
into an automatic framework that drive the designer from first input to final solution.

\subsection WEBSITE
<a href="http://www.hepsycode.com">www.hepsycode.com</a>

\subsection LICENSE
GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007 
(see <a href="https://www.gnu.org/licenses/gpl-3.0.en.html">gpl-3.0.en.html</a>)

\subsection SUPPORT

We currently support:

Email:
	- Luigi Pomante: luigi.pomante@univaq.it
	- Vittoriano Muttillo: vittoriano.muttillo@guest.univaq.it
	- Main contact: info@hepsycode.com

(please take care to use [HEPSYCODE SUPPORT] as object

\subsection Additional information

Research publications are available on 
<a href="http://www.hepsycode.com/">Hepsycode Website</a> and 
<a href="http://www.pomante.net/sito_gg/Publications.htm">Publications</a>

\section Example Use Case FirFirGCD

We provide an example Hepsycode project, called FirFirGCD (FFG). FFG is a 
synthetic application that takes in input pairs of values (triggered by Stimulus), 
makes two filtering actions (FIR8 and FIR16) and then makes the Greatest Common 
Divisor (GCD) between the filters outputs and displays the result. This application 
is composed of three main components: 2 Finite Impulse Response (FIR) digital 
filters and a Greatest Common Divisor (GCD) component, as show in the figure below.
 
\image html ./HepsycodeModel/FirFirGCD_Model_0_0.png

More details can be found at the link:
<a href="http://www.hepsycode.com">www.hepsycode.com</a>

 */

/********************************************************************************
 * main.cpp : Defines the HEPSIM2 main file.                                    *
 *                                                                              *
 * HEPSIM2 main file                                                            *
 *                                                                              *
********************************************************************************/

/*! \file main.cpp
    \brief Main Documented file.

    Details.
*/

/** @defgroup firfirgcd_main_group FirFirGCD Main.
 *
 *  MAIN
 *
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start firfirgcd_main_group


/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <time.h>
#include <string.h>

#include <systemc.h>

#include "define.h"
#include "sc_csp_channel_ifs.h"
#include "datatype.h"
#include "stim_gen.h"
#include "mainsystem.h"
#include "display.h"

#include "sc_csp_channel.h"
#include "SchedulingManager.h"
#include "SystemManager.h"
#include "tl.h"

using namespace std;

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

// Allocation of global SystemManager
SystemManager		*pSystemManager = new SystemManager();

// Allocation of global SchedulingManager
SchedulingManager	*pSchedulingManager = new SchedulingManager("SchedulingManager"); // It is a SC_MODULE (beacuse we need SC_THREADs) so the internal name is needed

// CONCURRENCY SAMPLING CONTROL (only for timing concurrency)
// Used to stop sampling SC_THREAD in SchedulingManager (in the future they will be external parameters)
unsigned int sampling_period = 1000; // HW architecture dependent: tipically in the interval 10-1000 SC_NS
bool stop_concurrency_sampling=false; // Used to stop sampling SC_THREAD in SchedulingManager

/////////////////////////////////////////////////////////////////////////////////////////////
// PARTIALLY SBM DEPENDENT
/////////////////////////////////////////////////////////////////////////////////////////////

int sc_main(int a, char* b[])
{

	/////////////////////////////////////////////////////////////////////////////////////////
	/// Testbench and System (SBM dependent)
	/////////////////////////////////////////////////////////////////////////////////////////
	
	/// Instantiation and connection of testbench and system

	sc_csp_channel< sc_uint<8> >   stim1_channel(12);
    sc_csp_channel< sc_uint<8> >   stim2_channel(13);
	sc_csp_channel< sc_uint<8> >   result_channel(14);

	/// Instantiation and connection of testbench and system

	stim_gen mystimgen("mystimgen");
	mystimgen.stim1_channel_port(stim1_channel);
	mystimgen.stim2_channel_port(stim2_channel);

	mainsystem mysystem("mysystem");
	mysystem.stim1_channel_port(stim1_channel);
	mysystem.stim2_channel_port(stim2_channel);
	mysystem.result_channel_port(result_channel);

	display mydisplay("mydisplay");
	mydisplay.result_channel_port(result_channel);

	/////////////////////////////////////////////////////////////////////////////////////////
	/// Simulation management (maybe SBM dependent)
	/////////////////////////////////////////////////////////////////////////////////////////

	// Time info
	sc_time end_sim, tot=sc_time(0, SC_MS), tot_sched_oh=sc_time(0, SC_MS);

    clock_t start = clock();

	// Start simulation
	cout << endl;
	sc_start();

	//  Total simulated and simulation times
	end_sim=sc_time_stamp();
	clock_t end = clock();

	#if _WIN32
	    system("pause");
	#endif

	/////////////////////////////////////////////////////////////////////////////////////////
	/// Report (SBM independent)
	/////////////////////////////////////////////////////////////////////////////////////////

	//LP: check tutti i save_csv, save_xml e trace

	#if defined(_SAVE_CSV_)
		// Initialize csv file for statistics storage
		ofstream myStatFile;
		myStatFile.open ("./Results.csv",std::ofstream::out | std::ofstream::app);

		string scenario_id;

		cout << "Insert Scenario ID: ";

		// Take input using cin
		cin >> scenario_id;

		myStatFile << "Scenario ID,";
		myStatFile << scenario_id +","; // @suppress("Function cannot be resolved")
	#endif

	/////////////////////////////////////////////////////////////////////////////////////////
	/// Timing DATA about simulation
	/////////////////////////////////////////////////////////////////////////////////////////
		
	cout << endl << "FINAL SIMULATION TIME: " << (((float)(end - start)) / CLOCKS_PER_SEC) << endl;

	#if defined _SAVE_CSV_
		myStatFile << "FINAL SIMULATION TIME,";
		myStatFile << to_string((((float)(end - start)) / CLOCKS_PER_SEC)) +","; // @suppress("Function cannot be resolved")
	#endif

	cout << endl << "FINAL SIMULATED TIME: " << end_sim.to_seconds() << endl;

	#if defined _SAVE_CSV_
		myStatFile << "FINAL SIMULATED TIME,";
		myStatFile << to_string(end_sim.to_seconds()) +",";  // @suppress("Function cannot be resolved")
	#endif

	/////////////////////////////////////////////////////////////////////////////////////////
	// Processes DATA
	/////////////////////////////////////////////////////////////////////////////////////////

	#if defined(_DEBUG_)
		// Print process mapping for DEBUG

		cout << endl << "PROCESSES MAPPING" << endl << endl;
		for (unsigned int j = 2; j<NPS; j++)
		{
			cout << "Process " << pSystemManager->VPS[j].name << "[" <<pSystemManager->VPS[j].id << "] is on BB" <<
			pSystemManager->VBB[pSystemManager->allocationPS_BB[j]].getName()<< "[" << pSystemManager->allocationPS_BB[j] << "]" << endl;
		}
		cout << endl;

		#if _WIN32
				system("pause");
		#endif
	#endif

	// Number of times each process has been executed (i.e., number of loops)
	cout << endl << "PROCESSES PROFILING" << endl;

	#if defined _SAVE_CSV_
		myStatFile << "PROCESSES PROFILING,";
	#endif

	for( unsigned int j=2; j<NPS; j++)
	{
		cout << pSystemManager->VPS[j].id << ": " << pSystemManager->VPS[j].profiling << endl;

		#if defined _SAVE_CSV_
			myStatFile << to_string(pSystemManager->VPS[j].profiling) +","; // @suppress("Function cannot be resolved")
		#endif
	}
	cout << endl;

	#if _WIN32
	    system("pause");
	#endif

	// Number of bytes exchanged among process
	cout << endl << "PROCESSES COMMUNICATIONS MATRIX (#written bits from W to R)" << endl;
	cout << "   ";
	for (int j = 0; j<NPS; j++)
	{
		cout << setw(4) << j;
	}
	cout << endl;

	for (int i = 0; i<NPS; i++)
	{
		cout << setw(2) << i << " ";
		for (int j = 0; j<NPS; j++)
		{
			pSchedulingManager->matrixCOM[i][j] = 0;
			for (int k = 0; k<NCH; k++)
			{
				if (pSystemManager->VCH[k].getW_id() == i && pSystemManager->VCH[k].getR_id() == j)
				{
					pSchedulingManager->matrixCOM[i][j] += pSystemManager->VCH[k].getWidth()*pSystemManager->VCH[k].getNum();
				}
			}
			cout << setw(4) << pSchedulingManager->matrixCOM[i][j];
		}
		cout << endl;
	}

	#if _WIN32
		system("pause");
	#endif


	#if defined(_TIMING_ENERGY_)

		cout << endl << "PROCESS TIME PROFILING" << endl;

		cout << endl << "Average NET TIME for each process:" << endl << endl;

		#if defined _SAVE_CSV_
			myStatFile << "Average NET TIME,"; // @suppress("Function cannot be resolved")
		#endif

		for(unsigned i =2; i<pSystemManager->VPS.size(); i++)
		{
			cout << pSystemManager->VPS[i].id << " - " << pSystemManager->VPS[i].name << "\t\t" << (pSystemManager->VPS[i].processTime/pSystemManager->VPS[i].profiling).to_seconds() << endl;
			tot+=pSystemManager->VPS[i].processTime;

			#if defined _SAVE_CSV_
				myStatFile << to_string((pSystemManager->VPS[i].processTime/pSystemManager->VPS[i].profiling).to_seconds()) +","; // @suppress("Function cannot be resolved")
			#endif
		}
		cout << "Total NET TIME for all the processes:" << tot.to_seconds() << endl;

		#if defined _SAVE_CSV_
			myStatFile << "Total NET TIME,"; // @suppress("Function cannot be resolved")
			myStatFile << to_string(tot.to_seconds()) +","; // @suppress("Function cannot be resolved")
		#endif

			cout << endl << "Schedulers Overhead [time - #loops/#CS]" << endl;

		#if defined _SAVE_CSV_
			myStatFile << "Schedulers Overhead,"; // @suppress("Function cannot be resolved")
		#endif

		for(int i = 0; i<NBB; i++) // Figures for SPP will be always 0
		{
			cout << pSchedulingManager->sched_oh[i].to_seconds() << " - " << pSchedulingManager->sched_loops[i] << "/" << pSchedulingManager->sched_CS[i] << endl;
			tot_sched_oh += pSchedulingManager->sched_oh[i];

			#if defined _SAVE_CSV_
				myStatFile << to_string(pSchedulingManager->sched_oh[i].to_seconds()) +","; // @suppress("Function cannot be resolved")
			#endif
		}

		cout << "Total overhead for all the schedulers: " << tot_sched_oh.to_seconds() << endl;

		#if defined _SAVE_CSV_
			myStatFile << "Tot Schedulers Overhead,"; // @suppress("Function cannot be resolved")
			myStatFile << to_string(tot_sched_oh.to_seconds()) +","; // @suppress("Function cannot be resolved")
		#endif

		cout << endl;

		#if _WIN32
				system("pause");
		#endif

	#endif

	/////////////////////////////////////////////////////////////////////////////////////////
	/// Communications
	/////////////////////////////////////////////////////////////////////////////////////////

	#if defined(_DEBUG_)
		cout << endl << "CHANNELS MAPPING" << endl << endl;
		for(unsigned int j=0; j<NCH; j++)
		{
			cout << "Channel " << pSystemManager->VCH[j].name <<"[" <<pSystemManager->VCH[j].id << "] is on Physical Link " << pSystemManager->VPL[pSystemManager->allocationCH_PL[j]].getName()<<"["<< pSystemManager->allocationCH_PL[j]<<"]"<<endl;
		}
		cout << endl;

		#if _WIN32
				system("pause");
		#endif
	#endif

	cout << endl << "COMMUNICATION PROFILING" << endl << endl;

	// Info about data transfers on CSP channels
	cout << endl << "CHANNELS PROFILING" << endl << endl;

	cout << "ID-W-R\tBIT\tNUM\tBIT*NUM\t[TIME(sec)]" << endl << endl;
	for( unsigned int j=0; j<NCH; j++)
	{
			cout << pSystemManager->VCH[j].id << "-" << pSystemManager->VCH[j].w_id << "-" << pSystemManager->VCH[j].r_id << ": "
				<< pSystemManager->VCH[j].width << "\t" << pSystemManager->VCH[j].num << "\t" << pSystemManager->VCH[j].width*pSystemManager->VCH[j].num
				
				#if defined(_TIMING_ENERGY_)
					<< "\t" << pSystemManager->VCH[j].working_time.to_seconds()
				#endif
				
				<< endl;

	}
	cout << endl;

	#if _WIN32
		system("pause");
	#endif

	/////////////////////////////////////////////////////////////////////////////////////////
	/// ENERGY DATA
	/////////////////////////////////////////////////////////////////////////////////////////

	#if defined(_TIMING_ENERGY_)
		// Energy info
		double totEnergyProcesses = 0;
		double totEnergyChannels = 0;
		double totEnergySchedulers = 0;
		double totEnergyPartSchedulers = 0;
		double totEnergy = 0;

		cout << endl << "Average ENERGY for each process:" << endl;

		#if defined _SAVE_CSV_
			myStatFile << "Energy For Processes,"; // @suppress("Function cannot be resolved")
		#endif

		for(unsigned i =2; i<pSystemManager->VPS.size(); i++)
		{
			cout << pSystemManager->VPS[i].id << " - " << pSystemManager->VPS[i].name << "\t\t" << (pSystemManager->VPS[i].energy/pSystemManager->VPS[i].profiling) <<" uJ"<< endl;
			totEnergyProcesses+=pSystemManager->VPS[i].getEnergy();

			#if defined _SAVE_CSV_
				myStatFile << to_string(pSystemManager->VPS[i].energy/pSystemManager->VPS[i].profiling) +","; // @suppress("Function cannot be resolved")
			#endif

		}
		cout<<endl;
		cout << "Total ENERGY for all the processes: " << totEnergyProcesses <<" uJ" <<endl;

		#if defined _SAVE_CSV_
			myStatFile << "Total Energy Processes,"; // @suppress("Function cannot be resolved")
			myStatFile << to_string(totEnergyProcesses) +","; // @suppress("Function cannot be resolved")
		#endif

		cout << endl << "CHANNEL ENERGY:" << endl<<endl;
		cout<<"ID-W-R\tENERGY (uJ)"<<endl<<endl;
		for(unsigned int i = 0; i<NCH; i++)
		{
			cout << pSystemManager->VCH[i].id <<"-"<<pSystemManager->VCH[i].w_id << "-" << pSystemManager->VCH[i].r_id << "\t"<< pSystemManager->VCH[i].working_energy <<" uJ"<< endl;
			totEnergyChannels+=pSystemManager->VCH[i].working_energy;
		}
		cout<<endl;
		cout << "Total ENERGY for all the channels: " << totEnergyChannels <<" uJ" <<endl;

		cout << endl << "SCHEDULERS ENERGY:" << endl;

		#if defined _SAVE_CSV_
			myStatFile << "SCHEDULERS ENERGY,"; // @suppress("Function cannot be resolved")
		#endif

		for(int i = 0; i<NBB; i++) // Figures for SPP will be always 0
		{
			cout << pSchedulingManager->sched_en[i] << " uJ"<<endl;
			totEnergySchedulers+=pSchedulingManager->sched_en[i];

			#if defined _SAVE_CSV_
				myStatFile << to_string(pSchedulingManager->sched_en[i]) +","; // @suppress("Function cannot be resolved")
			#endif
		}

		cout<<endl;
		cout << "Total ENERGY for all the Schedulers: " << totEnergySchedulers <<" uJ" <<endl;

		#if defined _SAVE_CSV_
			myStatFile << "TOT SCHEDULERS ENERGY,"; // @suppress("Function cannot be resolved")
			myStatFile << to_string(totEnergySchedulers) +",";
		#endif

		cout<<endl;

		totEnergy = totEnergyProcesses + totEnergyChannels + totEnergySchedulers + totEnergyPartSchedulers;

		cout << endl << "Total Energy (processes + channels + schedulers):  " << totEnergy <<" uJ"<<endl;

		#if defined _LOAD_
			pSystemManager->deleteConcXmlEnergy();
			pSystemManager->updateXmlEnergy();
		#endif

		#if defined _SAVE_CSV_
			myStatFile << "TOTAL ENERGY,";
			myStatFile << to_string(totEnergy) +","; // @suppress("Function cannot be resolved")
		#endif

	#endif

	/////////////////////////////////////////////////////////////////////////////////////////
	/// LOAD DATA
	/////////////////////////////////////////////////////////////////////////////////////////

	#if (defined(_TIMING_ENERGY_) && defined(_LOAD_))

		cout << endl << "LOAD ESTIMATION" << endl;

		double tot_proc_load = 0;

		pSystemManager->setFRT(end_sim);
		pSystemManager->loadEst(end_sim);

		for(unsigned i =2; i<pSystemManager->VPS.size(); i++)
		{
			cout <<endl<<"FRL:"<<" "<< pSystemManager->VPS[i].id << "-" << pSystemManager->VPS[i].name << " " << pSystemManager->getFRL()[i];
			tot_proc_load += pSystemManager->getFRL()[i];
		}
		cout << endl << endl << "FINAL TOTAL LOAD: " << tot_proc_load << endl << endl;

		pSystemManager->deleteConcXmlLoad();
		pSystemManager->updateXmlLoad();

	#endif

	/////////////////////////////////////////////////////////////////////////////////////////
	/// Report (concurrency)
	/////////////////////////////////////////////////////////////////////////////////////////

	#if ((!defined(_TIMING_ENERGY_)) || (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_))) // Printed only if (1) functional analizer or (2) timing concurrency
		// Number of times each process has been concurrently working with the others
		cout << endl << "POTENTIAL PROCESSES CONCURRENCY" << endl;
		cout << "  ";
		for (int j=2; j<NPS; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=2; i<NPS; i++)
		{
			cout << i << " " ;
			for (int j=2; j<NPS; j++)
			{
				cout<< setw(8) << pSchedulingManager->matrixCONC_PS_RR[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif
#endif

	#if (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_)) // Printed only if timing concurrency
		// Number of times each process has been concurrently working with the others
		cout << endl << "ACTUAL PROCESSES CONCURRENCY" << endl;
		cout << "  ";
		for (int j=2; j<NPS; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=2; i<NPS; i++)
		{
			cout << i << " " ;
			for (int j=2; j<NPS; j++)
			{
				cout<< setw(8) << pSchedulingManager->matrixCONC_PS_R[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif
#endif

	#if ((!defined(_TIMING_ENERGY_)) || (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_))) // Printed only if (1) functional analizer or (2) timing concurrency
		// Number of times each process has been concurrent with the others
		//with respect to the number of checks
		cout << endl << "NORMALIZED POTENTIAL PROCESSES CONCURRENCY (#TEST: " << pSchedulingManager->num_tests_CONC_PS_RR << ")" << endl;
		cout<< "   ";
		for (int j=2; j<NPS; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=2; i<NPS; i++)
		{
			cout<< setw(2) << i << " " ;
			for (int j=2; j<NPS; j++)
			{
				pSchedulingManager->matrixCONC_PS_RR_N[i][j] = pSchedulingManager->matrixCONC_PS_RR[i][j]/(float)pSchedulingManager->num_tests_CONC_PS_RR;
				cout<< setw(8) << setprecision(2) << pSchedulingManager->matrixCONC_PS_RR_N[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif
#endif

	#if (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_)) // Printed only if timing concurrency
		// Number of times each process has been concurrent with the others
		//with respect to the number of checks
			cout << endl << "NORMALIZED ACTUAL PROCESSES CONCURRENCY (#TEST: " << pSchedulingManager->num_tests_CONC_PS_R << ")" << endl;
		cout<< "   ";
		for (int j=2; j<NPS; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=2; i<NPS; i++)
		{
			cout<< setw(2) << i << " " ;
			for (int j=2; j<NPS; j++)
			{
				pSchedulingManager->matrixCONC_PS_R_N[i][j] = pSchedulingManager->matrixCONC_PS_R[i][j]/(float)pSchedulingManager->num_tests_CONC_PS_R;
				cout<< setw(8) << setprecision(2) << pSchedulingManager->matrixCONC_PS_R_N[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif
#endif

	#if ((!defined(_TIMING_ENERGY_)) || (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_))) // Printed only if (1) functional analizer or (2) timing concurrency
		// Number of times each channels has been concurrently working with the others
		cout << endl << "POTENTIAL CHANNELS CONCURRENCY" << endl;
		cout<< setw(2) << "   ";
		for (int j=0; j<NCH; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=0; i<NCH; i++)
		{
			cout<< setw(2) << i << " " ;
			for (int j=0; j<NCH; j++)
			{
				cout<< setw(8) << setprecision(2) << pSchedulingManager->matrixCONC_CH_RR[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif
#endif

	#if (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_)) // Printed only if timing concurrency
		// Number of times each channels has been concurrently working with the others
		cout << endl << "ACTUAL CHANNELS CONCURRENCY" << endl;
		cout<< setw(2) << "   ";
		for (int j=0; j<NCH; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=0; i<NCH; i++)
		{
			cout<< setw(2) << i << " " ;
			for (int j=0; j<NCH; j++)
			{
				cout<< setw(8) << setprecision(2) << pSchedulingManager->matrixCONC_CH_R[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif
#endif

	#if ((!defined(_TIMING_ENERGY_)) || (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_))) // Printed only if (1) functional analizer or (2) timing concurrency
		// Number of times each channels has been concurrently working with the others
		//with respect to the number of checks
		cout << endl << "NORMALIZED POTENTIAL CHANNELS CONCURRENCY (#TEST: " << pSchedulingManager->num_tests_CONC_CH_RR << ")" << endl;
		cout<< setw(2) << "   ";
		for (int j=0; j<NCH; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=0; i<NCH; i++)
		{
			cout<< setw(2) << i << " " ;
			for (int j=0; j<NCH; j++)
			{
				pSchedulingManager->matrixCONC_CH_RR_N[i][j] = pSchedulingManager->matrixCONC_CH_RR[i][j]/(float)pSchedulingManager->num_tests_CONC_CH_RR;
				cout<< setw(8) << setprecision(2) << pSchedulingManager->matrixCONC_CH_RR_N[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif
#endif

	#if (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_)) // Printed only if timing concurrency
		// Number of times each channels has been concurrently working with the others
		//with respect to the number of checks
		cout << endl << "NORMALIZED ACTUAL CHANNELS CONCURRENCY (#TEST: " << pSchedulingManager->num_tests_CONC_CH_R << ")" << endl;
		cout<< setw(2) << "   ";
		for (int j=0; j<NCH; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=0; i<NCH; i++)
		{
			cout<< setw(2) << i << " " ;
			for (int j=0; j<NCH; j++)
			{
				pSchedulingManager->matrixCONC_CH_R_N[i][j] = pSchedulingManager->matrixCONC_CH_R[i][j]/(float)pSchedulingManager->num_tests_CONC_CH_R;
				cout<< setw(8) << setprecision(2) << pSchedulingManager->matrixCONC_CH_R_N[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif

		// Number of times each BB has been concurrently active with the others
		cout << endl << "ACTUAL BB CONCURRENCY" << endl;
		cout<< setw(2) << "   ";
		for (int j=0; j<NBB; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=0; i<NBB; i++)
		{
			cout<< setw(2) << i << " " ;
			for (int j=0; j<NBB; j++)
			{
				cout<< setw(8) << setprecision(2) << pSchedulingManager->matrixCONC_BB[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif

		// Number of times each BB has been concurrently active with the others
		//with respect to the number of checks
		cout << endl << "NORMALIZED ACTUAL BB CONCURRENCY (#TEST: " << pSchedulingManager->num_tests_CONC_BB << ")" << endl;
		cout<< setw(2) << "   ";
		for (int j=0; j<NBB; j++)
		{
			cout<< setw(8) << j;
		}
		cout<< endl;

		for (int i=0; i<NBB; i++)
		{
			cout<< setw(2) << i << " " ;
			for (int j=0; j<NBB; j++)
			{
				pSchedulingManager->matrixCONC_BB_N[i][j] = pSchedulingManager->matrixCONC_BB[i][j]/(float)pSchedulingManager->num_tests_CONC_BB;
				cout<< setw(8) << setprecision(2) << pSchedulingManager->matrixCONC_BB_N[i][j];
			}
			cout<<endl;
		}

		#if _WIN32
			system("pause");
		#endif

		// Number of times a group of BBs have been concurrently active
		cout << endl << "ACTUAL BB GROUP CONCURRENCY" << endl;
		for (int j=0; j<NBB+1; j++)
		{
				cout << j << " ACTIVE BBs: " << pSchedulingManager->vectorCONC_BB[j] << endl;
		}

		// Number of times a group of BBs have been concurrently active
		cout << endl << "NORMALIZED ACTUAL BB GROUP CONCURRENCY (#TEST: " << pSchedulingManager->num_tests_CONC_BB << ")" << endl;
		for (int j=0; j<NBB+1; j++)
		{
				pSchedulingManager->vectorCONC_BB_N[j] = pSchedulingManager->vectorCONC_BB[j]/(float)pSchedulingManager->num_tests_CONC_BB;
				cout << j << " ACTIVE BBs: " << pSchedulingManager->vectorCONC_BB_N[j] << endl;
		}

		#if _WIN32
			system("pause");
		#endif
	#endif

	#if ((!defined(_TIMING_ENERGY_))) // || (defined(_TIMING_ENERGY_) && defined(_CONCURRENCY_))) // Printed only if (1) functional analizer or (2) timing concurrency
		cout << "Processes and Channels Concurrency, and Channels Communication XML update" << endl;

		// LP: Da controllare
		pSystemManager->deleteConcXmlConCom();

		// LP: da controllare
		pSystemManager->updateXmlConCom(pSchedulingManager->matrixCONC_PS_RR_N, pSchedulingManager->matrixCOM, pSchedulingManager->matrixCONC_CH_RR_N);
	#endif

	#if defined _SAVE_CSV_
		myStatFile << "\n";;

		// Save information about final population statistics into csv file
		myStatFile.close();
	#endif

	#if _WIN32
	    system("pause");
	#endif

	return 0;
}

/** @} */ // end of firfirgcd_main_group

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
