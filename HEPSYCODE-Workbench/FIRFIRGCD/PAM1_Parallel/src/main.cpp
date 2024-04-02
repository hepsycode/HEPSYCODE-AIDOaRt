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
#include <omp.h>

#include "population.h"
#include "specification.h"

using namespace std;

int main()
{
	// Variables for temporal information
	clock_t start,end;
	double ompStart, ompEnd;
	double time_c, time_i, time_final, time_c_Omp, time_f_Omp, time_i_Omp;

	// frequency with which store information about the population into csv files
	int freq = 25;

	// Create the specification
	specification mySpec(1);

	start=clock();
	ompStart = omp_get_wtime();

	// Create initial population
	population myPop( &mySpec );

	end=clock();
	ompEnd = omp_get_wtime();
	time_c=((double)(end-start))/CLOCKS_PER_SEC;
	time_c_Omp = ompEnd-ompStart;
	cout<<endl<<"Creation Time(Cpu time): "<< time_c <<endl;
	cout<<endl<<"Creation Time(Walltime): "<< time_c_Omp <<endl<<endl;

	cout << endl << "numPart:" << myPop.numPart << endl;
	cout<< "numPartMax:" << myPop.numPartMax;
	cout<<endl;

	// Delete the last mapping xml file
	myPop.deleteXml();
	     
	start=clock();
	ompStart = omp_get_wtime();
	// Evaluation of initial population
	//myPop.evaluation();
	myPop.parallel_evaluation();

    end=clock();
    ompEnd = omp_get_wtime();
    time_i=((double)(end-start))/CLOCKS_PER_SEC;
    time_i_Omp = ompEnd-ompStart;

    unsigned long i=0;

    // Initialize csv file for statistics storage
    ofstream myStatFile;
    myStatFile.open ("./PAM1_Parallel/PopulationStatistics/error_estimation_without_elitism.csv",std::ofstream::out | std::ofstream::app);
    myStatFile << "GENERATION,POP_AVG_CF,POP_STANDARD_DEVIATION,FEASIBLE_AVG_CF,"
    		"FEASIBLE_STANDARD_DEVIATION,EXECUTION_TIME,\n";

    //Save information about initial population into csv file
    myPop.memPop(i,freq);
    //myPop.memWeightedPop(i,freq);
	cout << endl << "Iteration: " << 0 <<" Population: " << myPop.numPart << " Execution Time(Cpu time): "<< time_i <<endl;
	cout << endl << "Iteration: " << 0 <<" Population: " << myPop.numPart << " Execution Time (Walltime): "<< ompEnd-ompStart <<endl;
	// Genetic algorithm in action
	for(i=0; i<mySpec.generations; i++)
	{
	    myPop.printMemStat(i, myStatFile, time_i_Omp);
	    myPop.crossover(mySpec.birthRate);
	    myPop.mutation(mySpec.radRate);
	    //myPop.evaluation();
	    myPop.parallel_evaluation();
	    //myPop.updateElite();
	    myPop.purge(mySpec.deathRate);
	    //myPop.elitismEV();
	    //myPop.weightsEqualization();

	    end=clock();
	    ompEnd = omp_get_wtime();
	    time_i =((double)(end-start))/CLOCKS_PER_SEC;
	    time_i_Omp = ompEnd-ompStart;
		cout << "Iteration: " << i + 1 <<" Population: " << myPop.numPart << " Execution Time(Cpu time): "<< time_i << " #Feasible: " << myPop.feasibleSol <<endl;
		cout << "Iteration: " << i + 1 <<" Population: " << myPop.numPart << " Execution Time(Walltime): "<< ompEnd-ompStart << " #Feasible: " << myPop.feasibleSol <<endl <<endl;

		//Save information about population every freq generations into csv file
		myPop.memPop(i,freq);
		//myPop.memWeightedPop(i,freq);

	}

	//Save information about final population into csv file
	myPop.memPop(i,freq);
	//myPop.memWeightedPop(i,freq);
	// Save information about final population statistics into csv file
	myPop.printMemStat(i, myStatFile, time_i_Omp);
	myStatFile.close();

	cout << "Iteration: " << i + 1 <<" Population: " << myPop.numPart << " Execution Time(Cpu time): "<< time_i <<endl;
	cout << "Iteration: " << i + 1 <<" Population: " << myPop.numPart << " Execution Time(Walltime): "<< ompEnd-ompStart <<endl;

	time_final= time_c + time_i;
	time_f_Omp = ompEnd-ompStart+time_c_Omp;
	cout <<endl<<"Final Execution Time(Cpu time): "<< time_final <<endl;
	cout <<endl<<"Final Execution Time(Walltime): "<< time_f_Omp <<endl<<endl;
	// Create the new mapping xml file
	// myPop.mappingXml( &mySpec );

	#if _WIN32
	    system("pause");
	#endif
}
