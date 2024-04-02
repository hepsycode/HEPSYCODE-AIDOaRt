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
 * Authors: Vittoriano Muttillo, Luigi Pomante                                  *
 *                                                                              *
 * email: vittoriano.muttillo@guest.univaq.it                                   *
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
// Description : Specifica
//============================================================================

#include "specifica.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>

#include "pugixml.hpp"

using namespace std;
using namespace pugi;

specifica::specifica(int start)
{
	load_constraints();
    load_parameters();
    create_basicBlocks();
    create_mapping();
    create_processes();
    create_logical_link();
    create_links();
}

void specifica::load_constraints(){

	/*****************************
	 *   LOAD CONSTRAINTS
	*****************************/

	xml_document myDoc;
	xml_parse_result myResult = myDoc.load_file("./XML/constraints.xml");
	xml_node constraints = myDoc.child("constraints");

	std::cout << "Constraints Load result: " << myResult.description() << endl;

	this->numberProcesses = atof(constraints.child_value("numberProcesses"));
	this->numLinkLogical = atof(constraints.child_value("numberLogicalLinks"));
	this->TTC = atof(constraints.child_value("TTC"));
	this->instanceBB = atof(constraints.child_value("numberInstancesBB"));
	this->instanceLinks = atof(constraints.child_value("numberInstancesLinks"));
	this->numLink = this->instanceLinks;
	this->instanceMaxBB = atof(constraints.child_value("numberMaxInstancesBB"));
	this->loadMax = atof(constraints.child_value("loadMax"));

	cout << endl << "****** CONSTRAINTS ******" << endl;
	cout << "numberProcesses: " << this->numberProcesses  << endl;
	cout << "instanceBB: " << this->instanceBB  << endl;
	cout << "instanceLinks: " << this->instanceLinks  << endl;
	cout << "instanceMaxBB: " << this->instanceMaxBB  << endl;
	cout << "TTC: " << this->TTC  << endl;
	cout << "Load MAX: " << this->loadMax << endl;

	myDoc.reset();

}

void specifica::load_parameters(){

	/*****************************
	 *   LOAD PARAMETERS
	*****************************/
	xml_document myDoc;
	xml_parse_result myResult = myDoc.load_file("./XML/PAM2parameter.xml");
	xml_node par = myDoc.first_child();
	std::cout <<endl<< "Parameter load result: " << myResult.description() << endl;
	xml_node ga_node = par.child("ga");
	xml_node_iterator ga_node_it =  ga_node.begin();

	char* temp;

	cout<<endl<<"****** PARAMETRI GA ******"<<endl;

	temp = (char*) ga_node_it->child_value();
	generazioni = atoi(temp);
	cout<<"Generations: "<<generazioni<<endl;

	ga_node_it++;
	temp = (char*) ga_node_it->child_value();
	initialPop = atoi(temp);
	cout<<"Starting Pop: "<<initialPop<<endl;

	ga_node_it++;
	temp = (char*) ga_node_it->child_value();
	nPart = atoi(temp);
	cout<<"Number of Partition: "<<nPart<<endl;

	ga_node_it++;
	temp = (char*) ga_node_it->child_value();
	numMaxPart = atoi(temp);
	cout<<"Number Max of Partition: "<<numMaxPart<<endl;

	ga_node_it++;
	temp = (char*) ga_node_it->child_value();
	crip = atof(temp);
	cout<<"birthRate: "<<crip<<endl;

	ga_node_it++;
	temp = (char*) ga_node_it->child_value();
	tmort = atof(temp);
	cout<<"deathRate: "<<tmort<<endl;

	ga_node_it++;
	temp = (char*) ga_node_it->child_value();
	crad = atof(temp);
	cout<<"radioactivityRate: "<<crad<<endl;

	cout<<endl<<"****** PESI ******"<<endl;

	xml_node weights = par.child("weights");
	xml_node_iterator weights_it = weights.begin();

	temp = (char*) weights_it->child_value();
	sat = atof(temp);
	cout<<"saturation: "<<sat<<endl;

	weights_it++;
	temp = (char*) weights_it->child_value();
	expl = atof(temp);
	cout<<"exploitation: "<<expl<<endl;

	weights_it++;
	temp = (char*) weights_it->child_value();
	conc = atof(temp);
	cout<<"concurrency: "<< conc <<endl;

	weights_it++;
	temp = (char*) weights_it->child_value();
	ph_cost = atof(temp);
	cout<<"physical_cost: "<<ph_cost<<endl;

	weights_it++;
	temp = (char*) weights_it->child_value();
	criticality = atof(temp);
	cout<<"criticality: "<<criticality<<endl;

	weights_it++;
	temp = (char*) weights_it->child_value();
	fatt = atof(temp);
	cout<<"Fattibilità: "<<fatt<<endl<<endl<<endl;

	myDoc.reset();

}

