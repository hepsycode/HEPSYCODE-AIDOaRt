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
 * main.cpp
 *
 *  Created on: 06/lug/2018
 *      Author: giuseppe
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "CsvUtil.h"
#include "DataSet.h"
#include "Pareto.h"
#include "Pareto2D.h"
#include "ParetoPlot.h"

using namespace std;

int main()
{

	clock_t start,end;
	double time_c;
	float coverage = 100;
	float hvi1 = 100;
	float hvi2 = 100;
	float coverageDiff = 0;
	float rni = 100;
	float gd = 0;
	float igd = 0;
	float maxSpread = 0;
	float epsilon = 0;
	string f1, f2, temp;
	// Frequency with which we have saved generations in csv file.
	const int freq = 50;
	// Max number of generation considered
	const int maxGen = 50;


//////////////////////////  Pareto p
	ParetoPlot pp;
	Pareto2D p2D;

	cout<< "Choose the first objective function to consider \n";
	cin >> f1;
	cout << "Choose the second objective function to consider \n";
	cin >> f2;

	// To set the name of the axes with gnuplot: the x axis contains the
	// "alphabetically" minor function
	if (f2 < f1)
	{
		temp = f1;
		f1 = f2;
		f2 = temp;
	}

	int count = 1;

	for (int gen = 0; gen <= maxGen; gen+=freq)
	{

		char csv[BUFSIZ];
		sprintf(csv, "%s%05d%s", "./ParetoAnalysis/PAM_Results/pareto_iteration_", gen, ".csv");

		// Creation dataset
		cout<< "Creating dataset " << count << "..." << endl;
		start=clock();
		DataSet dataset(csv);
		end=clock();
		time_c=((double)(end-start))/CLOCKS_PER_SEC;
		cout<<endl<<"Creation dataset " << count << ": " << time_c <<endl<<endl;

		// Create datapoints (for the 2D case only)
		dataset.createDatapoints(f1,f2);

		// Compute the dataset Pareto front
		start = clock();
		p2D.computeParetoFront_2D(dataset);
		end = clock();
		time_c=((double)(end-start))/CLOCKS_PER_SEC;
		cout<<endl<<"Pareto Front computation: "<< time_c <<endl<<endl;

		// Save into csv files the informations about Pareto front individuals
		CsvUtil::saveParetoFront2D(gen, dataset, f1, f2);

		// Plot the datasets
		string title_plot = "Generation "+to_string(gen);
		pp.plot2D(dataset, f1, f2, title_plot );

		// Print the Pareto fronts
		cout<< "###GENERATION " << gen << "###" <<endl;
		p2D.printParetoFront_2D(dataset, f1, f2);

		count++;
	}

/*
    // Generate metric for generations population (same GA)comparison from csv files.
	// Evaluate the evolution of a population

	cout<< "Choose the first objective function to consider \n";
	cin >> f1;
	cout << "Choose the second objective function to consider \n";
	cin >> f2;

	char  buf[BUFSIZ];
	sprintf(buf, "%s%s", "./ParetoAnalisi/metrics_without_elitism", ".csv");

	ofstream myfile;
	myfile.open(buf,std::ofstream::out | std::ofstream::trunc);

	myfile << "GENERATION,COVERAGE,HVI 1,HVI 2,COVERAGE_DIFF,RNI 1,RNI 2,GD,IGD,"
			"MAXIMUM SPREAD,EPSILON \n";


	for (int gen = 0; gen !=maxGen; gen+=freq)
	{
		cout << "Compute generations " << gen << "-" << gen+freq << endl;
		char  csv1[BUFSIZ];
		sprintf(csv1, "%s%05d%s", "./ParetoAnalysis/PAM_Results/pareto_iteration_", gen+freq, ".csv");

		char  csv2[BUFSIZ];
		sprintf(csv2, "%s%05d%s", "./ParetoAnalysis/PAM_Results/pareto_iteration_", gen, ".csv");

		cout<< "Creating dataset 1..." << endl;
		DataSet dataset1(csv1);
		cout << "Creating dataset 2..." << endl;
		DataSet dataset2(csv2);

		dataset1.createDatapoints(f1,f2);
		dataset2.createDatapoints(f1,f2);

		p2D.computeParetoFront_2D(dataset1);
		p2D.computeParetoFront_2D(dataset2);
		cout << endl;

		CsvUtil::saveAnalysis(1, gen, freq, myfile, dataset1, dataset2);
	}

	myfile.close();
*/


	// Generate metric for different population (different GA) comparison from csv files.
	// Evaluate the best solution from different GA
/*
	cout<< "Choose the first objective function to consider \n";
	cin >> f1;
	cout << "Choose the second objective function to consider \n";
	cin >> f2;

	char  buf[BUFSIZ];
	sprintf(buf, "%s%s", "./ParetoAnalysis/ParetoAnalisi/metrics_without_elitism_vs_with_elitism_with_rep", ".csv");

	ofstream myfile;
	myfile.open(buf,std::ofstream::out | std::ofstream::trunc);

	myfile << "GENERATION,COVERAGE,HVI 1,HVI 2,COVERAGE_DIFF,RNI 1,RNI 2,GD,IGD,"
			"MAXIMUM SPREAD,EPSILON \n";


	for (int gen = 0; gen <= maxGen; gen+=freq)
	{
		cout << "Compute generations " << gen << endl;
		char  csv1[BUFSIZ];
		sprintf(csv1, "%s%05d%s", "./ParetoAnalysis/PAM_Results/Pareto1/pareto_iteration_", gen, ".csv");
		//cout << csv1 << endl;

		char  csv2[BUFSIZ];
		sprintf(csv2, "%s%05d%s", "./ParetoAnalysis/PAM_Results/Pareto2/pareto_iteration_", gen, ".csv");
		//cout << csv2 << endl;

		cout<< "Creating dataset 1..." << endl;
		DataSet dataset1(csv1);
		cout << "Creating dataset 2..." << endl;
		DataSet dataset2(csv2);

		dataset1.createDatapoints(f1,f2);
		dataset2.createDatapoints(f1,f2);

		p2D.computeParetoFront_2D(dataset1);
		p2D.computeParetoFront_2D(dataset2);
		cout << endl;

		CsvUtil::saveAnalysis(2, gen, freq, myfile, dataset1, dataset2);
	}

	myfile.close();
*/

/*
	//###Compute and visualize metrics###
	hvi1 = p2D.computeHVI_2D(dataset1);
	hvi2 = p2D.computeHVI_2D(dataset2);
	coverage = p2D.computeCoverage_2D(dataset1, dataset2);
	rni = p2D.computeRNI(dataset1);
	gd = p2D.computeGD(dataset1, dataset2);
	igd = p2D.computeIGD(dataset1, dataset2);
	maxSpread = p2D.computeMaximumSpread(dataset1, dataset2);
	epsilon = p2D.computeEpsilon(dataset2, dataset1);

	cout << "COVERAGE: " << coverage << "\n";
	cout << "HYPER VOLUME INDICATOR (dataset1): " << hvi1 << "\n";
	cout << "HYPER VOLUME INDICATOR (dataset2): " << hvi2 << "\n";
	coverageDiff = p2D.computeCoverageDiff_2D(dataset1, dataset2);
	cout << "COVERAGE DIFFERENCE D(dataset1, dataset2) = " << coverageDiff << "\n";
	coverageDiff = p2D.computeCoverageDiff_2D(dataset2, dataset1);
	cout << "COVERAGE DIFFERENCE D(dataset2, dataset1) = " << coverageDiff << "\n";
	cout << "RNI dataset1: " << rni << "\n";
	cout << "GENERATIONAL DISTANCE: " << gd << "\n";
	cout << "INVERTED GENERATIONAL DISTANCE: " << igd << "\n";
	cout << "MAXIMUM SPREAD: " << maxSpread << "\n";
	cout << "EPSILON INDICATOR: " << epsilon << "\n";
*/
	//dataset1.printIdealPoint();
	//dataset1.printUtopianPoint();
	//dataset1.printNadirPoint();

#if _WIN32
	system("pause");
#endif
}

