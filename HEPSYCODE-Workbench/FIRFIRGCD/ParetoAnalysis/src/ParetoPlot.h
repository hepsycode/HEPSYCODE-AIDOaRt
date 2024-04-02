/*
 * ParetoPlot.h
 *
 *  Created on: 14/lug/2018
 *      Author: giuseppe
 */

#ifndef SRC_PARETOPLOT_H_
#define SRC_PARETOPLOT_H_

#include <stdlib.h>
#include "CsvUtil.h"
#include <vector>
#include "gnuplot-iostream.h"
#include "DataSet.h"

///
/// Class for the plot operations. Gnuplot is used
///

class ParetoPlot {
public:

	// Plot a specific 2D Pareto (in this case TDA-NTCC) front for the K>2 case
	//void plot_Tda_Ntcc(DataSet&);

	///
	/// Plot a 2D Pareto front for the K=2 case; the string parameters represent the two
	/// objective functions considered
	///
	void plot2D(DataSet&, string, string, string);
};

#endif /* SRC_PARETOPLOT_H_ */
