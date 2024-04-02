#ifndef __SPECIFICA__
#define __SPECIFICA__

#include "procedura.h"
#include "mapping.h"
#include "link.h"
#include "logical_link.h"
#include "basicBlock.h"

// Specifica: insieme di procedure che la compongono piu' varie info

class specifica
{      
      public:

			// Genetic Algorithm parameters
			unsigned long generazioni;
			unsigned long initialPop;
			unsigned long nPart;
			unsigned long numMaxPart;
			float crip;
			float crad;
			float tmort;

			// Cost function weight
			float sat;
			float expl;
			float conc;
			float ph_cost;
			float criticality;
			float fatt;

			// Constraints

			float TTC;
			unsigned int numberProcesses;
			unsigned int numLinkLogical;
			int instanceBB;
			int instanceLinks;
			int instanceMaxBB;
			float loadMax;
			int linkCostMax;

            // Procedure che compongono la specifica (puntatore ad array)
            procedura *progetto;

            // Link che compongono la specifica (puntatore ad array)
            logical_link *linksLogicalInst;

            // Mapping che compongono la specifica (puntatore ad array)
            mapping *mappingInst;

            // Link che compongono la specifica (puntatore ad array)
            link *linksInst;

            // Procedure che compongono la specifica (puntatore ad array)
            basicblock *architettura;


            // Numero di procedure che compongono la specifica
            int numProc;
            
            // Numero di BB che compongono la specifica
            int numBB;

            // Numero di Link che compongono la specifica
            int numLink;

            // Numero di Coppie che compongono la specifica
            int numPairs;

            // Numero di Coppie che compongono la specifica
            int *BING_i;
            int *BING_j;
            int *BING_band;

            // Coppie

            // Matrice delle comunicazioni tra le procedure
            // matrice simmetrica le cui righe e colonne rappresentano le procedure
            // e il contenuto i byte scambiati tra le coppie di procedure
            // Es.
            //      P1  P2  P3
            //   P1 0   10  30
            //   P2 10  0   15
            //   P3 30  15  0
            float *comMat;
            
            // Max costo possibile delle comunicazioni tra procedure
            // calcolato ipotizzando che tutte siano su esecutori diversi
            float maxTCC;

            //Matrice del parallelismo
            // matrice simmetrica le cui righe e colonne rappresentano le procedure
            // e il contenuto se c'e' (1) o meno (0) possibilita' di parallelismo
            // tra le coppie di procedure
            // Es.
            //      P1  P2  P3
            //   P1 0   1   1
            //   P2 1   0   0
            //   P3 1   0   0
            float *parMat;

            // Max parallelismo possibile
            // calcolato ipotizzando che tutte le procedure potenzialmente parallele
            // siano su esecutori diversi e quindi possano esserlo davvero
            float maxEP;

            //Matrice del parallelismo dei canali
            // matrice simmetrica le cui righe e colonne rappresentano i canali logici
            // e il contenuto se c'e' (1) o meno (0) possibilita' di parallelismo
            // tra le coppie di canali
            // Es.
            //      P1  P2  P3
            //   P1 0   1   1
            //   P2 1   0   0
            //   P3 1   0   0
            float *parMatCH;

            // Max parallelismo possibile
            // calcolato ipotizzando che tutti i canali potenzialmente paralleli
            // siano su link fisici diversi e quindi possano esserlo davvero
            float maxEPCH;

            float maxCOST;

            // Costruttore
            specifica(int start);
            
            void load_constraints();
            void load_parameters();
            void create_basicBlocks();
            void create_mapping();
            void create_processes();
            void create_logical_link();
            void create_links();

            // Distruttore
            ~specifica();
            
};

#endif
