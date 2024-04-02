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

#ifndef __DATATYPE__
#define __DATATYPE__

#include <systemc.h>

enum idEnum{EVENT_0,EVENT_A,EVENT_B};

struct stimulus_system_payload
{
	idEnum Id;
	sc_int<16> example;
};

struct system_display_payload
{
	sc_int<8> example;
};

struct sampleTimCord_cleanData_xx_payload
{
	sc_int<8> dev;
	sc_int<16> step;
	double ex_time;
	double sample_i;
	double sample_v;
};

//struct sampleTimCord_cleanData_01_payload
//{
//	sc_int<8> example;
//};
//
//struct sampleTimCord_cleanData_02_payload
//{
//	sc_int<8> example;
//};
//
//struct sampleTimCord_cleanData_03_payload
//{
//	sc_int<8> example;
//};
//
//struct sampleTimCord_cleanData_04_payload
//{
//	sc_int<8> example;
//};

struct cleanData_xx_ann_xx_payload
{
	sc_int<8> dev;
	sc_int<16> step;
	double ex_time;
	double device_i;
	double device_v;
	double device_t;
	double device_r;
	double x_0;
	double x_1;
	double x_2;
	double fault;
};

//struct cleanData_01_ann_01_payload
//{
//	sc_int<8> example;
//};
//
//struct cleanData_02_ann_02_payload
//{
//	sc_int<8> example;
//};
//
//struct cleanData_03_ann_03_payload
//{
//	sc_int<8> example;
//};
//
//struct cleanData_04_ann_04_payload
//{
//
//sc_int<8> example;
//
//};

struct ann_xx_dataCollector_payload
{
	sc_int<8> dev;
	sc_int<16> step;
	double ex_time;
	double device_i;
	double device_v;
	double device_t;
	double device_r;
	double x_0;
	double x_1;
	double x_2;
	double fault;
};


//struct ann_01_dataCollector_payload
//{
//	sc_int<8> example;
//};
//
//struct ann_02_dataCollector_payload
//{
//	sc_int<8> example;
//};
//
//struct ann_03_dataCollector_payload
//{
//	sc_int<8> example;
//};
//
//struct ann_04_dataCollector_payload
//{
//	sc_int<8> example;
//};

#endif


/*
struct stim_system_payload
{
	idEnum Id;
	sc_uint<8> type;
	void * p;
};

struct system_display_payload
{
	sc_uint<8> feedback;
};


#endif
*/
