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
 * Created on: 19/Aug/2019                                                      *
 * Authors: Vittoriano Muttillo, Luigi Pomante                                  *
 *                                                                              *
 * email: vittoriano.muttillo@guest.univaq.it                                   *
 *        luigi.pomante@univaq.it                                               *
 *                                                                              *
 ********************************************************************************
 * This code has been developed from an HEPSYCODE model used as demonstrator by	*
 * University of L'Aquila.                                                      *
 *                                                                              *
 * The code is used as a working example in the 'Embedded Systems' course of    *
 * the Master in Conputer Science Engineering offered by the                    *
 * University of L'Aquila                                                       *
 *******************************************************************************/

/********************************************************************************
 * datatypes.h : Defines the FirFirGCD datatypes.                               *
 *                                                                              *
 * Defines all the FirFirGCD related datatypes                                  *
 *                                                                              *
********************************************************************************/

/*! \file datatype.h
    \brief Datatype Documented file.

    Defines all the FirFirGCD related datatypes.
*/

/** @defgroup firfirgcd_datatypes_group FirFirGCD datatypes.
 *
 *  DATATYPES (i.e., MESSAGES) USED BY THE CHANNELS
 *
 *  Defines all the FirFirGCD related datatypes
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start firfirgcd_datatypes_group

#ifndef __DATATYPE_H__
#define __DATATYPE_H__

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include <systemc.h>

/********************************************************************************
 ***                                Defines                                   ***
 *******************************************************************************/

/********************************************************************************
 ***                                Typedefs                                  ***
 *******************************************************************************/

/********************************************************************************
 ***                              Struct                           	          ***
 *******************************************************************************/

/********************************************************************************
 ***                              fir8_group                           	      ***
 *******************************************************************************/

/*! \struct fir8e_parameters datatype.h "src/datatype.h"
 * @brief struct fir8e_parameters
 *
 * Some details about the fir8e_parameters struct. \n
 *
 */

/// Message from fir8m to fir8e

struct fir8e_parameters
{
	sc_uint<19> acc;  ///< Example 1.
	sc_uint<9> coef[8];  //!< Example 2.
	sc_uint<8> shift[8]; /*!< Example 3. */
	sc_uint<8> sample_tmp;  /**< Example 4. */
};

/*! \struct fir8e_results datatype.h "src/datatype.h"
 * @brief struct fir8e_results
 *
 * Some details about the fir8e_results struct. \n
 * Message from fir8e to fir8m
 */

struct fir8e_results
{
	sc_uint<19> acc;
};

/*! \struct fir8s_parameters datatype.h "src/datatype.h"
 * @brief struct fir8s_parameters
 *
 * Some details about the fir8s_parameters struct. \n
 * Message from fir8m to fir8s
 */

struct fir8s_parameters
{
	sc_uint<8> shift[8];
	sc_uint<8> sample_tmp;
};

/*! \struct fir8s_results datatype.h "src/datatype.h"
 * @brief struct fir8s_results
 *
 * Some details about the fir8s_results struct. \n
 * Message from fir8s to fir8m
 */

struct fir8s_results
{
	sc_uint<8> shift[8];
};

/********************************************************************************
 ***                              fir16_group                                 ***
 *******************************************************************************/

/// Message from fir16m to fir16e
struct fir16e_parameters
{
	sc_uint<19> acc;
	sc_uint<9> coef[16];
	sc_uint<8> shift[16];
	sc_uint<8> sample_tmp;
};

/// Message from fir16e to fir16m
struct fir16e_results
{
	sc_uint<19> acc;
};

/// Message from fir16m to fir16s
struct fir16s_parameters
{
	sc_uint<8> shift[16];
	sc_uint<8> sample_tmp;
};

/// Message from fir16s to fir16m
struct fir16s_results
{
sc_uint<8> shift[16];
};

/********************************************************************************
 ***                              gcd_group                                   ***
 *******************************************************************************/

/// Message from gcdm to gcde
struct gcde_parameters
{
	sc_uint<8> sample1;
	sc_uint<8> sample2;
};

/// Message from gcde to gcdm
struct gcde_results
{
	sc_uint<8> result;
};

//////////////////////////////

/** @} */ // end of firfirgcd_datatypes_group

#endif

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
