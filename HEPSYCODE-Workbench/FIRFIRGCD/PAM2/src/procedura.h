//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Procedure
//============================================================================

#ifndef __PROCEDURA__
#define __PROCEDURA__

#include "define.h"
#include <string>
#include <vector>

using namespace std;

// Descrive le caratteristiche della singola procedura

class procedura
{
 public:

    // Gradi di affinita' (tra 0 e 1) nei confronti degli esecutori
    //  che per ora sono tre (0=GPP, 1=DSP, 2=ASP)
	int id;
	string name;
	int priority;

	int criticality;  // metrica criticità;
      
	float DA[MAXCLUSTER]; // Affinity

	// Carico computazionale nei confronti di un GPP (tra 0 e 1)
	float load[MAXBB];

	// Occupazione di un ASP
	// (numero di gate-equivalenti necessari per l'implementazione)
	int size_SW_RAM[MAXBB];
	int size_SW_ROM[MAXBB];

    int eqg; // int size_HW;
};

#endif
