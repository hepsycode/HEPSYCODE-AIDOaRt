/*
 * ParetoPlot.cpp
 *
 *  Created on: 07/lug/2018
 *      Author: giuseppe
 */

#include "Pareto.h"
#include "DataSet.h"
#include <algorithm>
#include <string>

// Return true if the first individual dominate the second
// At the moment, we don't consider size and crit
bool Pareto::dominate(IndividualInfo &ind1, IndividualInfo &ind2){

	// Implementation of Pareto dominance
	if ((ind1.cost <= ind2.cost) && (ind1.ep <= ind2.ep) && (ind1.load <= ind2.load) &&
				(ind1.ntcc <= ind2.ntcc) && (ind1.tda <= ind2.tda))
		{
			if ((ind1.cost < ind2.cost) || (ind1.ep < ind2.ep) || (ind1.load < ind2.load) ||
				(ind1.ntcc < ind2.ntcc) || (ind1.tda < ind2.tda))
			{
				ind2.isDominated = true;
				return true;
			}
			else return false;

		}
		else return false;
}

// Comparison function for the sort function
bool compare (const IndividualInfo &i, const IndividualInfo &j) {
	// We can choose any objective function
	return (i.ntcc < j.ntcc);
}

// Case K-functions objective, or more precisely 5 objective functions (the function
// dominate does not take into account the size and crit objective functions)
void Pareto::computeParetoFront(DataSet &dataset){

	vector<IndividualInfo> front;
	vector<IndividualInfo>::iterator it;
	vector<IndividualInfo>::iterator front_it;
	vector<IndividualInfo>::iterator first_it;
	int control = 0;

	// True if a element is dominated
	bool flag = false;

	// True if the Pareto Front in empty
	bool empty;

	sort((dataset.individuals).begin(), (dataset.individuals).end(), compare);

	// Used to fill the Pareto Front in case it was empty
	first_it = (dataset.individuals).begin();

	front.push_back(*first_it);
	cout << "front size: " << front.size() << "\n";

	for (it = (dataset.individuals).begin() + 1; it != (dataset.individuals).end(); it++){
		cout << "control: " << control << "\n";
		front_it = front.begin();
		flag = false;
		// Let's check immediately if the elements already present in the front dominate
		// the individual pointed by it (one is enough) and in this case we do not
		// consider it in the calculation of the front
		for (front_it = front.begin(); front_it != front.end(); front_it++){
			if (dominate(*front_it, *it))
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
				if (dominate(*it,*front_it))
				{
					front.erase(front_it);
					cout << "Pareto front individual deleted: " << (*front_it).id << "\n";
					cout <<"Front size: " << front.size() << "\n";
				}
				if (front_it == front.end()) break;
			}

			if (front.empty())
			{
				// the Pareto front must have at least one element to make comparisons
				front.push_back(*first_it);
				empty = true;
			}

			// We add the elements that are not dominated by the elements already present
			// in the front
			for (front_it = front.begin(); front_it != front.end(); front_it++){
				if (!dominate(*front_it, *it))
				{
					front.push_back(*it);
					if (empty)
					{
						front.erase(front.begin());
						empty = false;
					}
					cout << "Individual added to the Pareto front: " << (*it).id << "\n";
					cout <<"Front size: " << front.size() <<"\n";
					break;
				}
			}
		}
		control++;
	}
	sort(front.begin(), front.end(),compare);
	dataset.paretoFront = front;
}


// Ratio of Non dominated Individuals (RNI)
// RNI is a significant measure in  that  it  checks  the  proportion  of non dominated
// individuals in population
float Pareto::computeRNI(DataSet &ds){

	return ((ds.paretoFront).size() / (ds.individuals).size());
}


// The metric coverage is defined for two sets of design points and describe the number of
// point that are dominated. A coverage C(A,B) = 1 means that all elements of B are weakly
// dominated by at least one element of the set A; C=0 indicates that no elements of the
// set B are weakly dominated by an element of A
float Pareto::computeCoverage(DataSet &ds1, DataSet &ds2){

	bool isDominated = false;
	int countDominated = 0;
	vector<IndividualInfo>::iterator it1;
	vector<IndividualInfo>::iterator it2;

	for (it2 = (ds2.paretoFront).begin(); it2 != (ds2.paretoFront).end(); it2++){
		for (it1 = (ds1.paretoFront).begin(); it1 != (ds1.paretoFront).end(); it1++){
			// If the individual pointed by it2 is dominated by an individual of ds1
			if (dominate(*it1, *it2)) isDominated = true;
		}

		// Increment the elements dominated by ds1
		if (isDominated == true) countDominated++;
		isDominated = false;
	}

	if (countDominated == 0)
		return 0;
	else
		return countDominated/(ds2.paretoFront).size();
}


