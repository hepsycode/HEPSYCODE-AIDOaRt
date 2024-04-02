//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Partitioning
//============================================================================

#include "partizionamento.h"
#include <stdlib.h>

#include <iostream>

using namespace std;

void partizionamento::inizializza( specifica *s )
{
      int j;

      spec=s; // Si aggancia alla specifica
      
      // Alloca la memoria
      Ltype   = new int[spec->numPairs];
      istanza = new int[spec->numPairs];
      salta   = new bool[spec->numPairs];

      // Inizializza i pesi      
      wBand=s->sat;  // Saturation
      wExpl=s->expl;  // Exploitation
      wConc=s->conc;  // Concurrency
      wCost=s->ph_cost;  // Cost
      wCrit=s->criticality; // Criticality

      wFattibilita=s->fatt;  // indice di fattibilità

      // Inizializza al MAX le funzioni di merito
      CF=1;
      Band=1;
      Expl=1;
      Conc=1;
      Cost=1;
      Crit=1;

      fattibilita=1;
      
      // Appena creato trattasi di neonato...
      // ovvero la CF non e' stata gia' calcolata
      neonato = true;

      // Creazione di un partizionamento casuale
      for( j=0; j < spec->numPairs; j++ )
      {
           // Per ogni procedura sceglie un tipo e una istanza di esecutore
           // a caso ma entro i limiti imposti

          int loc =(rand()%spec->numLink);
          istanza[j] = spec->linksInst[loc].id;

          if(spec->linksInst[loc].type == "PTP" ){
        	  Ltype[j] = 0;  // Point-to-point
          }else if (spec->linksInst[loc].type == "BUS" ){
        	  Ltype[j] = 1;  // Standard Bus
          }else if (spec->linksInst[loc].type == "MESH" ){
        	  Ltype[j] = 2; // Mesh
          }

      }

}

void partizionamento::inizializza_rid( specifica *s)
{

      spec=s; // Si aggancia alla specifica

       // Alloca la memoria
       Ltype   = new int[spec->numPairs];
       istanza = new int[spec->numPairs];
       salta   = new bool[spec->numPairs];

       // Inizializza i pesi
       wBand=s->sat;  // Saturation
       wExpl=s->expl;  // Exploitation
       wConc=s->conc;  // Concurrency
       wCost=s->ph_cost;  // Cost
       wCrit=s->criticality; // Criticality

       wFattibilita=s->fatt;  // indice di fattibilità

       // Inizializza al MAX le funzioni di merito
       CF=1;
       Band=1;
       Expl=1;
       Conc=1;
       Cost=1;
       Crit=1;

       fattibilita=0;

       // Appena creato trattasi di neonato...
       // ovvero la CF non e' stata gia' calcolata
       neonato = true;

}


partizionamento::~partizionamento()
{
      delete[] Ltype;
      delete[] istanza;
      delete[] salta;
}

// Valuta la funzione di costo complessiva
void partizionamento::valutaCF( float bestCF )
{
     // Calcola le varie funzioni di costo che costituiscono quella complesisva
     // L'ordine di valutazione dovrebbe essere a complessita' computazionale crescente
     // cosi' se esce prima si risparmia tempo

	CF=0;

	valutaBand();
	//cout<<B<<'\n';
	CF+=wBand*Band;

	valutaExpl();
	CF+=wExpl*Expl;

	valutaConc();
	CF+=wConc*Conc;

	valutaCost();
	CF+=wCost*Cost;

	valutaCriticality();
	CF+=wCrit*Crit;

	valutaFatt();
    CF+=wFattibilita*fattibilita;

}

//Valuta la banda per ogni link
void partizionamento::valutaBand()
{

    float bandaP=0, bandaT=0;
    int i,j,k,q;
    int num=0; //Numero di link diversi

    // Inizializza matrice tb per tenere traccia dei link gia' considerati
    for(i=1; i<spec->numPairs; i++) salta[i]=false;

    // Consideriamo gli esecutori a coppie
    for(i=1; i<spec->numPairs; i++)
    {
		if (salta[i]==false) // Se coppia non gia' considerata...
		{
			salta[i]=true;

			num++; //Aumenta il numero di link

			//Aggiunge la banda sul collegamento
			bandaP=spec->BING_band[i];

			// Calcola la banda sul link dovuta ad altre eventuali coppie
			for(k=1; k<spec->numPairs; k++)
			{
					if (salta[k]==false)
					{
						// Se un'altra coppia parla tramite lo stesso link
						if ((istanza[i]==istanza[k]))
						{
							 // Aggiunge la banda
							 bandaP+=spec->BING_band[k];
							 salta[k]=true;
						}
					}
			}

		   //prove di verifica

			// Penalizza se infattibile
			if (bandaP > spec->linksInst[istanza[i]].bandwidth)
			{
			   Band=1;
			   return;
			}

			// Banda totale utilizzata (in percentuale rispetto al max per ogni link)
			bandaT+=(bandaP/spec->linksInst[istanza[i]].bandwidth);
			bandaP=0;
		}
    }

	// Media di inutilizzo link (da minimizzare)
    if(num > 0){
    	Band=1-bandaT/num;
    }
}

