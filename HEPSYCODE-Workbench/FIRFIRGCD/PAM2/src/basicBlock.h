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

using namespace std;

// Descrive le caratteristiche della singola procedura

class basicblock
{
 public:

        // Gradi di affinita' (tra 0 e 1) nei confronti degli esecutori
        //  che per ora sono tre (0=GPP, 1=DSP, 2=ASP)
	int id;
	string name;
	string type;

	string processingUnit;
	string processorType;
	unsigned int idprocessor;

	float cost;

    // Occupazione di un ASP
    // (numero di gate-equivalenti necessari per l'implementazione)
	unsigned int codeSize;
	unsigned int dataSize;
	unsigned int eqG;

	string communicationUnit[MAXEIL];

    // Carico computazionale nei confronti di un GPP (tra 0 e 1)
    float FreeRunningTime;

};

#endif
