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
 * Authors: Vittoriano Muttillo, Marco Santic, Luigi Pomante                    *
 *                                                                              *
 * email: vittoriano.muttillo@guest.univaq.it                                   *
 *        marco.santic@guest.univaq.it                                          *
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
// Description : Define
//============================================================================

#ifndef __DEFINE__
#define __DEFINE__

/////////////////////////////////////////////////////////////////////////////////////////////
// SBM INDEPENDENT: DO NOT CHANGE
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////

//// Tags for conditionl compilation (LP: To be provided as flag to compiler)
// Possible options:
//- NO TAGS (Add only functional behavioral simulation?) or FUNCTIONAL?
//- NO TAGS (function alanalyzer = functional simulatoin + communications analysis + functional concurrency analysis)
//- TIMING_ENERGY (timing&energy simulation)
//- TIMING_ENERGY+CONCURRENCY (timing&energy simulation + timing concurrency analysis)
//- TIMING_ENERGY+LOAD (timing&energy simulation + load estimation)
//- TIMING_ENERGY+LOAD+CONCURRENCY (timing&energy simulation + load estimation + timing concurrency analysis) - WARNING: scheduler OVH is 0!

//#define _TIMING_ENERGY_
//#define _LOAD_
//#define _CONCURRENCY_

//// Tags for debug and log (LP: To be provided as flag to compiler)
//#define _DEBUG_
//#define _SAVE_CSV_
/////////////////////////////////////////////////////////////////////////////////////////////

//// Costants related to mapping files

#define APPLICATION "./XML/application.xml" // File for application
#define MAPPING_PS_BB "./XML/mappingPS.xml" // File for processes-processors mapping
#define MAPPING_LC_PL "./XML/mappingCH.xml" // File for logical links-physical links mapping

//// Costants related to processes/schedulers states and BB/modes

enum state { undefined, waiting, ready, running };
enum mode { off, suspended, active };

/////////////////////////////////////////////////////////////////////////////////////////////

//// Costants related to energy consumption estimation

// Method used to compute energy consumption (possible values: EPI/EPC) //LP: check formule
//#define energyComputation "EPI"
#define energyComputation "EPC"

/////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////
// SBM DEPENDENT
////////////////////////////

// Tekne Use case: costants

#define NPS 12  // Total number of processes (with Stimulus and Display)
enum p_id {stimulus_id, display_id, sampleTimCord_id, cleanData_01_id, cleanData_02_id, cleanData_03_id, cleanData_04_id, ann_01_id, ann_02_id, ann_03_id, ann_04_id, dataCollector_id};
#define NCH 14 // Total number of channels with Stimulus and Display

//// FirFirGCD: costants related to the HW architecture

#define NBB 5 // Total number of BB instances in instanceTL
enum bb_id {BB8051_0_id, BB8051_1_id, BBleon3_0_id, BBleon3_1_id, BBArtix7_0_id}; // BBs IDs (#id in the tag is starting from 0 to be aligned with istancesTL)
#define NPL 3 // Number of physical link instances in instanceTL

#endif
