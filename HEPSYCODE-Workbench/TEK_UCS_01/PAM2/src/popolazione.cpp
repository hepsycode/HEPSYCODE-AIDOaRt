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
// Description : Population
//============================================================================

#include "popolazione.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <fstream>

#define TR 1

// Un partizionamento rappresenta una scelta di numero e tipo di esecutori
// e dell'allocazione delle procedure su di essi

#include "pugixml.hpp"

using namespace std;
using namespace pugi;

popolazione::~popolazione()
{
      delete[] pop;
}

// specifica, nPartizioni, numPartizioniMax, 
popolazione::popolazione(specifica *s) // @suppress("Class members should be properly initialized")
{

      int i;
      
      numPart=s->nPart;
      numPartMax=s->numMaxPart;
      numProcess=s->numProc;
      numSol=s->numPairs;
      bestCF=100;
      bestCost=0;
      count = 100;
      
      pop= new partizionamento* [numPartMax];

      pop_Best = new int[numSol];

      // Inizializza il generatore di numeri casuali
      srand(1/*getpid()*/);

      // Si aggancia alla specifica
      spec=s;
            
      // Crea partizionamenti casuali per tutta la popolazione
      for(i=0; i< numPartMax; i++)
      {
            pop[i] = new partizionamento;      
            pop[i]->inizializza( spec );
      }
      
}
            

      
void popolazione::accoppiamento( float coeffRipr )
{
      int futPop;
      int boy, girl, posizione;
      int i;

      // Politica di controllo nascite
      if (numPart >= numPartMax)  return;

      // Numerosita' della popolazione futura
      //futPop = (int) ( numPart*(1.0+coeffRipr) );
      futPop = (int) ( numPart*(1.0+coeffRipr) );

      if (futPop > numPartMax-1 ) futPop = numPartMax-1;
      
      // Ripeto finche' non raggiungo futPop
      for( ;numPart<futPop; numPart+=2)
      {
            // Seleziono due individui
            boy  = rand() % numPart;
            girl = rand() % numPart;
            
            // ...e una posizione
            posizione = rand() % spec->numPairs;
            
            // Quindi procreano! Prima meta' dei figli
            for(i=0; i<posizione; i++)
            {
                 // pop[numPart]->allocataIn[i] = pop[boy]->allocataIn[i];
                  pop[numPart]->istanza[i]    = pop[boy]->istanza[i];
                  pop[numPart]->Ltype[i] 	  = pop[boy]->Ltype[i];
            }
            for(; i<spec->numPairs; i++)
            {
                  //pop[numPart]->allocataIn[i] = pop[girl]->allocataIn[i];
                  pop[numPart]->istanza[i]    = pop[girl]->istanza[i];
                  pop[numPart]->Ltype[i] 	  = pop[girl]->Ltype[i];
            }

            // Quindi procreano! Seconda meta' dei figli
            for(i=0; i<posizione; i++)
            {
                 // pop[numPart+1]->allocataIn[i] = pop[girl]->allocataIn[i];
                  pop[numPart+1]->istanza[i]    = pop[girl]->istanza[i];
                  pop[numPart+1]->Ltype[i] 	    = pop[girl]->Ltype[i];
            }
            for(; i<spec->numPairs; i++)
            {
                 // pop[numPart+1]->allocataIn[i] = pop[boy]->allocataIn[i];
                  pop[numPart+1]->istanza[i]    = pop[boy]->istanza[i];
                  pop[numPart+1]->Ltype[i] 	    = pop[boy]->Ltype[i];
            }
      
            pop[numPart]->neonato = true;
            pop[numPart+1]->neonato = true;
      
      }

}


