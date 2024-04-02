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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <iostream>
#include <string>
#include <fstream>
#include "population.h"
#include "pugixml.hpp"

#define TR_CRIT 2

using namespace std;
using namespace pugi;

// Destructor
population::~population()
{
      delete[] pop;
}

// Constructor
// Initializes the attributes of the population and creates the first random partitionings
population::population(specification *s)
{
      int i;
      
      numPart=s->nPart;
      numPartMax=s->numMaxPart;
      numProcess=s->numProc;
      bestCF=100;

      pop= new individual* [numPartMax];

      // Initialize elitism array
      elite = new individual*[s->numMaxElitism];
      for (int i=0; i<s->numMaxElitism; i++) elite[i] = new individual;

      pop_Best = new int[numProcess];

      // Initialize the random number generator
      srand(/*1*//*getpid()*/time(NULL));

      // It attaches to the specification
      spec=s;
            
      // Create random partitionings for the entire population
      for(i=0; i< numPartMax; i++)
      {
            pop[i] = new individual;
            pop[i]->initialize( spec );
      }
}
            

//increases the population by means of one-point crossover operations
void population::crossover( float repRate )
{
	  // Number of individuals of future population
      int futPop;
      // Individuals selected for the reproduction
      int boy, girl;
      // Point selected for the one-point crossover operation
      int position;
      int i;

      srand(time(NULL));

      // Birth control policy
      // If the number of partitionings of the population > max number of partitionings
      if (numPart >= numPartMax)  return;

      futPop = (int) ( numPart*(1.0+repRate) );

      // Birth control policy
      if (futPop > numPartMax-1 ) futPop = numPartMax-1;
      
      // until the new population reaches the value of the future population
      for( ;numPart<futPop; numPart+=2)
      {
            // Selection of two individuals
            boy  = rand() % numPart;
            girl = rand() % numPart;

            // ...and a position
            position = rand() % spec->numProc;

            // Reproduction. First part of the first new child
            for(i=0; i<position; i++)
            {
                  pop[numPart]->istance[i]    = pop[boy]->istance[i];
                  pop[numPart]->Ptype[i] 	  = pop[boy]->Ptype[i];
            }
            // Reproduction. Second part of the first new child
            for(; i<spec->numProc; i++)
            {
                  pop[numPart]->istance[i]    = pop[girl]->istance[i];
                  pop[numPart]->Ptype[i] 	  = pop[girl]->Ptype[i];
            }

            // Reproduction. First part of the second new child
            for(i=0; i<position; i++)
            {
                  pop[numPart+1]->istance[i]    = pop[girl]->istance[i];
                  pop[numPart+1]->Ptype[i] 	    = pop[girl]->Ptype[i];
            }
            // Reproduction. Second part of the second new child
            for(; i<spec->numProc; i++)
            {
                  pop[numPart+1]->istance[i]    = pop[boy]->istance[i];
                  pop[numPart+1]->Ptype[i] 	    = pop[boy]->Ptype[i];
            }

            // marks the new children as newborns
            pop[numPart]->newborn = true;
            pop[numPart+1]->newborn = true;
      }
}

// Select number of partitionings based on a radioactivity coefficient and carry out
// mutations on these partitionings
void population::mutation( float radRate )
{
	  //Individual subject to mutation
      int luckless;
      //Process subject to mutation
      int procSel;
      //Basic Block selected for the mutation
      int mutationI;

      srand(time(NULL));

      // Number of mutation
      int numMut = (int) ( numPart*radRate );
      
      // Random selection of individual, process and Basic Block mutation
      for(int i=0; i<numMut; i++)
      {
            luckless   = rand() % numPart;
            procSel   = rand() % spec->numProc;

            mutationI = rand()%spec->instanceBB;

            //Mutation
            pop[luckless]->istance[procSel]    = mutationI;

            if(spec->architecture[mutationI].procUnit->processorType == "SPP" ){
            	pop[luckless]->Ptype[procSel] = 2;  // SPP
            }else if (spec->architecture[mutationI].procUnit->processorType == "DSP" ){
            	pop[luckless]->Ptype[procSel] = 1;  // DSP
            }else if (spec->architecture[mutationI].procUnit->processorType == "GPP" ){
            	pop[luckless]->Ptype[procSel] = 0; // GPP
            }

            pop[luckless]->newborn = true;
      }
}

