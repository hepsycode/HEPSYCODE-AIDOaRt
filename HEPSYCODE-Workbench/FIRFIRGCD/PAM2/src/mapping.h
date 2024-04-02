/*
 * mapping.h
 *
 *  Created on: Jul 4, 2018
 *      Author: cerbero
 */

#ifndef __MAPPING_H__
#define __MAPPING_H__

#include "define.h"
#include <string>
#include <vector>

using namespace std;

// Descrive le caratteristiche della singola procedura

class mapping
{
 public:

	int process_id;
	string processor_name;
	int processor_id;

};

#endif /* MAPPING_H_ */
