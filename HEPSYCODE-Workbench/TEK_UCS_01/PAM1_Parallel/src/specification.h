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
	unsigned long generations;
	///
	/// Initial number of partitionings (individual) for the Genetic Algorithm
	///
	unsigned long nPart;
	///
	/// Max number of partitionings (individual) for the Genetic Algorithm
	///
	unsigned long numMaxPart;
	///
	/// Parameter for generate elitism array based on weight != 0
	///
	int numMaxElitism;
	///
	/// Birth rate parameter for the crossover operation
	///
	float birthRate;
	///
	/// Radioactivity rate parameter for the mutation operation
	///
	float radRate;
	///
	/// Death rate parameter for the purge operation
	///
	float deathRate;

	// Cost function weight
	// Weights must be a convex combination (ie sum == 1)
	///
	/// Affinity weight value
	///
	float aff;
	///
	/// Communication weight value
	///
	float comm;
	///
	/// Parallelism weight value
	///
	float par_w;
	///
	/// Load weight value
	///
	float load;
	///
	/// Cost weight value
	///
	float cost;
	///
	/// SW size weight value
	///
	float size_SW;
	///
	/// HW size weight value
	///
	float size_HW;
	///
	/// Criticality weight value
	///
	float crit;
	///
	/// Feasibility weight
	///
	float feas;

	// Constraints
	///
	/// Time to completion constraint
	///
	float TTC;
	///
	/// Processes number constraint
	///
	unsigned int numberProcesses;
	///
	/// Basic Block instances number constraint
	///
	int instanceBB;
	///
	/// Max Basic Block instances constraint
	///
	int instanceMaxBB;
	///
	/// Max load value constraint
	///
	float loadMax;
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
	int numProc;
	///
	/// Number of Basic Block that compose the specification
	///
	int numBB;
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
	float *comMat;
	///
	/// Total Communication Cost.
	/// Maximum possible cost of communication between procedures
	/// calculated assuming that all are on different executors
	///
	float maxTCC;
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
	float *parMat;
	///
	/// Max Exploited Parallelism.
	/// Max possible parallelism calculated assuming that all potentially parallel processes
	/// are on different executors
	///
	float maxEP;
	///
	/// Biggest cost among processing unit
	///
	float maxCOST;
	///
	/// Constructor
	///
	specification(int start);
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
