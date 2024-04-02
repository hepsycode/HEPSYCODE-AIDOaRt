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
// Name        : PAM1.cpp
// Authors     : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Main
//============================================================================

using namespace std;

#include <iostream>
#include <stdlib.h>
#include "specifica.h"
#include "popolazione.h"
#include <time.h>

using namespace std;

int main()
{
	clock_t start,end;
	double time_c, time_i, time_final;

	specifica miaSpec(1);

	// I pesi devono essere una combinazione convessa (ovvero somma == 1)

	start=clock();

	popolazione myPop( &miaSpec );

	end=clock();
	time_c=((double)(end-start))/CLOCKS_PER_SEC;
	cout<<endl<<"Creation Time: "<< time_c <<endl<<endl;

	cout << endl << "numPart:" << myPop.numPart << endl;
	cout<< "numPartMax:" << myPop.numPartMax;
	cout<<endl;

	//myPop.deleteXml();
	     
	start=clock();

	// La grande ruota che e' la vita!
	myPop.valutazione();

    end=clock();
    time_i=((double)(end-start))/CLOCKS_PER_SEC;

    //myPop.memStat_Initial();
    //myPop.memStat_print(0);
	cout << endl << "Iteration: " << 0 <<" Population: " << myPop.numPart << " Execution Time: "<< time_i <<endl;

	unsigned long i=0;
	for(i=0; i<miaSpec.generazioni; i++)
	{
	    myPop.memStat();
	    myPop.accoppiamento(miaSpec.crip);
	    myPop.mutazione(miaSpec.crad);
	    myPop.valutazione();
	    myPop.epurazione(miaSpec.tmort);

	    end=clock();
	    time_i =((double)(end-start))/CLOCKS_PER_SEC;
		cout << "Iteration: " << i + 1 <<" Population: " << myPop.numPart << " Execution Time: "<< time_i << " #Feasible: " << myPop.feasibleSol <<endl;

		if(i % 5 == 0){
			//myPop.memStat_print(i);
		}

	}

	//myPop.memStat_print(i);
	cout << "Iteration: " << i + 1 <<" Population: " << myPop.numPart << " Execution Time: "<< time_i <<endl;

	time_final= time_c + time_i;
	cout <<endl<<"Final Execution Time: "<< time_final <<endl<<endl;

	//myPop.mappingXml( &miaSpec );

	#if _WIN32
	    system("pause");
	#endif
}
