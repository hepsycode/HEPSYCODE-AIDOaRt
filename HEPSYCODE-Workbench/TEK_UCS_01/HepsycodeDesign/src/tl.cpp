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

/*
 * tl.cpp
 *
 *  Created on: 26 set 2016
 *      Author: daniele
 */

#include <systemc.h>
#include "tl.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

/*
 *  Processors methods
 */

unsigned int ProcessingUnit::getId(){
	return this->id;
}

void ProcessingUnit::setId(unsigned int c){
	this->id = c;
}

string ProcessingUnit:: getName()
{
	return this->name;
}

void ProcessingUnit:: setName(string x)
{
	name = x;
}

string ProcessingUnit:: getProcessorType()
{
	return this->processorType;
}

void ProcessingUnit:: setProcessorType(string x)
{
	processorType = x;
}

float ProcessingUnit:: getCost()
{
	return this->cost;
}

void ProcessingUnit:: setCost(float x)
{
	cost = x;
}

string ProcessingUnit:: getISA()
{
	return this->ISA;
}

void ProcessingUnit:: setISA(string x)
{
	ISA = x;
}

float ProcessingUnit:: getFrequency()
{
	return this->frequency;
}

void ProcessingUnit:: setFrequency(float x)
{
	frequency = x;
}

float** ProcessingUnit:: getCC4S()
{
	return this->CC4CS;
}

void ProcessingUnit:: setCC4S(float** x)
{
	CC4CS = x;
}

float ProcessingUnit:: getPower()
{
	return this->Power;
}

void ProcessingUnit:: setPower(float x)
{
	Power = x;
}

float ProcessingUnit:: getMIPS()
{
	return this->MIPS;
}

void ProcessingUnit:: setMIPS(float x)
{
	MIPS = x;
}

float ProcessingUnit:: getI4CSmin()
{
	return this->I4CSmin;
}

void ProcessingUnit:: setI4CSmin(float x)
{
	I4CSmin = x;
}

float ProcessingUnit:: getI4CSmax()
{
	return this->I4CSmax;
}

void ProcessingUnit:: setI4CSmax(float x)
{
	I4CSmax = x;
}

float ProcessingUnit:: getVdd()
{
	return this->Vdd;
}

void ProcessingUnit:: setVdd(float x)
{
	Vdd = x;
}

float ProcessingUnit:: getIdd()
{
	return this->Idd;
}

void ProcessingUnit:: setIdd(float x)
{
	Idd = x;
}

sc_time ProcessingUnit:: getOverheadCS()
{
	return this->overheadCS;
}

void ProcessingUnit:: setOverheadCS(sc_time x)
{
	overheadCS = x;
}


// BasicBlock methods

/*BasicBlock::BasicBlock(unsigned int id, string type, ProcessingUnit pu, float frt){
	this->id = id;
	this->type = type;
	this->processingUnit = pu;
	this->FRT = frt;
}*/

string BasicBlock:: getName()
{
	return this->name;
}

void BasicBlock:: setName(string x)
{
	name = x;
}

int BasicBlock:: getId()
{
	return this->id;
}

void BasicBlock:: setId(int x)
{
	id = x;
}

string BasicBlock:: getType()
{
	return type;
}


void BasicBlock:: setType(string x)
{
	type = x;
}

int BasicBlock:: getIdPU()
{
	return this->idPU;
}

void BasicBlock:: setIdPU(int x)
{
	idPU = x;
}

void BasicBlock:: setProcessor(vector<ProcessingUnit> p)
{
	vpu= p;
}


/*void BasicBlock:: setMem(Memory m)
{
	memSize = m;
}*/

vector<ProcessingUnit> BasicBlock::getProcessors()
{
	return vpu;
}


unsigned int BasicBlock::getCodeSize(){
	return this->codeSize;
}

void BasicBlock::setCodeSize(unsigned int c){
	this->codeSize = c;
}

unsigned int BasicBlock::getDataSize(){
	return this->dataSize;
}

void BasicBlock::setDataSize(unsigned int d){
	this->dataSize = d;
}

unsigned int BasicBlock::getEqG(){
	return this->eqG;
}

void BasicBlock::setEqG(unsigned int e){
	this->eqG = e;
}

void BasicBlock:: setFRT(float x){
	FRT = x;
}

float BasicBlock:: getFRT(){
	return FRT;
}

// process methods

Process::Process(){
	id = 0;
	eqGate = 0;
	dataType = 0;
	criticality = 0;
	profiling = 0;
	processTime = sc_time(0, SC_MS);
	priority = 0;
	energy = 0;
}

string Process:: getName()
{
	return this->name;
}

