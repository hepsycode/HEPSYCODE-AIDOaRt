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
 * SystemManager.cpp
 *
 *  Created on: 07 ott 2016
 *      Author: daniele
 */

#include <systemc.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string.h>

#include "tl.h"
#include "pugixml.hpp"

#include "SystemManager.h"

using namespace std;
using namespace pugi;

////////////////////////////
// SBM INDEPENDENT
////////////////////////////

// Constructor
SystemManager::SystemManager()
{

	VPS = generateProcessInstances();
	VCH = generateChannelInstances();

	VBB = generateBBInstances();
	VPL = generatePhysicalLinkInstances();
	mappingPS();
	mappingCH();
}

// Fill process data structure VPS from xml file (application.xml)
vector<Process> SystemManager:: generateProcessInstances(){

	vector<Process> vps2;

	int exp_id = 0;

	int processId;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(APPLICATION);

	xml_node instancesPS2 = doc.child("instancesPS");

	for (pugi::xml_node xn_process = instancesPS2.first_child(); !xn_process.empty(); xn_process = xn_process.next_sibling()){

		Process pi;

		// Process Name
		pi.setName(xn_process.child_value("name"));

		// Process id
		processId = atoi((char*) xn_process.child_value("id"));
		pi.setId(processId);

		// Process Priority
		pi.setPriority(atoi((char*) xn_process.child_value("priority")));

		// Process Criticality
		pi.setCriticality(atoi((char*) xn_process.child_value("criticality")));

		// Process eqGate (HW size)
		xml_node eqGate = xn_process.child("eqGate");
		pi.setEqGate((float)eqGate.attribute("value").as_int());

		// Process dataType
		pi.setDataType(atoi((char*) xn_process.child_value("dataType")));

		// Process MemSize (SW Size)
		xml_node memSize = xn_process.child("memSize");

		xml_node codeSize = memSize.child("codeSize");
		for (pugi::xml_node processorModel = codeSize.child("processorModel"); processorModel; processorModel = processorModel.next_sibling()) {
			pi.setCodeSize( processorModel.attribute("name").as_string(), processorModel.attribute("value").as_int() );
		}

		xml_node dataSize = memSize.child("dataSize");
		for (pugi::xml_node processorModel = dataSize.child("processorModel"); processorModel; processorModel = processorModel.next_sibling()) {
			pi.setDataSize( processorModel.attribute("name").as_string(), processorModel.attribute("value").as_int() );
		}

		// Process Affinity

		xml_node affinity = xn_process.child("affinity");
		for (pugi::xml_node processorType = affinity.child("processorType"); processorType; processorType = processorType.next_sibling()) {
			string processorType_name = processorType.attribute("name").as_string();
			float affinity_value = processorType.attribute("value").as_float();
			pi.setAffinity(processorType_name, affinity_value);
		}

		// Process Concurrency

		xml_node concurrency = xn_process.child("concurrency");
		for (pugi::xml_node xn_cprocessId = concurrency.child("processId"); xn_cprocessId; xn_cprocessId = xn_cprocessId.next_sibling()) {
			unsigned int process_id_n = xn_cprocessId.attribute("id").as_int();
			float process_concurrency_value = xn_cprocessId.attribute("value").as_float();
			pi.setConcurrency(process_id_n, process_concurrency_value);
		}

		// Process Load

		xml_node load = xn_process.child("load");
		for (pugi::xml_node processorId = load.child("processorId"); processorId; processorId = processorId.next_sibling()) {
			unsigned int processor_id_n = processorId.attribute("id").as_int();
			float process_load_value = processorId.attribute("value").as_float();
			pi.setLoad(processor_id_n, process_load_value);
		}

		// Process time (init)
		pi.processTime = sc_time(0, SC_MS);

		// Process energy (init)
		pi.setEnergy(0);

		// Process Communication
		// TO DO

		if(processId == exp_id){
			vps2.push_back(pi);
			exp_id++;
		} else {
			cout << "XML for application is corrupted\n";
			exit(11);
		}

	}
	if(exp_id != NPS){
		cout << "XML for application is corrupted (NPS)\n";
		exit(11);
	}

	doc.reset();

	return vps2;

}

// Fill channel data structure VCH from xml file
vector<Channel> SystemManager:: generateChannelInstances()
{
	vector<Channel> vch;

	// parsing xml file

	xml_document myDoc;
	xml_parse_result myResult = myDoc.load_file(APPLICATION);
	xml_node instancesLL = myDoc.child("instancesLL");

	//channel parameters

	xml_node_iterator seqChannel_it;

	for (seqChannel_it=instancesLL.begin(); seqChannel_it!=instancesLL.end(); ++seqChannel_it){

		xml_node_iterator channel_node_it = seqChannel_it->begin();

		Channel ch;

		char* temp;

		// CH-NAME
		string name = channel_node_it->child_value();
		ch.setName(name);

		// CH-ID
		channel_node_it++;
		temp = (char*) channel_node_it->child_value();
		int  id = atoi(temp);
		ch.setId(id);

		// writer ID
		channel_node_it++;
		temp = (char*) channel_node_it->child_value();
		int  w_id = atoi(temp);
		ch.setW_id(w_id);

		// reader ID
		channel_node_it++;
		temp = (char*) channel_node_it->child_value();
		int  r_id = atoi(temp);
		ch.setR_id(r_id);

		// CH-width (logical width)
		channel_node_it++;
		temp = (char*) channel_node_it->child_value();
		int  width = atoi(temp);
		ch.setWidth(width);

		ch.setNum(0);

		vch.push_back(ch);

	}

	return vch;
}

/*
* for a given processID, increments the profiling variable
* (the number of "loops" executed by the process)
*/
void SystemManager::PS_Profiling(int processId)
{
	VPS[processId].profiling++;
}

// Check if a process is allocated on a SPP
bool SystemManager::checkSPP(int processId)
{
	return VBB[allocationPS_BB[processId]].getProcessors()[0].getProcessorType() == "SPP";
}

// Return a subset of allocationPS by considering only processes mapped to BB with ID equal to bb_unit_id
vector<int> SystemManager::getAllocationPS_BB(int bb_id)
{
	vector<int> pu_alloc;
	for (unsigned int j = 2; j < allocationPS_BB.size(); j++) // 0 and 1 are the testbench
	{
		if (allocationPS_BB[j] == bb_id) pu_alloc.push_back(j);
	}
	return pu_alloc;
}


