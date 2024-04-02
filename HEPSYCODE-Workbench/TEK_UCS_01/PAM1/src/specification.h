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
 * Authors: Vittoriano Muttillo, Luigi Pomante                                  *
 *                                                                              *
 * email: vittoriano.muttillo@guest.univaq.it                                   *
 *        luigi.pomante@univaq.it                                               *
 *                                                                              *
 ********************************************************************************
 * This code has been developed from an HEPSYCODE model used as demonstrator by	*
 * University of L'Aquila.                                                      *
 *******************************************************************************/

#ifndef __SPECIFICATION__
#define __SPECIFICATION__

#include "basicBlock.h"
#include "process.h"

///
/// Specification: save information about genetic algorithm parameters, cost function weights,
/// constraints, processes considered, basic block and other information
///

class specification
{      
public:

	// Genetic Algorithm parameters

	///
	/// Number of generations for the Genetic Algorithm
	///
	unsigned long numGen;
	///
	/// Initial number of individuals for the Genetic Algorithm
	///
	unsigned long numIndiv;
	///
	/// Max number of partitionings (individual) for the Genetic Algorithm
	///
	unsigned long numMaxIndiv;
	///
	/// Parameter for generate elitism array based on weight != 0
	///
	int numMaxElitism;
	///
	/// Birth rate parameter for the crossover operation
	///
	double birthRate;
	///
	/// Radioactivity rate parameter for the mutation operation
	///
	double radRate;
	///
	/// Death rate parameter for the purge operation
	///
	double deathRate;

	///
	///Check the execution number (first or second) to save populations and statistics in specific folder
	///
	int exe_num;
	///
	///Check if we want use the elitism operation
	///
	int elitismCheck;
	///
	///Check if we want use the weights equalization operation (at the momento onl the load-cost case)
	///
	int equalizationCheck;
	///

	//Genetic Algorithm settings

	// Cost function weight
	// Weights must be a convex combination (ie sum == 1)
	///
	/// Affinity weight value
	///
	double aff_w;
	double aff_w_fixed;
	///
	/// Communication weight value
	///
	double comm_w;
	double comm_w_fixed;
	///
	/// Parallelism weight value
	///
	double par_w;
	double par_w_fixed;
	///
	/// Load weight value
	///
	double load_w;
	double load_w_fixed;
	///
	/// Cost weight value
	///
	double cost_w;
	double cost_w_fixed;
	///
	/// SW size weight value
	///
	double size_SW_w;
	double size_SW_w_fixed;
	///
	/// HW size weight value
	///
	double size_HW_w;
	double size_HW_w_fixed;
	///
	/// Energy weight value
	///
	double energy_w;
	double energy_w_fixed;
	///
	/// Energy To Completion weight value
	///
	double energyTC_w;
	double energyTC_w_fixed;
	///
	/// Feasibility weight
	///
	double feas_w;

	// Constraints
	///
	/// Time to completion constraint
	///
	double TTC;
	///
	/// Energy to completion constraint
	///
	double ETC;
	///
	/// Processes number constraint
	///
	unsigned long numberProcesses;
	///
	/// Basic Block instances number constraint
	///
	unsigned long numBBinstances;
	///
	/// Max Basic Block instances constraint (not used at the moment?)
	///
	unsigned long maxNumBBinstances;
	///
	/// Max load value constraint
	///
	double loadMax;
	///
	/// Array of processes that compose the specification
	///
	process *project;
	///
	/// Array of Basic Block that compose the specification
	///
	basicBlock *architecture;
	///
	/// Number of processes that compose the specification
	///
	unsigned long numProcesses;
	///
	/// Number of Basic Block that compose the specification
	///
	unsigned long numBB;
	///
	/// Communication Matrix.
	/// Matrix of communications between processes:
	/// symmetric matrix whose rows and columns represent the processes
	/// and the contents the bytes exchanged between the pairs of processes
	///
	// Ex.
	//      P1  P2  P3
	//   P1 0   10  30
	//   P2 10  0   15
	//   P3 30  15  0
	//
	unsigned long *comMat;
	///
	/// Total Communication Cost.
	/// Maximum possible cost of communication between procedures
	/// calculated assuming that all are on different executors
	///
	unsigned long maxTCC;
	///
	/// Parallelism Matrix:
	/// symmetric matrix whose rows and columns represent the processes
	/// and the content represent if there is (1) or less (0) possibility of
	/// parallelism between the pairs of processes
	///
	// Ex.
	//      P1  P2  P3
	//   P1 0   1   1
	//   P2 1   0   0
	//   P3 1   0   0
	//
	double *parMat;
	///
	/// Max Exploited Parallelism.
	/// Max possible parallelism calculated assuming that all potentially parallel processes
	/// are on different executors
	///
	double maxEP;
	///
	/// Biggest cost among processing unit
	///
	double maxCOST;
	///
	/// Constructor
	///
	specification();
	///
	/// Load into the specification the PAM parameters (from XML file)
	///
	void load_parameters();
	///
	/// Load into the specification the project constraints (from XML file)
	///
	void load_constraints();
	///
	/// Load into the specification the information about the processes that compose
	/// the application under test (from XML file)
	///
	void create_processes();
	///
	/// Load into the specification the information about the Basic Block
	/// considered (from XML file)
	void create_basicBlocks();
	///
	/// Distructor
	///
	~specification();

};

#endif