void popolazione::mutazione( float coeffRad )
{
      int sfigato;
      int procSel;
      int mutazioneI;
      
      // Numero di mutazioni
      int numMut = (int) ( numPart*coeffRad );
      
      // Seleziono individuo, posizione e mutazione a caso
      for(int i=0; i<numMut; i++)
      {
            sfigato   = rand() % numPart;
            procSel   = rand() % spec->numPairs;

            mutazioneI = rand()%spec->numLink;

            pop[sfigato]->istanza[procSel]    = mutazioneI;

            if(spec->linksInst[mutazioneI].type == "PTP" ){
            	pop[sfigato]->Ltype[procSel] = 0; // Point-to-point
             }else if (spec->linksInst[mutazioneI].type == "BUS" ){
            	pop[sfigato]->Ltype[procSel] = 1;  // Standard Bus
             }else if (spec->linksInst[mutazioneI].type == "MESH" ){
            	pop[sfigato]->Ltype[procSel] = 2; // Mesh
             }

            pop[sfigato]->neonato = true;
      }
}

void popolazione::valutazione( void )
{
      int i;

      for(i=0; i<numPart; i++)
      {
            if ( pop[i]->neonato == true )
            {
                  pop[i]->valutaCF( bestCF );
                  pop[i]->neonato = false;
            }
      }            
}

void popolazione::epurazione( float tassoMort )
{
      int vittima;
      float x;
      
      // Numero di tentativi di epurazione
      int numVittime = (int) ( numPart*tassoMort ); 
           
      // Epuro!
      for( ; numVittime>0; numVittime--)
      {
            vittima = rand() % numPart;
            
            // Valore casuale di discriminazione
            x= ( (float) rand())/RAND_MAX + spec->fatt;
            
            // Capita anche ai migliori...
            if ( pop[vittima]->CF > x )
            {
                  // ... la elimino!
                  numPart--;
                  pop[vittima]=pop[numPart];
                  // numVittime--;
            }

// Epurazione selettiva - eliminata per ora
//             // Se la vittima e' proprio scarsa...
//             if ( ( pop[vittima].TDA < x ) && ( pop[vittima].NTCC > x ) )
//             {
//                   // ... la elimino!
//                   numPart--;
//                   pop[vittima]=pop[numPart];
//             }

      }

}
            
/* void  popolazione::memStat()
{

      double sum=0, ave=0;
      double CFcopy;
      bool stat=false;

      for(int i=0; i<numPart; i++)
      {
            if(pop[i]->CF >= 0){
				CFcopy=pop[i]->CF;
				sum+=CFcopy;

				if( CFcopy < bestCF)
				{
					  stat=true;
					  bestCF = pop[i]->CF;

					  cout << endl << "TDA: " << pop[i]->TDA << endl;
					  cout << "NTCC: " << pop[i]->NTCC << endl;
					  cout << "EP: " << pop[i]->EP << endl;
					  cout << "L: " << pop[i]->L << endl;
					  cout << "C: " << pop[i]->C << endl;
					  cout << "Costo Totale: " << pop[i]->COSTO_INDIVIDUO << endl;
					  bestCost=pop[i]->COSTO_INDIVIDUO;
					  cout << "KB: " << pop[i]->KB << endl;
					  cout << "Geq: " << pop[i]->Geq << endl;
					  cout << "Crit: " << pop[i]->Crit << endl;
					  cout << "Miglior CF: " << pop[i]->CF << endl;

					  cout << "Process ID:  ";
					  for(int j=0; j< spec->numProc; j++)
							cout << j+2 << " ";
					  cout << endl;

					  cout << "Istanze:     ";
					  for(int j=0; j< spec->numProc; j++){
						  pop_Best[j] = pop[i]->istanza[j];
						  cout << pop[i]->istanza[j] << " ";
					  }
					  cout << endl;

					  mappingXmlFinal(spec);
					  count = count + 1;

				}
            }
      }

      if (stat==true)
      {
          stat=false;
          ave=sum/numPart;
          sum=0;
          for(int i=0; i<numPart; i++){
        	  if(pop[i]->CF >= 0){
        		  sum+=((pop[i]->CF-ave)*(pop[i]->CF-ave));
        	  }
          }
          
          cout << endl << "Media popolazione: " << ave << endl;      
          cout << " Scarto quad medio popolazione: " << sqrt(sum/numPart) << endl << endl;
      }
          
}  */

