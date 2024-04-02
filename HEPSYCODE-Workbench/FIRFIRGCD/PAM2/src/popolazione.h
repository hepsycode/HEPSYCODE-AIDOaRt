//============================================================================
// Name        : cpp.cpp
// Author      : Vittoriano Muttillo, Luigi Pomante
// Version     :
// Copyright   : Your copyright notice
// Description : Population
//============================================================================

#ifndef __POPOLAZIONE__
#define __POPOLAZIONE__

#include "partizionamento.h"
#include "specifica.h"

class popolazione
{
      public:
      
            // Punta alla specifica
            specifica *spec;
                                    
            // Popolazione di partizionamenti
            partizionamento **pop;
            
            int *pop_Best;

            // Miglior elemento
            float bestCF;
            int bestCost;

            unsigned int count;

            // Numero di partizioni
            int numPart;
            int numPartMax;
            int numProcess;
            int numSol;

            int feasibleSol;

            // Costruttore
            popolazione(specifica *s);
            
            ~popolazione();
            
            // Riproduzione
            void accoppiamento( float coeffRipr );
            
            // Mutazione genetica
            void mutazione( float coeffRad );
            
            // Valutazione
            void valutazione();
            
            // Selezione
            void epurazione( float tassoMort );

            void Criticality();
                        
            // Memorizza e stampa il miglior partizionamento e altro...
            void memStat();
            
            void deleteXml();

            void deleteXmlFinal();

            void mappingXmlFinal(specifica *s);

            void mappingXml(specifica *s);

            void memStat_print(int index_file);
      
};

#endif
