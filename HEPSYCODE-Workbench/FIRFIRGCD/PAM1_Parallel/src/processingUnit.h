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
	string Isa;
	///
	/// Processing unit frequency
	///
	unsigned int frequency;
	///
	/// Processing unit CC4S metric value
	///
	unsigned int Cc4s;
	///
	/// Processing unit overhead value
	///
	unsigned int overheadCS;
};

#endif /* PROCESSINGUNIT_H_ */
