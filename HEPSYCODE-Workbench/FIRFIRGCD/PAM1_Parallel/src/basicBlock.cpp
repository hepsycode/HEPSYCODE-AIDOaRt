/*
 * basicBlock.cpp
 *
 *  Created on: 02/lug/2018
 *      Author: giuseppe
 */

#include "basicBlock.h"

// Constructor
basicBlock::basicBlock() {
	procUnit = new processingUnit;
	memUnit = new memoryUnit;
	commUnit = new communicationUnit;

}

// Destructor
basicBlock::~basicBlock() {

}

