/*
 * CsvUtil.h
 *
 *  Created on: 06/lug/2018
 *      Author: giuseppe
 */

#ifndef CSVUTIL_H_
#define CSVUTIL_H_

#include "DataSet.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>


using namespace std;

///
/// Class used to manipulate csv files
///

class CsvUtil {

public:

	///
	/// Parse a record of the csv file passed as a parameter and inserts the info in the
	/// struct, returning it
	static struct IndividualInfo parseData(string iStr, int id);
	///
	/// Create a vector with all the info regarding the individuals of the population taken
	/// from a csv file
	///
	static vector<struct IndividualInfo> parseAllData(string csv_file);
	///
	/// Create a csv file to store information about performance metrics applied to compare
	/// different Pareto front
	static void saveAnalysis(int, int, int, ofstream&, DataSet&, DataSet&);
	///
	/// Create a csv file to store information about Pareto front individuals
	///
	static void saveParetoFront2D(int, DataSet&, string, string);
};

#endif /* CSVUTIL_H_ */
