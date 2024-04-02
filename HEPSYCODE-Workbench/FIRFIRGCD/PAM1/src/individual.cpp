//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Partitioning
//============================================================================

#include <stdlib.h>
#include <iostream>
#include "individual.h"

using namespace std;

/// Allocate the population vector, create random individuals and
/// initialize the weights
void individual::initializeDefault( specification *s , int BBId)
{
	unsigned long j;

	spec=s; // link to the specification (i.e., processes, basic blocks)

	// Memory allocation
	Ptype   = new int[spec->numProcesses];
	mapping = new unsigned long[spec->numProcesses];
	jump   = new bool[spec->numProcesses];

	// Weights initialization
	wTDA = (float) s->aff_w;  // Affinity
	wNTCC = (float) s->comm_w;  // Communication
	wEP = (float) s->par_w;  // Parallelism
	wL = (float) s->load_w;  // Load
	wC = (float) s->cost_w;  // Cost
	wKB = (float) s->size_SW_w;  // Size SW
	wGeq = (float) s->size_HW_w;  // Size HW
	wEn = (float) s->energy_w;	//Energy Max
	wEnTC = (float) s->energyTC_w;	//ETC
	wFeasibility = (float) s->feas_w;  // Feasibility index

	// Initialize the objective functions to the worts case
	CF=1;
	TDA=1;
	NTCC=1;
	EP=1;
	L=1; // It was 0, why?
	C=1;
	KB=1;
	Geq=1;
	Ener=1;
	EnerETC=1;
	Feasibility=0; // 0 == it is feasible
	INDIVIDUAL_COST=0;

	// Just created, this is a newborn ...
	// so the CF has not been already calculated
	newborn = true;

	// Random individuals creation
	for( j=0; j < spec->numProcesses; j++ )
	{

		// Map each process onto a specific BB
		mapping[j] = spec->architecture[BBId].id;

		// For later convenience...
		if(spec->architecture[BBId].procUnit->processorType == "SPP" ){
			Ptype[j] = 2;  // SPP
		}else if (spec->architecture[BBId].procUnit->processorType == "DSP" ){
			Ptype[j] = 1;  // DSP
		}else if (spec->architecture[BBId].procUnit->processorType == "GPP" ){
			Ptype[j] = 0; // GPP
		}

	}
}

/// Allocate the population vector, create random individuals and
/// initialize the weights
void individual::initialize( specification *s )
{
	unsigned long j;

	spec=s; // link to the specification (i.e., processes, basic blocks)

	// Memory allocation
	Ptype   = new int[spec->numProcesses];
	mapping = new unsigned long[spec->numProcesses];
	jump   = new bool[spec->numProcesses];

	// Weights initialization
	wTDA = (float) s->aff_w;  // Affinity
	wNTCC = (float) s->comm_w;  // Communication
	wEP = (float) s->par_w;  // Parallelism
	wL = (float) s->load_w;  // Load
	wC = (float) s->cost_w;  // Cost
	wKB = (float) s->size_SW_w;  // Size SW
	wGeq = (float) s->size_HW_w;  // Size HW
	wEn = (float) s->energy_w;	//Energy Max
	wEnTC = (float) s->energyTC_w;	//ETC
	wFeasibility = (float) s->feas_w;  // Feasibility index

	// Initialize the objective functions to the worts case
	CF=1;
	TDA=1;
	NTCC=1;
	EP=1;
	L=1; // It was 0, why?
	C=1;
	KB=1;
	Geq=1;
	Ener=1;
	EnerETC=1;
	Feasibility=0; // 0 == it is feasible
	INDIVIDUAL_COST=0;

	// Just created, this is a newborn ...
	// so the CF has not been already calculated
	newborn = true;

	// Random individuals creation
	for( j=0; j < spec->numProcesses; j++ )
	{

		// Randomly map each process onto a BB
		unsigned int bb =(rand()%spec->numBBinstances);
		mapping[j] = spec->architecture[bb].id;

		// For later convenience...
		if(spec->architecture[bb].procUnit->processorType == "SPP" ){
			Ptype[j] = 2;  // SPP
		}else if (spec->architecture[bb].procUnit->processorType == "DSP" ){
			Ptype[j] = 1;  // DSP
		}else if (spec->architecture[bb].procUnit->processorType == "GPP" ){
			Ptype[j] = 0; // GPP
		}

	}
}

// Destructor
individual::~individual()
{
	//delete spec;
	delete[] Ptype;
	delete[] mapping;
	delete[] jump;
}

