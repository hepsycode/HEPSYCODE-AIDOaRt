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
 * DataSet.cpp
 *
 *  Created on: 09/lug/2018
 *      Author: giuseppe
 */

#include "DataSet.h"
#include "CsvUtil.h"
#include <cmath>

DataSet::DataSet(string csv_file) {

	this->individuals = CsvUtil::parseAllData(csv_file);

	this->createIdealPoint();
	this->createNadirPoint();
	this->createUtopianPoint(0.1);

}

void DataSet::createDatapoints(string f1, string f2){

	vector<IndividualInfo>::iterator it;
	IndividualInfo2D ind;
	int id = 1;

	if ((f1 == "tda" && f2 == "ntcc")||((f1 == "ntcc") && (f2 == "tda")))
	{
		for (it = this->individuals.begin(); it != this->individuals.end(); it++){
			ind.id = (*it).id;
			ind.cf = (*it).cf;
			ind.f1 = (*it).ntcc;
			ind.f2 = (*it).tda;
			ind.processors = (*it).processors;
			if (ind.cf < 1) ind.feasible = true;
			else ind.feasible = false;
			this->datapoints.push_back(ind);
			id++;
		}
		return;
	}
	else if ((f1 == "tda" && f2 == "ep")||((f1 == "ep") && (f2 == "tda")))
	{
		for (it = this->individuals.begin(); it != this->individuals.end(); it++){
			ind.id = (*it).id;
			ind.cf = (*it).cf;
			ind.f1 = (*it).ep;
			ind.f2 = (*it).tda;
			ind.processors = (*it).processors;
			if (ind.cf < 1) ind.feasible = true;
			else ind.feasible = false;
			this->datapoints.push_back(ind);
			id++;
		}
		return;
	}
	else if ((f1 == "ep" && f2 == "ntcc")||((f1 == "ntcc") && (f2 == "ep")))
	{
		for (it = this->individuals.begin(); it != this->individuals.end(); it++){
			ind.id = (*it).id;
			ind.cf = (*it).cf;
			ind.f1 = (*it).ep;
			ind.f2 = (*it).ntcc;
			ind.processors = (*it).processors;
			if (ind.cf < 1) ind.feasible = true;
			else ind.feasible = false;
			this->datapoints.push_back(ind);
			id++;
		}
		return;
	}
	else if ((f1 == "load" && f2 == "cost")||((f1 == "cost") && (f2 == "load")))
	{
		for (it = this->individuals.begin(); it != this->individuals.end(); it++){
			ind.id = (*it).id;
			ind.cf = (*it).cf;
			ind.f1 = (*it).cost;
			ind.f2 = (*it).load;
			ind.processors = (*it).processors;
			if (ind.cf < 1) ind.feasible = true;
			else ind.feasible = false;
			this->datapoints.push_back(ind);
			id++;
		}
		return;
	}else if ((f1 == "load" && f2 == "ntcc")||((f1 == "ntcc") && (f2 == "load")))
	{
		for (it = this->individuals.begin(); it != this->individuals.end(); it++){
			ind.id = (*it).id;
			ind.cf = (*it).cf;
			ind.f1 = (*it).ntcc;
			ind.f2 = (*it).load;
			ind.processors = (*it).processors;
			if (ind.cf < 1) ind.feasible = true;
			else ind.feasible = false;
			this->datapoints.push_back(ind);
			id++;
		}
		return;
	}else if ((f1 == "load" && f2 == "energy")||((f1 == "energy") && (f2 == "load")))
	{
		for (it = this->individuals.begin(); it != this->individuals.end(); it++){
			ind.id = (*it).id;
			ind.cf = (*it).cf;
			ind.f1 = (*it).energy;
			ind.f2 = (*it).load;
			ind.processors = (*it).processors;
			if (ind.cf < 1) ind.feasible = true;
			else ind.feasible = false;
			this->datapoints.push_back(ind);
			id++;
		}
		return;
	}else if ((f1 == "load" && f2 == "energyTC")||((f1 == "energyTC") && (f2 == "load")))
	{
		for (it = this->individuals.begin(); it != this->individuals.end(); it++){
			ind.id = (*it).id;
			ind.cf = (*it).cf;
			ind.f1 = (*it).energyTC;
			ind.f2 = (*it).load;
			ind.processors = (*it).processors;
			if (ind.cf < 1) ind.feasible = true;
			else ind.feasible = false;
			this->datapoints.push_back(ind);
			id++;
		}
		return;
	}else if ((f1 == "cost" && f2 == "energyTC")||((f1 == "energyTC") && (f2 == "cost")))
	{
		for (it = this->individuals.begin(); it != this->individuals.end(); it++){
			ind.id = (*it).id;
			ind.cf = (*it).cf;
			ind.f1 = (*it).energyTC;
			ind.f2 = (*it).cost;
			ind.processors = (*it).processors;
			if (ind.cf < 1) ind.feasible = true;
			else ind.feasible = false;
			this->datapoints.push_back(ind);
			id++;
		}
		return;
	}
	else cout << "Functions entered incorrect or not covered\n";
}

