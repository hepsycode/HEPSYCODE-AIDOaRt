//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Partitioning
//============================================================================

#include <stdlib.h>

#include <iostream>
#include <omp.h>
#include <pthread.h>

#include "individual.h"

using namespace std;


// Allocate the partitioning vector, create random partitioning and
// initialize the weights
void individual::initialize( specification *s )
{
	int j;

	spec=s; // coupling to the specification

	// Memory allocation
	Ptype   = new int[spec->numProc];
	istance = new int[spec->numProc];
	jump   = new bool[spec->numProc];

	// Weights initialization
	wTDA=s->aff;  // Affinity
	wNTCC=s->comm;  // Communication
	wEP=s->par_w;  // Parallelism
	wL=s->load;  // Load
	wC=s->cost;  // Cost
	wKB=s->size_SW;  // Size SW
	wGeq=s->size_HW;  // Size HW
	wCrit=s->crit; // Criticality

	wFeasibility=s->feas;  // feasibility index

	// Initialize the objective functions to the MAX
	CF=1;
	TDA=1;
	NTCC=1;
	EP=1;
	L=0;
	C=1;
	KB=1;
	Geq=1;
	Crit=1;

	feasibility=0;

	// Just created, this is a newborn ...
	// so the CF has not been already calculated
	newborn = true;

	// Random partitioning creation
	for( j=0; j < spec->numProc; j++ )
	{
		// For each process choose a type and an instance of executor
		// randomly but within the limits imposed

		int loc =(rand()%spec->instanceBB);
		istance[j] = spec->architecture[loc].id;

		if(spec->architecture[loc].procUnit->processorType == "SPP" ){
			Ptype[j] = 2;  // SPP
		}else if (spec->architecture[loc].procUnit->processorType == "DSP" ){
			Ptype[j] = 1;  // DSP
		}else if (spec->architecture[loc].procUnit->processorType == "GPP" ){
			Ptype[j] = 0; // GPP
		}

		// Specify maximum number of BB instances I want (Future work)

		/* if(sum_BB < spec->instanceMaxBB){

        	   int loc =(rand()%spec->instanceBB);

        	   if(maxBBArray[loc]==0){

        		   localBBArray[i]=loc;
        		   sum_BB++;
        		   maxBBArray[loc]++;

				   istance[j] = spec->architecture[loc].id;

				   if(spec->architecture[loc].processorType == "SPP" ){
					   Ptype[j] = 2;  // SPP
				   }else if (spec->architecture[loc].processorType == "DSP" ){
					   Ptype[j] = 1;  // DSP
				   }else if (spec->architecture[loc].processorType == "GPP" ){
					   Ptype[j] = 0; // GPP
				   }
				   i++;

        	   }else{
        		   istance[j] = spec->architecture[loc].id;

				   if(spec->architecture[loc].processorType == "SPP" ){
					   Ptype[j] = 2;  // SPP
				   }else if (spec->architecture[loc].processorType == "DSP" ){
					   Ptype[j] = 1;  // DSP
				   }else if (spec->architecture[loc].processorType == "GPP" ){
					   Ptype[j] = 0; // GPP
				   }
        	   }
           }else{

        	   int temp = (rand()%spec->instanceMaxBB);

        	   istance[j] = spec->architecture[localBBArray[temp]].id;

			   if(spec->architecture[localBBArray[temp]].processorType == "SPP" ){
				   Ptype[j] = 2;  // SPP
			   }else if (spec->architecture[localBBArray[temp]].processorType == "DSP" ){
				   Ptype[j] = 1;  // DSP
			   }else if (spec->architecture[localBBArray[temp]].processorType == "GPP" ){
				   Ptype[j] = 0; // GPP
			   }

           }  */

		//istance[j] = 0;
		//Ptype[j] = 0;

	}

	// delete the infeasible individuals

}

// Destructor
individual::~individual()
{
	//delete spec;
	delete[] Ptype;
	delete[] istance;
	delete[] jump;
}

