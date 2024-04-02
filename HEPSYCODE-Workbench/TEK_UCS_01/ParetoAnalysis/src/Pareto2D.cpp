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
 * Pareto2D.cpp
 *
 *  Created on: 14/lug/2018
 *      Author: giuseppe
 */

#include "Pareto2D.h"
#include <algorithm>
#include <string>
#include "DataSet.h"

// Implement the Pareto dominance for the K=2 case
// f1 is the value ​​of the first objective function for the individuals
// considered; f2 is the value ​​of the second objective function
bool Pareto2D::dominated(const IndividualInfo2D &ind1, const IndividualInfo2D &ind2)
{
	if ((ind1.f1 > ind2.f1) && (ind1.f2 > ind2.f2))
		return true;
	else if ((ind1.f1 == ind2.f1) && (ind1.f2 > ind2.f2))
		return true;
	else if ((ind1.f1 > ind2.f1) && (ind1.f2 == ind2.f2))
		return true;

	return false;
}

bool Pareto2D::weaklyDominated(const IndividualInfo2D &ind1, const IndividualInfo2D &ind2)
{
	if ((ind1.f1 >= ind2.f1) && (ind1.f2 >= ind2.f2))
		return true;

	return false;
}

/*
//Aggiorna il dataset con i dati sulla pareto dominance
//Per ora considero solo il caso 2D con le funzioni costo tda e ntcc
//Il calcolo è molto lento, si potrebbe velocizzare uscendo dal ciclo appena ci si accorge che
//un punto è dominato, ma nn so se possa servire in futuro per altri calcoli sulle performance
void Pareto2D::countDominated_2D(DataSet &dataset){

	vector<IndividuoInfo>::iterator it1;
	vector<IndividuoInfo>::iterator it2;
	int control = 0;
	for (it1 = (dataset.individui).begin(); it1 != (dataset.individui).end(); it1++){
		cout<< control++;
		cout<< "\n";
		for (it2 = (dataset.individui).begin(); it2 != (dataset.individui).end(); it2++){
			if ((*it1).id != (*it2).id) //si controlla se nn è lo stesso individuo
			{
				//Se l'individuo puntato da it1 è dominato dall'individuo puntato da it2 incrementiamo
				//il numero di punti che dominano it1
				if (dominated((*it1).tda,(*it2).tda,(*it1).ntcc,(*it2).ntcc))
					((*it1).dominated)++;
			}
		}
	}
}
*/


// Comparison function for the sort function
bool Pareto2D::compare (const IndividualInfo2D &i, const IndividualInfo2D &j) {
	if (i.f1 != j.f1)
		return (i.f1 < j.f1);
	return (i.f2 < j.f2);
}


