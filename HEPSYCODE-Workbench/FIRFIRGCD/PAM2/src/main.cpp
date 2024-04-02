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