// Evaluate the total cost function, i.e. the multi-objective function
void individual::evaluateCF( float bestCF )
{

	//One at a time compute the single objective function and sum them to the total
	//multi-objective function
	// (The evaluation order should be of increasing computational complexity
	// so if you go out first you save time)
	CF=0;

	// Update the weights after the equalization
	wC = spec->cost;
	wL = spec->load;

	// If the weight associated with a function is zero, execution time can be saved

	// Affinity
	if (spec->aff != 0)
	{
		evaluateTDA();
		CF+=wTDA*TDA;
	}

	// Parallelism
	if (spec->par_w != 0)
	{
		evaluateEP();
		CF+=wEP*EP;
	}

	// Communication
	if (spec->comm != 0)
	{
		evaluateNTCC();
		CF+=wNTCC*NTCC;
	}

	// Monetary cost
	if (spec->cost != 0)
	{
		evaluateC();
		CF+=wC*C;
	}

	// Load
	if (spec->load != 0)
	{
		evaluateL();
		CF+=wL*L;
	}

	// Size
	if (spec->size_SW != 0 && spec->size_HW != 0)
	{
		evaluateSize();
		CF+=wKB*KB;
		CF+=wGeq*Geq;
	}

	// Feasibility index
	CF+=wFeasibility*feasibility;
}
/*
// Parallel evaluation with pthreads
void individual::parallel_evaluateCF( float bestCF )
{
	pthread_t thread1, thread2;

	int iret1 = pthread_create( &thread1, NULL, evaluateLStatic, this );
	if(iret1)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}

	int iret2 = pthread_create( &thread2, NULL, evaluateCStatic, this );
	if(iret2)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
		exit(EXIT_FAILURE);
	}

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	CF+=wC*C;
	CF+=wL*L;

	//One at a time compute the single objective function and sum them to the total
	//multi-objective function
	// (The evaluation order should be of increasing computational complexity
	// so if you go out first you save time)
	CF=0;

	// Update the weights after the equalization
	wC = spec->cost;
	wL = spec->load;

	// If the weight associated with a function is zero, execution time can be saved

	// Affinity
	if (spec->aff != 0)
	{
		evaluateTDA();
		CF+=wTDA*TDA;
	}

	// Parallelism
	if (spec->par_w != 0)
	{
		evaluateEP();
		CF+=wEP*EP;
	}

	// Communication
	if (spec->comm != 0)
	{
		evaluateNTCC();
		CF+=wNTCC*NTCC;
	}
//
//	// Monetary cost
//	if (spec->cost != 0)
//	{
//		evaluateC();
//		CF+=wC*C;
//	}
//
//	// Load
//	if (spec->load != 0)
//	{
//		evaluateL();
//		CF+=wL*L;
//	}

	// Size
	if (spec->size_SW != 0 && spec->size_HW != 0)
	{
		evaluateSize();
		CF+=wKB*KB;
		CF+=wGeq*Geq;
	}

	// Feasibility index
	CF+=wFeasibility*feasibility;
}
*/

// Parallel evaluation with OpenMp
void individual::parallel_evaluateCF( float bestCF )
{

	//One at a time compute the single objective function and sum them to the total
	//multi-objective function
	// (The evaluation order should be of increasing computational complexity
	// so if you go out first you save time)
	CF=0;

	// Update the weights after the equalization
	wC = spec->cost;
	wL = spec->load;

#pragma omp parallel sections num_threads(2)
	{
#pragma omp section
		{
			// Affinity
			if (spec->aff != 0)
			{
				evaluateTDA();
			}
			// Parallelism
			if (spec->par_w != 0)
			{
				evaluateEP();
			}
			// Communication
			if (spec->comm != 0)
			{
				evaluateNTCC();
			}
		}
#pragma omp section
		{
			// Monetary cost
			if (spec->cost != 0)
			{
				evaluateC();
			}
			// Load
			if (spec->load != 0)
			{
				evaluateL();
			}
			// Size
			if (spec->size_SW != 0 && spec->size_HW != 0)
			{
				evaluateSize();
			}
		}
	}//close parallel, implicit barrier

	CF+=wTDA*TDA;
	CF+=wEP*EP;
	CF+=wNTCC*NTCC;
	CF+=wC*C;
	CF+=wL*L;
	CF+=wKB*KB;
	CF+=wGeq*Geq;

	// Feasibility index
	CF+=wFeasibility*feasibility;
}


// Evaluate affinity (Total Degree of Affinity)
void individual::evaluateTDA()
{
	int i;
	float sumDA=0;

	// Compute TDA
	// Average affinity from actual allocations
	// It is an average of values ​​between 0 and 1, so it is itself between 0 and 1
	// High TDA imply that the processes are allocated to the most suitable executors
	for(i=0; i < spec->numProc; i++) sumDA += spec->project[i].DA[Ptype[i]];

	// We carry out the subtraction because it is a minimization problem
	TDA= 1 - (sumDA/spec->numProc);

}

// Evaluate the communication function (Normalized Total Communication Cost)
void individual::evaluateNTCC()
{
	int i, j;

	// Inter Cluster Communication Cost
	// Represents the cost associated to process communication if processes are
	// allocated on different processors
	long ICCC=0;

	for(i=0; i<spec->numProc; i++)
		for(j=0; j<spec->numProc; j++){
			if (istance[i] != istance[j])  ICCC += spec->comMat[i*spec->numProc+j];
		}

	// Normalized Total Communication Cost
	NTCC = ( (float) ICCC)/spec->maxTCC;

}