void specifica::create_basicBlocks(){

	/*****************************
	 *   LOAD BASIC BLOCKS
	*****************************/

	int i, j;
	numBB=instanceBB;
	char* temp;

    architettura = new basicblock[numBB]; // Array dei basicBlock

	/////////////////////////////////////////////////

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("./XML/instancesTL.xml");
    cout << "Basic Blocks Load result: " << result.description() << endl;

	cout<<endl<<"****** Basic Blocks ******"<<endl;

    //method 2: use object/node structure
	xml_node instancesBB = doc.child("instancesBB");
	xml_node basicB = instancesBB.child("basicBlock");

	j = 0;
	this->maxCOST = 0;
	for(i = 0; i < numBB; i++){

		// BB id
		temp = (char*) basicB.child_value("id");
		architettura[j].id = atoi(temp);
		cout << "id: " << architettura[j].id << endl;

		// BB Name
		string name = basicB.child_value("name");
		architettura[j].name = basicB.child_value("type");
		cout << "BB Name: " << architettura[j].name << endl;

		// BB Name
		string type2 = basicB.child_value("type");
		architettura[j].type = basicB.child_value("type");
		cout << "Type: " << architettura[j].type << endl;

		// BB processing unit
		xml_node processingUnit = basicB.child("processingUnit");

		string p_name = processingUnit.child_value("name");
		architettura[j].processingUnit =p_name;
		cout << "processingUnit Name: " << architettura[j].processingUnit << endl;

		string pt_name = processingUnit.child_value("processorType");
		architettura[j].processorType =pt_name;
		cout << "processor Type: " << architettura[j].processorType << endl;

		temp = (char*) processingUnit.child_value("idprocessor");
		architettura[j].idprocessor = atoi(temp);
		cout << "Id Processor: " << architettura[j].idprocessor << endl;

		temp = (char*) processingUnit.child_value("cost");
		architettura[j].cost = atof(temp);

		if(maxCOST < architettura[j].cost){
			maxCOST = architettura[j].cost;
		}
		cout << "cost: " << architettura[j].cost << endl;

		// BB Mem (SW Size)
		xml_node memBB = basicB.child("localMemory");

		temp = (char*) memBB.child_value("codeSize");
		architettura[j].codeSize = atoi(temp);
		cout << "CodeSize: " << architettura[j].codeSize << endl;

		temp = (char*) memBB.child_value("dataSize");
		architettura[j].dataSize = atoi(temp);
		cout << "DataSize: " << architettura[j].dataSize << endl;

		temp = (char*) memBB.child_value("eqG");
		architettura[j].eqG = atoi(temp);
		cout << "eqG: " << architettura[j].eqG << endl;

		// BB communication Unit
		xml_node communicationUnit = basicB.child("communicationUnit");
		for(int iii = 0; iii < MAXEIL; iii++){
			architettura[j].communicationUnit[iii] = "0";
		}
		int k = 0;
		for (pugi::xml_node processId = communicationUnit.child("name"); processId; processId = processId.next_sibling()) {
			string c_name = processId.child_value();
			architettura[j].communicationUnit[k] =c_name;
			cout << "EIL: " << architettura[j].communicationUnit[k] << endl;
			k++;
		}

		// BB loadEstimation
		xml_node loadEstimation = basicB.child("loadEstimation");

		xml_node frl_load = loadEstimation.child("FreeRunningTime");

		architettura[j].FreeRunningTime = frl_load.attribute("value").as_float();
		cout << "FreeRunningTime: " << architettura[j].FreeRunningTime << endl;

		j++;

		cout << endl;
		basicB = basicB.next_sibling();
	}

	doc.reset();

}