// Evaluate the total cost function, i.e. the multi-objective function
void individual::evaluateCF( double bestCF )
{
	//One at a time compute the single objective functions and sum them to the total
	//multi-objective function
	// (The evaluation order should be of increasing computational complexity
	// so if you go out first you save time)
	CF=0;

	// If the weight associated with a function is zero, execution time can be saved

	// Affinity
	if (wTDA!= 0)
	{
		evaluateTDA();
		CF+=wTDA*TDA;
	}

	// Parallelism
	if (wEP != 0)
	{
		evaluateEP();
		CF+=wEP*EP;
	}

	// Communication
	if (wNTCC != 0)
	{
		evaluateNTCC();
		CF+=wNTCC*NTCC;
	}

	// Monetary cost
	if (wC != 0)
	{
		evaluateC();
		CF+=wC*C;
	}

	// Load
	if (wL != 0)
	{
		evaluateL();
		CF+=wL*L;
		
	}

	// Energy Max
	if (wEn != 0)
	{
		evaluateEn();
		CF+=wEn*Ener;
	}
	// ETC
	if (wEnTC != 0)
	{
		evaluateETC();
		CF+=wEnTC*EnerETC;
	}

	// Size
	if (wKB != 0 && wGeq != 0)
	{
		evaluateSize();
		CF+=wKB*KB;
		CF+=wGeq*Geq;
	}

	// Feasibility index
	CF+=wFeasibility*Feasibility;

	//if (L != 0 && EnerETC==0) cout<<"ETC = "<<wEnTC*EnerETC<< "; wEnTC = "<< wEnTC << "; EnerETC = "<< EnerETC<< "; CF = "<<CF<<endl; 
}


// Evaluate affinity (Total Degree of Affinity)
void individual::evaluateTDA()
{
	unsigned int i;
	double sumDA=0;

	// Compute TDA
	// Average affinity from actual allocations
	// It is an average of values​between 0 and 1, so it is itself between 0 and 1
	// High TDA imply that the processes are allocated to the most suitable BBs
	for(i=0; i < spec->numProcesses; i++) sumDA += spec->project[i].DA[Ptype[i]];

	// We carry out the subtraction because it is a minimization problem
	TDA = 1 - (sumDA/spec->numProcesses);

}

// Evaluate the communication function (Normalized Total Communication Cost)
void individual::evaluateNTCC()
{
	unsigned int i, j;

	// Inter Cluster Communication Cost
	// Represents the cost associated to process communication if processes are
	// allocated on different processors
	unsigned long ICCC=0;

	for(i=0; i<spec->numProcesses; i++)
		for(j=0; j<spec->numProcesses; j++){
			if (mapping[i] != mapping[j])  ICCC += spec->comMat[i*spec->numProcesses+j];
		}

	// Normalized Total Communication Cost
	NTCC = ( (double) ICCC)/spec->maxTCC;

}

// Evaluate the parallelism function (Exploited Parallelism)
void individual::evaluateEP()
{
	unsigned int i, j;

	// Inter Cluster Exploited Parallelism
	// Indicates how much an individual can exploit the potential concurrency
	double ICEP=0;

	// If potentially competing processes are on different executors
	// the degree of potential parallelism offered by partitioning increases
	for(i=0; i < spec->numProcesses; i++)
		for(j=0; j < spec->numProcesses; j++){
			if (mapping[i] != mapping[j])  ICEP += spec->parMat[i*spec->numProcesses+j];
		}

	// Normalized parallelism
	// We carry out the subtraction because it is a minimization problem
	EP = 1 - ICEP/spec->maxEP;

}

