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
/// and the allocation of the processes on them
///

class individual
{
public:
	///
	/// Pointer to the specification
	///
	specification *spec;
	///
	/// Array to keep track of the processes already considered
	/// for the evaluation of some values
	///
	bool *jump;
	///
	/// Identify a new partitioning (for which the CF has not been evaluated)
	///
	bool newborn;
	///
	/// The element i of this vector specifies on which type of executors
	/// (0 = GPP, 1 = DSP, 2 = ASP)the process i of the specification is allocated
	///
	int *Ptype;
	///
	/// The element i of this vector specifies in which instance of executor
	/// the process i of the specification is allocated
	///
	int *istance;

	// Objective function and their weights
	///
	/// Total cost function, the multi-objective function
	///
	double CF;
	///
	/// Affinity index value
	///
	float TDA;
	///
	/// Affinity weight
	///
	float wTDA;
	///
	/// Communication index value
	///
	float NTCC;
	///
	/// Communication weight
	///
	float wNTCC;
	///
	/// Parallelism index value
	///
	float EP;
	///
	/// Parallelism weight
	///
	float wEP;
	///
	/// Load index value
	///
	float L;
	///
	/// Load weight
	///
	float wL;
	///
	/// Monetary cost index value
	///
	float C;
	///
	/// Monetary cost weight
	///
	float wC;
	///
	/// Total partitioning monetary cost
	///
	float INDIVIDUAL_COST;
	///
	/// Size index value for SW processor
	///
	float KB;
	///
	/// Size weight for SW processor
	///
	float wKB;
	///
	/// Size index value for HW processor
	///
	float Geq;
	///
	/// Size weight for HW processor
	///
	float wGeq;
	///
	/// Criticality index value
	///
	float Crit;
	///
	///Criticality weight
	///
	float wCrit;
	///
	/// Feasibility index
	///
	float feasibility;
	///
	///Feasibility weight
	///
	float wFeasibility;
	///
	/// Allocate the partitioning vector, create random partitioning and
	/// initialize the weights
	///
	void initialize( specification *s );
	///
	/// Destructor
	///
	~individual();
	///
	/// Compute the cost functions related to partitioning
	///
	void evaluateCF( float bestCF );

	void parallel_evaluateCF( float bestCF );
	///
	/// Evaluate the affinity index related to the partitioning
	///
	void evaluateTDA();
	///
	/// Evaluate the Communication index related to the partitioning
	///
	void evaluateNTCC();
	///
	/// Evaluate the Parallelism index related to the partitioning
	///
	void evaluateEP();
	///
	/// Evaluate the Load index related to the partitioning
	///
	void evaluateL();

	static void *evaluateLStatic(void*);
	///
	/// Evaluate the monetary cost index related to the partitioning
	///
	void evaluateC();

	static void *evaluateCStatic(void*);
	///
	/// Evaluate the Size index related to the partitioning
	///
	void evaluateSize();

	//void evaluateCrit();
	//bool criticalityCheck();

};

#endif
