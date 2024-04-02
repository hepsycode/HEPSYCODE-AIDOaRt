/*
 * link.h
 *
 *  Created on: Jul 4, 2018
 *      Author: cerbero
 */

#ifndef LINK_H_
#define LINK_H_

#include "define.h"
#include <string>

using namespace std;

// Descrive le caratteristiche della singola procedura

class link
{
 public:

	int id;
	string name;
	string type;

	unsigned int physical_width;
	float tcomm;
	float tacomm;

    // Occupazione di un ASP
    // (numero di gate-equivalenti necessari per l'implementazione)
	unsigned int bandwidth;
	unsigned int maxBBs;
	unsigned int cost;

};

#endif /* LINK_H_ */
