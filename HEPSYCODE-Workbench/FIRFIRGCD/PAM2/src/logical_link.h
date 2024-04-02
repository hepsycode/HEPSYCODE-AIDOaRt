/*
 * logical_link.h
 *
 *  Created on: Jul 5, 2018
 *      Author: cerbero
 */

#ifndef __LOGICAL_LINK_H__
#define __LOGICAL_LINK_H__

#include "define.h"
#include <string>

using namespace std;

// Descrive le caratteristiche della singolo link fisico

class logical_link
{
 public:

	int id;
	string name;

	unsigned int w_id;
	unsigned int r_id;
	unsigned int width;

};

#endif /* __LOGICAL_LINK_H__ */