// Evaluate the Load function
void individual::evaluateL()
{
	// Partial and total load (for SW processor)
	double loadT=0;

	double loadP[MAXBB];
	int boolLoadP[MAXBB];
	// Average of loads on SW processors
	double ave1=0;
	Feasibility=0;

	unsigned int i,j;
	// Count the number of SW processors
	unsigned int num=0;
	
	// Initialize the jump array to keep track of processes already considered
	for(i=0; i<spec->numProcesses; i++) jump[i]=false;
	//the processes allocated to the same executor are identified and the partial load
	//is calculated
	for(i=0; i<MAXBB; i++) loadP[MAXBB] = 0;
	for(i=0; i<MAXBB; i++) boolLoadP[MAXBB] = 0;

	for(i=0; i<spec->numProcesses; i++)
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
				loadP[mapping[i]]=spec->project[i].load[mapping[i]];

				// check if other processes are allocated on the same executor
				for(j=i+1; j<spec->numProcesses; j++)
				{
					if (jump[j]==false)
					{

						if (mapping[i]==mapping[j])
						{
							loadP[mapping[i]]+=spec->project[j].load[mapping[j]];
							boolLoadP[mapping[i]] = 1;
							//Mark the process as already considered
							jump[j]=true;
						}
					}
				}
				//Mark the process as already considered
				jump[i]=true;

				// Penalize if infeasible (load of the executor that we are
				//considering > loadMax , imposed by the specification)
				if (loadP[mapping[i]]>spec->loadMax)
				{
					L=1;
					Feasibility=1;
					return;
				}

				// Total load: sum of partial load
				// It varies depending on how many processes are in HW
				loadT+=loadP[mapping[i]];
				// loadP=0;
			}
		}
	}
	// Compute the Load Index
	if (num!=0) {
		ave1=loadT/num;
		// L = 1 - (ave1);
		// L = 1-(spec->loadMax - (ave1));
		L = spec->loadMax - (ave1); // When ave1 is == loadMax it is perfect!
									// It cannot be greater because it is checked before
	}
	/*double Lpart = 0;
	if(num!=0){
		for(i = 0; i < spec->numBB-1; i++){
			if (loadP[mapping[i]] <= spec->loadMax){
				Lpart += abs(boolLoadP[i]*(spec->loadMax - loadP[i]));
			}else{
				L=1;
				Feasibility=1;
				return;
			}
		}
		L = Lpart;
	}*/
	else{
		L=0;
	}
}


// Evaluate the Energy Max function
void individual::evaluateEn()
{
	// partial energy and partial energy max
	double energyP=0, energyPMax=0, energyT = 0;
	unsigned int i,j;
	// Count the number of SW processors
	unsigned int num=0;
	// Initialize the jump array to keep track of processes already considered
	for(i=0; i<spec->numProcesses; i++) jump[i]=false;
	//the processes allocated to the same executor are identified and the partial energy
	//is calculated
	for(i=0; i<spec->numProcesses; i++)
	{
			// if the i-th process has not been considered yet
			if (jump[i]==false)
			{
				//Increase the number of SW processor considered
				num++;
				//add to the partial energy the energy of the current process
				energyP = spec->project[i].energy[mapping[i]];

				// check if other processes are allocated on the same executor
				for(j=i+1; j<spec->numProcesses; j++)
				{
					if (jump[j]==false)
					{
						if (mapping[i]==mapping[j])
						{
							energyP += spec->project[j].energy[mapping[j]];
							energyPMax += spec->project[j].energyMax;
							//Mark the process as already considered
							jump[j]=true;
						}
					}
				}
				//Mark the process as already considered
				jump[i]=true;
				energyT+=energyP;
				energyP = 0;	
		}	
	}
		//Energy Index
		Ener= energyT/energyPMax;
}




// Evaluate the Energy function related to ETC
void individual::evaluateETC()
{
	// partial energy and partial energy max
	double energyP=0, energyPETC=0, energyT=0;
	unsigned int i,j;
	// Count the number of SW processors
	unsigned int num=0;
	Feasibility=0;
	// Initialize the jump array to keep track of processes already considered
	for(i=0; i<spec->numProcesses; i++) jump[i]=false;
	//the processes allocated to the same executor are identified and the partial energy
	//is calculated
	for(i=0; i<spec->numProcesses; i++)
	{
			// if the i-th process has not been considered yet
			if (jump[i]==false)
			{
				//Increase the number of SW processor considered
				num++;
				//add to the partial energy the energy of the current process
				energyP = spec->project[i].energy[mapping[i]];
				// check if other processes are allocated on the same executor
				energyPETC += spec->project[i].energyMax;
				for(j=i+1; j<spec->numProcesses; j++)
				{
					if (jump[j]==false)
					{

						if (mapping[i]==mapping[j])
						{
							energyP += spec->project[j].energy[mapping[j]];
							energyPETC += spec->project[j].energyMax;
							//Mark the process as already considered
							jump[j]=true;
						}
					}
				}
				//Mark the process as already considered
				jump[i]=true;
				//Partial energy sum
				energyT+=energyP;
				energyP = 0;			
		}
	}
	//Check if energy is greater than ETC value
	if(energyT>spec->ETC){
		EnerETC=1;
		Feasibility=1;
		return;
	}else{
		EnerETC= energyT/energyPETC;
		return;
	}
}