// Compute the solutions that are part of the Pareto front and place them in an array
// of the DataSet class. This implementation refers to the 2D case, in which we consider
// only two objective functions (the datapoints values) in the computation
// Also puts "doubles" in the Front
void Pareto2D::computeParetoFront_2D(DataSet &dataset){

	vector<IndividualInfo2D> front;
	// Pointer to the individuals of the population under test
	vector<IndividualInfo2D>::const_iterator it;
	// Pointer to the individuals belonging to the Pareto Front computed
	vector<IndividualInfo2D>::const_iterator front_it;
	vector<IndividualInfo2D>::iterator it_first;
	int control = 0;

	// True if a element is dominated
	bool flag = false;

	// True if the Pareto Front in empty
	bool empty = false;

	sort((dataset.datapoints).begin(), (dataset.datapoints).end(), compare);
	// Used to fill the Pareto Front in case it was empty
	it_first = (dataset.datapoints).begin();
	front.push_back(*it_first);
	cout << "front size: " << front.size() << "\n";

	for (it = (dataset.datapoints).begin() + 1; it != (dataset.datapoints).end(); it++){
		//cout << "control: " << control << "\n";
		front_it = front.begin();
		flag = false;
		// Let's check immediately if the elements already present in the front dominate
		// the individual pointed by it (one is enough) and in this case we do not
		// consider it in the calculation of the front
		for (front_it = front.begin(); front_it != front.end(); front_it++){
			if (dominated(*it, *front_it))
			{
				flag = true;
				break;
			}
		}

		if (!flag)
		{
			// We are at the point where we have a element that is not dominated by any
			// element of the front.
			// Let's go then to check if it dominates the elements present in the front
			// and in this case we delete them
			for (front_it = front.begin(); front_it != front.end(); front_it++){
				if (dominated(*front_it, *it))
				{
					front.erase(front_it);
					cout << "Pareto front individual deleted: \n";
					cout <<"Front size: " << front.size() << "\n";
				}
				if (front_it == front.end()) break;
			}
			// To avoid the case in which the front could be empty at the first iterations
			// and the later control would not produce results
			if (front.empty())
			{
				// the Pareto front must have at least one element to make comparisons
				front.push_back(*it_first);
				empty = true;
			}

			// We add the elements that are not dominated by the elements already present
			// in the front
			for (front_it = front.begin(); front_it != front.end(); front_it++){
				if (!dominated(*it, *front_it))
				{
					front.push_back(*it);
					if (empty)
					{
						front.erase(front.begin());
						empty = false;
					}
					cout << "Individual added to the Pareto front\n";
					cout <<"Front size: " << front.size() <<"\n";
					break;
				}
			}
		}
		control++;
	}
	sort(front.begin(), front.end(),compare);
	dataset.front_datapoints = front;
}

// The metric covarage is defined for two sets of design points and describe the number of
// point that are dominated. A covarage C(A,B) = 1 means that all elements of B are weakly
// dominated by at least one element of the set A; C=0 indicates that no elements of the
// set B are weakly dominated by an element of A
float Pareto2D::computeCoverage_2D(const DataSet &ds1, const DataSet &ds2){

	bool isDominated = false;
	int countDominated = 0;
	vector<IndividualInfo2D>::const_iterator it1;
	vector<IndividualInfo2D>::const_iterator it2;

	for (it1 = (ds2.front_datapoints).begin(); it1 != (ds2.front_datapoints).end(); it1++)
	{
		for (it2 = (ds1.front_datapoints).begin(); it2 != (ds1.front_datapoints).end(); it2++)
		{
			// If the individual pointed by it1 is weakly dominated by an individual of ds1
			if (weaklyDominated(*it1,*it2))
				isDominated = true;
		}
		// Increment the elements dominated by ds1
		if (isDominated == true) countDominated++;
		isDominated = false;
	}

	if (countDominated == 0)
		return 0;
	else
		return (float)countDominated/(float)(ds2.front_datapoints).size();
}

// Useful when coverage metrics do not provide useful information
// Difference between HyperVolumes
float Pareto2D::computeCoverageDiff_2D(const DataSet &ds1, const DataSet &ds2){

	float hvi1 = computeHVI_2D(ds1);
	float hvi2 = computeHVI_2D(ds2);

	float covDiff = hvi1 - hvi2;

	//if (covDiff > 0) cout <<"The first Pareto Front dominates the second \n";
	//else if (covDiff < 0) cout << "The second Pareto Front dominates the first \n";
	//else cout << "Coverage Difference = 0, nothing can be said a priori \n";

	return covDiff;
}