///// UPDATE XML Concurrency and Communication

void SystemManager::deleteConcXmlConCom()
{

	pugi::xml_document myDoc;
	pugi::xml_parse_result myResult = myDoc.load_file("./XML/application.xml");
	cout << "XML Delete result: " << myResult.description() << endl;

	//method 2: use object/node structure
	pugi::xml_node instancesPS = myDoc.child("instancesPS");
	xml_node processes = instancesPS.child("process");

	for (int i = 0; i < NPS; i++){

		xml_node concom = processes.child("concurrency");
		for (pugi::xml_node processorId = concom.child("processId"); processorId; processorId = processorId.next_sibling()) {
			concom.remove_child(processorId);
		}

		xml_node concom2 = processes.child("comunication");
		for (pugi::xml_node processorId = concom2.child("rec"); processorId; processorId = processorId.next_sibling()) {
			concom2.remove_child(processorId);
		}

		processes = processes.next_sibling();

	}

	xml_node instancesCH = myDoc.child("instancesLL");
	xml_node processesCH = instancesCH.child("logical_link");

	for (int i = 0; i < NCH; i++){

		xml_node concom3 = processesCH.child("concurrency");
		for (pugi::xml_node processorId = concom3.child("channelId"); processorId; processorId = processorId.next_sibling()) {
			concom3.remove_child(processorId);
		}

		processesCH = processesCH.next_sibling();

	}

	myDoc.save_file("./XML/application.xml");
	cout << endl;
}

void SystemManager::updateXmlConCom(float matrixCONC_PS_N[NPS][NPS], unsigned int matrixCOM[NPS][NPS], float matrixCONC_CH_N[NCH][NCH])
{
	pugi::xml_document myDoc;
	pugi::xml_parse_result myResult = myDoc.load_file("./XML/application.xml");
	cout << "XML result: " << myResult.description() << endl;

	//method 2: use object/node structure
	pugi::xml_node instancesPS = myDoc.child("instancesPS");

	for (xml_node_iterator seqProcess_it = instancesPS.begin(); seqProcess_it != instancesPS.end(); ++seqProcess_it){
		int Id = atoi(seqProcess_it->child_value("id"));

		if (seqProcess_it->child("concurrency")){
			pugi::xml_node concurrency = seqProcess_it->child("concurrency");
			for (int i = 0; i<NPS; i++){
				if (i != Id){
					pugi::xml_node conc_it = concurrency.append_child("processId");
					conc_it.append_attribute("id").set_value(i);
					conc_it.append_attribute("value").set_value(matrixCONC_PS_N[Id][i]);
				}
			}
		}
		else{
			pugi::xml_node concurrency = seqProcess_it->append_child("concurrency");
			for (int i = 0; i<NPS; i++){
				if (i != Id){
					pugi::xml_node conc_it = concurrency.append_child("processId");
					conc_it.append_attribute("id").set_value(i);
					conc_it.append_attribute("value").set_value(matrixCONC_PS_N[Id][i]);
				}
			}
		}
	}

	//method 2: use object/node structure
	pugi::xml_node instancesCOM = myDoc.child("instancesPS");

	for (pugi::xml_node_iterator seqProcess_it = instancesCOM.begin(); seqProcess_it != instancesCOM.end(); ++seqProcess_it){
		int Id = atoi(seqProcess_it->child_value("id"));

		if (seqProcess_it->child("comunication")){
			pugi::xml_node comunication = seqProcess_it->child("comunication");
			for (int i = 0; i<NPS; i++){
				if (i != Id){
					pugi::xml_node com_it = comunication.append_child("rec");
					com_it.append_attribute("idRec").set_value(i);
					com_it.append_attribute("value").set_value(matrixCOM[Id][i]);
				}
			}
		}
		else{
			pugi::xml_node comunication = seqProcess_it->append_child("comunication");
			for (int i = 0; i<NPS; i++){
				if (i != Id){
					pugi::xml_node com_it = comunication.append_child("rec");
					com_it.append_attribute("idRec").set_value(i);
					com_it.append_attribute("value").set_value(matrixCOM[Id][i]);
				}
			}
		}

	}

	pugi::xml_node instancesLL = myDoc.child("instancesLL");

	for (xml_node_iterator seqLink_it = instancesLL.begin(); seqLink_it != instancesLL.end(); ++seqLink_it){
		int Id = atoi(seqLink_it->child_value("id"));

		if (seqLink_it->child("concurrency")){
			pugi::xml_node concurrencyL = seqLink_it->child("concurrency");
			for (int i = 0; i<NCH; i++){
				if (i != Id){
					pugi::xml_node concL_it = concurrencyL.append_child("channelId");
					concL_it.append_attribute("id").set_value(i);
					concL_it.append_attribute("value").set_value(matrixCONC_CH_N[Id][i]);
				}
			}
		}
		else{
			pugi::xml_node concurrencyL = seqLink_it->append_child("concurrency");
			for (int i = 0; i<NCH; i++){
				if (i != Id){
					pugi::xml_node concL_it = concurrencyL.append_child("channelId");
					concL_it.append_attribute("id").set_value(i);
					concL_it.append_attribute("value").set_value(matrixCONC_CH_N[Id][i]);
				}
			}
		}
	}

	cout << "Saving result: " << myDoc.save_file("./XML/application.xml") << endl;
	myDoc.reset();
	cout << endl;
}