float DataSet::minFirstFunction(vector<IndividualInfo2D> data){

	vector<IndividualInfo2D>::iterator it = data.begin();
	float min = (*it).f1;

	for (it = data.begin()+1; it != data.end(); it++){
		if((*it).f1 < min) min = (*it).f1;
	}

	return min;
}

float DataSet::minSecondFunction(vector<IndividualInfo2D> data){

	vector<IndividualInfo2D>::iterator it = data.begin();
	float min = (*it).f2;

	for (it = data.begin()+1; it != data.end(); it++){
		if((*it).f2 < min) min = (*it).f2;
	}

	return min;
}


float DataSet::minTda(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).tda;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).tda < min) min = (*it).tda;
	}

	return min;
}

float DataSet::minCf(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).cf;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).cf < min) min = (*it).cf;
	}

	return min;
}

float DataSet::minCost(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).cost;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).cost < min) min = (*it).cost;
	}

	return min;
}

float DataSet::minCrit(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).crit;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).crit < min) min = (*it).crit;
	}

	return min;
}

float DataSet::minEp(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).ep;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).ep < min) min = (*it).ep;
	}

	return min;
}

float DataSet::minLoad(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).load;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).load < min) min = (*it).load;
	}

	return min;
}

float DataSet::minNtcc(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).ntcc;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).ntcc < min) min = (*it).ntcc;
	}

	return min;
}

float DataSet::minSize(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).size;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).size < min) min = (*it).size;
	}

	return min;
}

float DataSet::minTotalCost(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float min = (*it).totalCost;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).totalCost < min) min = (*it).totalCost;
	}

	return min;
}

float DataSet::maxFirstFunction(vector<IndividualInfo2D> data){

	vector<IndividualInfo2D>::iterator it = data.begin();
	float max = (*it).f1;

	for (it = data.begin()+1; it != data.end(); it++){
		if((*it).f1 > max) max = (*it).f1;
	}

	return max;
}

float DataSet::maxSecondFunction(vector<IndividualInfo2D> data){

	vector<IndividualInfo2D>::iterator it = data.begin();
	float max = (*it).f2;

	for (it = data.begin()+1; it != data.end(); it++){
		if((*it).f2 > max) max = (*it).f2;
	}

	return max;
}

float DataSet::maxTda(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).tda;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).tda > max) max = (*it).tda;
	}

	return max;
}

float DataSet::maxCf(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).cf;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).cf > max) max = (*it).cf;
	}

	return max;
}

float DataSet::maxCost(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).cost;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).cost > max) max = (*it).cost;
	}

	return max;
}

float DataSet::maxCrit(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).crit;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).crit > max) max = (*it).crit;
	}

	return max;
}

float DataSet::maxEp(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).ep;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).ep > max) max= (*it).ep;
	}

	return max;
}

