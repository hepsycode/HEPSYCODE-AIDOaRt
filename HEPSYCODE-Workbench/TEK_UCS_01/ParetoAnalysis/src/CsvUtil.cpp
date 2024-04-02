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
 * CsvUtil.cpp
 *
 *  Created on: 06/lug/2018
 *      Author: giuseppe
 */

#include "CsvUtil.h"
#include "Pareto2D.h"
#include <fstream>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

// Parse a record of the csv file passed as a parameter and inserts the info in the
// struct, returning it
struct IndividualInfo CsvUtil::parseData(string record, int id) {

	struct IndividualInfo info;

	// Tokanizer and iterator to parse the record
	tokenizer<escaped_list_separator<char> > tk(record, escaped_list_separator<char>('\\', ',', '\"'));
	tokenizer<escaped_list_separator<char> >::iterator i = tk.begin();

	//Populate the struct with the information about the individual
	info.id = id;
	info.tda = atof((*i).c_str());
	i++;
	info.ntcc = atof((*i).c_str());
	i++;
	info.ep = atof((*i).c_str());
	i++;
	info.load = atof((*i).c_str());
	i++;
	info.cost = atof((*i).c_str());
	i++;
	info.totalCost = atof((*i).c_str());
	i++;
	info.energy = atof((*i).c_str());
	i++;
	info.energyTC = atof((*i).c_str());
	i++;
	info.cf = atof((*i).c_str());
	i++;
	info.processes = (*i).c_str();
	i++;
	info.processors = (*i).c_str();
	info.dominated = 0;
	info.isDominated = false;

	return info;
}

// Create a vector with all the info regarding the individuals of the population taken
// from a csv file
vector<struct IndividualInfo> CsvUtil::parseAllData(string csv_file){

	vector<struct IndividualInfo> infoVec;
	fstream csvFile(csv_file,ios::in);
	string record;
	int id = 1;
	// The first record of csv file contain titles; don't consider it
	getline(csvFile,record);
	while (getline(csvFile,record)) {
		infoVec.push_back(parseData(record, id));
		id++;
	}
	return infoVec;
}

// Create a csv file to store information about performance metrics applied to compare
// different Pareto front
void CsvUtil::saveAnalysis(int sel, int gen, int freq, ofstream &myfile, DataSet &ds1, DataSet &ds2)
{
	Pareto2D p2D;

	// Compute the metrics
	float hvi1 = p2D.computeHVI_2D(ds1);
	float hvi2 = p2D.computeHVI_2D(ds2);
	float coverage = p2D.computeCoverage_2D(ds1, ds2);
	float rni1 = p2D.computeRNI(ds1);
	float rni2 = p2D.computeRNI(ds2);
	float gd = p2D.computeGD(ds1, ds2);
	float igd = p2D.computeIGD(ds1, ds2);
	float maxSpread = p2D.computeMaximumSpread(ds1, ds2);
	float epsilon = p2D.computeEpsilon(ds2, ds1);
	float coverageDiff = p2D.computeCoverageDiff_2D(ds1, ds2);

	//char  buf[BUFSIZ];
	//sprintf(buf, "%s%s", "./ParetoAnalisi/pareto_analysis", ".csv");

	string text_value;

	//ofstream myfile;

	//myfile.open(buf,std::ofstream::out | std::ofstream::trunc);
/*
	myfile << "GENERATION,COVERAGE,HVI 1,HVI 2,COVERAGE_DIFF,RNI 1,RNI 2,GD,IGD,"
			"MAXIMUM SPREAD,EPSILON \n";
*/
	// Save the metrics

	// The sel parameters is only for differentiate two cases of comparison and so the
	// respective layout of csv file
	if (sel == 1)
	{
		text_value = to_string(gen) + "-" + to_string(gen+freq) + ",";
		myfile << text_value;
	}
	else if (sel ==2 )
	{
		text_value = to_string(gen) + ",";
		myfile << text_value;
	}

	text_value = to_string(coverage) +",";
	myfile << text_value;

	text_value = to_string(hvi1) +",";
	myfile << text_value;

	text_value = to_string(hvi2) +",";
	myfile << text_value;

	text_value = to_string(coverageDiff) +",";
	myfile << text_value;

	text_value = to_string(rni1) +",";
	myfile << text_value;

	text_value = to_string(rni2) +",";
	myfile << text_value;

	text_value = to_string(gd) +",";
	myfile << text_value;

	text_value = to_string(igd) +",";
	myfile << text_value;

	text_value = to_string(maxSpread) +",";
	myfile << text_value;

	text_value = to_string(epsilon);
	myfile << text_value;

	text_value = ",\n";
	myfile << text_value;

	//myfile.close();
}

// Create a csv file to store information about Pareto front individuals
void  CsvUtil::saveParetoFront2D(int gen, DataSet &ds, string f1, string f2)
{
	int id = 1;
	vector<IndividualInfo2D>::iterator it;
	char  buf[BUFSIZ];
	sprintf(buf, "%s%05d%s", "./ParetoAnalysis/ParetoIndividuals/with_elitism_with_rep/paretoFront_iteration_", gen, ".csv");

	string text_value;

	ofstream myfile;

	myfile.open(buf,std::ofstream::out | std::ofstream::trunc);

	myfile << "ID,ID Ind,"+f1+","+f2+",CF,Processors,\n";

	for(it = ds.front_datapoints.begin(); it != ds.front_datapoints.end(); it++)
	{
		text_value = to_string(id) +",";
		myfile << text_value;

		text_value = to_string((*it).id) +",";
		myfile << text_value;

		text_value = to_string((*it).f1) +",";
		myfile << text_value;

		text_value = to_string((*it).f2) +",";
		myfile << text_value;

		text_value = to_string((*it).cf) +",";
		myfile << text_value;

		text_value = ((*it).processors);
		myfile << text_value;

		text_value = ",\n";
		myfile << text_value;

		id++;
	}

	myfile.close();

}


