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
