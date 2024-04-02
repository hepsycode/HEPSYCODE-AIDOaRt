//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Individual
//============================================================================

#ifndef __INDIVIDUAL__
#define __INDIVIDUAL__

#include "define.h"
#include "specification.h"

///
/// An individual represents a partitioning, a choice of number and type of executors
/// and the mapping of the processes on them
///

class individual
{
public:

/// DATA

	/// Pointer to the specification
	specification *spec;
	
	/// Array to keep track of the processes already considered
	/// for the evaluation of some values
	bool *jump;
	
	/// Identify a new individual (for which the CF has not been evaluated)
	bool newborn;
	
	/// The element i of this vector specifies on which class of executors
	/// (0 = GPP, 1 = DSP, 2 = SPP)the process i of the specification is mapped to
	int *Ptype;
	
	/// The element i of this vector specifies in which instance of executors
	/// the process i of the specification is mapped to
	unsigned long *mapping;

	/// Multi-objective cost function
	double CF;
	
	// Indexes that compose the cost function and their weights

		/// Affinity index value
		double TDA;
		/// Affinity weight
		float wTDA;

		/// Communication index value
		double NTCC;
		/// Communication weight
		float wNTCC;
		
		/// Parallelism index value
		double EP;
		/// Parallelism weight
		float wEP;

		/// Load index value
		double L;
		/// Load weight
		float wL;

		/// Monetary cost index value
		double C;
		/// Monetary cost weight
		float wC;
		/// Individual monetary cost (the absolute cost)
		float INDIVIDUAL_COST;

		/// Size index value for SW processor (considering both ROM and RAM)
		double KB;
		/// Size weight for SW processor
		float wKB;
		
		/// Size index value for HW processor
		double Geq;
		/// Size weight for HW processor
		float wGeq;
		//weight energy processor
		double wEn;
		//weight Energy To Completion processor
		double wEnTC;
		//energy index cost
		double Ener;
		//energy index cost
		double EnerETC;
		
		/// Feasibility index (actually 0 or 1 but we could think to other options...)
		float Feasibility;
		///Feasibility weight
		float wFeasibility;

	
/// METHODS

	/// Allocate the population vector, create random individuals and
	/// initialize the weights
	void initialize( specification *s );
	
	void initializeDefault( specification *s , int BBId);

	/// Destructor
	~individual();
	
	/// Compute the cost function related to an individual
	void evaluateCF( double bestCF );

	/// Evaluate the Affinity index
	void evaluateTDA();
	
	/// Evaluate the Communication index
	void evaluateNTCC();
	
	/// Evaluate the Parallelism index
	void evaluateEP();
	
	/// Evaluate the Load index
	void evaluateL();

	/// Evaluate the monetary cost index
	void evaluateC();
	
	/// Evaluate the Energy index
	void evaluateEn();

	/// Evaluate the Size index (considering both HW and SW)
	void evaluateSize();

	/// Evaluate the Energy To Completion (ETC)
	void evaluateETC();
};

#endif
