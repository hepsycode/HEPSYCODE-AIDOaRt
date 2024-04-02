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

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include "pugixml.hpp"
#include "specification.h"

using namespace std;
using namespace pugi;

// Constructor
specification::specification(int start)
{
	numMaxElitism = 0;

	load_constraints();
    load_parameters();
    create_basicBlocks();
    create_processes();
}

// Load into the specification the project constraints (from XML file)
void specification::load_constraints(){

	/*****************************
	 *   LOAD CONSTRAINTS
	*****************************/

	xml_document myDoc;
	xml_parse_result myResult = myDoc.load_file("./XML/constraints.xml");
	xml_node constraints = myDoc.child("constraints");

	std::cout << "Constraints Load result: " << myResult.description() << endl;

	this->numberProcesses = atof(constraints.child_value("numberProcesses"));
	this->TTC = atof(constraints.child_value("TTC"));
	this->instanceBB = atof(constraints.child_value("numberInstancesBB"));
	this->instanceMaxBB = atof(constraints.child_value("numberMaxInstancesBB"));
	this->loadMax = atof(constraints.child_value("loadMax"));

	cout << endl << "****** CONSTRAINTS ******" << endl;
	cout << "numberProcesses: " << this->numberProcesses  << endl;
	cout << "instanceBB: " << this->instanceBB  << endl;
	cout << "instanceMaxBB: " << this->instanceMaxBB  << endl;
	cout << "TTC: " << this->TTC  << endl;
	cout << "Load MAX: " << this->loadMax << endl;

	myDoc.reset();

}

// Load into the specification the PAM parameters (from XML file)
void specification::load_parameters(){

	/*****************************
	 *   LOAD PARAMETERS
	*****************************/
	xml_document myDoc;
	xml_parse_result myResult = myDoc.load_file("./XML/PAM1parameter.xml");
	xml_node par = myDoc.first_child();
	std::cout <<endl<< "Parameter load result: " << myResult.description() << endl;
	xml_node ga_node = par.child("ga");
	xml_node_iterator ga_node_it =  ga_node.begin();

	char* temp;

	cout<<endl<<"****** GA PARAMETERS ******"<<endl;

	temp = (char*) ga_node_it->child_value();
	generations = atoi(temp);
	cout<<"Generations: "<<generations<<endl;

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
	birthRate = atof(temp);
	cout<<"birthRate: "<<birthRate<<endl;

	ga_node_it++;
	temp = (char*) ga_node_it->child_value();
	deathRate = atof(temp);
	cout<<"deathRate: "<<deathRate<<endl;

	ga_node_it++;
	temp = (char*) ga_node_it->child_value();
	radRate = atof(temp);
	cout<<"radioactivityRate: "<<radRate<<endl;

	cout<<endl<<"****** PESI ******"<<endl;

	xml_node weights = par.child("weights");
	xml_node_iterator weights_it = weights.begin();

	temp = (char*) weights_it->child_value();
	aff = atof(temp);
	cout<<"affinity_w: "<<aff<<endl;
	// For generate elitism array based on weight != 0
	if (aff != 0) numMaxElitism++;

	weights_it++;
	temp = (char*) weights_it->child_value();
	comm = atof(temp);
	cout<<"comm_w: "<<comm<<endl;
	if (comm != 0) numMaxElitism++;

	weights_it++;
	temp = (char*) weights_it->child_value();
	par_w = atof(temp);
	cout<<"parall_w: "<<par_w<<endl;
	if (par_w != 0) numMaxElitism++;

	weights_it++;
	temp = (char*) weights_it->child_value();
	load = atof(temp);
	cout<<"load_w: "<<load<<endl;
	if (load != 0) numMaxElitism++;

	weights_it++;
	temp = (char*) weights_it->child_value();
	cost = atof(temp);
	cout<<"cost_w: "<<cost<<endl;
	if (cost != 0) numMaxElitism++;

	weights_it++;
	temp = (char*) weights_it->child_value();
	size_SW = atof(temp);
	cout<<"kbSize_w: "<<size_SW<<endl;
	if (size_SW != 0) numMaxElitism++;

	weights_it++;
	temp = (char*) weights_it->child_value();
	size_HW = atof(temp);
	cout<<"eqgSize_w: "<<size_HW<<endl;
	if (size_HW != 0) numMaxElitism++;

	weights_it++;
	temp = (char*) weights_it->child_value();
	crit = atof(temp);
	cout<<"crit_w: "<<crit<<endl;
	if (crit != 0) numMaxElitism++;

	weights_it++;
	temp = (char*) weights_it->child_value();
	feas = atof(temp);
	cout<<"Feasibility: "<<feas<<endl<<endl<<endl;

	myDoc.reset();

	// This increase is to consider the individual with best CF in the elite individuals
	numMaxElitism++;

}