// Evaluate the total cost function of the newborns
void population::evaluation( void )
{
	int i;

	//Serial Version
	for(i=0; i<numPart; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateCF( bestCF );
			pop[i]->newborn = false;
		}
	}
}


// Evaluate the total cost function of the newborns. Parallel versions
void population::parallel_evaluation( void )
{
      int i;
      int maxThreads = omp_get_max_threads();
      //cout << "Max number threads: " << maxThreads << endl;
/*
	  // Parallel evaluation functions case
      for(i=0; i<numPart; i++)
      {
            if ( pop[i]->newborn == true )
            {
                  pop[i]->parallel_evaluateCF( bestCF );
                  pop[i]->newborn = false;
            }
      }
*/

// Parallel evaluation omp parralel for case
// The for index is private by default
#pragma omp parallel for  schedule(guided,5000) num_threads(maxThreads)
	for(i=0; i<numPart; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateCF( bestCF );
			pop[i]->newborn = false;
		}
	}

/*
// Parallel evaluation omp parralel for case
// The for index is private by default, individual private, nowait clause, schedule guided
#pragma omp parallel num_threads(maxThreads)
      {
    	  individual *ind;
#pragma omp for private(ind) nowait schedule(guided,20000)
    	  for(i=0; i<numPart; i++)
    	  	{
    		  ind = pop[i];
    	  		if ( ind->newborn == true )
    	  		{
    	  			ind->evaluateCF( bestCF );
    	  			ind->newborn = false;
    	  		}
    	  	}
      }
*/
/*
// Parallel evaluation splitting the population; omp parallel sections case
#pragma omp parallel sections private(i) num_threads(4)
{
 #pragma omp section
 {
	for(i=0; i<numPart/4; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateCF( bestCF );
			pop[i]->newborn = false;
		}
	}
 }
 #pragma omp section
 {
	for(i=numPart/4; i<numPart/2; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateCF( bestCF );
			pop[i]->newborn = false;
		}
	}
 }
#pragma omp section
 {
	for(i=numPart/2; i<3*numPart/4; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateCF( bestCF );
			pop[i]->newborn = false;
		}
	}
 }
#pragma omp section
 {
	for(i=3*numPart/4; i<numPart; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateCF( bestCF );
			pop[i]->newborn = false;
		}
	}
 }
}
*/
/*
// Parallel version with single obj.function evaluation in parallel and population splitting
for (i=0; i < numPart; i++)
{
	if (pop[i]->newborn == true) pop[i]->CF = 0;
}

#pragma omp parallel sections private(i) num_threads(2)
{
 #pragma omp section
 {
	for(i=0; i<numPart/2; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateL();
			pop[i]->evaluateC();
			pop[i]->evaluateSize();
			pop[i]->CF+=pop[i]->wC*pop[i]->C;
			pop[i]->CF+=pop[i]->wL*pop[i]->L;
			pop[i]->CF+=pop[i]->wKB*pop[i]->KB;
			pop[i]->CF+=pop[i]->wGeq*pop[i]->Geq;
		}
	}
 }
 #pragma omp section
 {
	for(i=numPart/2; i<numPart; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateTDA();
			pop[i]->evaluateNTCC();
			pop[i]->evaluateEP();
			pop[i]->CF+=pop[i]->wTDA*pop[i]->TDA;
			pop[i]->CF+=pop[i]->wNTCC*pop[i]->NTCC;
			pop[i]->CF+=pop[i]->wEP*pop[i]->EP;
		}
	}
 }
}
#pragma omp parallel sections private(i) num_threads(2)
{
#pragma omp section
	{
		for(i=0; i<numPart/2; i++)
		{
			if ( pop[i]->newborn == true )
			{
				pop[i]->evaluateTDA();
				pop[i]->evaluateNTCC();
				pop[i]->evaluateEP();
				pop[i]->CF+=pop[i]->wTDA*pop[i]->TDA;
				pop[i]->CF+=pop[i]->wNTCC*pop[i]->NTCC;
				pop[i]->CF+=pop[i]->wEP*pop[i]->EP;
				pop[i]->CF+=pop[i]->wFeasibility*pop[i]->feasibility;
				pop[i]->newborn = false;
			}
		}
	}
#pragma omp section
 {
	for(i=numPart/2; i<numPart; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateL();
			pop[i]->evaluateC();
			pop[i]->evaluateSize();
			pop[i]->CF+=pop[i]->wC*pop[i]->C;
			pop[i]->CF+=pop[i]->wL*pop[i]->L;
			pop[i]->CF+=pop[i]->wKB*pop[i]->KB;
			pop[i]->CF+=pop[i]->wGeq*pop[i]->Geq;
			pop[i]->CF+=pop[i]->wFeasibility*pop[i]->feasibility;
			pop[i]->newborn = false;
		}
	}
 }
}
*/
}