void  popolazione::memStat()
{
      double sum=0, sum_feasible=0, ave=0, ave_feasible=0;
      double CFcopy, CFcopy_feasible;
      bool stat=true;
      feasibleSol = 0;

      for(int i=0; i<numPart; i++)
      {
            if(pop[i]->CF >= 0){
				CFcopy=pop[i]->CF;
				sum+=CFcopy;

				if(pop[i]->CF < TR){
					feasibleSol++;
					CFcopy_feasible=pop[i]->CF;
					sum_feasible+=CFcopy_feasible;
				}

				if (CFcopy < bestCF)
				{
					  stat=true;
					  bestCF = pop[i]->CF;

					  cout << endl << "Saturation: " << pop[i]->Band << endl;
					  cout << "Exploitation: " << pop[i]->Expl << endl;
					  cout << "Concurrency: " << pop[i]->Conc << endl;
					  cout << "Feasible: " << pop[i]->fattibilita << endl;
					  cout << "Cost: " << pop[i]->Cost << endl;
					  cout << "Miglior CF: " << pop[i]->CF << endl;

					  cout << "BB Pairs ID:  ";
					  for(int j=0; j< spec->numPairs; j++)
							cout << j << " ";
					  cout << endl;

					  cout << "Istanze:      ";
					  for(int j=0; j< spec->numPairs; j++){
						  pop_Best[j] = pop[i]->istanza[j];
						  cout << pop[i]->istanza[j] << " ";
					  }
					  cout << endl;

				}
            }
      }

      if (stat==true)
      {
          stat=true;

          ave=sum/numPart;
          sum=0;
          for(int i=0; i<numPart; i++){
        	  if(pop[i]->CF >= 0){
        		  sum+=((pop[i]->CF-ave)*(pop[i]->CF-ave));
        	  }
          }

          cout << endl << "Media popolazione: " << ave;
          cout << ", Scarto quad medio popolazione: " << sqrt(sum/numPart) << endl;

            ave_feasible=sum_feasible/feasibleSol;
            sum_feasible=0;
			for(int i=0; i<numPart; i++){
				if(pop[i]->CF >= 0 && pop[i]->CF <= TR){
				  sum_feasible+=((pop[i]->CF-ave_feasible)*(pop[i]->CF-ave_feasible));
				}
			}

			cout << "Media popolazione Feasible: " << ave_feasible;
			cout << ", Scarto quad medio popolazione Feasible: " << sqrt(sum_feasible/feasibleSol) << endl << endl;
      }

}

