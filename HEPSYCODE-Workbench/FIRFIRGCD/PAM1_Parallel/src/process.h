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
