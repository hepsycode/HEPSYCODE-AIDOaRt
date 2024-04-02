/*
 * memoryUnit.h
 *
 *  Created on: 02/lug/2018
 *      Author: giuseppe
 */

#ifndef __MEMORYUNIT_H__
#define __MEMORYUNIT_H__

///
/// Describe Memory unit that compose a BB
///

class memoryUnit
{
public:

	//At the moment the id is not necessary

	///
	/// Code size value of the memory unit
	///
	unsigned int codeSize;
	///
	/// Data size value of the memory unit
	///
	unsigned int dataSize;
	///
	/// Equivalent gates value of the memory unit
	///
	unsigned int eqG; //???
};

#endif /* MEMORYUNIT_H_ */
