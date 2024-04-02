//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Basic Blocks
//============================================================================

#ifndef __BASICBLOCK__
#define __BASICBLOCK__

#include "define.h"
#include <string>
#include "processingUnit.h"
#include "memoryUnit.h"
#include "communicationUnit.h"

using namespace std;

///
/// Describe the characteristics of Basic Blocks, composed by processing unit, memory unit and
/// communication unit
///

class basicBlock {
public:

	///
	/// The identifier of basic block
	///
	int id;
	///
	/// Name of basic block
	///
	string name;
	///
	/// Type of basic block
	///
	string type;
	///
	/// Pointer to Processing unit that compose the BB
	///
	processingUnit *procUnit;
	///
	/// Pointer to Memory unit that compose the BB
	///
	memoryUnit *memUnit;
	///
	/// Pointer to Communication unit that compose the BB
	///
	communicationUnit *commUnit;
	///
	/// Total application simulated time on one processor (only for GPP, value between 0 and 1)
	///
	float FreeRunningTime;
	///
	/// Constructor
	///
	basicBlock();
	///
	/// Destructor
	///
	~basicBlock();

};

#endif

