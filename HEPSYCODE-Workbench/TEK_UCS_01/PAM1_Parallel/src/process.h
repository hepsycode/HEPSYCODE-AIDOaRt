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
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Procedure
//============================================================================

#ifndef __PROCESSO__
#define __PROCESSO__

#include "define.h"
#include <string>
#include <vector>

using namespace std;

///
/// Describe the process characteristics of the application under test
///

class process
{
 public:

	///
	/// The identifier of the process
	///
	int id;
	///
	/// Process name
	///
	string name;
	///
	/// Process priority
	///
	int priority;
	///
	/// Criticality of the process
	///
	int criticality;
	///
	/// Array containing information about affinity between the process and the families
	/// of executors
	///
	float DA[MAXCLUSTER];
	///
	///Computational load of the process against the executors (only GPP and ASP, value between 0 and 1)
	///
	float load[MAXBB];
	///
	/// Data size of the process for each GPP and ASP
	///
	int size_SW_RAM[MAXBB];
	///
	/// Code size of the process for each GPP and ASP
	///
	int size_SW_ROM[MAXBB];
	///
	/// Number of equivalent gates needed for implementation on HW executor
	///
    int eqg;
};

#endif