float DataSet::maxLoad(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).load;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).load > max) max = (*it).load;
	}

	return max;
}

float DataSet::maxNtcc(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).ntcc;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).ntcc > max) max = (*it).ntcc;
	}

	return max;
}

float DataSet::maxSize(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).size;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).size > max) max = (*it).size;
	}

	return max;
}

float DataSet::maxTotalCost(vector<IndividualInfo> vec){

	vector<IndividualInfo>::iterator it = vec.begin();
	float max = (*it).totalCost;

	for (it = vec.begin()+1; it != vec.end(); it++){
		if((*it).totalCost > max) max = (*it).totalCost;
	}

	return max;
}

/*
float DataSet::computeTdaAvg(){

	float avg = 0;
	float tot = 0;
	vector<IndividualInfo>::iterator it;

	for (it = (this->individuals).begin(); it != (this->individuals).end(); it++){
		tot += (*it).tda;
	}

	return avg = tot/(this->individuals).size();
}

float DataSet::computeNtccAvg(){

	float tot = 0;
	vector<IndividualInfo>::iterator it;

	for (it = (this->individuals).begin(); it != (this->individuals).end(); it++){
		tot += (*it).ntcc;
	}

	return tot/(this->individuals).size();
}

float DataSet::computeTdaVar(float avg){

	float temp = 0;
	float sum = 0;
	vector<IndividualInfo>::iterator it;

	for (it = (this->individuals).begin(); it != (this->individuals).end(); it++){
			temp = pow((*it).tda - avg, 2);
			sum += temp;
		}

	return sum/(this->individuals).size();
}

float DataSet::computeNtccVar(float avg){

	float temp = 0;
	float sum = 0;
	vector<IndividualInfo>::iterator it;

	for (it = (this->individuals).begin(); it != (this->individuals).end(); it++){
			temp = pow((*it).ntcc - avg, 2);
			sum += temp;
		}

	return sum/(this->individuals).size();
}
*/
void DataSet::createIdealPoint(){

	(this->idealPoint).cf = 0;
	(this->idealPoint).cost = minCost(this->individuals);
	(this->idealPoint).crit = minCrit(this->individuals);
	(this->idealPoint).ep = minEp(this->individuals);
	(this->idealPoint).load = minLoad(this->individuals);
	(this->idealPoint).ntcc = minNtcc(this->individuals);
	(this->idealPoint).size = minSize(this->individuals);
	(this->idealPoint).tda = minTda(this->individuals);
	(this->idealPoint).totalCost = 0;
	(this->idealPoint).dominated = 0;
	(this->idealPoint).isDominated = false;
	(this->idealPoint).processes = "xxxxxxxx";
	(this->idealPoint).processors = "xxxxxxxx";
}



void DataSet::printIdealPoint(){

	cout << "######INFO IDEAL POINT######" << "\n";
	cout << "\n";

	cout << "Partitioning: " << (this->idealPoint).processors << "\n";
	cout << "Affinity: " << (this->idealPoint).tda << "\n";
	cout << "Communication: " << (this->idealPoint).ntcc << "\n";
	cout << "Parallelism: " << (this->idealPoint).ep << "\n";
	cout << "Load: " << (this->idealPoint).load << "\n";
	cout << "Cost: " << (this->idealPoint).cost << "\n";
	cout << "Total cost: " << (this->idealPoint).totalCost << "\n";
	cout << "Size: " << (this->idealPoint).size << "\n";
	cout << "Criticality: " << (this->idealPoint).crit << "\n";

	cout << "\n";

}