#if defined(_TIMING_ENERGY_)

	// Fill VBB data structure from xml file (instancesTL.xml)
	vector<BasicBlock> SystemManager::generateBBInstances(){

		/*****************************
		*   LOAD BASIC BLOCKS
		*****************************/

		char* temp;
		vector<BasicBlock> vbb;

		// parsing xml file
		xml_document myDoc;
		xml_parse_result myResult = myDoc.load_file("./XML/instancesTL.xml");
		xml_node instancesBB = myDoc.child("instancesBB");

		for (xml_node_iterator seqBB_it=instancesBB.begin(); seqBB_it!=instancesBB.end(); ++seqBB_it){

			xml_node_iterator BB_it = seqBB_it->begin();
			BasicBlock bb;

			//BB-ID
			int id = atoi(BB_it->child_value());
			bb.setId(id);

			//BB-NAME
			BB_it++;
			string BBname = BB_it->child_value();
			bb.setName(BBname);

			//BB-TYPE
			BB_it++;
			string type = BB_it->child_value();
			bb.setType(type);

			// PROCESSING UNIT

			BB_it++;

			vector<ProcessingUnit> vpu;

			for(xml_node child = seqBB_it->child("processingUnit");child;child= child.next_sibling("processingUnit")){

				xml_node_iterator pu_it = child.begin();
				ProcessingUnit pu;

				//PU-NAME
				string puName = pu_it->child_value();
				pu.setName(puName);

				//PU-ID
				pu_it++;
				int idPU = atoi(pu_it->child_value());

				pu.setId(idPU);

				//Processor Type
				pu_it++;
				string puType = pu_it->child_value();
				pu.setProcessorType(puType);

				// PU-cost
				pu_it++;
				float idCost = (float) atof(pu_it->child_value());
				pu.setCost(idCost);

				//PU-ISA
				pu_it++;
				string puISA = pu_it->child_value();
				pu.setISA(puISA);

				// PU-Frequency (MHz)
				pu_it++;
				float idFreq = (float) atof(pu_it->child_value());
				pu.setFrequency(idFreq);

				// PU-CC4CS
				float** array = new float*[5];

				//Int8
				pu_it++;
				float idCC4CSminint8 = (float) atof(pu_it->child_value());
				pu_it++;
				float idCC4CSmaxint8 = (float) atof(pu_it->child_value());
				//Int16
				pu_it++;
				float idCC4CSminint16 = (float) atof(pu_it->child_value());
				pu_it++;
				float idCC4CSmaxint16 = (float) atof(pu_it->child_value());
				//Int32
				pu_it++;
				float idCC4CSminint32 = (float) atof(pu_it->child_value());
				pu_it++;
				float idCC4CSmaxint32 = (float) atof(pu_it->child_value());
				//Float
				pu_it++;
				float idCC4CSminfloat = (float) atof(pu_it->child_value());
				pu_it++;
				float idCC4CSmaxfloat = (float) atof(pu_it->child_value());
				//Tot
				pu_it++;
				float idCC4CSmin = (float) atof(pu_it->child_value());
				pu_it++;
				float idCC4CSmax = (float) atof(pu_it->child_value());

				array[0] = new float[2];
				array[0][0] = idCC4CSminint8;
				array[0][1] = idCC4CSmaxint8;
				array[1] = new float[2];
				array[1][0] = idCC4CSminint16;
				array[1][1] = idCC4CSmaxint16;
				array[2] = new float[2];
				array[2][0] = idCC4CSminint32;
				array[2][1] = idCC4CSmaxint32;
				array[3] = new float[2];
				array[3][0] = idCC4CSminfloat;
				array[3][1] = idCC4CSmaxfloat;
				array[4] = new float[2];
				array[4][0] = idCC4CSmin;
				array[4][1] = idCC4CSmax;
				pu.setCC4S(array);

				// PU-Power (W)
				pu_it++;
				float idPow = (float) atof(pu_it->child_value());
				pu.setPower(idPow);

				// PU-MIPS
				pu_it++;
				float idMIPS = (float) atof(pu_it->child_value());
				pu.setMIPS(idMIPS);

				// PU-I4CS
				pu_it++;
				float idI4CSmin = (float) atof(pu_it->child_value());
				pu.setI4CSmin(idI4CSmin);
				pu_it++;
				float idI4CSmax = (float) atof(pu_it->child_value());
				pu.setI4CSmax(idI4CSmax);

				// PU-Vdd (V)
				pu_it++;
				float idVdd = (float)atof(pu_it->child_value());
				pu.setVdd(idVdd);

				// PU-Idd (A)
				pu_it++;
				float idIdd = (float)atof(pu_it->child_value());
				pu.setIdd(idIdd);

				// PU-overheadCS (us)
				pu_it++;
				float idOver = (float)atof(pu_it->child_value());
				pu.setOverheadCS(sc_time((int)idOver, SC_US));

				vpu.push_back(pu);

	}
			// LOACL MEMORY
			bb.setProcessor(vpu);

			BB_it++;

			xml_node instancesLM = seqBB_it->child("localMemory");
			xml_node_iterator lm_it = instancesLM.begin();

			//CODE SIZE
			int lmCodeSize = (int)atof(lm_it->child_value());
			bb.setCodeSize(lmCodeSize);

			//DATA SIZE
			lm_it++;
			int lmDataSize = (int)atof(lm_it->child_value());
			bb.setDataSize(lmDataSize);

			//eQG
			lm_it++;
			temp = (char*)lm_it->child_value();
			int lmEqG = (int)atof(temp);
			bb.setEqG(lmEqG);

			// Comunication
			BB_it++;

			xml_node instancesCU = seqBB_it->child("communicationUnit");
			xml_node_iterator cu_it = instancesCU.begin();

			// TO DO

			// Free Running time
			BB_it++;

			xml_node instancesFRT = seqBB_it->child("loadEstimation");
			xml_node_iterator frt_it = instancesFRT.begin();

			float lmFreeRunningTime = frt_it->attribute("value").as_float();
			bb.setFRT(lmFreeRunningTime);

			vbb.push_back(bb);
		}

		return vbb;
	}
#else