// Elimination of random population partitionings
void population::purge( float deathRate )
{
	//Purge's victim
      int victim;
    //Value of discrimination for the purge
      float x;
      
      srand(time(NULL));

      // Select the number of victims of the purge by means of death rate
      int numVictims = (int) ( numPart*deathRate );
           
      // Purge
      for( ; numVictims>0; numVictims--)
      {
    	  //Random victim selection
            victim = rand() % numPart;
            
            // Random value of discrimination
            x= ( (float) rand())/RAND_MAX + spec->feas;
            
            // It also happens to the best ...
            if ( pop[victim]->CF > x )
            {
                  // ... elimination of the victim
                  numPart--;
                  pop[victim]=pop[numPart];
            }
      }
}

// Return the partitioning with min Affinity value
individual* population::minTDAPart()
{
	int i;
	// Pointer to the partitioning with min TDA
	individual *minPart = new individual;

	// Min TDA value found in the population
	float minTDA = 99;
	// Used if there are partitionings with same TDA value: control the min CF
	float minCF = 999;

	for (i = 0; i < numPart; i++)
	{
		if (pop[i]->TDA < minTDA)
		{
			minPart = pop[i];
			minTDA = pop[i]->TDA;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min TDA value, check the min CF
		else if (pop[i]->TDA == minTDA)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minTDA = pop[i]->TDA;
				minCF = pop[i]->CF;
			}
		}
	}

	return minPart;
}

// Return the partitioning with min Communication value
individual* population::minNTCCPart()
{
	int i;
	// Pointer to the partitioning with min Communication
	individual *minPart = new individual;
	// Min NTCC value found in the population
	float minNTCC = 99;
	// Used if there are partitionings with same Communicarion value: control the min CF
	float minCF = 999;

	for (i = 0; i < numPart; i++)
	{
		if (pop[i]->NTCC < minNTCC)
		{
			minPart = pop[i];
			minNTCC = pop[i]->NTCC;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min NTCC value, check the min CF
		else if (pop[i]->NTCC == minNTCC)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minNTCC = pop[i]->NTCC;
				minCF = pop[i]->CF;
			}
		}
	}

	return minPart;
}

// Return the partitioning with min Parallelism value
individual* population::minEPPart()
{
	int i;
	// Pointer to the partitioning with min Parallelism
	individual *minPart = new individual;
	// Min EP value found in the population
	float minEP = 99;
	// Used if there are partitionings with same EP value: control the min CF
	float minCF = 999;

	for (i = 0; i < numPart; i++)
	{
		if (pop[i]->EP < minEP)
		{
			minPart = pop[i];
			minEP = pop[i]->EP;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min EP value, check the min CF
		else if (pop[i]->EP == minEP)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minEP = pop[i]->EP;
				minCF = pop[i]->CF;
			}
		}
	}

	return minPart;
}

