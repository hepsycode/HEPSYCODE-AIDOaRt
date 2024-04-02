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
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "population.h"
#include "pugixml.hpp"

#define TR_CRIT 2

using namespace std;
using namespace pugi;

bool exe_num;

// Destructor
population::~population()
{
      delete[] pop;
      delete[] pop_Best;
}

// Constructor
// Initializes the attributes of the population and creates the first random partitionings
population::population(specification *s) // @suppress("Class members should be properly initialized")
{
	unsigned int i;

	this->numFeasibleSol = 0;

	numInd=s->numIndiv;
	numIndMax=s->numMaxIndiv;
	numProcessesess=s->numProcesses;
	bestCF=100;

	pop= new individual* [numIndMax];

	// Initialize elitism array
	elite = new individual*[s->numMaxElitism];
	for (int i=0; i<s->numMaxElitism; i++) elite[i] = new individual;

	pop_Best = new int[numProcessesess];

	// Initialize the random number generator
	srand((unsigned int)time(NULL));

	// It attaches to the specification
	spec=s;

	// Create random partitionings for the entire population
	for(i=0; i< numIndMax; i++)
	{
		if(i < spec->numBB){
			pop[i] = new individual;
			pop[i]->initializeDefault( spec , i);
		}else{
			pop[i] = new individual;
			pop[i]->initialize( spec );
		}
	}

}


//increases the population by means of one-point crossover operations
void population::crossover( double repRate )
{
	  // Number of individuals of future population
      unsigned int futPop;
      // Individuals selected for the reproduction
      unsigned int boy, girl;
      // Point selected for the one-point crossover operation
      unsigned int position;
      unsigned int i;

      //srand(time(NULL));

      // Birth control policy
      // If the number of partitionings of the population > max number of partitionings
      if (numInd >= numIndMax)  return;

      futPop = (int) ( numInd*(1.0+repRate) );

      // Birth control policy
      if (futPop > numIndMax-1 ) futPop = numIndMax-1;

      // until the new population reaches the value of the future population
      for( ;numInd<futPop; numInd+=2)
      {
            // Selection of two individuals
            boy  = rand() % numInd;
            girl = rand() % numInd; // Function Selection

            // ...and a position
            position = rand() % spec->numProcesses;

            // Reproduction. First part of the first new child
            for(i=0; i<position; i++)
            {
                  pop[numInd]->mapping[i]    = pop[boy]->mapping[i];
                  pop[numInd]->Ptype[i] 	  = pop[boy]->Ptype[i];
            }
            // Reproduction. Second part of the first new child
            for(; i<spec->numProcesses; i++)
            {
                  pop[numInd]->mapping[i]    = pop[girl]->mapping[i];
                  pop[numInd]->Ptype[i] 	  = pop[girl]->Ptype[i];
            }

            // Reproduction. First part of the second new child
            for(i=0; i<position; i++)
            {
                  pop[numInd+1]->mapping[i]    = pop[girl]->mapping[i];
                  pop[numInd+1]->Ptype[i] 	    = pop[girl]->Ptype[i];
            }
            // Reproduction. Second part of the second new child
            for(; i<spec->numProcesses; i++)
            {
                  pop[numInd+1]->mapping[i]    = pop[boy]->mapping[i];
                  pop[numInd+1]->Ptype[i] 	    = pop[boy]->Ptype[i];
            }

            // marks the new children as newborns
            pop[numInd]->newborn = true;
            pop[numInd+1]->newborn = true;
      }
}

