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
// Description : Partitioning
//============================================================================

#ifndef __PARTIZIONAMENTO__
#define __PARTIZIONAMENTO__

#include "specifica.h"
#include "define.h"

// Un partizionamento rappresenta una scelta di numero e tipo di esecutori
// e dell'allocazione delle procedure su di essi

class partizionamento
{
      public:
      
            // Punta alla specifica
            specifica *spec;

            // Array per tenere traccia delle procedure gia' considerate
            // in fase di valutazione di alcuni valori
            bool *salta;
            
            int *maxBBArray;

            int *localBBArray;

            // Identifica un nuovo partizionamento (per il quale non e' stata valutata la CF)
            bool neonato;

            // L'elemento i di questo vettore specifica su quale tipologia di esecutore (0=GPP, 1=DSP, 2=ASP)
            // e' allocata la procedura i della specifica.
           int *Ltype;

            // L'elemento i di questo vettore specifica in quale istanza di esecutore
            // e' allocata la procedura i della specifica.
            int *istanza;

    	    // Array che contiene il MAX numero di istanze per ogni tipologia di esecutori
	        //int IMAX[MAXCLUSTER];
                        
            // Varie funzioni di costo e relativi pesi (fare i pesi static?)

            double CF; //Funzione di costo complessiva

            float COSTO_INDIVIDUO;

            float Band;    //Funzione di costo banda
            float wBand;

            float Expl;    //Funzione di costo comunicazioni (numero di esecutori per ogni link)
            float wExpl;

            float Cost;   //Funzione di costo monetario
            float wCost;

            float Conc;   //Funzione di concorrenza
            float wConc;

            float Crit;   //Funzione di criticità
            float wCrit;

            float fattibilita;
            float wFattibilita;
                                   
            // Alloca il vettore dei partizionamenti, crea i partizionamenti casuali e inizializza i pesi
            void inizializza( specifica *s );
            void inizializza_rid( specifica *s);
            
            // Distruttore
            ~partizionamento();
            
            // Calcola le funzioni di costo relative al partizionamento
            // Calcola le funzioni di merito relative al partizionamento
            void valutaCF( float bestCF );
            void valutaBand();
            void valutaExpl();
            void valutaConc();
            void valutaCost();
            void valutaCriticality();
            void valutaFatt();

};

#endif