/*
This method generates a dummy instance of a basic block.
Each BB contains more than one processing unit inside.
*/
vector<BasicBlock> SystemManager::generateBBInstances(){

	vector<BasicBlock> vbb;

	for (int i = 0; i < NBB; i++){

		BasicBlock bb;

		//BB-ID
		bb.setId(i);

		//BB-NAME
		bb.setName("dummy");

		//BB-TYPE
		bb.setType("dummy");

		// PROCESSING UNIT

		vector<ProcessingUnit> vpu;

		for (int j = 0; j < 4; j++){       // each block contains at most 4 pu


			ProcessingUnit pu;

			//PU-NAME

			pu.setName("dummy");

			//PU-ID
			int idPU = j;

			pu.setId(idPU);

			//Processor Type
			pu.setProcessorType("dummy");

			//// PU-cost
			//pu.setCost(0);

			//PU-ISA
			pu.setISA("dummy");

			// PU-Frequency (MHz)
			pu.setFrequency(0);

			// PU-CC4CS
			float** array = new float*[5]; //TODO: eliminare **?

			//Int8
			float idCC4CSminint8 = 0;
			float idCC4CSmaxint8 = 0;
			//Int16

			float idCC4CSminint16 = 0;
			float idCC4CSmaxint16 = 0;
			//Int32
			float idCC4CSminint32 = 0;
			float idCC4CSmaxint32 = 0;
			//Float
			float idCC4CSminfloat = 0;
			float idCC4CSmaxfloat = 0;
			//Tot
			float idCC4CSmin = 0;
			float idCC4CSmax = 0;

			//TODO: ciclo con tutti 0!
			array[0] = new float[2];
			array[0][0] = idCC4CSminint8;
			array[0][1] = idCC4CSmaxint8;
			array[1] = new float[2];
			array[1][0] = idCC4CSminint16;
			array[1][1] = idCC4CSmaxint16;
			array[2] = new float[2];
			array[2][0] = idCC4CSminint32;
			array[2][1] = idCC4CSmaxint32;
			array[3] = new float[2];
			array[3][0] = idCC4CSminfloat;
			array[3][1] = idCC4CSmaxfloat;
			array[4] = new float[2];
			array[4][0] = idCC4CSmin;
			array[4][1] = idCC4CSmax;
			pu.setCC4S(array);

			// PU-Power (W)
			pu.setPower(0);

			// PU-MIPS
			float idMIPS = 0;
			pu.setMIPS(idMIPS);

			// PU-I4CS
			float idI4CSmin = 0;
			pu.setI4CSmin(idI4CSmin);
			float idI4CSmax = 0;
			pu.setI4CSmax(idI4CSmax);

			// PU-Vdd (V)
			float idVdd = 0;
			pu.setVdd(idVdd);

			// PU-Idd (A)
			float idIdd = 0;
			pu.setIdd(idIdd);

			// PU-overheadCS (us)
			float idOver = 0;
			pu.setOverheadCS(sc_time((int)idOver, SC_US));

			vpu.push_back(pu);

		}
		bb.setProcessor(vpu);

		// LOCAL MEMORY

		//CODE SIZE
		bb.setCodeSize(0);

		//DATA SIZE
		bb.setDataSize(0);

		//eQG
		bb.setEqG(0);

		// Free Running time
		float lmFreeRunningTime = 0;
		bb.setFRT(lmFreeRunningTime);
		vbb.push_back(bb);
	}

	return vbb;
}

#endif

#if defined(_TIMING_ENERGY_)

	// Fill link data structure VPL from xml file (instancesTL.xml)
	vector<PhysicalLink> SystemManager:: generatePhysicalLinkInstances()
	{
		vector<PhysicalLink> VPL;

		PhysicalLink l;

		// parsing xml file

		xml_document myDoc;
		xml_parse_result myResult = myDoc.load_file("./XML/instancesTL.xml");
		xml_node instancesPL = myDoc.child("instancesPL");

		//link parameters

		xml_node_iterator seqLink_it;

		for (seqLink_it=instancesPL.begin(); seqLink_it!=instancesPL.end(); ++seqLink_it){

			xml_node_iterator link_node_it = seqLink_it->begin();

			char* temp;

			// Link NAME
			string name = link_node_it->child_value();
			l.setName(name);

			// Link ID
			link_node_it++;
			temp = (char*) link_node_it->child_value();
			unsigned int id = atoi(temp);
			l.setId(id);

			// Link PHYSICAL WIDTH
			link_node_it++;
			temp = (char*) link_node_it->child_value();
			unsigned int physical_width = atoi(temp);
			l.setPhysicalWidth(physical_width);

			// Link TCOMM
			link_node_it++;
			temp = (char*) link_node_it->child_value();
			float tc = (float) atof(temp);
			sc_time tcomm(tc, SC_MS);
			l.setTcomm(tcomm);

			// Link TACOMM
			link_node_it++;
			temp = (char*) link_node_it->child_value();
			float tac = (float) atof(temp);
			sc_time tacomm(tac, SC_MS);
			l.setTAcomm(tacomm);

			// Link BANDWIDTH
			link_node_it++;
			temp = (char*) link_node_it->child_value();
			unsigned int bandwidth = atoi(temp);
			l.setBandwidth(bandwidth);

			// Link a2 (coefficient needed to compute energy of the communication)
			link_node_it++;
			temp = (char*) link_node_it->child_value();
			float a2 = (float) atof(temp);
			l.seta2(a2);

			// Link a1 (coefficient needed to compute energy of the communication)
			link_node_it++;
			temp = (char*) link_node_it->child_value();
			float a1 = (float) atof(temp);
			l.seta1(a1);

			VPL.push_back(l);
		}

		return VPL;
	}

#else

vector<PhysicalLink> SystemManager::generatePhysicalLinkInstances()
{
	vector<PhysicalLink> VPL;

	for (int i = 0; i < NPL; i++){

		PhysicalLink pl;

		pl.setId(i);

		pl.setName("dummy");

		pl.physical_width=1; // width of the physical link
		pl.tcomm=sc_time(0, SC_MS); // LP: (bandwidth / phisycal_widht = 1/sec=hz (inverto)) ( per 1000)  (non sforare i 5 ms)
		pl.tacomm=sc_time(0, SC_MS); // LP: tcomm * K (es:K=1)
		pl.bandwidth=0; // bandwidth in bit/s
		pl.a2=0; // a2 coefficient of energy curve
		pl.a1=0; // a1 coefficient of energy curve

		VPL.push_back(pl);
	}

	return VPL;
}

#endif 

#if defined(_TIMING_ENERGY_)

	// Fill allocationPS data structure from xml file
	void SystemManager:: mappingPS()
	{
		int exp_id = 0;

		// parsing xml file

		xml_document myDoc;
		xml_parse_result myResult = myDoc.load_file(MAPPING_PS_BB);
		xml_node mapping = myDoc.child("mapping");

		//mapping parameters (process to processor)

		xml_node_iterator mapping_it;

		for (mapping_it=mapping.begin(); mapping_it!=mapping.end(); ++mapping_it){

			xml_node_iterator child_mapping_it = mapping_it->begin();

			int processId = child_mapping_it->attribute("PSid").as_int();
			//string processorName = child_mapping_it->attribute("PRname").as_string();
			string bbName = child_mapping_it->attribute("BBname").as_string();
			int bbId = child_mapping_it->attribute("value").as_int();
			int processingunitID = child_mapping_it->attribute("PUid").as_int();    //added **************
			int partitionID = child_mapping_it->attribute("PTid").as_int();      //added **************

			if(processId == exp_id){
				allocationPS_BB.push_back(bbId);
				exp_id++;
			} else {
				cout << "XML for allocation is corrupted\n";
				exit(11);
			}
		}
	}