// Return the partitioning with min Load value
individual* population::minLPart()
{
	int i;
	// Pointer to the partitioning with min Load
	individual *minPart = new individual;
	// Min Load value found in the population
	float minL = 99;
	// Used if there are partitionings with same Load value: control the min CF
	float minCF = 999;

	for (i = 0; i < numPart; i++)
	{
		if (pop[i]->L < minL)
		{
			minPart = pop[i];
			minL = pop[i]->L;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min Load value, check the min CF
		else if (pop[i]->L == minL)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minL = pop[i]->L;
				minCF = pop[i]->CF;
			}
		}
	}

	return minPart;
}

// Return the partitioning with min Cost value
individual* population::minCPart()
{
	int i;
	// Pointer to the partitioning with min Cost
	individual *minPart = new individual;
	// Min Cost value found in the population
	float minC = 99;
	// Used if there are partitionings with same Cost value: control the min CF
	float minCF = 999;

	for (i = 0; i < numPart; i++)
	{
		if (pop[i]->C < minC)
		{
			minPart = pop[i];
			minC = pop[i]->C;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min Cost value, check the min CF
		else if (pop[i]->C == minC)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minC = pop[i]->C;
				minCF = pop[i]->CF;
			}
		}
	}

	return minPart;
}

// Return the partitioning with min SW Size value
individual* population::minSWSizePart()
{
	int i;
	// Pointer to the partitioning with min Cost
	individual *minPart = new individual;
	// Min Cost value found in the population
	float minSize = 99;
	// Used if there are partitionings with same SW Size value: control the min CF
	float minCF = 999;

	for (i = 0; i < numPart; i++)
	{
		if (pop[i]->KB < minSize)
		{
			minPart = pop[i];
			minSize = pop[i]->KB;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min SW Size value, check the min CF
		else if (pop[i]->KB == minSize)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minSize = pop[i]->KB;
				minCF = pop[i]->CF;
			}
		}
	}

	return minPart;
}

// Return the partitioning with min HW Size value
individual* population::minHWSizePart()
{
	int i;
	// Pointer to the partitioning with min Cost
	individual *minPart = new individual;
	// Min Cost value found in the population
	float minSize = 99;
	// Used if there are partitionings with same HW Size value: control the min CF
	float minCF = 999;

	for (i = 0; i < numPart; i++)
	{
		if (pop[i]->Geq < minSize)
		{
			minPart = pop[i];
			minSize = pop[i]->Geq;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min HW Size value, check the min CF
		else if (pop[i]->Geq == minSize)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minSize = pop[i]->Geq;
				minCF = pop[i]->CF;
			}
		}
	}

	return minPart;
}

// Return the partitioning with min Cost Function value
individual* population::minCFPart()
{
	int i;
	// Pointer to the partitioning with min Cost Function
	individual *minPart = new individual;
	// Min Cost Function value found in the population
	float minCF = 999;

	for (i = 0; i < numPart; i++)
	{
		if (pop[i]->CF < minCF)
		{
			minPart = pop[i];
			minCF = pop[i]->CF;
		}
	}

	return minPart;
}

//Update the elite array
void population::updateElite()
{
	int i = 0;

	if (spec->aff != 0)
	{
		elite[i] = minTDAPart();
		i++;
	}
	if (spec->comm != 0)
	{
		elite[i] = minNTCCPart();;
		i++;
	}
	if (spec->par_w != 0)
	{
		elite[i] = minEPPart();
		i++;
	}
	if (spec->load != 0)
	{
		elite[i] = minLPart();
		i++;
	}
	if (spec->cost != 0)
	{
		elite[i] = minCPart();
		i++;
	}
	if (spec->size_SW != 0)
	{
		elite[i] = minSWSizePart();
		i++;
	}
	if (spec->size_HW != 0)
	{
		elite[i] = minHWSizePart();
		i++;
	}

	elite[i] = minCFPart();
}