///////////////////// LOAD MAPPING ///////////////////

void specifica::create_mapping(){

	/*****************************
	 *   LOAD MAPPING
	*****************************/

	int i, j;
	numProc=numberProcesses;
	char* temp;

	mappingInst = new mapping[numProc]; // Array delle progedure

	/////////////////////////////////////////////////

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("./XML/mappingPS.xml");
    cout << "Mapping result: " << result.description() << endl;

    cout<<endl<<"****** Mapping ******"<<endl;

	xml_node instancesPS2 = doc.child("mapping");
	xml_node processes = instancesPS2.child("allocation");

	j = 0;
	for(i = 0; i < numProc + 2; i++){

		if(i > 1){

			// Process id
			xml_node procID = processes.child("processId");
			mappingInst[j].process_id = procID.attribute("PSid").as_int();
			cout << "Process id: " << mappingInst[j].process_id << endl;

			// Process Name
			mappingInst[j].processor_name = procID.attribute("PRname").as_string();
			cout << "Processor name: " << mappingInst[j].processor_name << endl;

			// Process id
			mappingInst[j].processor_id = procID.attribute("value").as_int();
			cout << "Process id: " << mappingInst[j].processor_id << endl;

			j++;

		}

		cout << endl;
		processes = processes.next_sibling();
	}

	doc.reset();

}


////////////////////////////////////////////////////////////

