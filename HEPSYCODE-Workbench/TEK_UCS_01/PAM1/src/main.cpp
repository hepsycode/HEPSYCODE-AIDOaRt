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

//============================================================================
// Name        : PAM1.cpp
// Authors     : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Main
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "population.h"
#include "specification.h"

using namespace std;

int main(){

	// Variables for temporal information
	clock_t start,end;
	double time_c, time_i, time_final;
	unsigned long i=0;

	// Frequency with which store information about the population into csv files
	int freq = 50;

	// Create the specification
	specification mySpec;

	start=clock();

	// Create initial population
	population myPop( &mySpec);

	end=clock();
	time_c=((double)(end-start))/CLOCKS_PER_SEC;

	cout<<endl<<"Creation Time(Cpu time): "<< time_c << " numIndividuals:" << myPop.numInd << " numIndividualsMax:" << myPop.numIndMax << endl;

	#if _WIN32
	    system("pause");
	#endif

	// Delete the last mapping xml file
	myPop.deleteXml();

	start=clock();

    // Initialize csv file for statistics storage
    ofstream myStatFile;
	if(mySpec.exe_num != 0){
		myStatFile.open ("./PAM1/PAM1_Results/Exe01_PopStat.csv",std::ofstream::out | std::ofstream::trunc);
		myStatFile << "GENERATION,POP_AVG_CF,POP_STANDARD_DEVIATION,POP_SIZE,FEASIBLE_AVG_CF,"
					"FEASIBLE_STANDARD_DEVIATION,POP_SIZE_FEASIBLE,EXECUTION_TIME,POP_AVG_TDA,FEASIBLE_AVG_TDA,w_TDA,"
					"POP_AVG_NTCC,FEASIBLE_AVG_NTCC,w_NTCC,POP_AVG_EP,FEASIBLE_AVG_EP,w_EP,"
					"POP_AVG_COST,FEASIBLE_AVG_COST,w_COST,POP_AVG_LOAD,FEASIBLE_AVG_LOAD,w_LOAD,"
					"POP_AVG_SIZESW,FEASIBLE_AVG_SIZESW,w_SIZESW,POP_AVG_ENERGY,FEASIBLE_AVG_ENERGY,"
					"w_ENERGY,POP_AVG_ENERGYTC,FEASIBLE_AVG_ENERGYTC,w_ENERGYTC,\n";
	}else{
		myStatFile.open ("./PAM1/PAM1_Results/Exe02_PopStat.csv",std::ofstream::out | std::ofstream::trunc);
		myStatFile << "GENERATION,POP_AVG_CF,POP_STANDARD_DEVIATION,POP_SIZE,FEASIBLE_AVG_CF,"
					"FEASIBLE_STANDARD_DEVIATION,POP_SIZE_FEASIBLE,EXECUTION_TIME,POP_AVG_TDA,FEASIBLE_AVG_TDA,w_TDA,"
					"POP_AVG_NTCC,FEASIBLE_AVG_NTCC,w_NTCC,POP_AVG_EP,FEASIBLE_AVG_EP,w_EP,"
					"POP_AVG_COST,FEASIBLE_AVG_COST,w_COST,POP_AVG_LOAD,FEASIBLE_AVG_LOAD,w_LOAD,"
					"POP_AVG_SIZESW,FEASIBLE_AVG_SIZESW,w_SIZESW,POP_AVG_ENERGY,FEASIBLE_AVG_ENERGY,"
					"w_ENERGY,POP_AVG_ENERGYTC,FEASIBLE_AVG_ENERGYTC,w_ENERGYTC,\n";
	}

	// Genetic algorithm in action
	for(i=0; i<=mySpec.numGen; i++)
	{

	    myPop.evaluation();

	    end=clock();
	    time_i =((double)(end-start))/CLOCKS_PER_SEC;

		cout << "Iteration: " << i <<" Population: " << myPop.numInd << " Execution Time(Cpu time): "<< time_i << " #Feasible: " << myPop.numFeasibleSol <<endl;

		// Save Best Individuals
	    if(mySpec.elitismCheck != 0){
	    	myPop.updateElite();
	    }

		//Save information about initial population into csv file
		myPop.printMemStat(i, myStatFile, time_i);
		myPop.memPop(i,freq);

	    myPop.crossover(mySpec.birthRate);
	    myPop.mutation(mySpec.radRate);
	    myPop.purge(mySpec.deathRate);

	    // Re-introduce Individuals into population
	    if(mySpec.elitismCheck != 0){
		    myPop.elitismEV();
	    }

	    if(mySpec.equalizationCheck != 0){
			myPop.weightsEqualization(); // For weight equalization
		}

	}

	// Save information about final population statistics into csv file
	myStatFile.close();

	time_final= time_c + time_i;
	cout <<endl<<"Final Execution Time(Cpu time): "<< time_final <<endl;

	// Create the new mapping xml file
	myPop.mappingXml( &mySpec );

	#if _WIN32
	    system("pause");
	#endif
}