// Metric Concerning Spread of the Solutions
// A higher value of MS reflects that a larger area of the PF true is covered by the PF
// known (ds)
float Pareto::computeMaximumSpread(DataSet &pf, DataSet &ds ){

	float minParetoTda = DataSet::minTda(pf.paretoFront);
	float minParetoNtcc = DataSet::minNtcc(pf.paretoFront);
	float minParetoEp = DataSet::minEp(pf.paretoFront);
	float minParetoCost = DataSet::minCost(pf.paretoFront);
	float minParetoLoad = DataSet::minLoad(pf.paretoFront);
	float maxParetoTda = DataSet::maxTda(pf.paretoFront);
	float maxParetoNtcc = DataSet::maxNtcc(pf.paretoFront);
	float maxParetoEp = DataSet::maxEp(pf.paretoFront);
	float maxParetoCost = DataSet::maxCost(pf.paretoFront);
	float maxParetoLoad = DataSet::maxLoad(pf.paretoFront);

	float minTda = min(minParetoTda, DataSet::minTda(ds.paretoFront));
	float minNtcc = min(minParetoNtcc, DataSet::minNtcc(ds.paretoFront));
	float minEp = min(minParetoEp, DataSet::minEp(ds.paretoFront));
	float minCost = min(minParetoCost, DataSet::minCost(ds.paretoFront));
	float minLoad = min(minParetoLoad, DataSet::minLoad(ds.paretoFront));
	float maxTda = max(maxParetoTda, DataSet::maxTda(ds.paretoFront));
	float maxNtcc = max(maxParetoNtcc, DataSet::maxNtcc(ds.paretoFront));
	float maxEp = max(maxParetoEp, DataSet::maxEp(ds.paretoFront));
	float maxCost = max(maxParetoCost, DataSet::maxCost(ds.paretoFront));
	float maxLoad = max(maxParetoLoad, DataSet::maxLoad(ds.paretoFront));

	float sum1 = pow((minTda-maxTda)/(maxParetoTda-minParetoTda),2);
	float sum2 = pow((minNtcc-maxNtcc)/(maxParetoNtcc-minParetoNtcc),2);
	float sum3 = pow((minEp-maxEp)/(maxParetoEp-minParetoEp),2);
	float sum4 = pow((minCost-maxCost)/(maxParetoCost-minParetoCost),2);
	float sum5 = pow((minLoad-maxLoad)/(maxParetoLoad-minParetoLoad),2);

	return sqrt((sum1+sum2+sum3+sum4+sum5)/5);
}


void Pareto::printParetoFront(DataSet &dataset){

	vector<IndividualInfo>::iterator it;

	cout << "######INFO PARETO FRONT INDIVIDUALS######" << "\n";
	cout << "\n";
	cout << "Number of Pareto front individuals: " << (dataset.paretoFront).size();
	cout << "\n";

	for(it = (dataset.paretoFront).begin(); it != (dataset.paretoFront).end(); it++)
	{
		cout << "INDIVIDUAL n°: " << (*it).id << "\n";
		cout << "Partitioning: " << (*it).processors << "\n";
		cout << "Affinity: " << (*it).tda << "\n";
		cout << "Communication: " << (*it).ntcc << "\n";
		cout << "Parallelism: " << (*it).ep << "\n";
		cout << "Load: " << (*it).load << "\n";
		cout << "Cost: " << (*it).cost << "\n";
		cout << "Total cost: " << (*it).totalCost << "\n";
		cout << "Size: " << (*it).size << "\n";
		cout << "Criticality: " << (*it).crit << "\n";
		cout << "Cost Function: " << (*it).cf << "\n";
		cout << "\n";
		cout << "\n";
	}
}

Pareto::Pareto() {
	// TODO Auto-generated constructor stub

}

Pareto::~Pareto() {
	// TODO Auto-generated destructor stub
}