#else

void SystemManager::mappingPS(){
	for (int j = 0; j<NPS; j++){
		int bbId = 0;
		allocationPS_BB.push_back(bbId);
	}
}

#endif

#if defined(_TIMING_ENERGY_)

	// Fill allocationCH_PL data structure from xml file
	void SystemManager::mappingCH()
	{
		int exp_id = 0;

		// parsing xml file

		xml_document myDoc;
		xml_parse_result myResult = myDoc.load_file(MAPPING_LC_PL);
		xml_node mapping = myDoc.child("mapping");

		//mapping parameters (channel to link)

		xml_node_iterator mapping_it;

		for (mapping_it=mapping.begin(); mapping_it!=mapping.end(); ++mapping_it){

			xml_node_iterator child_mapping_it = mapping_it->begin();

			int channelId = child_mapping_it->attribute("CHid").as_int();
			string linkName = child_mapping_it->attribute("Lname").as_string();
			int linkId = child_mapping_it->attribute("value").as_int();

			if(channelId == exp_id){
				allocationCH_PL.push_back(linkId);
				exp_id++;
			} else {
				cout << "XML for allocation is corrupted\n";
				exit(11);
			}
		}
	}

#else

void SystemManager::mappingCH(){
	for (int j = 0; j < NCH; j++){
		int linkId = 0;
		allocationCH_PL.push_back(linkId);
	}
}