void specifica::create_processes(){

	/*****************************
	 *   LOAD PROCESSES
	*****************************/

	int i, j;
	numProc=numberProcesses;
	int numProcMat = numProc*numProc;
	char* temp;

    progetto = new procedura[numProc]; // Array delle progedure
    comMat   = new float[numProcMat]; // MAtrice di comunicazione
    parMat   = new float[numProcMat]; // MAtrice del parallelismo

    for(i = 0; i < numProc; i++){
    	progetto[i].name = "";
		progetto[i].id = 0;
		progetto[i].priority = 0;
		progetto[i].criticality = 0;
		progetto[i].eqg = 0;
		for(j = 0; j < MAXCLUSTER; j++){
			progetto[i].DA[j]=0;
		}
		for(j = 0; j < MAXBB; j++){
			progetto[i].size_SW_RAM[j] = 0;
			progetto[i].size_SW_ROM[j] = 0;
			progetto[i].load[j]=0;
		}
    }

    for(i = 0; i < numProcMat; i++){
    	comMat[i]=0;
    	parMat[i]=0;
    }

    for(i = 0; i < numProc; i++){
    	for(j = 0; j < instanceBB; j++){
    		progetto[i].load[j]=0;
    	}
    }

	/////////////////////////////////////////////////

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("./XML/application.xml");
    cout << "Processes Load result: " << result.description() << endl;

    cout<<endl<<"****** Processes ******"<<endl;

	xml_node instancesPS2 = doc.child("instancesPS");
	xml_node processes = instancesPS2.child("process");

	j = 0;
	for(i = 0; i < numProc + 2; i++){

		if(i > 1){

			// Process Name
			string name = processes.child_value("name");
			progetto[j].name = processes.child_value("name");
			cout << "name: " << progetto[j].name << endl;

			// Process id
			temp = (char*) processes.child_value("id");
			progetto[j].id = atoi(temp);
			cout << "id: " << progetto[j].id << endl;

			// Process Priority
			temp = (char*) processes.child_value("priority");
			progetto[j].priority = atoi(temp);
			cout << "priority: " << progetto[j].priority << endl;

			// Process Criticality
			temp = (char*) processes.child_value("criticality");
			progetto[j].criticality = atoi(temp);
			cout << "criticality: " << progetto[j].criticality << endl;

			// Process eqGate (HW size)
			xml_node eqGate = processes.child("eqGate");
			progetto[j].eqg = eqGate.attribute("value").as_int();
			cout << "eqGate: " << progetto[j].eqg << endl;

			// Process MemSize (SW Size)
			cout << "MemSize: " << endl;
			xml_node memSize = processes.child("memSize");

			cout << "CodeSize: " << endl;
			xml_node codeSize = memSize.child("codeSize");
			int k = 0;
			for (pugi::xml_node processorModel = codeSize.child("processorModel"); processorModel; processorModel = processorModel.next_sibling()) {
				cout << "ProcessorModel: " << processorModel.attribute("name").as_string() << " Id: " << processorModel.attribute("id").as_int() << " Code Size: " << processorModel.attribute("value").as_int()<<endl;
				k = processorModel.attribute("id").as_int();
				progetto[j].size_SW_RAM[k] = processorModel.attribute("value").as_int();
			}

			cout << "DataSize: " << endl;
			xml_node dataSize = memSize.child("dataSize");
			for (pugi::xml_node processorModel = dataSize.child("processorModel"); processorModel; processorModel = processorModel.next_sibling()) {
				cout << "Processor Model: " << processorModel.attribute("name").as_string()<< " Id: " << processorModel.attribute("id").as_int() << " Data Size: " << processorModel.attribute("value").as_int()<<endl;
				k = processorModel.attribute("id").as_int();
				progetto[j].size_SW_RAM[k] = processorModel.attribute("value").as_int();
			}

			// Process Affinity

			cout << "Affinity: " << endl;
			xml_node affinity = processes.child("affinity");
			for (pugi::xml_node processorType = affinity.child("processorType"); processorType; processorType = processorType.next_sibling()) {
				string processorType_name = processorType.attribute("name").as_string();
				float affinity_value = processorType.attribute("value").as_float();
				if(processorType_name == "GPP"){
					progetto[j].DA[0] = processorType.attribute("value").as_float();
					cout << "Processor Type: " << processorType_name << " Id: 0 " << " Affinity: " << affinity_value <<endl;
				}else if(processorType_name == "DSP"){
					progetto[j].DA[1] = processorType.attribute("value").as_float();
					cout << "Processor Type: " << processorType_name << " Id: 1 " << " Affinity: " << affinity_value <<endl;
				}else if(processorType_name == "SPP"){
					progetto[j].DA[2] = processorType.attribute("value").as_float();
					cout << "Processor Type: " << processorType_name << " Id: 2 " << " Affinity: " << affinity_value <<endl;
				}
				//cout << "Processor Type: " << processorType_name << " Affinity: " << affinity_value <<endl;
			}

			// Process Concurrency

			cout << "Concurrency: " << endl;
			xml_node concurrency = processes.child("concurrency");
			for (pugi::xml_node processId = concurrency.child("processId"); processId; processId = processId.next_sibling()) {
				unsigned int process_id_n = processId.attribute("id").as_int();
				float process_concurrency_value = processId.attribute("value").as_float();
				if(process_id_n > 1){
					parMat[j*numProc + (process_id_n-2)] = process_concurrency_value;
					cout << "Process Row Id " << j + 2 << " Process Column Id: " << (process_id_n) << " Concurrency: " << parMat[j*numProc + (process_id_n-2)] <<endl;
				}
			}

			// Process Load

			cout << "Load: " << endl;
			xml_node load = processes.child("load");
			for (pugi::xml_node processorId = load.child("processorId"); processorId; processorId = processorId.next_sibling()) {
				unsigned int processor_id_n = processorId.attribute("id").as_int();
				float process_load_value = processorId.attribute("value").as_float();
				if(TTC < architettura[processor_id_n].FreeRunningTime){
					progetto[j].load[processor_id_n] = process_load_value/(TTC/architettura[processor_id_n].FreeRunningTime);
				}else{
					progetto[j].load[processor_id_n] = process_load_value;
				}
				cout << "Basic Block Id: " << processor_id_n << " Load: " << progetto[j].load[processor_id_n] << endl;
			}

			// Process Communication
			cout << "Comunication: " << endl;
			xml_node comunication = processes.child("comunication");
			for (pugi::xml_node rec = comunication.child("rec"); rec; rec = rec.next_sibling()) {
				unsigned int rec_id_n = rec.attribute("idRec").as_int();
				unsigned int comunication_value = rec.attribute("value").as_int();
				if(rec_id_n > 1){
					comMat[j*numProc + (rec_id_n - 2)] = comunication_value;
					cout << "Receiver Id: " << rec_id_n + 2 << " Comunication: " << comMat[j*numProc + (rec_id_n - 2)] <<endl;
				}
			}

			j++;

		}

		cout << endl;
		processes = processes.next_sibling();
	}

	doc.reset();

	cout<<endl<<"****** Parallel MATRIX ******"<<endl;

	cout<< setw(2) << "   ";
	for (int j=0; j<numProc; j++){
		cout<< setw(8) << j + 2 <<" ";
	}
	cout<< endl;

	for(i=0; i<numProc; i++){
		cout<< setw(2) << i + 2 << " " ;
		for(j=0; j<numProc; j++)
		{
			cout<< setw(8) << parMat[i*numProc+j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl<<"****** Comunication MATRIX ******"<<endl;

	cout<< setw(2) << "   ";
	for (int j=0; j<numProc; j++){
		cout<< setw(6) << j + 2 <<" ";
	}
	cout<< endl;

	for(i=0; i<numProc; i++){
		cout<< setw(2) << i + 2 << " " ;
		for(j=0; j<numProc; j++)
		{
			cout<< setw(6) << comMat[i*numProc+j]<<" ";
		}
		cout<<endl;
	}

	/////////// Calcolo coppie ////////////////////

	cout<<endl<<"****** Coppie MATRIX ******"<<endl;

	int matrix_bandwidth[numBB][numBB] = {};

	for(i=0; i<numProc; i++){
		for(j=0; j<numProc; j++)
		{
			if(comMat[i*numProc+j]!=0){
				if(mappingInst[i].processor_id != mappingInst[j].processor_id){
					matrix_bandwidth[mappingInst[i].processor_id][mappingInst[j].processor_id] += comMat[i*numProc+j];
					matrix_bandwidth[mappingInst[j].processor_id][mappingInst[i].processor_id] += comMat[i*numProc+j];
				}
			}
		}
	}
	cout << endl;

	int tot_BBs_pair2 = 0;
	int kk = 0;
	for(i=0; i<numBB; i++){
		for(j=0; j<numBB; j++)
		{
			if(matrix_bandwidth[i][j] != 0 && j > i){
				cout<< setw(6) << "ID: " << kk <<" ";
				cout<< setw(6) << "BBi: " << i <<" ";
				cout<< setw(6) << "BBj: " << j <<" ";
				cout<< setw(6) << "Bandwidth: " << matrix_bandwidth[i][j] << " ";
				tot_BBs_pair2++;
				kk++;
				cout<<endl;
			}
		}
	}
	cout << endl;

	cout << "Total BBs Pairs: " << tot_BBs_pair2 << endl<< endl;
	numPairs = tot_BBs_pair2;

	BING_i = new int[numPairs];
	BING_j = new int[numPairs];
	BING_band = new int[numPairs];

	int k=0;
	for(i=0; i<numBB; i++){
		for(j=0; j<numBB; j++)
		{
			if(matrix_bandwidth[i][j] != 0 && j > i){
				BING_i[k] = i;
				BING_j[k] = j;
				BING_band[k] = matrix_bandwidth[i][j];
				//cout << "BING_i: " << BING_i[k] << " BING_j:" << BING_j[k] << " BING_band: " << BING_band[k];
				k++;
				//cout<<endl;
			}
		}
	}

	//cout << " BING LENGHT: " << sizeof(BING_band)/sizeof(int) << endl;

	/////////////////////////////////////////////////

    // Calcolo di maxTCC
    maxTCC=0;

    // Si ottiene sommando i dati della parte triangolare bassa della matrice
    for(i=0; i<numProc; i++)
          for(j=0; j < numProc; j++)
          {
                maxTCC += comMat[i*numProc+j];
          }
    if (maxTCC==0) maxTCC=1; // Non si sa mai...

    // Calcolo del max parallelismo
    maxEP=0;

    // Si ottiene sommando i dati della parte triangolare bassa della matrice
    for(i=0; i<numProc; i++)
          for(j=0; j < numProc; j++)
          {
                maxEP += parMat[i*numProc+j];
          }
    if (maxEP==0) maxEP=1; // Non si sa mai...
}

////////////////////////////////////////////////////////////

void specifica::create_logical_link(){

	/*****************************
	 *   LOAD PROCESSES
	*****************************/

	int i, j;
	int numChMat = numLinkLogical*numLinkLogical;
	char* temp;

	linksLogicalInst = new logical_link[numLinkLogical]; // Array delle progedure
    parMatCH   = new float[numChMat]; // MAtrice del parallelismo

    for(i = 0; i < numLinkLogical; i++){
    	linksLogicalInst[i].id = 0;
    	linksLogicalInst[i].name = "";
    	linksLogicalInst[i].w_id = 0;
    	linksLogicalInst[i].r_id = 0;
    	linksLogicalInst[i].width = 0;
    }

    for(i = 0; i < numChMat; i++){
    	parMatCH[i]=0;
    }

	/////////////////////////////////////////////////

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("./XML/application.xml");
    cout << "Logical Link Load result: " << result.description() << endl;

    cout<<endl<<"****** Channels ******"<<endl;

	xml_node instancesCh = doc.child("instancesLL");
	xml_node plogChannel = instancesCh.child("logical_link");

	j = 0;
	for(i = 0; i < numLinkLogical; i++){

		// Process Name
		string name = plogChannel.child_value("name");
		linksLogicalInst[j].name = plogChannel.child_value("name");
		cout << "name: " << linksLogicalInst[j].name << endl;

		// Process id
		temp = (char*) plogChannel.child_value("id");
		linksLogicalInst[j].id = atoi(temp);
		cout << "id: " << linksLogicalInst[j].id << endl;

		// Process w_id
		temp = (char*) plogChannel.child_value("w_id");
		linksLogicalInst[j].w_id = atoi(temp);
		cout << "w_id: " << linksLogicalInst[j].w_id << endl;

		// Process r_id
		temp = (char*) plogChannel.child_value("r_id");
		linksLogicalInst[j].r_id = atoi(temp);
		cout << "r_id: " << linksLogicalInst[j].r_id << endl;

		// Process width
		temp = (char*) plogChannel.child_value("width");
		linksLogicalInst[j].width = atoi(temp);
		cout << "width: " << linksLogicalInst[j].width << endl;

		// Channel Concurrency

		cout << "Concurrency: " << endl;
		xml_node concurrency = plogChannel.child("concurrency");
		for (pugi::xml_node channelId = concurrency.child("channelId"); channelId; channelId = channelId.next_sibling()) {
			unsigned int channel_id_n = channelId.attribute("id").as_int();
			float channel_concurrency_value = channelId.attribute("value").as_float();
			parMatCH[j*numLinkLogical + (channel_id_n)] = channel_concurrency_value;
			cout << "Channel Row Id " << j << " Channel Column Id: " << (channel_id_n) << " Concurrency: " << parMatCH[j*numLinkLogical + (channel_id_n)] <<endl;
		}

		j++;

		cout << endl;
		plogChannel = plogChannel.next_sibling();
	}

	doc.reset();

	cout<<endl<<"****** Channel Parallel MATRIX ******"<<endl;

	cout<< setw(2) << "   ";
	for (j=0; j<numLinkLogical; j++){
		cout<< setw(8) << j <<" ";
	}
	cout<< endl;

	for(i=0; i<numLinkLogical; i++){
		cout<< setw(2) << i << " " ;
		for(j=0; j<numLinkLogical; j++)
		{
			cout<< setw(8) << parMatCH[i*numLinkLogical+j]<<" ";
		}
		cout<<endl;
	}

	/////////////////////////////////////////////////

    // Calcolo del max parallelismo
    maxEPCH=0;

    // Si ottiene sommando i dati della parte triangolare bassa della matrice
    for(i=0; i<numLinkLogical; i++)
          for(j=0; j < numLinkLogical; j++)
          {
        	  maxEPCH += parMatCH[i*numLinkLogical+j];
          }
    if (maxEPCH==0) maxEPCH=1; // Non si sa mai...
}

///////////////// CREATE LINKS //////////////////////////

void specifica::create_links(){

	/*****************************
	 *   LOAD LINKS
	*****************************/

	int i, j;
	numLink=instanceLinks;
	char* temp1;

    linksInst = new link[numLink]; // Array dei link

	/////////////////////////////////////////////////

    pugi::xml_document docLink;
    pugi::xml_parse_result result = docLink.load_file("./XML/instancesTL.xml");
    cout << "Links Load result: " << result.description() << endl;

	cout<<endl<<"****** Links ******"<<endl;

    //method 2: use object/node structure
	xml_node instancesLink = docLink.child("instancesPL");
	xml_node basicLink = instancesLink.child("physical_link");

	j = 0;
	linkCostMax = 0;
	for(i = 0; i < numLink; i++){

		// Link Name
		string name = basicLink.child_value("name");
		linksInst[j].name = basicLink.child_value("name");
		cout << "Link Name: " << linksInst[j].name << endl;

		// Link id
		temp1 = (char*) basicLink.child_value("id");
		linksInst[j].id = atoi(temp1);
		cout << "id: " << linksInst[j].id << endl;

		temp1 = (char*) basicLink.child_value("physical_width");
		linksInst[j].physical_width = atoi(temp1);
		cout << "Physical Width: " << linksInst[j].physical_width << endl;

		temp1 = (char*) basicLink.child_value("tcomm");
		linksInst[j].tcomm = atof(temp1);
		cout << "tcomm: " << linksInst[j].tcomm << endl;

		temp1 = (char*) basicLink.child_value("tacomm");
		linksInst[j].tacomm = atof(temp1);
		cout << "tacomm: " << linksInst[j].tacomm << endl;

		temp1 = (char*) basicLink.child_value("bandwidth");
		linksInst[j].bandwidth = atoi(temp1);
		cout << "Bandwidth: " << linksInst[j].bandwidth << endl;

		temp1 = (char*) basicLink.child_value("maxBBs");
		linksInst[j].maxBBs = atoi(temp1);
		cout << "MaxBBs: " << linksInst[j].maxBBs << endl;

		temp1 = (char*) basicLink.child_value("cost");
		linksInst[j].cost = atoi(temp1);
		if(linksInst[j].cost > linkCostMax){
			linkCostMax += linksInst[j].cost;
		}
		cout << "Cost: " << linksInst[j].cost << endl;

		// Link Name
		string type2 = basicLink.child_value("type");
		linksInst[j].type = basicLink.child_value("type");
		cout << "Type: " << linksInst[j].type << endl;

		cout << endl;
		basicLink = basicLink.next_sibling();
		j++;
	}

	docLink.reset();

}

////////////////////////////////////////////////////////////////////

specifica::~specifica()
{
	// Deallocazione della memoria
	delete[] progetto;
	delete[] comMat;
	delete[] parMat;
}

