//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Processing Units
//============================================================================

#ifndef __PROCESSINGUNIT_H__
#define __PROCESSINGUNIT_H__

#include "define.h"
#include <string>

using namespace std;

///
/// Describe Processing unit that compose a BB
///

class processingUnit
{
 public:

	///
	/// Processing unit name
	///
	string processingUnitName;
	///
	/// Processing unit identifier
	///
	unsigned int idprocessor;
	///
	/// Processor type: GPP, DSP or SPP
	///
	string processorType;
	///
	/// Monetary cost
	///
	float cost;
	///
	/// Processing unit ISA
	///

};

#endif /* PROCESSINGUNIT_H_ */