void DataSet::createUtopianPoint(float e){

	// Objective functions are normalized, except for some cases ranging between 0 and 1;
	// then the epsilon we should consider for the utopian point should be at most 1
	if (e > 1)
	{
		cout << "Value greater than 1, the utopian point will not be created \n";
		return;
	}
	(this->utopianPoint).cf = 0;
	(this->utopianPoint).dominated = 0;
	(this->utopianPoint).isDominated = false;
	(this->utopianPoint).processes = "xxxxxxxx";
	(this->utopianPoint).processors = "xxxxxxxx";
	(this->utopianPoint).totalCost = 0;

	// we do not consider negative objective functions
	if (((this->idealPoint).cost - e) < 0) (this->utopianPoint).cost = 0;
	else (this->utopianPoint).cost = (this->idealPoint).cost - e;

	if (((this->idealPoint).crit - e) < 0) (this->utopianPoint).crit = 0;
		else (this->utopianPoint).crit = (this->idealPoint).crit - e;

	if (((this->idealPoint).ep - e) < 0) (this->utopianPoint).ep = 0;
		else (this->utopianPoint).ep = (this->idealPoint).ep - e;

	if (((this->idealPoint).load - e) < 0) (this->utopianPoint).load = 0;
		else (this->utopianPoint).load = (this->idealPoint).load - e;

	if (((this->idealPoint).ntcc - e) < 0) (this->utopianPoint).ntcc = 0;
		else (this->utopianPoint).ntcc = (this->idealPoint).ntcc - e;

	if (((this->idealPoint).size - e) < 0) (this->utopianPoint).size = 0;
		else (this->utopianPoint).size = (this->idealPoint).size - e;

	if (((this->idealPoint).tda - e) < 0) (this->utopianPoint).tda = 0;
		else (this->utopianPoint).tda = (this->idealPoint).tda - e;
}

void DataSet::printUtopianPoint(){


	cout << "######INFO UTOPIAN POINT######" << "\n";
	cout << "\n";

	cout << "Partitioning: " << (this->utopianPoint).processors << "\n";
	cout << "Affinity: " << (this->utopianPoint).tda << "\n";
	cout << "Communication: " << (this->utopianPoint).ntcc << "\n";
	cout << "Parallelism: " << (this->utopianPoint).ep << "\n";
	cout << "Load: " << (this->utopianPoint).load << "\n";
	cout << "Cost: " << (this->utopianPoint).cost << "\n";
	cout << "Total cost: " << (this->utopianPoint).totalCost << "\n";
	cout << "Size: " << (this->utopianPoint).size << "\n";
	cout << "Criticality: " << (this->utopianPoint).crit << "\n";

	cout << "\n";

}

void DataSet::createNadirPoint(){

	(this->nadirPoint).cf = 9999;
	(this->nadirPoint).cost = maxCost(this->individuals);
	(this->nadirPoint).crit = maxCrit(this->individuals);
	(this->nadirPoint).ep = maxEp(this->individuals);
	(this->nadirPoint).load = maxLoad(this->individuals);
	(this->nadirPoint).ntcc = maxNtcc(this->individuals);
	(this->nadirPoint).size = maxSize(this->individuals);
	(this->nadirPoint).tda = maxTda(this->individuals);
	(this->nadirPoint).totalCost = 9999;
	(this->nadirPoint).dominated = 99999;
	(this->nadirPoint).isDominated = true;
	(this->nadirPoint).processes = "xxxxxxxx";
	(this->nadirPoint).processors = "xxxxxxxx";
}

void DataSet::printNadirPoint(){

	cout << "######INFO NADIR POINT######" << "\n";
	cout << "\n";

	cout << "Partitioning: " << (this->nadirPoint).processors << "\n";
	cout << "Affinity: " << (this->nadirPoint).tda << "\n";
	cout << "Communication: " << (this->nadirPoint).ntcc << "\n";
	cout << "Parallelism: " << (this->nadirPoint).ep << "\n";
	cout << "Load: " << (this->nadirPoint).load << "\n";
	cout << "Cost: " << (this->nadirPoint).cost << "\n";
	cout << "Total cost: " << (this->nadirPoint).totalCost << "\n";
	cout << "Size: " << (this->nadirPoint).size << "\n";
	cout << "Criticality: " << (this->nadirPoint).crit << "\n";

	cout << "\n";

}

DataSet::~DataSet() {
	// TODO Auto-generated destructor stub
}