// Evaluate the parallelism function (Exploited Parallelism)
void individual::evaluateEP()
{
	int i, j;

	// Inter Cluster Exploited Parallelism
	// Indicates how much an individual can exploit the potential concurrency
	float ICEP=0;

	// If potentially competing processes are on different executors
	// the degree of potential parallelism offered by partitioning increases
	for(i=0; i < spec->numProc; i++)
		for(j=0; j < spec->numProc; j++){
			if (istance[i] != istance[j])  ICEP += spec->parMat[i*spec->numProc+j];
		}

	// Normalized parallelism
	// We carry out the subtraction because it is a minimization problem
	EP = 1 - ( (float) ICEP)/spec->maxEP;

}

// Evaluate the Load function
void individual::evaluateL()
{
	// Partial and total load (for SW processor)
	float loadP=0, loadT=0;
	// Average of loads on SW processors
	float ave1=0;
	feasibility=0;

	int i,j;
	// Count the number of SW processors
	int num=0;

	// Initialize the jump array to keep track of processes already considered
	for(i=0; i<spec->numProc; i++) jump[i]=false;

	//the processes allocated to the same executor are identified and the partial load
	//is calculated

	for(i=0; i<spec->numProc; i++)
	{
		// If it isn't HW processor
		if (Ptype[i] != 2)
		{
			// if the i-th process has not been considered yet
			if (jump[i]==false)
			{
				//Increase the number of SW processor considered
				num++;
				//add to the partial load the load of the current process
				loadP=spec->project[i].load[istance[i]];

				// check if other processes are allocated on the same executor
				for(j=i+1; j<spec->numProc; j++)
				{
					if (jump[j]==false)
					{

						if (istance[i]==istance[j])
						{
							loadP+=spec->project[j].load[istance[j]];
							//Mark the process as already considered
							jump[j]=true;
						}
					}
				}
				//Mark the process as already considered
				jump[i]=true;

				// Penalize if infeasible (load of the executor that we are
				//considering > loadMax , imposed on the specification)
				if (loadP>spec->loadMax)
				{
					L=1;
					feasibility=1;
					return;
				}

				// Total load: sum of partial load
				// It varies depending on how many processes are in HW
				loadT+=loadP;
				loadP=0;
			}
		}
	}

	// Compute the Load Index
	if (num!=0) {
		ave1=loadT/num;
		L = 1 - (ave1);
	}
}


void *individual::evaluateLStatic(void*arg)
{
	individual *obj = (individual *)arg;
	obj->evaluateL();
}


// Evaluate the monetary cost function
void individual::evaluateC()
{
	float cost=0;
	int i,j;

	// Initialize the jump array to keep track of processes already considered
	for(i=0; i<spec->numProc; i++) jump[i]=false;

	for(i=0; (i<spec->numProc); i++)
	{
		// For each new executor considered, add the cost
		// If it is an executor not considered yet...
		if (jump[i]==false)
		{
			cost+= spec->architecture[istance[i]].procUnit->cost;

			// Mark any other presence of the executor
			for(j=i+1; (j<spec->numProc); j++)
			{
				if (jump[j]==false)
				{
					if ((istance[i]==istance[j])) jump[j]=true;
				}
			}
			jump[i]=true;

		}
	}

	INDIVIDUAL_COST = cost;
	//Compute the Cost Index
	// Ratio with max possible cost
	C= cost/(spec->numBB*spec->maxCOST);
}

void *individual::evaluateCStatic(void*arg)
{
	individual *obj = (individual *)arg;
	obj->evaluateC();
}