/*void popolazione::deleteXml()
{

	int i;
	pugi::xml_document myDoc;
	pugi::xml_parse_result myResult = myDoc.load_file("./XML/mapping.xml");
	cout << "XML Delete result: " << myResult.description() << endl;

	//method 2: use object/node structure
	pugi::xml_node instancesMAP = myDoc.child("mapping");

	xml_node allocation = instancesMAP.child("allocation");

	for(i = 0; i < numProcess + 2; i++){
		xml_node processorId = allocation.child("processId");
		allocation.remove_child(processorId);
		allocation = allocation.next_sibling();
	}

	myDoc.save_file("./XML/mapping.xml");
	myDoc.reset();

}

void popolazione::deleteXmlFinal()
{

	string path_file = "./XML/Mapping/mapping";
	string format_file = ".xml";
	string final_string;
	char numstr[3];
	sprintf(numstr, "%d", count);
	final_string = path_file + numstr;

	string result;
	result = final_string + format_file;

	cout << " RESULTS: " << result.c_str() << endl;

	int i;
	pugi::xml_document myDoc;
	pugi::xml_parse_result myResult = myDoc.load_file(result.c_str());
	cout << "XML Delete result: " << myResult.description() << endl;

	//method 2: use object/node structure
	pugi::xml_node instancesMAP = myDoc.child("mapping");

	xml_node allocation = instancesMAP.child("allocation");

	for(i = 0; i < numProcess + 2; i++){
		xml_node processorId = allocation.child("processId");
		allocation.remove_child(processorId);
		allocation = allocation.next_sibling();
	}

	myDoc.save_file(result.c_str());
	myDoc.reset();

}

void popolazione::mappingXml(specifica *s)
{
	pugi::xml_document doc;

	pugi::xml_parse_result myResult = doc.load_file("./XML/mapping.xml");
	//pugi::xml_parse_result myResult = doc.load_file(result2.c_str());
	cout << "Mapping result: " << myResult.description() << endl;

	xml_node instancesMAP = doc.child("mapping");

	xml_node allocation = instancesMAP.child("allocation");

	int i = 0;
	for(i = 0; i < numProcess + 2; i++){

		xml_node map = allocation.append_child("processId");

		map.append_attribute("PSid").set_value(i);
		if(i > 1){
			map.append_attribute("PRname").set_value(s->architettura[pop_Best[i-2]].processingUnit.c_str());
			map.append_attribute("value").set_value(pop_Best[i-2]);
		}else{
			map.append_attribute("PRname").set_value("NA");
			map.append_attribute("value").set_value("NA");
		}

		allocation = allocation.next_sibling();
	}

	doc.save_file("./XML/mapping.xml");
	doc.reset();
}

void popolazione::mappingXmlFinal(specifica *s)
{

	string path_file = "./XML/Mapping/mapping";
	string format_file = ".xml";
	string final_string;
	string result;
	char numstr[4];
	sprintf(numstr, "%d", count);
	final_string = path_file + numstr;
	result = final_string + format_file;

	//cout << " RESULTS: " << result.c_str() << endl;

	pugi::xml_document doc;

	pugi::xml_parse_result myResult = doc.load_file("./XML/mapping.xml");
	//pugi::xml_parse_result myResult = doc.load_file(result2.c_str());
	cout << "Mapping result: " << myResult.description() << endl;

	xml_node instancesMAP = doc.child("mapping");

	xml_node allocation = instancesMAP.child("allocation");

	int i = 0;
	for(i = 0; i < numProcess + 2; i++){

		xml_node map = allocation.append_child("processId");

		map.append_attribute("PSid").set_value(i);
		if(i > 1){
			map.append_attribute("PRname").set_value(s->architettura[pop_Best[i-2]].processingUnit.c_str());
			map.append_attribute("value").set_value(pop_Best[i-2]);
		}else{
			map.append_attribute("PRname").set_value("NA");
			map.append_attribute("value").set_value("NA");
		}

		allocation = allocation.next_sibling();
	}

	//doc.save_file("./XML/mapping.xml"); result2

	doc.save_file(result.c_str());
	doc.reset();

	string text_value = to_string(count) +"\n";
	string text_temp = to_string(bestCost) + "\n\n";

	ofstream file; // use fstream (for reading and writing)

	file.open("./XML/Mapping/output.txt", std::ofstream::out | std::ofstream::app);
	file << text_value;
    file << text_temp;
    file.close();

}

//////////////////////////////////////////////////////////

void popolazione::memStat_print(int index_file)
{
      double sum=0;
      double CFcopy;
      string text_value;

      char  buf[BUFSIZ];
      sprintf(buf, "%s%05d%s", "./PARETO/pareto_iteration_", index_file, ".csv");

      ofstream myfile;
      myfile.open(buf,std::ofstream::out | std::ofstream::trunc);

      myfile << "TDA,NTCC,EP,L,C,CostoTotale,Crit,CF,Processes,Partition,Processor,\n";

      for(int i=0; i<numPartMax; i++)
      {
            if(pop[i]->CF >= 0){
				CFcopy=pop[i]->CF;
				sum+=CFcopy;

				if (pop[i]->CF < TR_CRIT)
				{
					feasibleSol++;

					text_value = to_string(pop[i]->TDA) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->NTCC) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->EP) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->L) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->C) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->COSTO_INDIVIDUO) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->Crit) +",";
					myfile << text_value;

					text_value = to_string(pop[i]->CF) +",";
					myfile << text_value;

					for(int j=0; j< spec->numProc; j++){
						text_value = to_string(j+2);
						myfile << text_value;
					}

					text_value = ",";
					myfile << text_value;

					for(int j=0; j< spec->numProc; j++){
						text_value = to_string(pop[i]->istanza[j]);
						myfile << text_value;
					}

					text_value = ",\n";
					myfile << text_value;

				}
            }
      }

      myfile.close();

}
*/

