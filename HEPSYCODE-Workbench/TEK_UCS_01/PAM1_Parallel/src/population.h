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

//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Population
//============================================================================

#ifndef __POPULATION__
#define __POPULATION__

#include "individual.h"
#include "specification.h"

///
/// A population represents a set of individuals.
/// Manages operations related to population evolution based on a genetic algorithm.
/// Save information about population into csv files
///

class population
{
public:
	///
	/// Pointer to the specification
	///
	specification *spec;
	///
	/// Population of partitioning
	///
	individual **pop;
	///
	/// Array containing the elite partitioning for the elitism operation
	/// (for Elitism with Extreme Values operation).
	/// The size varies according to the weights of the non-zero objective functions
	///
	individual **elite;
	///
	/// Array containing the best couple process-processors of the population
	///
	int *pop_Best;
	///
	/// Best Cost Function value of the population
	///
	float bestCF;
	///
	/// Keep the current number of partitionings of the population
	///
	int numPart;
	///
	/// Max number of partitionings that will compose the population
	///
	int numPartMax;
	///
	/// Number of processes of the application under test
	///
	int numProcess;
	///
	/// Count the number of feasible solutions
	///
	int feasibleSol;
	///
	/// Constructor
	///
	population(specification *s);
	///
	/// Distructor
	///
	~population();
	///
	/// Reproduction operation for the Genetic Algorithm
	///
	void crossover( float repRate );
	///
	/// Genetic mutation operation
	///
	void mutation( float radRate );
	///
	/// Evaluate the total cost function of the newborns
	///
	void evaluation();

	void parallel_evaluation();
	///
	/// Elimination of random population individuals
	///
	void purge( float deathRate );
	///
	/// Elitism with Extreme Values operation
	///
	void elitismEV();
	///
	/// Update the elite array
	///
	void updateElite();
	///
	/// Equalizes weights at each iteration.
	/// At the moment only load and cost weights
	///
	void weightsEqualization();
	///
	/// Return the partitioning with min Affinity value
	///
	individual* minTDAPart();
	///
	/// Return the partitioning with min Communication value
	///
	individual* minNTCCPart();
	///
	/// Return the partitioning with min Parallelism value
	///
	individual* minEPPart();
	///
	/// Return the partitioning with min Load value
	///
	individual* minLPart();
	///
	/// Return the partitioning with min Cost value
	///
	individual* minCPart();
	///
	/// Return the partitioning with min SW SIze value
	///
	individual* minSWSizePart();
	///
	/// Return the partitioning with min HW Size value
	///
	individual* minHWSizePart();
	///
	/// Return the partitioning with min Cost Function value
	///
	individual* minCFPart();
	///
	/// Save and print the best partitioning of the population and some statistics.
	/// Save the statistics into csv file
	///
	void printMemStat(unsigned long gen, ofstream &myFile, double execTime);
	///
	/// Save the informations about the partitionings of the population into csv
	/// files during the evolution of genetic algorithm ever j generation
	///
	void memPop(int i, int j);
	///
	/// Save the informations about the partitionings of the population into csv
	/// files during the evolution of genetic algorithm ever j generation.
	/// The information about objective function are weighted.
	/// At the moment only cost-load objective functions are considered
	///
	void memWeightedPop(int i, int j);
	///
	/// Delete the last xml mapping file containing the best partitioning of the population
	///
	void deleteXml();
	///
	/// Create the xml mapping file containing the best partitioning of the population
	///
	void mappingXml(specification *s);
};

#endif