// Elitism with Extreme Values operation
void population::elitismEV()
{
	// Check if the partitioning is equal to someone in the population
	int isEqual;
	bool isPresent = false;

	// Replacement Partitioning
	int sub;

	// Check if the elite partitionings are in the population; if not re-add the elite
	// partitioning in the population
	for (int i = 0; i < spec->numMaxElitism; i++)
	{
		isPresent = false;

		for (int j = 0; j < numPart; j++)
		{
			isEqual = 0;

			for (int p = 0; p < spec->numProc; p++)
			{
				if (elite[i]->istance[p] == pop[j]->istance[p])	isEqual++;
			}
			// This means that the elite partitioning is in the pop
			// All the pair process-processor are the same
			if (isEqual == 8)
			{
				isPresent = true;
				break;
			}
		}
		// This means that the elite partitioning isn't in the pop; add the elite
		// partitioning to the population
		if (isPresent == false)
		{
			// Check if the population has reached the max
			if (numPart+1 > numPartMax-1)
			{
				// Substitute a random partitioning
				sub  = rand() % numPart;
				*(&pop[sub]) = *(&elite[i]);
			}
			else
			{
				*(&pop[numPart+1]) = *(&elite[i]);
				numPart++;
			}

		}
	}
}

// Equalizes weights at each iteration for the CF computation
// At the moment only load and cost weights (it works only if load and cost weights are setted)
void population::weightsEqualization()
{
	float sumL=0, sumC=0, aveL, aveC;
	float temp_wL, temp_wC;

	for (int i = 0; i < numPart; i++)
	{
		sumL+= pop[i]->L;
		sumC+= pop[i]->C;
	}

	aveL = sumL/numPart;
	aveC = sumC/numPart;

	// Compute the equalization system
	// aveL*wL = aveC*wC and wL+wC = 1
	temp_wC = aveL/(aveL+aveC);
	temp_wL = 1 - temp_wC;

	// Update the weights in the specification
	spec->cost = temp_wC;
	spec->load = temp_wL;
}