// The hypervolume (HV), also known as S metric, hyper-area or Lebesgue measure, is an
// unary metric that measures the size of the objective space covered by an approximation
// set. A reference point must be used to calculate the mentioned covered space. HV
// considers all three aspects: accuracy, diversity and cardinality, being the only unary
// metric with this capability.
// Here we think in 2D
// The procedure in simple terms is the following: we calculate the maximum area of ​​the
// rectangle that contains "the area of ​​the HVI" and gradually remove the "piece" in excess
// As a parameter, we pass the dataset that will contain the Pareto Front vector already
// ordered
float Pareto2D::computeHVI_2D(const DataSet &ds){

	// Initialize the reference point z
	float z_x = 1;
	float z_y = 1;
	float A_max = 0;// at the end of the computation it will contain the value of HVI

	vector<IndividualInfo2D>::const_iterator it1 = (ds.front_datapoints).begin();
	vector<IndividualInfo2D>::const_iterator it2 = (ds.front_datapoints).end() - 1;

	// base and height calculation for the max area
	float b_max = z_x - (*it1).f1;
	float a_max = z_y - (*it2).f2;
	if (b_max == 0) b_max = z_x;
	if (a_max == 0) a_max = z_y;
	A_max = b_max * a_max;

	// variables for the calculation of the area of ​​the "piece" to be eliminated
	float b_diff = 0;
	float a_diff = 0;
	float A_diff = 0;
	// to calculate the base of the "pieces" to remove we must always keep as a reference
	// for the abscissa the x of the first element
	float x_diff = (*it1).f1;
	// Cyclically remove a "piece at a time"
	for (it1 = (ds.front_datapoints).begin(); it1 != (ds.front_datapoints).end() - 1; it1++ ){
		it2 = it1 + 1;
		b_diff = (*it2).f1 - x_diff;
		a_diff = (*it1).f2 - (*it2).f2;
		A_diff = b_diff * a_diff;
		A_max -= A_diff;
	}

	return A_max;
}


// Ratio of Non dominated Individuals (RNI)
// RNI is a significant measure in  that  it  checks  the  proportion  of non dominated
// individuals in population
float Pareto2D::computeRNI(DataSet &ds){

	float rni = (float)ds.front_datapoints.size() / (float)ds.datapoints.size();
	return rni;
}



// Compute the Euclidean distance between two points
float Pareto2D::distance(float x1, float x2, float y1, float y2){

	float x_dist = 0;
	float y_dist = 0;

	x_dist = pow(x1-x2, 2);
	y_dist = pow(y1-y2, 2);

	return sqrt(x_dist + y_dist);
}


// Generational Distance (GD) metric
// Metrics Measuring the Closeness of the Solutions to the True Pareto Front (or a reference
// Pareto front) - Convergence
// Is a measure representing how “far” the approximation front (contained into dataset ds)
// is from the true Pareto front (pf parameter).
// Lower value of GD represents a better performance
float Pareto2D::computeGD(const DataSet &pf, const DataSet &ds){

	float dist = 0;
	float min_dist;
	float tot_dist = 0;
	vector<IndividualInfo2D>::const_iterator it1;
	vector<IndividualInfo2D>::const_iterator it2;

	// For each Pareto front's element that we are evaluating
	for (it1 = (ds.front_datapoints).begin(); it1 != (ds.front_datapoints).end(); it1++){
		min_dist = 99999;

		// The minimum distance from the reference Pareto front (pf) is found
		for (it2 = pf.front_datapoints.begin(); it2 != pf.front_datapoints.end(); it2++){
			dist = distance((*it1).f1, (*it2).f1, (*it1).f2, (*it2).f2);
			if (dist < min_dist) min_dist = dist;
		}

		tot_dist += pow(min_dist, 2);
	}

	return (sqrt(tot_dist/(ds.front_datapoints).size()));
}


// Inverted Generational Distance (IGD)
// This  metric  measures  both  convergence  and  diversity
// To have a low value of IGD, the set should be close to true PF (or reference Pareto front
// and cannot miss any part of the whole true PF
float Pareto2D::computeIGD(const DataSet &pf, const DataSet &ds){

	float dist = 0;
	float min_dist;
	float tot_dist = 0;
	vector<IndividualInfo2D>::const_iterator it1;
	vector<IndividualInfo2D>::const_iterator it2;

	// For each reference Pareto front's element
	for (it1 = pf.front_datapoints.begin(); it1 != pf.front_datapoints.end(); it1++){
		min_dist = 99999;
		// The minimum distance from the Pareto front that we are evaluating (ds) is found)
		for (it2 = (ds.front_datapoints).begin(); it2 != (ds.front_datapoints).end(); it2++){
			dist = distance((*it1).f1, (*it2).f1, (*it1).f2, (*it2).f2);
			if (dist < min_dist) min_dist = dist;
		}

		tot_dist += min_dist;
	}

	return (tot_dist/pf.front_datapoints.size());
}