//Valuta il numero di esecutori per ogni link (rispetto al max)
void partizionamento::valutaExpl()
{
    int i,j,l,ist;
    int num=0; //Numero di esecutori per link
    int nl=0; //numero di link diversi presenti
    bool usato= false;

    Expl=0;


}

//// Valuta la concorrenza
void partizionamento::valutaConc()
{

}

//// Valuta il costo monetario
void partizionamento::valutaCost()
{
    float cost=0;
    int i,j,k,q;
    //int num=0; //Numero di link diversi

     // Inizializza matrice tb per tenere traccia dei link gia' considerati
    for(i=1; i<spec->numPairs; i++) salta[i]=false;

    // Consideriamo gli esecutori a coppie
    for(i=1; i<spec->numPairs; i++)
    {

		if (salta[i]==false) // Se coppia non gia' considerata...
		{
				salta[i]=true;

				//num++; //Aumenta il numero di link
				//Aggiunge il costo sul collegamento
				cost+=spec->linksInst[istanza[i]].cost;

				// Elimina evenatuali altre presenze dell'esecutore
				for(k=1; k<spec->numPairs; k++)
				{
						if (salta[k]==false)
						{
							// Se un'altra coppia parla tramite lo stesso link
							if (istanza[i]==istanza[k])
							{
								salta[k]=true;
							}
						}
				 }
		}
	}

    Cost=cost/(spec->numPairs * spec->linkCostMax);

}

     //originale
/*
   float cost=0;
   int i,j;

    // Inizializza array per tenere traccia delle procedure gia' considerate
   for(i=0; i<spec->numProc; i++) salta[i]=false;

   for(i=0; (i<spec->numProc); i++)
    {
       if (salta[i]==false) // Se non gia' considerata...
        {
            // Calcola il costo

           cost+=COSTO[allocataIn[i]];

           // Elimina evenatuali altre presenze dell'esecutore
           for(j=i+1; (j<spec->numProc); j++)
            {
                   if (salta[j]==false)
                    {
                       if ((allocataIn[i]==allocataIn[j])&&(istanza[i]==istanza[j])) salta[j]=true;
                   }
            }
           salta[i]=true;

        }
    }

    C=cost/(spec->numProc*MAXCOST);
}
*/

//// Valuta la criticità
void partizionamento::valutaCriticality()
{

}

//// Valuta la fattibilità
void partizionamento::valutaFatt()
{

    float bandaP=0, bandaT=0;
    int i,j,k,q, bb1_id, bb2_id;
    int num=0; //Numero di link diversi

    // Inizializza matrice tb per tenere traccia dei link gia' considerati
    for(i=1; i<spec->numPairs; i++) salta[i]=false;

    int feas[spec->numPairs];
	for(int iii = 0; iii < spec->numPairs; iii++){
		feas[iii] = 1;
	}

    // Consideriamo gli esecutori a coppie
    for(i=1; i<spec->numPairs; i++)
    {
		if (salta[i]==false) // Se coppia non gia' considerata...
		{
			salta[i]=true;

			num++; //Aumenta il numero di link

			//Aggiunge il link sul collegamento
			bb1_id=spec->BING_i[i];
			bb2_id=spec->BING_j[i];

			if( (spec->architettura[bb1_id].communicationUnit[0] == spec->linksInst[istanza[i]].name ||
			spec->architettura[bb1_id].communicationUnit[1] == spec->linksInst[istanza[i]].name ||
			spec->architettura[bb1_id].communicationUnit[2] == spec->linksInst[istanza[i]].name ||
			spec->architettura[bb1_id].communicationUnit[3] == spec->linksInst[istanza[i]].name ||
			spec->architettura[bb1_id].communicationUnit[4] == spec->linksInst[istanza[i]].name) &&
			(spec->architettura[bb2_id].communicationUnit[0] == spec->linksInst[istanza[i]].name ||
			spec->architettura[bb2_id].communicationUnit[1] == spec->linksInst[istanza[i]].name ||
			spec->architettura[bb2_id].communicationUnit[2] == spec->linksInst[istanza[i]].name ||
			spec->architettura[bb2_id].communicationUnit[3] == spec->linksInst[istanza[i]].name ||
			spec->architettura[bb2_id].communicationUnit[4] == spec->linksInst[istanza[i]].name) ){
				feas[i] = 0;
			}
			else{ feas[i] = 1;}

		}
    }
    fattibilita = feas[0];
	for(int iii = 1; iii < spec->numPairs; iii++){
		fattibilita *= feas[iii];
	}

}
