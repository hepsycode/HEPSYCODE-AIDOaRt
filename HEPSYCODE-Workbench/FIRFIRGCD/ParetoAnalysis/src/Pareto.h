/*
 * ParetoPlot.h
 *
 *  Created on: 07/lug/2018
 *      Author: giuseppe
 */

#ifndef PARETO_H_
#define PARETO_H_

#include <stdlib.h>
#include "CsvUtil.h"
#include <vector>
#include "gnuplot-iostream.h"
#include "DataSet.h"

///
/// Manages the computations related to the Pareto Front for the K > 2 case and the
/// performance metrics
///
class Pareto {
public:
	///
	/// Constructor
	///
	Pareto();
	///
	/// Destructor
	///
	virtual ~Pareto();
	///
	/// Compute the Pareto Front of a given Dataset
	///
	void computeParetoFront(DataSet&);
	///
	/// Print the information of individuals belonging to the Pareto front
	///
	void printParetoFront(DataSet&);
	///
	/// Return true if the first individual dominate the second
	///
	bool dominate(IndividualInfo&, IndividualInfo&);
	///
	/// Compute the RNI metric (Unary metric)
	///
	float computeRNI(DataSet&);
	///
	/// Compute the Coverage metric regarding two Pareto Fronts (Binary metric)
	///
	float computeCoverage(DataSet&, DataSet&);
	///
	/// Compute the Maximum Spread metric regarding two Pareto Fronts (Binary metric)
	///
	float computeMaximumSpread(DataSet&, DataSet&);
};

#endif /* PARETO_H_ */