// Metric Concerning Spread of the Solutions
// A higher value of MS reflects that a larger area of the PF true is covered by the PF
// known (ds)
float Pareto2D::computeMaximumSpread(DataSet &pf, DataSet &ds ){

	float minFirstPareto = DataSet::minFirstFunction(pf.front_datapoints);
	float minSecondPareto = DataSet::minSecondFunction(pf.front_datapoints);
	float maxFirstPareto = DataSet::maxFirstFunction(pf.front_datapoints);
	float maxSecondPareto = DataSet::maxSecondFunction(pf.front_datapoints);
	float minFirst = min(minFirstPareto, DataSet::minFirstFunction(ds.front_datapoints));
	float minSecond = min(minSecondPareto, DataSet::minSecondFunction(ds.front_datapoints));
	float maxFirst = max(maxFirstPareto, DataSet::maxFirstFunction(ds.front_datapoints));
	float maxSecond = max(maxSecondPareto, DataSet::maxSecondFunction(ds.front_datapoints));

	float sum1 = pow((minFirst-maxFirst)/(maxFirstPareto-minFirstPareto),2);
	float sum2 = pow((minSecond-maxSecond)/(maxSecondPareto-minSecondPareto),2);

	return sqrt((sum1 + sum2)/2);
}

// Binary indicator Epsilon
// Compute the minimal translation to apply on the set ds1 so that every solution in set
// ds2 is dominated by at least one solution in ds1
float Pareto2D::computeEpsilon(const DataSet& ds1, const DataSet& ds2){

	float dist = 0;
	float min_dist;
	float epsilon = 0;
	vector<float> min_distances;

	vector<IndividualInfo2D>::const_iterator it1;
	vector<IndividualInfo2D>::const_iterator it2;
	vector<float>::iterator it;

	//For each point of the reference Pareto front
	for (it1 = ds1.front_datapoints.begin(); it1 != ds1.front_datapoints.end(); it1++){
		min_dist = 99999;
		// For each point of ds1, it is checked whether it is dominated by the points of
		// ds2. In this case the distance is calculated and the minimum distance from ds2
		// is kept. If the point of ds1 is not dominated by ds2 it should not be taken into
		// account in the calculation
		for (it2 = (ds2.front_datapoints).begin(); it2 != (ds2.front_datapoints).end(); it2++){
			if (dominated(*it1,*it2))
			{
				dist = distance((*it1).f1, (*it2).f1, (*it1).f2, (*it2).f2);
				if (dist < min_dist) min_dist = dist;
			}
		}
		if (min_dist != 99999) min_distances.push_back(min_dist);
	}
	// Now we have to take the maximum distance between the minimum found, which will
	// correspond to the minimum translation to do on ds1 to ensure that each point of ds2
	// is dominated from at least one of ds1
	if (!min_distances.empty())
	{
		epsilon = min_distances.front();
		for (it = min_distances.begin(); it != min_distances.end(); it++){
			if ((*it) > epsilon) epsilon = (*it);
		}
	}

	return epsilon;
}


void Pareto2D::printParetoFront_2D(DataSet &dataset, string f1, string f2){

	vector<IndividualInfo2D>::iterator it;
	int num = 1;

	cout << "######INFO PARETO FRONT INDIVIDUALS######" << "\n";
	cout << "\n";
	cout << "Number of Pareto front individuals: " << (dataset.front_datapoints).size();
	cout << "\n";

	for(it = (dataset.front_datapoints).begin(); it != (dataset.front_datapoints).end(); it++)
	{
		cout << "INDIVIDUAL n°: " << (*it).id << "\n";
		cout << f1 <<": " << (*it).f1 << "\n";
		cout << f2 <<": " << (*it).f2 << "\n";
		cout << "Cost function: " << (*it).cf  << endl;
		cout << "Processors: " << (*it).processors << endl;
		cout << "\n";
		cout << "\n";
		num++;
	}
}


Pareto2D::Pareto2D() {
	// TODO Auto-generated constructor stub

}

Pareto2D::~Pareto2D() {
	// TODO Auto-generated destructor stub
}