// Load into the specification the information about the Basic Block considered (from XML file)
void specification::create_basicBlocks(){

	/*****************************
	 *   LOAD BASIC BLOCKS
	*****************************/

	int i, j;
	numBB=instanceBB;
	char* temp;

    architecture = new basicBlock[numBB]; // BasicBlock array

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
		architecture[j].id = atoi(temp);
		cout << "id: " << architecture[j].id << endl;

		// BB Name
		string name = basicB.child_value("name");
		architecture[j].name = basicB.child_value("name");
		cout << "BB Name: " << architecture[j].name << endl;

		// BB Name
		string type2 = basicB.child_value("type");
		architecture[j].type = basicB.child_value("type");
		cout << "Type: " << architecture[j].type << endl;

		// BB processing unit
		xml_node processingUnit = basicB.child("processingUnit");

		string p_name = processingUnit.child_value("name");
		architecture[j].procUnit->processingUnitName =p_name;
		cout << "processingUnit Name: " << architecture[j].procUnit->processingUnitName << endl;

		string pt_name = processingUnit.child_value("processorType");
		architecture[j].procUnit->processorType =pt_name;
		cout << "processor Type: " << architecture[j].procUnit->processorType << endl;

		temp = (char*) processingUnit.child_value("idprocessor");
		architecture[j].procUnit->idprocessor = atoi(temp);
		cout << "Id Processor: " << architecture[j].procUnit->idprocessor << endl;

		temp = (char*) processingUnit.child_value("cost");
		architecture[j].procUnit->cost = atof(temp);

		if(maxCOST < architecture[j].procUnit->cost){
			maxCOST = architecture[j].procUnit->cost;
		}
		cout << "cost: " << architecture[j].procUnit->cost << endl;

		// BB Mem (SW Size)
		xml_node memBB = basicB.child("localMemory");

		temp = (char*) memBB.child_value("codeSize");
		architecture[j].memUnit->codeSize = atoi(temp);
		cout << "CodeSize: " << architecture[j].memUnit->codeSize << endl;

		temp = (char*) memBB.child_value("dataSize");
		architecture[j].memUnit->dataSize = atoi(temp);
		cout << "DataSize: " << architecture[j].memUnit->dataSize << endl;

		//BB Mem (HW Size)
		temp = (char*) memBB.child_value("eqG");
		architecture[j].memUnit->eqG = atoi(temp);
		cout << "eqG: " << architecture[j].memUnit->eqG << endl;

		// BB communication Unit
		xml_node communicationUnit = basicB.child("communicationUnit");
		string c_name = communicationUnit.child_value("name");
		architecture[j].commUnit->name =c_name;
		cout << "communicationUnit Name: " << architecture[j].commUnit->name << endl;


		// BB loadEstimation
		xml_node loadEstimation = basicB.child("loadEstimation");

		xml_node frl_load = loadEstimation.child("FreeRunningTime");

		architecture[j].FreeRunningTime = frl_load.attribute("value").as_float();
		cout << "FreeRunningTime: " << architecture[j].FreeRunningTime << endl;

		j++;

		cout << endl;
		basicB = basicB.next_sibling();
	}

	doc.reset();

}

