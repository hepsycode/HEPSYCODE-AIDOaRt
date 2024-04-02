/*
 * DataSet.h
 *
 *  Created on: 09/lug/2018
 *      Author: giuseppe
 */

#ifndef DATASET_H_
#define DATASET_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

///
/// Type of struct that will contain info about individual of population for K>2 case.
/// The information consists of the objective function values, the partitioning
/// and Pareto dominance
///
struct IndividualInfo {
		int id;
	    float tda;
	    float ntcc;
	    float ep;
	    float load;
	    float cost;
	    float totalCost;
	    float size;
	    float crit;
	    float cf;
	    string processes;
	    string processors;
	    int dominated;
	    bool isDominated;
	};

///
/// Type of struct that will contain info about individual of population for K=2 case.
/// The information consists of the objective function values, the partitioning
/// and feasibility
///
struct IndividualInfo2D {
	int id;
	float f1;
	float f2;
	float cf;
	string processors;
	bool feasible;
};

///
/// Class containing information on the population and statistics
///

class DataSet {
public:
	///
	/// Vector containing the informations about the individuals of the population
	/// (considering all the objective functions, K>2 case)
	///
	vector<IndividualInfo> individuals;
	///
	/// Vector containing the individuals that compose the Pareto Front (considering
	/// all the objective functions)
	///
	vector<IndividualInfo> paretoFront;
	///
	/// Vector containing the informations about the individuals of the population
	/// (considering 2 objective functions, K=2 case)
	///
	vector <IndividualInfo2D> datapoints;
	///
	/// Vector containing the individuals that compose the Pareto Front (considering
	/// 2 objective functions, K=2 case)
	///
	vector <IndividualInfo2D> front_datapoints;
	///
	/// Ideal Point of the Dataset
	///
	IndividualInfo idealPoint;
	///
	/// Nadir Point of the Dataset
	///
	IndividualInfo nadirPoint;
	///
	/// Utopian Point of the Dataset
	///
	IndividualInfo utopianPoint;
	///
	/// Constructor
	///
	DataSet(string);
	///
	/// Destructor
	///
	virtual ~DataSet();
	///
	/// Create the datapoints vector considering the objective functions passed as parameters
	///
	void createDatapoints(string, string);
	///
	/// Return the min values of the first objective function of the datapoint (K=2 case)
	///
	static float minFirstFunction(vector<IndividualInfo2D>);
	///
	/// Return the min values of the second objective function of the datapoint (K=2 case)
	///
	static float minSecondFunction(vector<IndividualInfo2D>);
	///
	/// Return the min value of the Affinity objective function
	///
	static float minTda(vector<IndividualInfo>);
	///
	/// Return the min value of the Communication objective function
	///
	static float minNtcc(vector<IndividualInfo>);
	///
	/// Return the min value of the Parallelism objective function
	///
	static float minEp(vector<IndividualInfo>);
	///
	/// Return the min value of the Load objective function
	///
	static float minLoad(vector<IndividualInfo>);
	///
	/// Return the min values of the Cost objective function
	///
	static float minCost(vector<IndividualInfo>);
	///
	/// Return the min Total cost value of a population
	///
	static float minTotalCost(vector<IndividualInfo>);
	///
	/// Return the min value of the Size objective function
	///
	static float minSize(vector<IndividualInfo>);
	///
	/// Return the min value of the Criticality objective function
	///
	static float minCrit(vector<IndividualInfo>);
	///
	/// Return the min Cost Function value of a population
	///
	static float minCf(vector<IndividualInfo>);
	///
	/// Return the max value of the first objective function of the datapoint (K=2 case)
	///
	static float maxFirstFunction(vector<IndividualInfo2D>);
	///
	/// Return the max value of the second objective function of the datapoint (K=2 case)
	///
	static float maxSecondFunction(vector<IndividualInfo2D>);
	///
	/// Return the max value of the Affinity objective function
	///
	static float maxTda(vector<IndividualInfo>);
	///
	/// Return the max value of the Communication objective function
	///
	static float maxNtcc(vector<IndividualInfo>);
	///
	/// Return the max value of the Parallelism objective function
	///
	static float maxEp(vector<IndividualInfo>);
	///
	/// Return the max value of the Load objective function
	///
	static float maxLoad(vector<IndividualInfo>);
	///
	/// Return the max value of the Cost objective function
	///
	static float maxCost(vector<IndividualInfo>);
	///
	/// Return the max Total cost value of a population
	///
	static float maxTotalCost(vector<IndividualInfo>);
	///
	/// Return the max value of the Size objective function
	///
	static float maxSize(vector<IndividualInfo>);
	///
	/// Return the max value of the Criticality objective function
	///
	static float maxCrit(vector<IndividualInfo>);
	///
	/// Return the max Cost Function value of a population
	///
	static float maxCf(vector<IndividualInfo>);

	// Compute and return average and variance values
	//float computeTdaAvg();
	//float computeNtccAvg();
	//float computeTdaVar(float);
	//float computeNtccVar(float);

	///
	/// Compute the Ideal Point of the dataset (K>2 case)
	///
	void createIdealPoint();
	///
	/// Print the Ideal Point of the dataset
	///
	void printIdealPoint();
	///
	/// Compute the Utopian Point of the dataset (K>2 case)
	///
	void createUtopianPoint(float);
	///
	/// Print the Utopian Point of the dataset
	///
	void printUtopianPoint();
	///
	/// Compute the Nadir Point of the dataset (K>2 case)
	///
	void createNadirPoint();
	///
	/// Print the Nadir Point of the dataset
	///
	void printNadirPoint();
};

#endif /* DATASET_H_ */