// Evaluate the monetary cost function
void individual::evaluateC()
{
	float cost=0;
	unsigned int i,j;

	// Initialize the jump array to keep track of processes already considered
	for(i=0; i<spec->numProcesses; i++) jump[i]=false;

	for(i=0; (i<spec->numProcesses); i++)
	{
		// For each new executor considered, add the cost
		// If it is an executor not considered yet...
		if (jump[i]==false)
		{
			cost+= spec->architecture[mapping[i]].procUnit->cost;

			// Mark any other presence of the executor
			for(j=i+1; (j<spec->numProcesses); j++)
			{
				if (jump[j]==false)
				{
					if ((mapping[i]==mapping[j])) jump[j]=true;
				}
			}
			jump[i]=true;

		}
	}

	INDIVIDUAL_COST = cost; //perchè?
	//Compute the Cost Index
	// Ratio with max possible cost
	C = cost/(spec->numBB*spec->maxCOST);
}

// Evaluate the Size function (da rivedere???)
void individual::evaluateSize()
{
	// Sum of data size of the processes on certain SW executor
	double sizeSW_RAM=0;
	// Sum of code size of the processes on certain SWexecutor
	double sizeSW_ROM=0;
	// Sum of data and code size available on the SW executors used
	double sizeSW_Max=0;

	// Sum of size (equivalent gates) of the processes on certain HW executor
	double sizeHW=0;
	// Sum of size (equivalent gates) available on the HW executors used
	double sizeHWMax=0;

	// Temp
	double KB_temp = 0;
	double Geq_temp = 0;

	unsigned int i, j;

	// Initialize the jump array to keep track of processes already considered
	for(i=0; i<spec->numProcesses; i++) jump[i]=false;

	for(i=0; (i<spec->numProcesses); i++)
	{
		//For each new executor considered, add the size
		// if not considered yet...
		if (jump[i]==false)
		{
			// SW executors
			if(spec->architecture[mapping[i]].procUnit->processorType == "GPP" || spec->architecture[mapping[i]].procUnit->processorType == "DSP"){
				//Add data size of the process for this executor
				sizeSW_RAM += spec->project[i].size_SW_RAM[mapping[i]];
				//Add code size of the process for this executor
				sizeSW_ROM += spec->project[i].size_SW_ROM[mapping[i]];

				for(j=i+1; (j<spec->numProcesses); j++)
				{
					if (jump[j]==false)
					{
						//If the j-th process is allocated on the same i executor
						//add data and code size
						if (mapping[i]==mapping[j])
						{
							sizeSW_RAM += spec->project[j].size_SW_RAM[mapping[j]];
							sizeSW_ROM += spec->project[j].size_SW_ROM[mapping[j]];
							//Mark the process as already considered
							jump[j]=true;
						}
					}
				}
				//Mark the process as already considered
				jump[i]=true;

				// Penalize if infeasible (size of the processes allocated on certain
				//executor > size of the executor)
				if ( sizeSW_RAM > (spec->architecture[mapping[i]].memUnit->dataSize) )
				{
					KB=1;
					Feasibility=1;
					return;
				}else if( sizeSW_ROM > (spec->architecture[mapping[i]].memUnit->codeSize) ){
					KB=1;
					Feasibility=1;
					return;
				}else{
					// if it is feasible save the partial values for the size index
					sizeSW_Max += (spec->architecture[mapping[i]].memUnit->dataSize) + (spec->architecture[mapping[i]].memUnit->codeSize);
					KB_temp += sizeSW_RAM + sizeSW_ROM;
					sizeSW_RAM = 0;
					sizeSW_ROM = 0;
				}

				//HW executors
			}else if(spec->architecture[mapping[i]].procUnit->processorType == "SPP"){ // Esecutore HW
				//Add size of the process for this HW executor (equivalent gates)
				sizeHW += spec->project[i].eqg;

				for(j=i+1; (j<spec->numProcesses); j++)
				{
					if (jump[j]==false)
					{
						//If the j-th process is allocated on the same i executor
						//add the size
						if (mapping[i]==mapping[j])
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
				if ( sizeHW > (spec->architecture[mapping[i]].memUnit->eqG) )
				{
					Geq=1;
					Feasibility=1;
					return;
				}else{
					// if it isn't infeasible, save the partial value for the size index
					sizeHWMax += (spec->architecture[mapping[i]].memUnit->eqG);
					Geq_temp += sizeHW;
					sizeHW = 0;
				}
			}

			// Mark any other attendance of the executor
			for(j=i+1; (j<spec->numProcesses); j++)
			{
				if (jump[j]==false)
				{
					if ((mapping[i]==mapping[j])) jump[j]=true;
				}
			}
			jump[i]=true;

		}
	}

	//Compute the Size Index (TO BE CHECKED!!!)
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