// Save and print the best partitioning of the population and some statistics
void  population::printMemStat(unsigned long gen, ofstream &myFile, double execTime)
{
	double sum=0, ave=0, sd = 0;
	//For statistics about only feasible solutions
	double sumFeasible=0, aveFeasible=0, sdFeasible=0;
	double CFcopy;
	bool stat=false;
	feasibleSol = 0;
	string text_value;

	for(int i=0; i<numPart; i++)
	{
		if(pop[i]->CF >= 0){
			CFcopy=pop[i]->CF;
			sum+=CFcopy;

			// If the solution is feasible (CF < 1)
			if(pop[i]->CF < 1.0){
				feasibleSol++;
				sumFeasible+= CFcopy;
			}

			if (CFcopy < bestCF)
			{
				stat=true;
				bestCF = pop[i]->CF;

				cout << endl << "TDA: " << pop[i]->TDA << endl;
				cout << "NTCC: " << pop[i]->NTCC << endl;
				cout << "EP: " << pop[i]->EP << endl;
				cout << "L: " << pop[i]->L << endl;
				cout << "C: " << pop[i]->C << endl;
				cout << "Total monetary cost: " << pop[i]->INDIVIDUAL_COST << endl;
				cout << "KB: " << pop[i]->KB << endl;
				cout << "Geq: " << pop[i]->Geq << endl;
				cout << "Crit: " << pop[i]->Crit << endl;
				cout << "Total Cost Function: " << pop[i]->CF << endl;

				cout << "Process ID:  ";
				for(int j=0; j< spec->numProc; j++)
					cout << j+2 << " ";
				cout << endl;

				cout << "Istances:     ";
				for(int j=0; j< spec->numProc; j++){
					pop_Best[j] = pop[i]->istance[j];
					cout << pop[i]->istance[j] << " ";
				}
				cout << endl;

			}
		}
		stat=false;
	}

	//Print informations about weights
	cout << "###Weights informations###"<< endl;
	cout << "Affinity weight: " << spec->aff << endl;
	cout << "Communication weight: " << spec->comm << endl;
	cout << "Parallelism weight: " << spec->par_w << endl;
	cout << "Cost weight: " << spec->cost << endl;
	cout << "Load weight: " << spec->load << endl;
	cout << "SW Size weight: " << spec->size_SW << endl;
	cout << "HW Size weight: " << spec->size_HW << endl << endl;

	ave=sum/numPart;
	aveFeasible = sumFeasible/feasibleSol;
	sumFeasible = 0;
	sum=0;
	for(int i=0; i<numPart; i++){
		if(pop[i]->CF >= 0){
			sum+=((pop[i]->CF-ave)*(pop[i]->CF-ave));
		}
	}
	// Compute standard deviation
	sd = sqrt(sum/numPart);

	for(int i=0; i<numPart; i++){
			if(pop[i]->CF >= 0 && pop[i]->CF < 1){
				sumFeasible+=((pop[i]->CF-aveFeasible)*(pop[i]->CF-aveFeasible));
			}
		}
	// Compute standard deviation for feasible partitionings
	sdFeasible = sqrt(sumFeasible/feasibleSol);

	cout << endl << "Population CF average: " << ave << endl;
	cout << " Population Standard deviation: " << sd << endl;

	cout << endl << "Population feasible CF average: " << aveFeasible << endl;
	cout << " Population feasible Standard deviation: " << sdFeasible << endl << endl;

	// Save statistics into the csv file
	// Generation number
	text_value = to_string(gen) +",";
	myFile << text_value;

	// Population CF average
	text_value = to_string(ave) +",";
	myFile << text_value;

	// Population Standard deviation
	text_value = to_string(sd) +",";
	myFile << text_value;

	// Population feasible CF average
	text_value = to_string(aveFeasible) +",";
	myFile << text_value;

	// Population feasible Standard deviation
	text_value = to_string(sdFeasible) +",";
	myFile << text_value;

	// Execution time
	text_value = to_string(execTime) +",";
	myFile << text_value;

	text_value = ",\n";
	myFile << text_value;

}

// Save the informations about the partitionings of the population into csv files during
// the evolution of genetic algorithm every j generations
void  population::memPop(int it, int j)
{
	if (it % j == 0)
	{
		char  buf[BUFSIZ];
		sprintf(buf, "%s%05d%s", "./PAM1_Parallel/PARETO/populations_without_elitism/pareto_iteration_", it, ".csv");

		float size_tot = 0;
		string text_value;

		ofstream myfile;

		myfile.open(buf,std::ofstream::out | std::ofstream::trunc);

		myfile << "TDA,NTCC,EP,L,C,CostoTotale,Size,Crit,CF,Processes,Processor,\n";

		for(int i=0; i<numPartMax; i++)
		{
			if(pop[i]->CF >= 0){

				if (pop[i]->Crit < TR_CRIT)
				{
					feasibleSol++;

					text_value = to_string(pop[i]->TDA) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->NTCC) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->EP) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->L) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->C) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->INDIVIDUAL_COST) +",";
					myfile << text_value;

					size_tot = pop[i]->KB + pop[i]->Geq;
					text_value = to_string(size_tot) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->Crit) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->CF) +",";
					myfile << text_value;

					for(int j=0; j< spec->numProc; j++){
						text_value = to_string(j+2);
						myfile << text_value;
					}

					text_value = ",";
					myfile << text_value;

					for(int j=0; j< spec->numProc; j++){
						text_value = to_string(pop[i]->istance[j]);
						myfile << text_value;
					}

					text_value = ",\n";
					myfile << text_value;
				}
			}
		}
		myfile.close();
	}
}