// Evaluate the Size function
void individual::evaluateSize()
{
	// Sum of data size of the processes on certain SW executor
	float sizeSW_RAM=0;
	// Sum of code size of the processes on certain SWexecutor
	float sizeSW_ROM=0;
	// Sum of data and code size of the SW executors used
	float sizeSW_Max=0;
	// Sum of size (equivalent gates) of the processes on certain HW executor
	float sizeHW=0;
	// Sum of size (equivalent gates) of the HW executors used
	float sizeHWMax=0;
	float KB_temp = 0;
	float Geq_temp = 0;
	int i, j;

	// Initialize the jump array to keep track of processes already considered
	for(i=0; i<spec->numProc; i++) jump[i]=false;

	for(i=0; (i<spec->numProc); i++)
	{
		//For each new executor considered, add the size
		// if not considered yet...
		if (jump[i]==false)
		{
			// SW executors
			if(spec->architecture[istance[i]].procUnit->processorType == "GPP" || spec->architecture[istance[i]].procUnit->processorType == "DSP"){
				//Add data size of the process for this executor
				sizeSW_RAM += spec->project[i].size_SW_RAM[istance[i]];
				//Add code size of the process for this executor
				sizeSW_ROM += spec->project[i].size_SW_ROM[istance[i]];

				for(j=i+1; (j<spec->numProc); j++)
				{
					if (jump[j]==false)
					{
						//If the j-th process is allocated on the same i executor
						//add data and code size
						if (istance[i]==istance[j])
						{
							sizeSW_RAM += spec->project[j].size_SW_RAM[istance[j]];
							sizeSW_ROM += spec->project[j].size_SW_ROM[istance[j]];
							//Mark the process as already considered
							jump[j]=true;
						}
					}
				}
				//Mark the process as already considered
				jump[i]=true;

				// Penalize if infeasible (size of the processes allocated on certain
				//executor > size of the executor)
				if ( sizeSW_RAM > (spec->architecture[istance[i]].memUnit->dataSize) )
				{
					KB=1;
					return;
				}else if( sizeSW_ROM > (spec->architecture[istance[i]].memUnit->codeSize) ){
					KB=1;
					return;
				}else{
					// if it isn't infeasible, save the partial value for the size index
					sizeSW_Max += (spec->architecture[istance[i]].memUnit->dataSize) + (spec->architecture[istance[i]].memUnit->codeSize);
					KB_temp += sizeSW_RAM + sizeSW_ROM;
					sizeSW_RAM = 0;
					sizeSW_ROM = 0;
				}

				//HW executors
			}else if(spec->architecture[istance[i]].procUnit->processorType == "SPP"){ // Esecutore HW
				//Add size of the process for this HW executor (equivalent gates)
				sizeHW += spec->project[i].eqg;

				for(j=i+1; (j<spec->numProc); j++)
				{
					if (jump[j]==false)
					{
						//If the j-th process is allocated on the same i executor
						//add the size
						if (istance[i]==istance[j])
						{
							sizeHW += spec->project[j].eqg;
							//Mark the process as already considered
							jump[j]=true;
						}
					}
				}
				//Mark the process as already considered
				jump[i]=true;

				// Penalize if infeasible (size of the processes allocated on certain
				//executor > size of the executor)
				if ( sizeHW > (spec->architecture[istance[i]].memUnit->eqG) )
				{
					Geq=1;
					return;
				}else{
					// if it isn't infeasible, save the partial value for the size index
					sizeHWMax += (spec->architecture[istance[i]].memUnit->eqG);
					Geq_temp += sizeHW;
					sizeHW = 0;
				}
			}

			// Mark any other attendance of the executor
			for(j=i+1; (j<spec->numProc); j++)
			{
				if (jump[j]==false)
				{
					if ((istance[i]==istance[j])) jump[j]=true;
				}
			}
			jump[i]=true;

		}
	}

	//Compute the Size Index
	if((KB_temp - sizeSW_Max) > 0 && sizeSW_Max > 0)
	{
		KB = (KB_temp - sizeSW_Max)/sizeSW_Max;
	}
	else if(sizeSW_Max > 0)
	{
		KB = (-(KB_temp - sizeSW_Max)) / sizeSW_Max;
	}

	if((Geq_temp - sizeHWMax) > 0 && sizeHWMax > 0)
	{
		Geq = (Geq_temp - sizeHWMax)/sizeHWMax;
	}
	else if(sizeHWMax > 0)
	{
		Geq = (-(Geq_temp - sizeHWMax))/sizeHWMax;
	}
}

// Evaluate the criticality
/*void individual::evaluateCrit()
{
      int i, j;
      int threeshold = 0;

      // If processes with equal criticality are on different executors
      // or processes with different criticalities are on equal executors
      // set the Crit parameter to 1
      Crit = 0;
      for(i=0; i < spec->numProc; i++){
            for(j=0; j < spec->numProc; j++)
            {
				if (istance[i] == istance[j]){
					if( abs(spec->project[i].criticality - spec->project[j].criticality) > threeshold ){
						Crit = 1;
					}
				} */
/*if (istance[i] != istance[j] && abs(spec->project[i].criticality - spec->project[j].criticality) == 0 ){
					Crit = 1;
				} */
/* }
       }
} */

// Evaluate feasibility with criticality
/*bool individual::criticalityCheck()
{
      int i, j;
      bool criticality;
      int threeshold = 0;

      criticality = false;
      for(i=0; i < spec->numProc; i++){
            for(j=0; j < spec->numProc; j++)
            {
				if (istanza[i] == istanza[j]){
					if( abs(spec->progetto[i].criticality - spec->progetto[j].criticality) > threeshold ){
						criticality = true;
					}
				}
				if (istanza[i] != istanza[j] && abs(spec->progetto[i].criticality - spec->progetto[j].criticality) == 0 ){
					criticality = true;
				}
            }
       }
      return criticality;
} */

