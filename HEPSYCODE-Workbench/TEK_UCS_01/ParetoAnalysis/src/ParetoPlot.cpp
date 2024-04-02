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
 * ParetoPlot.cpp
 *
 *  Created on: 14/lug/2018
 *      Author: giuseppe
 */

#include "ParetoPlot.h"

/*
void ParetoPlot::plot_Tda_Ntcc(DataSet &ds){

	vector<struct IndividualInfo>::iterator it;
	std::vector<std::pair<float,float>> data;
	for (it = (ds.individuals).begin(); it != (ds.individuals).end(); it++)
	{
		data.emplace_back((*it).ntcc,(*it).tda);
	}

	std::vector<std::pair<float,float>> frontData;
	for (it = (ds.paretoFront).begin(); it != (ds.paretoFront).end(); it++)
	{
		frontData.emplace_back((*it).ntcc,(*it).tda);
	}

	Gnuplot gp;
	gp << "set xrange [0:1.2]\nset yrange [0:1.2]\n";
	gp << "plot '-' with points title 'tda-ntcc', '-' with lines title 'Pareto Front'\n";
	gp.send1d(data);
	gp.send1d(frontData);
}
*/

void ParetoPlot::plot2D(DataSet &ds, string f1, string f2, string title){

	vector<struct IndividualInfo2D>::iterator it;
	std::vector<std::pair<float,float>> data;
	float temp1, temp2;
	int id = 1;

	for (it = (ds.datapoints).begin(); it != (ds.datapoints).end(); it++)
	{
		data.emplace_back((*it).f1,(*it).f2);
	}

	std::vector<std::pair<float,float> > frontData;
	std::vector<boost::tuple<float, float, int> > vecs;

	it = (ds.front_datapoints).begin();

	frontData.emplace_back((*it).f1,(*it).f2);

	vecs.push_back(boost::make_tuple((*it).f1, (*it).f2, id));

	temp1 = (*it).f1;
	temp2 = (*it).f2;

	for (it = (ds.front_datapoints).begin(); it != (ds.front_datapoints).end(); it++)
	{
		if ((temp1 != (*it).f1) && (temp2 != (*it).f2))
		{
		frontData.emplace_back((*it).f1,(*it).f2);
		vecs.push_back(boost::make_tuple((*it).f1, (*it).f2, id));
		}
		temp1 = (*it).f1;
		temp2 = (*it).f2;
		id++;
	}

	Gnuplot gp;
	gp << "set xrange [0:1.2]\nset yrange [0:1.2]\n";
	gp << "set title '"<< title << "' \n";
	gp << "set xlabel '"<< f1 << "'\n";
	gp << "set ylabel '"<< f2 << "'\n";
	gp << "plot '-' with points pt 1 ps 1 lc rgb 'black' title 'datapoints',"
			" '-' with linespoint lc rgb 'red' title 'Pareto Front',"
			" '-' using 1:2:3 with labels center offset 1,-.5 textcolor 'red' notitle\n";

	gp.send1d(data);
	gp.send1d(frontData);
	gp.send1d(vecs);
}