// Load into the specification the information about the processes that compose
// the application under test (from XML file)
void specification::create_processes(){

	/*****************************
	 *   LOAD PROCESSES
	*****************************/

	int i, j;
	numProc=numberProcesses;
	int numProcMat = numProc*numProc;
	char* temp;

    project = new process[numProc]; // Processes array
    comMat   = new float[numProcMat]; // Communication Matrix
    parMat   = new float[numProcMat]; // Parallelism Matrix

    //For each process of the specification
    for(i = 0; i < numProc; i++){
    	project[i].name = "";
		project[i].id = 0;
		project[i].priority = 0;
		project[i].criticality = 0;
		project[i].eqg = 0;
		//For each type of executor save the affinity value (at the moment choose by the
		//designer)
		for(j = 0; j < MAXCLUSTER; j++){
			project[i].DA[j]=0;
		}
		//For each considered Basic Block
		for(j = 0; j < MAXBB; j++){
			project[i].size_SW_RAM[j] = 0;
			project[i].size_SW_ROM[j] = 0;
			project[i].load[j]=0;
		}
    }

    //initialize communication and parallelism matrix
    for(i = 0; i < numProcMat; i++){
    	comMat[i]=0;
    	parMat[i]=0;
    }

    for(i = 0; i < numProc; i++){
    	for(j = 0; j < instanceBB; j++){
    		project[i].load[j]=0;
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
		//We don't consider the stimulus and display processes (that are the first and
		//second process in the XML file)
		if(i > 1){

			// Process Name
			string name = processes.child_value("name");
			project[j].name = processes.child_value("name");
			cout << "name: " << project[j].name;
			cout << endl;

			// Process id
			temp = (char*) processes.child_value("id");
			project[j].id = atoi(temp);
			cout << "id: " << project[j].id << endl;

			// Process Priority
			temp = (char*) processes.child_value("priority");
			project[j].priority = atoi(temp);
			cout << "priority: " << project[j].priority << endl;

			// Process Criticality
			temp = (char*) processes.child_value("criticality");
			project[j].criticality = atoi(temp);
			cout << "criticality: " << project[j].criticality << endl;

			// Process eqGate (HW size)
			xml_node eqGate = processes.child("eqGate");
			project[j].eqg = eqGate.attribute("value").as_int();
			cout << "eqGate: " << project[j].eqg << endl;

			// Process MemSize (SW Size)
			cout << "MemSize: " << endl;
			xml_node memSize = processes.child("memSize");

			cout << "CodeSize: " << endl;
			xml_node codeSize = memSize.child("codeSize");
			int k = 0;
			for (pugi::xml_node processorModel = codeSize.child("processorModel"); processorModel; processorModel = processorModel.next_sibling()) {
				cout << "ProcessorModel: " << processorModel.attribute("name").as_string() << " Id: " << processorModel.attribute("id").as_int() << " Code Size: " << processorModel.attribute("value").as_int()<<endl;
				k = processorModel.attribute("id").as_int();
				project[j].size_SW_ROM[k] = processorModel.attribute("value").as_int();
			}

			cout << "DataSize: " << endl;
			xml_node dataSize = memSize.child("dataSize");
			for (pugi::xml_node processorModel = dataSize.child("processorModel"); processorModel; processorModel = processorModel.next_sibling()) {
				cout << "Processor Model: " << processorModel.attribute("name").as_string()<< " Id: " << processorModel.attribute("id").as_int() << " Data Size: " << processorModel.attribute("value").as_int()<<endl;
				k = processorModel.attribute("id").as_int();
				project[j].size_SW_RAM[k] = processorModel.attribute("value").as_int();
			}

			// Process Affinity
			//Based on processor type assign an affinity value (from XML file)
			cout << "Affinity: " << endl;
			xml_node affinity = processes.child("affinity");
			for (pugi::xml_node processorType = affinity.child("processorType"); processorType; processorType = processorType.next_sibling()) {
				string processorType_name = processorType.attribute("name").as_string();
				float affinity_value = processorType.attribute("value").as_float();
				if(processorType_name == "GPP"){
					project[j].DA[0] = processorType.attribute("value").as_float();
					cout << "Processor Type: " << processorType_name << " Id: 0 " << " Affinity: " << affinity_value <<endl;
				}else if(processorType_name == "DSP"){
					project[j].DA[1] = processorType.attribute("value").as_float();
					cout << "Processor Type: " << processorType_name << " Id: 1 " << " Affinity: " << affinity_value <<endl;
				}else if(processorType_name == "SPP"){
					project[j].DA[2] = processorType.attribute("value").as_float();
					cout << "Processor Type: " << processorType_name << " Id: 2 " << " Affinity: " << affinity_value <<endl;
				}
				//cout << "Processor Type: " << processorType_name << " Affinity: " << affinity_value <<endl;
			}

			// Process Concurrency
			//Creation of Parallelism Matrix
			cout << "Concurrency: " << endl;
			xml_node concurrency = processes.child("concurrency");
			for (pugi::xml_node processId = concurrency.child("processId"); processId; processId = processId.next_sibling()) {
				unsigned int process_id_n = processId.attribute("id").as_int();
				float process_concurrency_value = processId.attribute("value").as_float();
				//We don't consider the stimulus and display processes
				if(process_id_n > 1){
					//Matrix build as array where each numProc values represent a row of
					//the matrix
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
				//Save for each process (contained in the project array) the load value
				//estimated for each SW processor
				if(TTC < architecture[processor_id_n].FreeRunningTime){
					project[j].load[processor_id_n] = process_load_value/(TTC/architecture[processor_id_n].FreeRunningTime);
				}else{
					project[j].load[processor_id_n] = process_load_value;
				}
				cout << "Basic Block Id: " << processor_id_n << " Load: " << project[j].load[processor_id_n] << endl;
			}

			// Process Communication
			cout << "Communication: " << endl;
			xml_node communication = processes.child("communication");
			for (pugi::xml_node rec = communication.child("rec"); rec; rec = rec.next_sibling()) {
				unsigned int rec_id_n = rec.attribute("idRec").as_int();
				unsigned int communication_value = rec.attribute("value").as_int();
				//We don't consider the stimulus and display processes
				if(rec_id_n > 1){
					//Matrix build as array where each numProc values represent a row of
					//the matrix
					comMat[j*numProc + (rec_id_n - 2)] = communication_value;
					cout << "Receiver Id: " << rec_id_n << " Communication: " << comMat[j*numProc + (rec_id_n - 2)] <<endl;
				}
			}

			j++;

		}

		cout << endl;
		processes = processes.next_sibling();
	}

	doc.reset();

	//Print Parallelism and Communication Matrix
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

	cout<<endl<<"****** Communication MATRIX ******"<<endl;

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

	/////////////////////////////////////////////////

    // Compute max Total Communication Cost
    maxTCC=0;

    // Is the sum of all value of the Communication Matrix
    for(i=0; i<numProc; i++)
          for(j=0; j < numProc; j++)
          {
                maxTCC += comMat[i*numProc+j];
          }
    if (maxTCC==0) maxTCC=1;

    // Compute max Exploited Parallelism
    maxEP=0;

    // Is the sum of all value of the Parallelism Matrix
    for(i=0; i<numProc; i++)
          for(j=0; j < numProc; j++)
          {
                maxEP += parMat[i*numProc+j];
          }
    if (maxEP==0) maxEP=1;
}

// Destructor
specification::~specification()
{
	// Memory deallocation
	delete[] project;
	delete[] comMat;
	delete[] parMat;
}

