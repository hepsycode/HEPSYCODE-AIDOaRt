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
