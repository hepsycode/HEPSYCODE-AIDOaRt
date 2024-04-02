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
 * tl : HEPSIM Technologies Library.
 *
 * tl: HEPSIM Technologies Library file
 *
********************************************************************************/

/*! \file tl.h
    \brief HEPSIM Technologies Library Documented file.

    Technologies Library: Technologies Library file
*/

/** @defgroup tl_group HEPSIM Technologies Library.
 *
 *  Technologies Library Implementation
 *
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start tl_group

#ifndef TL_H_
#define TL_H_

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include <systemc.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <set>

using namespace std;

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

class ProcessingUnit
{
    public:

		string name;
		unsigned int id;
        string processorType;
        float cost;
        string ISA;
        float frequency; // in MHz
        float** CC4CS; // multiple CC4CS: rows are int8, int16, int32, float, tot; columns are Q1 and Q3
		float Power; // in W
		float MIPS; 
		float I4CSmin;
		float I4CSmax;
		float Vdd; // in V
		float Idd; // in A
        sc_time overheadCS; // in us

    public:
        unsigned int getId();
        void setId(unsigned int c);

        string getName();
        void setName(string x);

        string getProcessorType();
        void setProcessorType(string x);

        float getCost();
        void setCost(float x);

        string getISA();
        void setISA(string x);

        float getFrequency();
        void setFrequency(float x);

        float** getCC4S();
        void setCC4S(float** x);

		float getPower();
		void setPower(float x);

		float getMIPS();
		void setMIPS(float x);

		float getI4CSmin();
		void setI4CSmin(float x);

		float getI4CSmax();
		void setI4CSmax(float x);

		float getVdd();
		void setVdd(float x);

		float getIdd();
		void setIdd(float x);

        sc_time getOverheadCS();
        void setOverheadCS(sc_time x);

};

class Memory
{
	private:
		unsigned int codeSize;
		unsigned int dataSize;

	public:
		//Memory();
		Memory(unsigned int code, unsigned int data);

		unsigned int getCodeSize();
		void setCodeSize(unsigned int c);

		unsigned int getDataSize();
		void setDataSize(unsigned int c);
};

class Process
{
	public:
        string name;
        unsigned int id;
        unsigned int priority;
        unsigned int criticality;
        float eqGate;
		unsigned int dataType;
     	map <string, unsigned int> codeSizeMap;
     	map <string, unsigned int> dataSizeMap;
        //Memory mem;
        map <string,float> affinity;
        map <int,float> concurrency;
        map <int,float> load;
        unsigned int profiling;
        sc_time processTime;
        float energy;

	public:
        Process();

        string getName();
        void setName(string x);

        int getId();
        void setId(int x);

        int getPriority();
        void setPriority(int x);

        int getCriticality();
        void setCriticality(int x);

        float getEqGate();
        void setEqGate(float g);

		int getDataType();
        void setDataType(int x);

        void setMemSize(Memory m);
        void setCodeSize(string procName, unsigned int value);
        void setDataSize(string procName, unsigned int value);

        float getAffinityByName(string processorName);
        void setAffinity(string processorName, float affinity);

        void setConcurrency(int procId, float conc);

        void setLoad (int procId, float value);

        int getPS_Profiling();
        sc_time getProcessTime();

        void setEnergy(float energy);
        float getEnergy();
};

class BasicBlock{

private:
	string name;
	unsigned int id;
	string type;
	int idPU;
	vector <ProcessingUnit> vpu;
 	//Memory memSize;
 	//communicationUnit
	unsigned int codeSize;
	unsigned int dataSize;
	unsigned int eqG;
 	float FRT;

public:
 	//BasicBlock();

	//BasicBlock (unsigned int id, string type, ProcessingUnit pu, float frt);

	string getName();
	void setName(string x);

	int getId();
	void setId(int x);

	string getType();
	void setType(string x);

	int getIdPU();
	void setIdPU(int x);

	vector<ProcessingUnit> getProcessors();
	void setProcessor(vector<ProcessingUnit> pu);

	//Memory getMemSize();
	//void setMem(Memory m);

    unsigned int getCodeSize();
    void setCodeSize(unsigned int c);

    unsigned int getDataSize();
    void setDataSize(unsigned int c);


    unsigned int getEqG();
    void setEqG(unsigned int c);

	float getFRT();
	void setFRT(float x);


};

class PhysicalLink
{
	public:
		string name;
		unsigned int id;
		unsigned int physical_width; // width of the physical link
		sc_time tcomm; // LP: (bandwidth / phisycal_widht = 1/sec=hz (inverto)) ( per 1000)  (non sforare i 5 ms)
		sc_time tacomm; // LP: tcomm * K (es:K=1)
		unsigned int bandwidth; // bandwidth in bit/s
		float a2; // a2 coefficient of energy curve
		float a1; // a1 coefficient of energy curve

	public:
		string getName();
		void setName(string x);

		int getId();
		void setId(int x);

		int getPhysicalWidth();
		void setPhysicalWidth(int x);

		sc_time getTcomm();
		void setTcomm(sc_time x);

		sc_time getTAcomm();
		void setTAcomm(sc_time x);

		int getBandwidth();
		void setBandwidth(int x);

		float geta2();
		void seta2(float x);

		float geta1();
		void seta1(float x);

};

class Channel
{
	public:
		string name;
		unsigned int id;
		unsigned int w_id;
		unsigned int r_id;
		unsigned int width; // logical width of the channel
		unsigned int num;
		sc_time working_time;
		double working_energy;

	public:
		string getName();
		void setName(string x);

		int getId();
		void setId(int x);

		int getW_id();
		void setW_id(int x);

		int getR_id();
		void setR_id(int x);

		int getWidth();
		void setWidth(int x);

		int getNum();
		void setNum(int x);

};

/** @} */ // end of tl_group

#endif /* TL_H_ */

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