// Select number of partitionings based on a radioactivity coefficient and carry out
// mutations on these partitionings
void population::mutation( double radRate )
{
	  //Individual subject to mutation
      int luckless;
      //Process subject to mutation
      int procSel;
      //Basic Block selected for the mutation
      int mutationI;

      //srand(time(NULL));

      // Number of mutation
      int numMut = (int) ( numInd*radRate );

      // Random selection of individual, process and Basic Block mutation
      for(int i=0; i<numMut; i++)
      {
            luckless   = rand() % numInd;
            procSel   = rand() % spec->numProcesses;

            mutationI = rand()%spec->numBBinstances;

            //Mutation
            pop[luckless]->mapping[procSel]    = mutationI;

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

// evale the total cost function of the newborns
void population::evaluation()
{
	unsigned int i;

	//Serial Version
	for(i=0; i<numInd; i++)
	{
		if ( pop[i]->newborn == true )
		{
			pop[i]->evaluateCF( bestCF );
			pop[i]->newborn = false;
		}
	}
}

// Elimination of random population partitionings (CHECK!!!)
void population::purge( double deathRate )
{
	//Purge's victim
      int victim;
    //Value of discrimination for the purge
      double x;

      // Select the number of victims of the purge by means of death rate
      int numVictims = (int) ( numInd*deathRate );		 
      // Purge (CHECK!!!)
      //for( ; numVictims>0; numVictims--)
      for( ; numVictims>0; )
      {
    	    //Random victim selection
            victim = rand() % numInd;
			
            // Random value of discrimination
            //x= ( (float) rand())/RAND_MAX + spec->feas_w;
            x= ( (float) rand())/RAND_MAX;

            // It also happens to the best ...
            if ((pop[victim]->CF > x ))
			{
                // ... elimination of the victim
				numVictims--;
				numInd--;
                pop[victim]=pop[numInd];
            }
      }
}

/*********************************/
/************ ELITISM ************/
/*********************************/

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

	for (i = 0; i < numInd; i++)
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

	for (i = 0; i < numInd; i++)
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

	for (i = 0; i < numInd; i++)
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

	for (i = 0; i < numInd; i++)
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

	for (i = 0; i < numInd; i++)
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

	for (i = 0; i < numInd; i++)
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

	for (i = 0; i < numInd; i++)
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

// Return the partitioning with min HW Size value
individual* population::minEnergyPart()
{
	int i;
	// Pointer to the partitioning with min Cost
	individual *minPart = new individual;
	// Min Cost value found in the population
	float minSize = 99;
	// Used if there are partitionings with same HW Size value: control the min CF
	float minCF = 999;

	for (i = 0; i < numInd; i++)
	{
		if (pop[i]->Ener < minSize)
		{
			minPart = pop[i];
			minSize = pop[i]->Ener;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min HW Size value, check the min CF
		else if (pop[i]->Ener == minSize)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minSize = pop[i]->Ener;
				minCF = pop[i]->CF;
			}
		}
	}

	return minPart;
}

// Return the partitioning with min HW Size value
individual* population::minEnergyTCPart()
{
	int i;
	// Pointer to the partitioning with min Cost
	individual *minPart = new individual;
	// Min Cost value found in the population
	float minSize = 99;
	// Used if there are partitionings with same HW Size value: control the min CF
	float minCF = 999;

	for (i = 0; i < numInd; i++)
	{
		if (pop[i]->EnerETC < minSize)
		{
			minPart = pop[i];
			minSize = pop[i]->EnerETC;
			minCF = pop[i]->CF;
		}
		// if the partitionig has the same min HW Size value, check the min CF
		else if (pop[i]->EnerETC == minSize)
		{
			if (pop[i]->CF < minCF)
			{
				minPart = pop[i];
				minSize = pop[i]->EnerETC;
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
	double CFcopy;
	double bestCF_Elite=100;

	for (i = 0; i < numInd; i++)
	{
		if(pop[i]->CF >= 0){
			CFcopy=pop[i]->CF;
			if (CFcopy < bestCF_Elite)
			{
				minPart = pop[i];
				bestCF_Elite = pop[i]->CF;
			}
		}
	}

	return minPart;
}

//Update the elite array
void population::updateElite()
{
	int i = 0;

	if (spec->aff_w != 0)
	{
		elite[i] = minTDAPart();
		cout << "Elite-" << i << " Value:" << elite[i]->TDA << endl;
		i++;
	}
	if (spec->comm_w != 0)
	{
		elite[i] = minNTCCPart();
		cout << "Elite-" << i << " Value:" << elite[i]->NTCC << endl;
		i++;
	}
	if (spec->par_w != 0)
	{
		elite[i] = minEPPart();
		cout << "Elite-" << i << " Value:" << elite[i]->EP << endl;
		i++;
	}
	if (spec->load_w != 0)
	{
		elite[i] = minLPart();
		cout << "Elite-" << i << " Value:" << elite[i]->L << endl;
		i++;
	}
	if (spec->cost_w != 0)
	{
		elite[i] = minCPart();
		cout << "Elite-" << i << " Value:" << elite[i]->C << endl;
		i++;
	}
	if (spec->size_SW_w != 0)
	{
		elite[i] = minSWSizePart();
		cout << "Elite-" << i << " Value:" << elite[i]->KB << endl;
		i++;
	}
	if (spec->size_HW_w != 0)
	{
		elite[i] = minHWSizePart();
		cout << "Elite-" << i << " Value:" << elite[i]->Geq << endl;
		i++;
	}
	if (spec->energy_w != 0)
	{
		elite[i] = minEnergyPart();
		cout << "Elite-" << i << " Value:" << elite[i]->Ener << endl;
		i++;
	}
	if (spec->energyTC_w != 0)
	{
		elite[i] = minEnergyTCPart();
		cout << "Elite-" << i << " Value:" << elite[i]->EnerETC << endl;
		i++;
	}

	elite[i] = minCFPart();
	cout << "Elite-" << i << " Value:" << elite[i]->CF << endl;
}

// Elitism with Extreme Values operation
void population::elitismEV()
{
	// Check if the partitioning is equal to someone in the population
	int isEqual;
	bool isPresent = false;

	// Replacement Partitioning
	unsigned int  sub;

	sub  = rand() % numInd-spec->numMaxElitism-1;

	// Check if the elite partitionings are in the population; if not re-add the elite
	// partitioning in the population
	for (int i = 0; i < spec->numMaxElitism; i++)
	{
		isPresent = false;

		/*for (int j = 0; j < numInd; j++)
		{
			isEqual = 0;

			for (int p = 0; p < spec->numProcesses; p++)
			{
				if (elite[i]->mapping[p] == pop[j]->mapping[p])	isEqual++;
			}
			// This means that the elite partitioning is in the pop
			// All the pair process-processor are the same
			if (isEqual == 8)
			{
				isPresent = true;
				break;
			}
		}*/

		// This means that the elite partitioning isn't in the pop; add the elite
		// partitioning to the population
		if (isPresent == false)
		{
			// Check if the population has reached the max
			if (numInd+1 > numIndMax-5)
			{
				// Substitute a random partitioning
				// sub  = rand() % numInd;
				*(&pop[sub+i]) = *(&elite[i]);
			}
			else
			{
				*(&pop[numInd+1]) = *(&elite[i]);
				numInd++;
			}

		}
	}
}

/***************** WEIGHT EQUALIZATION *****************/

// Equalizes weights at each iteration for the CF computation
// At the moment only load and cost weights (it works only if load and cost weights are setted)
void population::weightsEqualization()
{
	/********* A Genetic Algorithm Approach for an Equitable Treatment of Objective Functions in Multi-objective Optimization Problems ******/

	individual *bestInd;
	float aff_bestInd=0, comm_bestInd=0, par_bestInd=0, load_bestInd=0, cost_bestInd=0, energy_bestInd=0, energyTC_bestInd=0, tot_bestInd=0;
	unsigned int best_I=0;
	int type_weight=1; // 0: Weight in Equation, 1: No weight in equation

	bestInd = minCFPart();

	if (spec->aff_w != 0)
	{
		// aff_w_temp = (type_weight != 0) ? 1 : spec->aff_w_fixed;
		aff_bestInd = bestInd->TDA;
		best_I++;
		tot_bestInd += bestInd->TDA;
	}

	if (spec->comm_w != 0)
	{
		comm_bestInd = bestInd->NTCC;
		best_I++;
		tot_bestInd += bestInd->NTCC;
	}

	if (spec->par_w != 0)
	{
		par_bestInd = bestInd->EP;
		best_I++;
		tot_bestInd += bestInd->EP;
	}

	if (spec->load_w != 0)
	{
		load_bestInd = bestInd->L;
		best_I++;
		tot_bestInd += bestInd->L;
	}

	if (spec->cost_w != 0)
	{
		cost_bestInd = bestInd->C;
		best_I++;
		tot_bestInd += bestInd->C;
	}

	if (spec->energy_w != 0)
	{
		energy_bestInd = bestInd->Ener;
		best_I++;
		tot_bestInd += bestInd->Ener;
	}

	if (spec->energyTC_w != 0)
	{
		energyTC_bestInd = bestInd->EnerETC;
		best_I++;
		tot_bestInd += bestInd->EnerETC;
	}

	cout << "best_I: " << best_I << " tot_bestInd: " << tot_bestInd << endl;

	if(tot_bestInd != 0){
		if (spec->aff_w != 0)
		{
			spec->aff_w = (comm_bestInd + par_bestInd + load_bestInd + cost_bestInd + energy_bestInd + energyTC_bestInd)/( (best_I-1) * tot_bestInd);  // Update the weights in the specification
			cout << "aff_bestInd: " << aff_bestInd << " aff_w: " << spec->aff_w << endl;
		}

		if (spec->comm_w != 0)
		{
			spec->comm_w = (aff_bestInd + par_bestInd + load_bestInd + cost_bestInd + energy_bestInd + energyTC_bestInd)/( (best_I-1) * tot_bestInd);
			cout << "comm_bestInd: " << comm_bestInd << " comm_w: " << spec->comm_w << endl;
		}

		if (spec->par_w != 0)
		{
			spec->par_w = (aff_bestInd + comm_bestInd + load_bestInd + cost_bestInd + energy_bestInd + energyTC_bestInd)/( (best_I-1) * tot_bestInd);
			cout << "par_bestInd: " << par_bestInd << " par_w: " << spec->par_w << endl;
		}

		if (spec->load_w != 0)
		{
			spec->load_w = (aff_bestInd + comm_bestInd + par_bestInd + cost_bestInd + energy_bestInd + energyTC_bestInd)/( (best_I-1) * tot_bestInd);
			cout << "load_bestInd: " << load_bestInd << " load_w: " << spec->load_w << endl;
		}

		if (spec->cost_w != 0)
		{
			spec->cost_w = (aff_bestInd + comm_bestInd + par_bestInd + load_bestInd + energy_bestInd + energyTC_bestInd)/( (best_I-1) * tot_bestInd);
			cout << "cost_bestInd: " << cost_bestInd << " cost_w: " << spec->cost_w << endl;
		}

		if (spec->energy_w != 0)
		{
			spec->energy_w = (aff_bestInd + comm_bestInd + par_bestInd + load_bestInd + cost_bestInd + energyTC_bestInd)/( (best_I-1) * tot_bestInd);
			cout << "energy_bestInd: " << energy_bestInd << " energy_w: " << spec->energy_w << endl;
		}

		if (spec->energyTC_w != 0)
		{
			spec->energyTC_w = (aff_bestInd + comm_bestInd + par_bestInd + load_bestInd + cost_bestInd + energy_bestInd)/( (best_I-1) * tot_bestInd);
			cout << "energyTC_bestInd: " << energyTC_bestInd << " energyTC_w: " << spec->energyTC_w << endl;
		}
	}

	aff_bestInd=0, comm_bestInd=0, par_bestInd=0, load_bestInd=0, cost_bestInd=0, energy_bestInd=0, energyTC_bestInd=0, tot_bestInd=0, best_I=0;

	/***************** POMANTE Solution *********************/
	/*
	float sumL=0, sumC=0, sumTDA=0, sumEP=0, sumNTCC=0, sumE=0, sumETC=0, aveL, aveC, aveTDA, aveEP, aveNTCC, aveE, aveETC;
	float feasibleTOT=0;
	float temp_wL, temp_wC, temp_wTDA, temp_wEP, temp_wNTCC, temp_wE, temp_wETC;
	float minAve=999.0, maxAve=0.0;

	for (int i = 0; i < numInd; i++)
	{
		if(pop[i]->CF < 1.0){
			sumTDA+= pop[i]->TDA;
			sumNTCC+=pop[i]->NTCC;
			sumEP+= pop[i]->EP;
			sumL+= pop[i]->L;
			sumC+= pop[i]->C;
			// kb SIZE and eq SIZE
			sumE+= pop[i]->Ener;
			sumETC+= pop[i]->EnerETC;

			feasibleTOT++;
		}
	}

	// If the weight associated with a function is zero, execution time can be saved
	// Compute the equalization system [ aveL*wL = aveC*wC and wL+wC = 1]

	// Affinity
	if (spec->aff_w != 0)
	{
		aveTDA = sumTDA/feasibleTOT;
		if(aveTDA < minAve){
			minAve = aveTDA;
		}
		cout << "aveTDA: " << aveTDA << " minAve: " << minAve << " aff_w: " << spec->aff_w << endl;
	}

	// Communication
	if (spec->comm_w != 0)
	{
		aveNTCC = sumNTCC/feasibleTOT;
		if(aveNTCC < minAve){
			minAve = aveNTCC;
		}
		cout << "aveNTCC: " << aveNTCC << " minAve: " << minAve << " comm_w: " << spec->comm_w << endl;
	}

	// Parallelism
	if (spec->par_w != 0)
	{
		aveEP = sumEP/feasibleTOT;
		if(aveEP < minAve){
			minAve = aveEP;
		}
		cout << "aveEP: " << aveEP << " minAve: " << minAve << " par_w: " << spec->par_w << endl;
	}

	// Load
	if (spec->load_w != 0)
	{
		aveL = sumL/feasibleTOT;
		if(aveL < minAve){
			minAve = aveL;
		}
		cout << "aveL: " << aveL << " minAve: " << minAve << " load_w: " << spec->load_w << endl;
	}

	// Monetary cost
	if (spec->cost_w != 0)
	{
		aveC = sumC/feasibleTOT;
		if(aveC < minAve){
			minAve = aveC;
		}
		cout << "aveC: " << aveC << " minAve: " << minAve << " cost_w: " << spec->cost_w << endl;
	}

	// Size
	//if (spec->size_SW_w != 0 && spec->size_HW_w != 0)
	//{
		// kb SIZE and eq SIZE
	//}

	// Energy Max
	if (spec->energy_w != 0)
	{
		aveE = sumE/feasibleTOT;
		if(aveE < minAve){
			minAve = aveE;
		}
		cout << "aveE: " << aveE << " minAve: " << minAve << " energy_w: " << spec->energy_w << endl;
	}
	// ETC
	if (spec->energyTC_w != 0)
	{
		aveETC = sumETC/feasibleTOT;
		if(aveETC < minAve){
			minAve = aveETC;
		}
		cout << "aveETC: " << aveETC << " minAve: " << minAve << " energyTC_w: " << spec->energyTC_w << endl;
	}

	if (spec->aff_w != 0)
	{
		temp_wTDA = minAve/aveTDA;
		spec->aff_w *= temp_wTDA;  // Update the weights in the specification
	}

	if (spec->comm_w != 0)
	{
		temp_wNTCC = minAve/aveNTCC;
		spec->comm_w *= temp_wNTCC;
	}

	if (spec->par_w != 0)
	{
		temp_wEP = minAve/aveEP;
		spec->par_w *= temp_wEP;
	}

	if (spec->load_w != 0)
	{
		temp_wL = minAve/aveL;
		spec->load_w *= temp_wL;
	}

	if (spec->cost_w != 0)
	{
		temp_wC = minAve/aveC;
		spec->cost_w *= temp_wC;
	}

	if (spec->energy_w != 0)
	{
		temp_wE = minAve/aveE;
		spec->energy_w *= temp_wE;
	}

	if (spec->energyTC_w != 0)
	{
		temp_wETC = minAve/aveETC;
		spec->energyTC_w *= temp_wETC;
	}
	*/

}

/*************** PRINT AND SAVE XML ********************/
// Save the informations about the partitionings of the population into csv files during
// the evolution of genetic algorithm every j generations
void  population::memPop(int it, int j)
{
	// int feasibleSol = 0;

	if (it % j == 0)
	{
		char  buf[BUFSIZ];
		if(spec->exe_num != 0){
			sprintf(buf, "%s%05d%s", "./PAM1/PAM1_Results/Exe01/pareto_iteration_", it, ".csv");
		}else{
			sprintf(buf, "%s%05d%s", "./PAM1/PAM1_Results/Exe02/pareto_iteration_", it, ".csv");
		}


		float size_tot = 0;
		string text_value;

		ofstream myfile;

		myfile.open(buf,std::ofstream::out | std::ofstream::trunc);

		myfile << "TDA,NTCC,EP,L,C,CostoTotale,Energy,EnergyTC,CF,";
		for(int j=0; j< spec->numProcesses; j++){
			text_value = to_string(j+2) +",";; // @suppress("Function cannot be resolved")
			myfile << text_value;
		}
		text_value = "\n";
		myfile << text_value;

		for(int i=0; i<numIndMax; i++)
		{
			if(pop[i]->CF >= 0 && pop[i]->CF < 1){

				// if (pop[i]->Crit < TR_CRIT)
				// {
					// feasibleSol++;

					text_value = to_string(pop[i]->TDA) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					text_value = to_string(pop[i]->NTCC) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					text_value = to_string(pop[i]->EP) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					text_value = to_string(pop[i]->L) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					text_value = to_string(pop[i]->C) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					text_value = to_string(pop[i]->INDIVIDUAL_COST) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					text_value = to_string(pop[i]->Ener) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					text_value = to_string(pop[i]->EnerETC) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					//size_tot = pop[i]->KB + pop[i]->Geq;
					//text_value = to_string(size_tot) +","; // @suppress("Function cannot be resolved")
					//myfile << text_value;

					// text_value = to_string(pop[i]->Crit) +",";
					// myfile << text_value;

					text_value = to_string(pop[i]->CF) +","; // @suppress("Function cannot be resolved")
					myfile << text_value;

					//for(int j=0; j< spec->numProcesses; j++){
					//	text_value = to_string(j+2); // @suppress("Function cannot be resolved")
					//	myfile << text_value;
					//}

					//text_value = ",";
					//myfile << text_value;

					for(int j=0; j< spec->numProcesses; j++){
						text_value = to_string(pop[i]->mapping[j])+","; // @suppress("Function cannot be resolved")
						myfile << text_value;
					}

					text_value = "\n";
					myfile << text_value;
				// }
			}
		}
		myfile.close();
	}
}

// Save and print the best partitioning of the population and some statistics
void  population::printMemStat(unsigned long gen, ofstream &myFile, double time_i)
{
	double sum=0, ave=0, sd = 0;
	double sumTDA=0, aveTDA=0, sdTDA=0;
	double sumNTCC=0, aveNTCC=0, sdNTCC=0;
	double sumEP=0, aveEP=0, sdEP=0;
	double sumCOST=0, aveCOST=0, sdCOST=0;
	double sumLOAD=0, aveLOAD=0, sdLOAD=0;
	double sumSizeSW=0, aveSizeSW=0, sdSizeSW=0;
	double sumEnergy=0, aveEnergy=0, sdEnergy=0;
	double sumEnergyTC=0, aveEnergyTC=0, sdEnergyTC=0;

	//For statistics about only feasible solutions
	double sumFeasible=0, aveFeasible=0, sdFeasible=0;
	double sumTDAFeasible=0, aveTDAFeasible=0, sdTDAFeasible=0;
	double sumNTCCFeasible=0, aveNTCCFeasible=0, sdNTCCFeasible=0;
	double sumEPFeasible=0, aveEPFeasible=0, sdEPFeasible=0;
	double sumCOSTFeasible=0, aveCOSTFeasible=0, sdCOSTFeasible=0;
	double sumLOADFeasible=0, aveLOADFeasible=0, sdLOADFeasible=0;
	double sumSizeSWFeasible=0, aveSizeSWFeasible=0, sdSizeSWFeasible=0;
	double sumEnergyFeasible, aveEnergyFeasible, sdEnergyFeasible;
	double sumEnergyTCFeasible, aveEnergyTCFeasible, sdEnergyTCFeasible;
	double CFcopy;
	numFeasibleSol = 0;
	string text_value;

	for(int i=0; i<numInd; i++)
	{
		if(pop[i]->CF >= 0){
			CFcopy=pop[i]->CF;
			sumTDA+=pop[i]->TDA;
			sumNTCC=pop[i]->NTCC;
			sumEP+=pop[i]->EP;
			sumCOST+=pop[i]->C;
			sumLOAD+=pop[i]->L;
			sumSizeSW+=pop[i]->KB;
			sumEnergy+=pop[i]->Ener;
			sumEnergyTC+=pop[i]->EnerETC;
			sum+=CFcopy;

			// If the solution is feasible (CF < 1)
			if(pop[i]->CF >= 0 && CFcopy < 1.0){
				numFeasibleSol++;
				sumFeasible+= CFcopy;
				sumTDAFeasible+=pop[i]->TDA;
				sumNTCCFeasible=pop[i]->NTCC;
				sumEPFeasible+=pop[i]->EP;
				sumCOSTFeasible+=pop[i]->C;
				sumLOADFeasible+=pop[i]->L;
				sumSizeSWFeasible+=pop[i]->KB;
				sumEnergyFeasible+=pop[i]->Ener;
				sumEnergyTCFeasible+=pop[i]->EnerETC;
			}

			if (CFcopy < bestCF)
			{
				bestCF = pop[i]->CF;

				cout << endl << "TDA: " << pop[i]->TDA << endl;
				cout << "NTCC: " << pop[i]->NTCC << endl;
				cout << "EP: " << pop[i]->EP << endl;
				cout << "L: " << pop[i]->L << endl;
				cout << "C: " << pop[i]->C << endl;
				cout << "Total monetary cost: " << pop[i]->INDIVIDUAL_COST << endl;
				cout << "KB: " << pop[i]->KB << endl;
				cout << "Geq: " << pop[i]->Geq << endl;
				cout << "Energy: " << pop[i]->Ener << endl;
				cout << "EnergyTC: " << pop[i]->EnerETC << endl;
				// cout << "Crit: " << pop[i]->Crit << endl;
				cout << "Total Cost Function: " << pop[i]->CF << endl;

				cout << "Process ID:  ";
				for(int j=0; j< spec->numProcesses; j++)
					cout << j+2 << " ";
				cout << endl;

				cout << "Istances:     ";
				for(int j=0; j< spec->numProcesses; j++){
					pop_Best[j] = pop[i]->mapping[j];
					cout << pop[i]->mapping[j] << " ";
				}
				cout << endl;

			}
		}
	}

	//Print informations about weights
	//cout << "###Weights informations###"<< endl;
	//cout << "Affinity weight: " << spec->aff << endl;
	//cout << "Communication weight: " << spec->comm << endl;
	//cout << "Parallelism weight: " << spec->par_w << endl;
	//cout << "Cost weight: " << spec->cost << endl;
	//cout << "Load weight: " << spec->load << endl;
	//cout << "SW Size weight: " << spec->size_SW << endl;
	//cout << "HW Size weight: " << spec->size_HW << endl << endl;

	ave=sum/numInd;
	aveFeasible = sumFeasible/numFeasibleSol;
	sumFeasible = 0;
	sum=0;

	aveTDA=sumTDA/numInd;
	aveTDAFeasible = sumTDAFeasible/numFeasibleSol;
	sumTDAFeasible = 0;
	sumTDA=0;

	aveNTCC=sumNTCC/numInd;
	aveNTCCFeasible = sumNTCCFeasible/numFeasibleSol;
	sumNTCCFeasible = 0;
	sumNTCC=0;

	aveEP=sumEP/numInd;
	aveEPFeasible = sumEPFeasible/numFeasibleSol;
	sumEPFeasible = 0;
	sumEP=0;

	aveCOST=sumCOST/numInd;
	aveCOSTFeasible = sumCOSTFeasible/numFeasibleSol;
	sumCOSTFeasible = 0;
	sumCOST=0;

	aveLOAD=sumLOAD/numInd;
	aveLOADFeasible = sumLOADFeasible/numFeasibleSol;
	sumLOADFeasible = 0;
	sumLOAD=0;

	aveSizeSW=sumSizeSW/numInd;
	aveSizeSWFeasible = sumSizeSWFeasible/numFeasibleSol;
	sumSizeSWFeasible = 0;
	sumSizeSW=0;

	aveEnergy=sumEnergy/numInd;
	aveEnergyFeasible = sumEnergyFeasible/numFeasibleSol;
	sumEnergyFeasible = 0;
	sumEnergy = 0;

	aveEnergyTC=sumEnergyTC/numInd;
	aveEnergyTCFeasible = sumEnergyTCFeasible/numFeasibleSol;
	sumEnergyTCFeasible = 0;
	sumEnergyTC = 0;

	for(int i=0; i<numInd; i++){
		if(pop[i]->CF >= 0){
			sum+=((pop[i]->CF-ave)*(pop[i]->CF-ave));
		}
	}
	// Compute standard deviation
	sd = sqrt(sum/numInd);

	for(int i=0; i<numInd; i++){
		if(pop[i]->CF >= 0 && pop[i]->CF < 1.0){
			sumFeasible+=((pop[i]->CF-aveFeasible)*(pop[i]->CF-aveFeasible));
		}
	}
	// Compute standard deviation for feasible partitionings
	sdFeasible = sqrt(sumFeasible/numFeasibleSol);

	cout << endl << "Population CF average: " << ave << endl;
	cout << " Population Standard deviation: " << sd << endl;

	cout << endl << "Population feasible CF average: " << aveFeasible << endl;
	cout << " Population feasible Standard deviation: " << sdFeasible << endl << endl;

	// Save statistics into the csv file
	// Generation number
	text_value = to_string(gen) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// Population CF average
	text_value = to_string(ave) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// Population Standard deviation
	text_value = to_string(sd) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// Population Size
	text_value = to_string(numInd) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// Population feasible CF average
	text_value = to_string(aveFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// Population feasible Standard deviation
	text_value = to_string(sdFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// Population Size (Only Feasible)
	text_value = to_string(numFeasibleSol) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// Execution time
	text_value = to_string(time_i) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// TDA (AVG tot and feasible)
	text_value = to_string(aveTDA) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(aveTDAFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(spec->aff_w) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// NTCC (AVG tot and feasible)
	text_value = to_string(aveNTCC) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(aveNTCCFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(spec->comm_w) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// EP (AVG tot and feasible)
	text_value = to_string(aveEP) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(aveEPFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(spec->par_w) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// COST (AVG tot and feasible)
	text_value = to_string(aveCOST) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(aveCOSTFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(spec->cost_w) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// LOAD (AVG tot and feasible)
	text_value = to_string(aveLOAD) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(aveLOADFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(spec->load_w) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// SIZE (AVG tot and feasible)
	text_value = to_string(aveSizeSW) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(aveSizeSWFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(spec->size_SW_w) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// Energy (AVG tot and feasible)

	text_value = to_string(aveEnergy) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(aveEnergyFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(spec->energy_w) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	// EnergyTC (AVG tot and feasible)

	text_value = to_string(aveEnergyTC) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(aveEnergyTCFeasible) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = to_string(spec->energyTC_w) +","; // @suppress("Function cannot be resolved")
	myFile << text_value;

	text_value = "\n";
	myFile << text_value;

}

// Save and print the best partitioning of the population and some statistics
// CHECK!!!
void  population::printMemStat(unsigned long gen)
{
	double sum=0, ave=0, sd = 0;

	double CFcopy;
	numFeasibleSol = 0;
	string text_value;
	for(unsigned int i=0; i<numInd; i++)
	{
		if(pop[i]->CF >= 0){
			CFcopy=pop[i]->CF;
			sum+=CFcopy;	
			// If the solution is feasible (CF < 1)
			if(pop[i]->CF < 1.0){
				numFeasibleSol++;
			}

			if (CFcopy < bestCF)
			{
				bestCF = pop[i]->CF;
				cout << endl << "TDA: " << pop[i]->TDA << endl;
				cout << "NTCC: " << pop[i]->NTCC << endl;
				cout << "EP: " << pop[i]->EP << endl;
				cout << "L: " << pop[i]->L << endl;
				cout << "C: " << pop[i]->C << endl;
				cout << "Total monetary cost: " << pop[i]->INDIVIDUAL_COST << endl;
				cout << "KB: " << pop[i]->KB << endl;
				cout << "Geq: " << pop[i]->Geq << endl;
				cout << "Energy: " << pop[i]->Ener << endl;
				cout << "Energy To Completion: " << pop[i]->EnerETC << endl;
				cout << "Total Cost Function: " << pop[i]->CF << endl;

				cout << "Process ID:  ";
				for(unsigned int j=0; j< spec->numProcesses; j++)
					cout << j+2 << " ";
				cout << endl;

				cout << "mappings:     ";
				for(unsigned int j=0; j< spec->numProcesses; j++){
					pop_Best[j] = pop[i]->mapping[j];
					cout << pop[i]->mapping[j] << " ";
				}
				cout << endl;

#if _WIN32
system("pause");
#endif

			}
		}
	}

	ave=sum/numInd;
	sum=0;
	for(unsigned int i=0; i<numInd; i++){
		if(pop[i]->CF >= 0){
			sum+=((pop[i]->CF-ave)*(pop[i]->CF-ave));
		}
	}
	// Compute standard deviation
	sd = sqrt(sum/numInd);

	cout << endl << "Population CF average: " << ave << endl;
	cout << " Population Standard deviation: " << sd << endl;
}



// Delete the last xml mapping file containing the best partitioning of the
// population
void population::deleteXml()
{

	int i;
	pugi::xml_document myDoc;
	pugi::xml_parse_result myResult = myDoc.load_file("./XML/mappingPS.xml");
	cout << "XML Delete result: " << myResult.description() << endl;

	//method 2: use object/node structure
	pugi::xml_node instancesMAP = myDoc.child("mapping");

	xml_node allocation = instancesMAP.child("allocation");

	for(i = 0; i < spec->numProcesses + 2; i++){
		xml_node processorId = allocation.child("processId");
		allocation.remove_child(processorId);
		allocation = allocation.next_sibling();
	}

	myDoc.save_file("./XML/mappingPS.xml");
	myDoc.reset();

}

// Create the xml mapping file containing the best partitioning of the
// population
void population::mappingXml(specification *s)
{
	pugi::xml_document doc;

	pugi::xml_parse_result myResult = doc.load_file("./XML/mappingPS.xml");
	//pugi::xml_parse_result myResult = doc.load_file(result2.c_str());
	cout << "Mapping result: " << myResult.description() << endl;

	xml_node instancesMAP = doc.child("mapping");

	xml_node allocation = instancesMAP.child("allocation");

	int i = 0;
	for(i = 0; i < s->numProcesses + 2; i++){

		xml_node map = allocation.append_child("processId");

		map.append_attribute("PSid").set_value(i);
		if(i > 1){
			map.append_attribute("BBname").set_value(s->architecture[pop_Best[i-2]].name.c_str());
			map.append_attribute("value").set_value(pop_Best[i-2]);
			map.append_attribute("PUid").set_value(0);
			map.append_attribute("PTid").set_value(0);
		}else{
			map.append_attribute("BBname").set_value("NA");
			map.append_attribute("value").set_value("NA");
			map.append_attribute("PUid").set_value(0);
			map.append_attribute("PTid").set_value(0);
		}

		allocation = allocation.next_sibling();
	}

	doc.save_file("./XML/mappingPS.xml");
	doc.reset();
}