#endif

	///// OTHER METHODS ////////


	// Evaluate the simulated time for the execution of a statement
	/*
	* for a given processID, returns the simulated time
	* (the time needed by processor, for the allocated process, to
	* to execute a statement)
	*/
	sc_time SystemManager:: updateSimulatedTime(int processId)
	{	
		// Id representing process dominant datatype 
		int dataType = VPS[processId].getDataType();


		//*********************VPU WAS CHANGED IN VBB**********************
		float CC4Smin = VBB[allocationPS_BB[processId]].getProcessors()[0].getCC4S()[dataType][0]; // Average/min number of clock cycles needed by the PU to execute a C statement
		float CC4Smax = VBB[allocationPS_BB[processId]].getProcessors()[0].getCC4S()[dataType][1]; // Average/max number of clock cycles needed by the PU to execute a C statement

		// Affinity-based interpolation and round up of CC4CSaff
		unsigned int CC4Saff = (unsigned int) ceil(CC4Smin + ((CC4Smax-CC4Smin)*(1-VPS[processId].getAffinityByName(VBB[allocationPS_BB[processId]].getProcessors()[0].getProcessorType()))));

		float frequency = VBB[allocationPS_BB[processId]].getProcessors()[0].getFrequency(); // Frequency of the processor (MHz)
		sc_time value((CC4Saff/(frequency*1000)), SC_MS); // Average time (ms) needed to execute a C statement

		return value;
	}

	// The computation depends on the value setted for energyComputation (EPI or EPC)
	float SystemManager:: updateEstimatedEnergy(int processId)
	{
		float J4CS;
		float P;
		if(energyComputation == "EPC") {
			// EPC --> J4CS = CC4CSaff * EPC = CC4CSaff * (P/f)

			// Id representing process dominant datatype 
			int dataType = VPS[processId].getDataType();


			//I HAVE TO ADD A LOOP IN ORDER TO TAKE THE PARAMETERS OF EACH PROCESSOR (?) **********************

			float CC4Smin = VBB[allocationPS_BB[processId]].getProcessors()[0].getCC4S()[dataType][0]; // Average/min number of clock cycles needed by the PU to execute a C statement

			//float CC4Smin = VBB[allocationPS_BB[processId]].getCC4S()[dataType][0]; // Average/min number of clock cycles needed by the PU to execute a C statement

			//float CC4Smax = VBB[allocationPS_BB[processId]].getCC4S()[dataType][1];
			float CC4Smax = VBB[allocationPS_BB[processId]].getProcessors()[0].getCC4S()[dataType][1];// Average/max number of clock cycles needed by the PU to execute a C statement

			// Affinity-based interpolation 
			float CC4Saff = CC4Smin + ((CC4Smax-CC4Smin)*(1-VPS[processId].getAffinityByName(VBB[allocationPS_BB[processId]].getProcessors()[0].getProcessorType())));

			if(this->checkSPP(processId)) {
				// if the process is on a SPP (HW) --> P = Vdd * Idd (V*A = W)

				P = VBB[allocationPS_BB[processId]].getProcessors()[0].getVdd() * VBB[allocationPS_BB[processId]].getProcessors()[0].getIdd();

			} else {
				// if the process is on a GPP/DSP (SW) --> P (W)

				P = VBB[allocationPS_BB[processId]].getProcessors()[0].getPower();

			}
			// EPC = P/f (W/MHz = uJ)
			float EPC = P / VBB[allocationPS_BB[processId]].getProcessors()[0].getFrequency();

			J4CS = CC4Saff * EPC; // uJ
		} else { 
			// EPI 

			if(this->checkSPP(processId)) {
				// if the process is on a SPP (HW) --> J4CS = CC4CSaff * P * (1/f)

				// Id representing process dominant datatype 
				int dataType = VPS[processId].getDataType();	

				float CC4Smin = VBB[allocationPS_BB[processId]].getProcessors()[0].getCC4S()[dataType][0]; // Average/min number of clock cycles needed by the PU to execute a C statement

				float CC4Smax = VBB[allocationPS_BB[processId]].getProcessors()[0].getCC4S()[dataType][1]; // Average/max number of clock cycles needed by the PU to execute a C statement

				// Affinity-based interpolation 
				float CC4Saff = CC4Smin + ((CC4Smax-CC4Smin)*(1-VPS[processId].getAffinityByName(VBB[allocationPS_BB[processId]].getProcessors()[0].getProcessorType())));

				// P = Vdd * Idd (V*A = W)
				P = VBB[allocationPS_BB[processId]].getProcessors()[0].getVdd() * VBB[allocationPS_BB[processId]].getProcessors()[0].getIdd();

				J4CS = CC4Saff * (P / VBB[allocationPS_BB[processId]].getProcessors()[0].getFrequency()); // uJ
			} else {
				// if the process is on a GPP/DSP (SW) --> J4CS = I4CSaff * EPI = I4CSaff * (P/MIPS)

				float I4CSmin = VBB[allocationPS_BB[processId]].getProcessors()[0].getI4CSmin(); // Average/min number of assembly instructions to execute a C statement

				float I4CSmax = VBB[allocationPS_BB[processId]].getProcessors()[0].getI4CSmax(); // Average/max number of assembly instructions to execute a C statement

				// Affinity-based interpolation 
				float I4CSaff = I4CSmin + ((I4CSmax-I4CSmin)*(1-VPS[processId].getAffinityByName(VBB[allocationPS_BB[processId]].getProcessors()[0].getProcessorType())));

				P = VBB[allocationPS_BB[processId]].getProcessors()[0].getPower(); // Watt

				// EPI = P/MIPS (uJ/instr)
				float EPI = P / VBB[allocationPS_BB[processId]].getProcessors()[0].getMIPS();

				J4CS = I4CSaff * EPI; // uJ
			}
		} 
		return J4CS;
	}

	// Increase processTime for each statement
	void SystemManager:: increaseSimulatedTime(int processId)
	{
		VPS[processId].processTime += updateSimulatedTime(processId); // Cumulated sum of the statement execution time
	}

	// Increase energy for each statement
	void SystemManager:: increaseEstimatedEnergy(int processId)
	{
		VPS[processId].energy += updateEstimatedEnergy(processId); // Cumulated sum of the statement execution energy
	}

	// Increase processTime for the wait of the timers
	void SystemManager::increaseTimer(int processId, sc_time delta)
	{
		VPS[processId].processTime += delta; // Cumulated sum of the statement execution time
	}

	// Energy XML Updates

	void SystemManager::deleteConcXmlEnergy(){
		char* temp;
		int Id;

		pugi::xml_document myDoc;
		pugi::xml_parse_result myResult = myDoc.load_file("./XML/application.xml");
		cout << "XML Delete result: " << myResult.description() << endl;

		//method 2: use object/node structure
		pugi::xml_node instancesPS = myDoc.child("instancesPS");
		xml_node processes = instancesPS.child("process");
		for(int i = 0; i < NPS; i++){
			temp = (char*) processes.child_value("id");
			Id = atoi(temp); //id process

			xml_node energy = processes.child("energy");
			for (pugi::xml_node processorId = energy.child("processorId"); processorId; processorId = processorId.next_sibling()) {
				unsigned int processor_id_n = processorId.attribute("id").as_int();//
				float process_load_value = processorId.attribute("value").as_float();//
				if(allocationPS_BB[Id] == processor_id_n){
					energy.remove_child(processorId);
				}
			}
			processes = processes.next_sibling();
		}
		myDoc.save_file("./XML/application.xml");
		cout<<endl;

		/////////////////////////////////////

		pugi::xml_document myDoc2;
		pugi::xml_parse_result myResult2 = myDoc2.load_file("./XML/instancesTL.xml");
		cout << "XML result: " << myResult2.description() << endl;

		pugi::xml_node instancesBB = myDoc2.child("instancesBB");
		xml_node basicBlock = instancesBB.child("basicBlock");
		for(int i = 0; i < NBB; i++){
			temp = (char*) basicBlock.child_value("id");
			Id = atoi(temp); //id process

			xml_node energyEst = basicBlock.child("energyEstimation");
			for (pugi::xml_node energyTOT = energyEst.child("energyTOT"); energyTOT; energyTOT = energyTOT.next_sibling()) {
				unsigned int processor_id_n = energyTOT.attribute("id").as_int();//
				float energy_value = energyTOT.attribute("value").as_float();//
				if(Id == allocationPS_BB[2]){
					energyEst.remove_child(energyTOT);
				}
			}
			basicBlock = basicBlock.next_sibling();
		}
		cout << "Saving result: " << myDoc2.save_file("./XML/instancesTL.xml") << endl;
		cout<<endl;

	}

	void SystemManager:: updateXmlEnergy()
	{

		pugi::xml_document myDoc;
		pugi::xml_parse_result myResult = myDoc.load_file("./XML/application.xml");
		cout << "XML result: " << myResult.description() << endl;

		//method 2: use object/node structure
		pugi::xml_node instancesPS = myDoc.child("instancesPS");

		/////////////////////// ENERGY //////////////////////////////

		pugi::xml_node instancesPS2 = myDoc.child("instancesPS");
		float sumEnergyTot=0;
		for (xml_node_iterator seqProcess_it2=instancesPS2.begin(); seqProcess_it2!=instancesPS2.end(); ++seqProcess_it2){
			int Id = atoi(seqProcess_it2->child_value("id"));
			if(seqProcess_it2->child("energy")){
				pugi::xml_node energy = seqProcess_it2->child("energy");
				pugi::xml_node energy_it = energy.append_child("processorId");
				energy_it.append_attribute("id").set_value(allocationPS_BB[Id]);
				energy_it.append_attribute("value").set_value(VPS[Id].getEnergy());
			}else{
				pugi::xml_node energy = seqProcess_it2->append_child("energy");
				pugi::xml_node energy_it = energy.append_child("processorId");
				energy_it.append_attribute("id").set_value(allocationPS_BB[Id]);
				energy_it.append_attribute("value").set_value(VPS[Id].getEnergy());
			}

			sumEnergyTot+=VPS[Id].getEnergy();
		}

		cout << "Saving result: " << myDoc.save_file("./XML/application.xml") << endl;
		myDoc.reset();
		cout<<endl;

		pugi::xml_document myDoc2;
		pugi::xml_parse_result myResult2 = myDoc2.load_file("./XML/instancesTL.xml");
		cout << "XML result: " << myResult2.description() << endl;

		xml_node instancesBB = myDoc2.child("instancesBB");

		for (xml_node_iterator seqBB_it=instancesBB.begin(); seqBB_it!=instancesBB.end(); ++seqBB_it){
			int Id = atoi(seqBB_it->child_value("id"));
			///////////////////// ENERGY ////////////////////////
			if(Id == allocationPS_BB[2]){
				if(seqBB_it->child("energyEstimation")){
					pugi::xml_node energyEstimation = seqBB_it->child("energyEstimation");
					xml_node entot_node = energyEstimation.append_child("energyTOT");
					entot_node.append_attribute("id").set_value(allocationPS_BB[2]);
					entot_node.append_attribute("value").set_value(sumEnergyTot);
				}else{
					pugi::xml_node energyEstimation = seqBB_it->append_child("energyEstimation");
					xml_node entot_node = energyEstimation.append_child("energyTOT");
					entot_node.append_attribute("id").set_value(allocationPS_BB[2]);
					entot_node.append_attribute("value").set_value(sumEnergyTot);
				}
			}
		}
		cout << "Saving result: " << myDoc2.save_file("./XML/instancesTL.xml") << endl;
		myDoc2.reset();
		cout<<endl;

	}