void Process:: setName(string x)
{
	name = x;
}

int Process:: getId()
{
	return this->id;
}

void Process:: setId(int x)
{
	id = x;
}

float Process::getEnergy(){
	return this->energy;
}

void Process::setEnergy(float en){
	energy = en;
}

int Process:: getPriority()
{
	return this->priority;
}

void Process:: setPriority(int x)
{
	priority = x;
}

int Process:: getCriticality()
{
	return this->criticality;
}

void Process:: setCriticality(int x)
{
	criticality = x;
}

float Process:: getEqGate()
{
	return this->eqGate;
}

void Process:: setEqGate(float g)
{
	eqGate = g;
}

int Process:: getDataType()
{
	return this->dataType;
}

void Process:: setDataType(int x)
{
	dataType = x;
}

void Process::setCodeSize(string p, unsigned int mem){
	map <string, unsigned int>::iterator end = this->codeSizeMap.end();
	pair<string, unsigned int> item (p, mem);
	this->codeSizeMap.insert(end, item);
}

void Process::setDataSize(string p, unsigned int mem){
	map <string, unsigned int>::iterator end = this->dataSizeMap.end();
	pair<string, unsigned int> item (p, mem);
	this->dataSizeMap.insert(end, item);
}

/*void Process::setMemSize(Memory m){
	this->mem = m;
}*/

float Process::getAffinityByName (string processorName){
	map<string, float>::iterator it = this->affinity.find(processorName);
	if ( it != this->affinity.end() )
		return it->second;
	else
		return 0;
}

void Process:: setAffinity(string x, float y)
{
	map <string, float>::iterator end = this->affinity.end();
	pair<string, float> item (x, y);
	this->affinity.insert(end, item);
}

void Process:: setConcurrency(int p, float c)
{
	map <int, float>::iterator end = this->concurrency.end();
	pair<int, float> item (p, c);
	this->concurrency.insert(end, item);
}

void Process::setLoad(int p, float value){
	map <int, float>::iterator end = this->load.end();
	pair<int, float> item (p, value);
	this->load.insert(end, item);
}


int Process:: getPS_Profiling()
{
	return this->profiling;
}

sc_time Process:: getProcessTime()
{
	return this->processTime;
}


// memory methods

Memory::Memory(unsigned int c, unsigned int d){
	this->codeSize = c;
	this->dataSize = d;
}


unsigned int Memory::getCodeSize(){
	return this->codeSize;
}

void Memory::setCodeSize(unsigned int c){
	this->codeSize = c;
}

unsigned int Memory::getDataSize(){
	return this->dataSize;
}

void Memory::setDataSize(unsigned int d){
	this->dataSize = d;
}

// link methods

int PhysicalLink:: getId()
{
	return this->id;
}

string PhysicalLink::getName()
{
	return this->name;
}

int PhysicalLink::getPhysicalWidth()
{
	return this->physical_width;
}

sc_time PhysicalLink::getTcomm()
{
	return this->tcomm;
}

sc_time PhysicalLink::getTAcomm()
{
	return this->tacomm;
}

int PhysicalLink::getBandwidth()
{
	return this->bandwidth;
}

void PhysicalLink::setId(int x)
{
	id = x;
}

void PhysicalLink::setName(string x)
{
	name = x;
}

void PhysicalLink::setPhysicalWidth(int x)
{
	physical_width = x;
}

void PhysicalLink::setTcomm(sc_time x)
{
	tcomm = x;
}

void PhysicalLink::setTAcomm(sc_time x)
{
	tacomm = x;
}

void PhysicalLink::setBandwidth(int x)
{
	bandwidth = x;
}

float PhysicalLink::geta2()
{
	return this->a2;
}

void PhysicalLink::seta2(float x)
{
	a2 = x;
}

float PhysicalLink::geta1()
{
	return this->a1;
}

void PhysicalLink::seta1(float x)
{
	a1 = x;
}

// channel methods

string Channel:: getName()
{
	return this->name;
}

int Channel:: getId()
{
	return this->id;
}

int Channel:: getWidth()
{
	return this->width;
}

int Channel:: getW_id()
{
	return this->w_id;
}

int Channel:: getR_id()
{
	return this->r_id;
}

int Channel:: getNum()
{
	return this->num;
}

void Channel:: setName(string x)
{
	name = x;
}

void Channel:: setId(int x)
{
	id = x;
}

void Channel:: setWidth(int x)
{
	width = x;
}

void Channel:: setW_id(int x)
{
	w_id = x;
}

void Channel:: setR_id(int x)
{
	r_id = x;
}

void Channel:: setNum(int x)
{
	num = x;
}


