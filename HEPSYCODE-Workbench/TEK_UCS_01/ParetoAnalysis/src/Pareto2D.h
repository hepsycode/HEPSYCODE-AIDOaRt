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

/*
 * Pareto2D.h
 *
 *  Created on: 14/lug/2018
 *      Author: giuseppe
 */

#ifndef SRC_PARETO2D_H_
#define SRC_PARETO2D_H_

#include <stdlib.h>
#include <vector>
#include "gnuplot-iostream.h"
#include "DataSet.h"

///
/// Manages the computations related to the Pareto Front for the K = 2 case
///

class Pareto2D {
public:
	///
	/// Constructor
	///
	Pareto2D();
	///
	/// Destructor
	///
	virtual ~Pareto2D();
	///
	/// Implement the Pareto dominance for the K=2 case.
	/// Return true if the first individual is dominated by the second
	///
	bool dominated(const IndividualInfo2D&,const IndividualInfo2D&);
	///
	/// Implement the Pareto weakly dominance for the K=2 case
	/// Return true if the first individual is weakly dominated by the second
	///
	bool weaklyDominated(const IndividualInfo2D&,const IndividualInfo2D&);
	///
	/// Comparison function for the sort function
	///
	static bool compare(const IndividualInfo2D &i, const IndividualInfo2D &j);

	// For each datapoint of a dataset count how many elements dominate the datapoint
	//void countDominated_2D(DataSet&);

	///
	/// Compute the datapoints that belong to the Pareto front
	///
	void computeParetoFront_2D(DataSet&);
	///
	/// Print informations about datapoints that compose the Pareto front
	///
	void printParetoFront_2D(DataSet&, string, string);

	// Performance metric computations
	///
	/// Compute the Coverage metric (binary metric)
	///
	float computeCoverage_2D(const DataSet&, const DataSet&);
	///
	/// Compute the Coverage Difference metric (binary metric)
	///
	float computeCoverageDiff_2D(const DataSet&, const DataSet&);
	///
	/// Compute the Hyper Volume Indicator (Unary metric)
	///
	float computeHVI_2D(const DataSet&);
	///
	/// Compute the Ratio of Non dominated Individuals metric (Unary metric)
	///
	float computeRNI(DataSet&);
	///
	/// Compute the Generational Distance metric (Binary metric)
	///
	float computeGD(const DataSet&, const DataSet&);
	///
	/// Compute the Inverted Generational Distance metric (binary metric)
	///
	float computeIGD(const DataSet&, const DataSet&);
	///
	/// Compute the Maximum Spread metric (binary metric)
	///
	float computeMaximumSpread(DataSet&, DataSet&);
	///
	/// Compute the Epsilon metric (binary metric)
	///
	float computeEpsilon(const DataSet&, const DataSet&);
	///
	/// Compute the Euclidean distance between two points
	///
	float distance(float x1, float x2, float y1, float y2);
};

#endif /* SRC_PARETO2D_H_ */
