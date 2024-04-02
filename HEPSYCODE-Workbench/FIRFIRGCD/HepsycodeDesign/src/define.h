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
 * Created on: 09/May/2022                                                      *
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
 * datatypes.h : Defines the FirFirGCD defines.                                 *
 *                                                                              *
 * Defines all the FirFirGCD related defines                                    *
 *                                                                              *
********************************************************************************/

/*! \file define.h
    \brief Define Documented file.

    Defines all the FirFirGCD related defines.
*/

/** @defgroup firfirgcd_define_group FirFirGCD define.
 *
 *  DEFINE USED BY HEPSIM2
 *
 *  All the FirFirGCD related define
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start firfirgcd_define_group

#ifndef __DEFINE__
#define __DEFINE__

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

/********************************************************************************
 ***                                Defines and Enum                          ***
 *******************************************************************************/

////////////////////////////
/// SBM DEPENDENT
////////////////////////////

/// FirFirGCD: constants related to the SBM

#define NPS 10 /// Number of processes
enum p_id {stimulus_id, display_id, fir8m_id, fir8e_id, fir8s_id, fir16m_id, fir16e_id, fir16s_id, gcdm_id, gcde_id, s_fir8m_fir8e_id}; // Processes IDs
#define NCH 15 /// Number of channels

#define TAP8 8 /// FIR8
#define TAP16 16 /// FIR16
#define NUMBER_OF_INPUTS 10

/// FirFirGCD: constants related to the HW architecture

#define NBB 5 /// Total number of BB instances in instanceTL
enum bb_id {BB8051_0_id, BB8051_1_id, BBleon3_0_id, BBleon3_1_id, BBArtix7_0_id}; /// BBs IDs (#id in the tag is starting from 0 to be aligned with istancesTL)
#define NPL 3 /// Number of physical link instances in instanceTL

/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
/// SBM INDEPENDENT: DO NOT CHANGE
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////

//// Tags for conditionl compilation (LP: To be provided as flag to compiler)
///  Possible options:
///  - NO TAGS (Add only functional behavioral simulation?) or FUNCTIONAL?
///  - NO TAGS (function alanalyzer = functional simulatoin + communications analysis + functional concurrency analysis)
///  - TIMING_ENERGY (timing&energy simulation)
///  - TIMING_ENERGY+CONCURRENCY (timing&energy simulation + timing concurrency analysis)
///  - TIMING_ENERGY+LOAD (timing&energy simulation + load estimation)
///  - TIMING_ENERGY+LOAD+CONCURRENCY (timing&energy simulation + load estimation + timing concurrency analysis) - WARNING: scheduler OVH is 0!

/// #define _TIMING_ENERGY_
/// #define _LOAD_
/// #define _CONCURRENCY_

/// Tags for debug and log (LP: To be provided as flag to compiler)
/// #define _DEBUG_
/// #define _SAVE_CSV_

/////////////////////////////////////////////////////////////////////////////////////////////

/// Costants related to mapping files

#define APPLICATION "./XML/application.xml" /// File for application
#define MAPPING_PS_BB "./XML/mappingPS.xml" /// File for processes-processors mapping
#define MAPPING_LC_PL "./XML/mappingCH.xml" /// File for logical links-physical links mapping

/// Costants related to processes/schedulers states and BB/modes

enum state { undefined, waiting, ready, running };
enum mode { off, suspended, active };

/////////////////////////////////////////////////////////////////////////////////////////////

/// Costants related to energy consumption estimation

/// Method used to compute energy consumption (possible values: EPI/EPC) //LP: check formule
/// #define energyComputation "EPI"
#define energyComputation "EPC"

/********************************************************************************
 ***                                Typedefs                                  ***
 *******************************************************************************/

/********************************************************************************
 ***                              Struct                           	          ***
 *******************************************************************************/

/** @} */ // end of firfirgcd_define_group

#endif

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