// Load Metrics

	sc_time SystemManager::getFRT(){
		return this->FRT;
	}

	void SystemManager::setFRT(sc_time x){
		FRT = x;
	}

	float* SystemManager:: loadEst(sc_time FRT_n){
	for(unsigned i =2; i<VPS.size(); i++){
			FRL[i] = (float) ((VPS[i].processTime/VPS[i].profiling)/(FRT_n/VPS[i].profiling)); //
	}
	return FRL;
	}

	float* SystemManager:: getFRL(){
		return this->FRL;
	}

	// Load XML Updates

	void SystemManager::deleteConcXmlLoad(){
		char* temp;
		int Id;

		pugi::xml_document myDoc;
		pugi::xml_parse_result myResult = myDoc.load_file("./XML/application.xml");
		cout << "XML Delete result: " << myResult.description() << endl;

		//method 2: use object/node structure
		pugi::xml_node instancesPS = myDoc.child("instancesPS");
		xml_node processes = instancesPS.child("process");
			for(int i = 0; i < NPS; i++){
				temp = (char*) processes.child_value("id");
				Id = atoi(temp); //id process
				xml_node load = processes.child("load");
				for (pugi::xml_node processorId = load.child("processorId"); processorId; processorId = processorId.next_sibling()) {
						unsigned int processor_id_n = processorId.attribute("id").as_int();//
						float process_load_value = processorId.attribute("value").as_float();//
						if(allocationPS_BB[Id] == processor_id_n){
							load.remove_child(processorId);
						}
				}

				/*	xml_node WCET = processes.child("WCET");
				for (pugi::xml_node processorId = WCET.child("processorId"); processorId; processorId = processorId.next_sibling()) {
					WCET.remove_child(processorId);
				}

				xml_node Period = processes.child("Period");
				for (pugi::xml_node processorId = Period.child("processorId"); processorId; processorId = processorId.next_sibling()) {
					Period.remove_child(processorId);
				}

				xml_node Deadline = processes.child("Deadline");
				for (pugi::xml_node processorId = Deadline.child("processorId"); processorId; processorId = processorId.next_sibling()) {
					Deadline.remove_child(processorId);
				} */

				processes = processes.next_sibling();
			}
		myDoc.save_file("./XML/application.xml");
		cout<<endl;

		pugi::xml_document myDoc2;
		pugi::xml_parse_result myResult2 = myDoc2.load_file("./XML/instancesTL.xml");
		cout << "XML result: " << myResult2.description() << endl;

		pugi::xml_node instancesBB = myDoc2.child("instancesBB");
		xml_node basicBlock = instancesBB.child("basicBlock");
		for(int i = 0; i < NBB; i++){
			temp = (char*) basicBlock.child_value("id");
			Id = atoi(temp); //id process

			xml_node loadEst = basicBlock.child("loadEstimation");
			for (pugi::xml_node loadTOT = loadEst.child("FreeRunningTime"); loadTOT; loadTOT = loadTOT.next_sibling()) {
					unsigned int processor_id_n = loadTOT.attribute("id").as_int();//
					float energy_value = loadTOT.attribute("value").as_float();//
					if(Id == allocationPS_BB[2]){
						loadEst.remove_child(loadTOT);
					}
			}
			basicBlock = basicBlock.next_sibling();
		}
		cout << "Saving result: " << myDoc2.save_file("./XML/instancesTL.xml") << endl;
		myDoc2.reset();
		cout<<endl;

	}

	void SystemManager:: updateXmlLoad()
	{
		pugi::xml_document myDoc;
		pugi::xml_parse_result myResult = myDoc.load_file("./XML/application.xml");
		cout << "XML result: " << myResult.description() << endl;

		//method 2: use object/node structure
		pugi::xml_node instancesPS = myDoc.child("instancesPS");

		for (xml_node_iterator seqProcess_it=instancesPS.begin(); seqProcess_it!=instancesPS.end(); ++seqProcess_it){
			int Id = atoi(seqProcess_it->child_value("id"));

			///////////////////// LOAD ////////////////////////////

			if(seqProcess_it->child("load")){
				pugi::xml_node load = seqProcess_it->child("load");
				pugi::xml_node load_it = load.append_child("processorId");
				load_it.append_attribute("id").set_value(allocationPS_BB[Id]);
				load_it.append_attribute("value").set_value(FRL[Id]);
			}else{
				pugi::xml_node load = seqProcess_it->append_child("load");
				pugi::xml_node load_it = load.append_child("processorId");
				load_it.append_attribute("id").set_value(allocationPS_BB[Id]);
				load_it.append_attribute("value").set_value(FRL[Id]);
			}
		}

	/////////////////////// WCET //////////////////////////////

	////method 2: use object/node structure
	//pugi::xml_node instancesPS2 = myDoc.child("instancesPS");

	//for (pugi::xml_node_iterator seqProcess_it=instancesPS2.begin(); seqProcess_it!=instancesPS2.end(); ++seqProcess_it){
	//	int Id = atoi(seqProcess_it->child_value("id"));
	//
	//	if(seqProcess_it->child("WCET")){
	//		pugi::xml_node comunication = seqProcess_it->child("WCET");
	//		for (int i=0; i<NPS; i++){
	//			if(i!=Id){
	//				pugi::xml_node wcet_it = comunication.append_child("processorId");
	//				double wcet_task = (VPS[Id].processTime.to_seconds());
	//				wcet_it.append_attribute("id").set_value(i);
	//				wcet_it.append_attribute("value").set_value((wcet_task/VPS[Id].profiling)*1000000.0);
	//			}
	//		}
	//	}else{
	//		pugi::xml_node WCET = seqProcess_it->append_child("WCET");
	//		for (int i=0; i<VPU.size(); i++){
	//			if(i!=Id){
	//				pugi::xml_node wcet_it = WCET.append_child("processorId");
	//				double wcet_task = (VPS[Id].processTime.to_seconds());
	//				wcet_it.append_attribute("id").set_value(i);
	//				wcet_it.append_attribute("value").set_value((wcet_task/VPS[Id].profiling)*1000000.0);
	//			}
	//		}
	//	}
	//}

	/////////////////////// PERIOD //////////////////////////////

	//pugi::xml_node instancesPS3 = myDoc.child("instancesPS");

	//for (xml_node_iterator seqLink_it=instancesPS3.begin(); seqLink_it!=instancesPS3.end(); ++seqLink_it){
	//	int Id = atoi(seqLink_it->child_value("id"));
	//
	//	if(seqLink_it->child("Period")){
	//		pugi::xml_node Period = seqLink_it->child("Period");
	//		for (int i=0; i<NPS; i++){
	//			if(i!=Id){
	//				pugi::xml_node period_it = Period.append_child("processorId");
	//				period_it.append_attribute("id").set_value(i);
	//				double period_value = (FRT.to_seconds());
	//				period_it.append_attribute("value").set_value((period_value/VPS[Id].profiling)*1000000.0);
	//			}
	//		}
	//	}else{
	//		pugi::xml_node Period = seqLink_it->append_child("Period");
	//		for (int i=0; i<NPS; i++){
	//			if(i!=Id){
	//				pugi::xml_node period_it = Period.append_child("processorId");
	//				period_it.append_attribute("id").set_value(i);
	//				double period_value = (FRT.to_seconds());
	//				period_it.append_attribute("value").set_value((period_value/VPS[Id].profiling)*1000000.0);
	//			}
	//		}
	//	}
	//}

	///////////////////////// DEADLINE //////////////////////////////

	//	pugi::xml_node instancesPS4 = myDoc.child("instancesPS");

	//for (xml_node_iterator seqLink_it=instancesPS4.begin(); seqLink_it!=instancesPS4.end(); ++seqLink_it){
	//	int Id = atoi(seqLink_it->child_value("id"));

	//	if(seqLink_it->child("Deadline")){
	//		pugi::xml_node Deadline = seqLink_it->child("Deadline");
	//		for (int i=0; i<NPS; i++){
	//			if(i!=Id){
	//				pugi::xml_node dead_it = Deadline.append_child("processorId");
	//				dead_it.append_attribute("id").set_value(i);
	//				double deadline_value = (FRT.to_seconds());
	//				double dead_tot = (deadline_value/VPS[Id].profiling)*1000000.0;
	//				cout<<"VPS["<<Id<<"].profiling -->  "<<VPS[Id].profiling<<endl;
	//				dead_it.append_attribute("value").set_value(dead_tot);
	//			}
	//		}
	//	}else{
	//		pugi::xml_node Deadline = seqLink_it->append_child("Deadline");
	//		for (int i=0; i<NPS; i++){
	//			if(i!=Id){
	//				pugi::xml_node dead_it = Deadline.append_child("processorId");
	//				dead_it.append_attribute("id").set_value(i);
	//				double deadline_value = (FRT.to_seconds());
	//				double dead_tot = (deadline_value/VPS[Id].profiling)*1000000.0;
	//				dead_it.append_attribute("value").set_value(dead_tot);
	//			}
	//		}
	//	}
	//}

	cout << "Saving result: " << myDoc.save_file("./XML/application.xml") << endl;
	myDoc.reset();
	cout<<endl;

	/* pugi::xml_document myDoc2;
	pugi::xml_parse_result myResult2 = myDoc2.load_file("./XML/instancesTL.xml");
	cout << "XML result: " << myResult2.description() << endl;

	xml_node instancesBB = myDoc2.child("instancesBB");

	for (xml_node_iterator seqBB_it=instancesBB.begin(); seqBB_it!=instancesBB.end(); ++seqBB_it){
		int Id = atoi(seqBB_it->child_value("id"));

		///////////////////// LOAD ////////////////////////////

		if(seqBB_it->child("loadEstimation")){
			pugi::xml_node loadEstimation = seqBB_it->child("loadEstimation");
			xml_node frl_node = loadEstimation.child("FreeRunningTime");
			if(!(allocationPS_BB[Id] != Id))
			{
				sc_time local_frt = FRT;
				//frl_node.attribute("value")=(local_frt.to_double()*1000); //another solution for the number conversion
				frl_node.attribute("value")=(local_frt.to_seconds()*1000);
			}
		}else{
				pugi::xml_node loadEstimation = seqBB_it->append_child("loadEstimation");
				xml_node frl_node = loadEstimation.append_child("FreeRunningTime");
				if(allocationPS_BB[Id] == Id)
				{
					sc_time local_frt = FRT;
					//frl_node.attribute("value")=(local_frt.to_double()*1000);  //another solution for the number conversion
					frl_node.attribute("value")=(local_frt.to_seconds()*1000);
				}

			}
	}

	cout << "Saving result: " << myDoc2.save_file("./XML/instancesTL.xml") << endl;
	myDoc2.reset();
	cout<<endl; */

	///////////////////////////////////////////////////

	pugi::xml_document myDoc2;
	pugi::xml_parse_result myResult2 = myDoc2.load_file("./XML/instancesTL.xml");
	cout << "XML result: " << myResult2.description() << endl;

	xml_node instancesBB = myDoc2.child("instancesBB");

	for (xml_node_iterator seqBB_it=instancesBB.begin(); seqBB_it!=instancesBB.end(); ++seqBB_it){
		int Id = atoi(seqBB_it->child_value("id"));
			///////////////////// ENERGY ////////////////////////
		if(Id == allocationPS_BB[2]){
			if(seqBB_it->child("loadEstimation")){
				pugi::xml_node energyEstimation = seqBB_it->child("loadEstimation");
				xml_node entot_node = energyEstimation.append_child("FreeRunningTime");
				entot_node.append_attribute("id").set_value(allocationPS_BB[2]);
				sc_time local_frt = FRT;
				entot_node.append_attribute("value").set_value(local_frt.to_seconds()*1000);
			}else{
				pugi::xml_node energyEstimation = seqBB_it->append_child("energyEstimation");
				xml_node entot_node = energyEstimation.append_child("energyTOT");
				entot_node.append_attribute("id").set_value(allocationPS_BB[2]);
				sc_time local_frt = FRT;
				entot_node.append_attribute("value").set_value(local_frt.to_seconds()*1000);
			}
		}
	}
	cout << "Saving result: " << myDoc2.save_file("./XML/instancesTL.xml") << endl;
	myDoc2.reset();
	cout<<endl;

}