// Save the informations about the partitionings of the population into csv files during
// the evolution of genetic algorithm every j generations
// The information about objective function are weighted.
// At the moment only cost-load objective functions are considered
void  population::memWeightedPop(int it, int j)
{
	if (it % j == 0)
	{
		char  buf[BUFSIZ];
		sprintf(buf, "%s%05d%s", "./PAM1_Parallel/PARETO/populations_elitism_with_rep_eq/pareto_iteration_", it, ".csv");

		float weightedSize_tot = 0;
		string text_value;
		float weightedLoad, weightedCost, weightedTda, weightedNtcc, weightedEp;

		ofstream myfile;

		myfile.open(buf,std::ofstream::out | std::ofstream::trunc);

		// At the moment save only additional informations about load and cost weighted
		myfile << "TDA,NTCC,EP,L,C,CostoTotale,Size,Crit,CF,Processes,Processor,\n";

		for(int i=0; i<numPartMax; i++)
		{
			if(pop[i]->CF >= 0){

				if (pop[i]->Crit < TR_CRIT)
				{
					feasibleSol++;

					weightedTda = spec->aff * pop[i]->TDA;
					text_value = to_string(weightedTda) +",";
					myfile << text_value;

					weightedNtcc = spec->comm * pop[i]->NTCC;
					text_value = to_string(weightedNtcc) +",";
					myfile << text_value;

					weightedEp = spec->par_w * pop[i]->EP;
					text_value = to_string(weightedEp) +",";
					myfile << text_value;

					weightedLoad = spec->load * pop[i]->L;
					text_value = to_string(weightedLoad) +",";
					myfile << text_value;

					weightedCost = spec->cost * pop[i]->C;
					text_value = to_string(weightedCost) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->INDIVIDUAL_COST) +",";
					myfile << text_value;

					weightedSize_tot = spec->size_SW*pop[i]->KB + spec->size_HW*pop[i]->Geq;
					text_value = to_string(weightedSize_tot) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->Crit) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->CF) +",";
					myfile << text_value;

					for(int j=0; j< spec->numProc; j++){
						text_value = to_string(j+2);
						myfile << text_value;
					}

					text_value = ",";
					myfile << text_value;

					for(int j=0; j< spec->numProc; j++){
						text_value = to_string(pop[i]->istance[j]);
						myfile << text_value;
					}

					text_value = ",\n";
					myfile << text_value;
				}
			}
		}
		myfile.close();
	}
}

// Delete the last xml mapping file containing the best partitioning of the
// population
void population::deleteXml()
{

	int i;
	pugi::xml_document myDoc;
	pugi::xml_parse_result myResult = myDoc.load_file("./XML/mapping.xml");
	cout << "XML Delete result: " << myResult.description() << endl;

	//method 2: use object/node structure
	pugi::xml_node instancesMAP = myDoc.child("mapping");

	xml_node allocation = instancesMAP.child("allocation");

	for(i = 0; i < numProcess + 2; i++){
		xml_node processorId = allocation.child("processId");
		allocation.remove_child(processorId);
		allocation = allocation.next_sibling();
	}

	myDoc.save_file("./XML/mapping.xml");
	myDoc.reset();

}

// Create the xml mapping file containing the best partitioning of the
// population
void population::mappingXml(specification *s)
{
	pugi::xml_document doc;

	pugi::xml_parse_result myResult = doc.load_file("./XML/mapping.xml");
	//pugi::xml_parse_result myResult = doc.load_file(result2.c_str());
	cout << "Mapping result: " << myResult.description() << endl;

	xml_node instancesMAP = doc.child("mapping");

	xml_node allocation = instancesMAP.child("allocation");

	int i = 0;
	for(i = 0; i < numProcess + 2; i++){

		xml_node map = allocation.append_child("processId");

		map.append_attribute("PSid").set_value(i);
		if(i > 1){
			map.append_attribute("PRname").set_value(s->architecture[pop_Best[i-2]].name.c_str());
			map.append_attribute("value").set_value(pop_Best[i-2]);
		}else{
			map.append_attribute("PRname").set_value("NA");
			map.append_attribute("value").set_value("NA");
		}

		allocation = allocation.next_sibling();
	}

	doc.save_file("./XML/mapping.xml");
	doc.reset();
}
