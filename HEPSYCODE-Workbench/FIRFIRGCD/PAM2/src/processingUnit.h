//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Processing Units
//============================================================================

#ifndef PROCESSINGUNIT_H_
#define PROCESSINGUNIT_H_

#include "define.h"
#include <string>

using namespace std;

// Descrive le caratteristiche della singola procedura

class processingUnit
{
 public:

	string processingUnitName;
	unsigned int idprocessor;
	string processorType;

};

#endif /* PROCESSINGUNIT_H_ */
