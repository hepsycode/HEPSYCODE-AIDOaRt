include settings.sh

SRC_NO_INSTR=$(wildcard HepsycodeDesign/src/*.cpp)  $(wildcard HepsycodeDesign/src/processes/*.cpp)  
SRC=$(wildcard HepsycodeDesign/src/*.cpp)  $(wildcard HepsycodeDesign/src/processesInstr/*.cpp)  
SRC_PAM1=$(wildcard PAM1/src/*.cpp)
SRC_PAM1_PARALLEL=$(wildcard PAM1_Parallel/src/*.cpp)
SRC_PAM2=$(wildcard PAM2/src/*.cpp)
SRC_PARETO=$(wildcard ParetoAnalysis/src/*.cpp)

#Functional simulation
EXECUTABLE_NO_INSTR=functional_noinstr
EXECUTABLE=functional

#Metrics
EX_LOAD=load

#DSE
EX_PAM1=pam1
EX_PAM1_PARALLEL=pam1_parallel
EX_PAM2=pam2
EX_PARETO=pareto

#timing simulation
EX_TIMING_COMCON_SIM=timing_concom_sim
EX_TIMING_SIM=timing_sim
EX_TIMING_SIM_SAVE_CSV=timing_sim_save_csv

#per Linux a 32 bit ---> compilazione
functional_noinstr: $(SRC_NO_INSTR) 
	g++ -I$(SYSTEMCPATHINCLUDE) -L$(SYSTEMCPATHLIB) -o $(EXECUTABLE_NO_INSTR) -D _FUNCTIONAL_ -lsystemc $(SRC_NO_INSTR) -fpermissive

functional: $(SRC) 
	g++ -I$(SYSTEMCPATHINCLUDE) -L$(SYSTEMCPATHLIB) -o $(EXECUTABLE) -D _FUNCTIONAL_ -lsystemc $(SRC) -fpermissive

load: $(SRC) 
	g++ -I$(SYSTEMCPATHINCLUDE) -L$(SYSTEMCPATHLIB) -o $(EX_LOAD) -D _TIMING_ENERGY_ -D _LOAD_ -lsystemc $(SRC) -fpermissive

timing_concom: $(SRC) 
	g++ -I$(SYSTEMCPATHINCLUDE) -L$(SYSTEMCPATHLIB) -o $(EX_TIMING_COMCON_SIM) -D _TIMING_ENERGY_ -D _CONCURRENCY_ -lsystemc $(SRC) -fpermissive

timing: $(SRC) 
	g++ -I$(SYSTEMCPATHINCLUDE) -L$(SYSTEMCPATHLIB) -o $(EX_TIMING_SIM) -D _TIMING_ENERGY_ -lsystemc $(SRC) -fpermissive

timing_save_csv: $(SRC) 
	g++ -I$(SYSTEMCPATHINCLUDE) -L$(SYSTEMCPATHLIB) -o $(EX_TIMING_SIM_SAVE_CSV) -D _TIMING_ENERGY_ -D _SAVE_CSV_ -lsystemc $(SRC) -fpermissive

pam1: $(SRC_PAM1)
	$(CXX) -std=c++0x -O3 -o $(EX_PAM1) $(SRC_PAM1)

pam1_parallel: $(SRC_PAM1_PARALLEL)
	$(CXX) -std=c++0x -O3 -o $(EX_PAM1_PARALLEL) -fopenmp $(SRC_PAM1_PARALLEL) 

pam2: $(SRC_PAM2)
	$(CXX) -std=c++0x -O3 -o $(EX_PAM2) $(SRC_PAM2)
	
pareto: $(SRC_PARETO)
	$(CXX) -std=c++11 -O3 -o $(EX_PARETO) $(SRC_PARETO) -lboost_system -lboost_filesystem 

#Comune a 32 e 64 bit ---> eseguibile
functional_noinstr_run: 
	./$(EXECUTABLE_NO_INSTR)
	
functional_run: 
	./$(EXECUTABLE)

load_run: 
	./$(EX_LOAD)

timing_concom_run:
	./$(EX_TIMING_COMCON_SIM)

timing_run: 
	./$(EX_TIMING_SIM)
	
timing_save_csv_run:
	./$(EX_TIMING_SIM_SAVE_CSV)

pam1_run: 
	./$(EX_PAM1)
	
pam1_parallel_run: 
	./$(EX_PAM1_PARALLEL)
	
pareto_run: 
	./$(EX_PARETO)

pam2_run: 
	./$(EX_PAM2)

#Comune a 32 e 64 bit ---> clean
functional_noinstr_clean:
	rm $(EXECUTABLE_NO_INSTR)

functional_clean:
	rm $(EXECUTABLE)

load_clean:
	rm $(EX_LOAD)

timing_concom_clean:
	rm $(EX_TIMING_COMCON_SIM)

timing_clean:
	rm $(EX_TIMING_SIM)
	
timing_save_csv_clean:
	rm $(EX_TIMING_SIM_SAVE_CSV)

pam1_clean:
	rm $(EX_PAM1)
	
pam1_parallel_clean:
	rm $(EX_PAM1_PARALLEL)
	
pareto_clean: 
	rm $(EX_PARETO)

pam2_clean:
	rm $(EX_PAM2)

clean:
	rm -f $(EX_PARETO) $(EXECUTABLE_NO_INSTR) $(EXECUTABLE) $(EX_LOAD) $(EX_TIMING_COMCON_SIM) $(EX_TIMING_SIM) $(EX_TIMING_SIM_SAVE_CSV) $(EX_PAM1) $(EX_PAM1_PARALLEL) $(EX_PAM2) #  $(EX_CONCURR) $(EX_ENERGY) $(EX_TIMING_NO_CONCURRENCY_SAMPLING_SIM) 

# HW/SW CO-DEsign of HEterogeneous Parallel dedicated SYstems (Hepsycode)

## --------------------------------------------------------------------------------------------
## Hepsycode is a prototypal tool to improve the design time of embedded applications. It is 
## based on a System-Level methodology for HW/SW Co-Design of Heterogeneous Parallel Dedicated 
## Systems. The whole framework drives the designer from an Electronic System-Level (ESL) 
## behavioral model, with related NF requirements, including real-time and mixed-criticality 
## ones, to the final HW/SW implementation, considering specific HW technologies, scheduling 
## policies and Inter-Process Communication (IPC) mechanisms. The system behavior modeling 
## language introduced in Hepsycode, named HML (HEPSY Modeling Language), is based on the 
## Communicating Sequential Processes (CSP) Model of Computation (MoC). It allows modeling the 
## behavior of the system as a network of processes communicating through unidirectional 
## synchronous channels. By means of HML it is possible to specify the System Behavior Model 
## (SBM), an executable model of the system behavior, a set of Non Functional Constraints (NFC) 
## and a set of Reference Inputs (RI) to be used for simulation-based activities. Through the 
## execution of different steps, including a system-level Design Space Exploration (DSE) 
## approach that allows the related co-design methodology to suggest an HW/SW partitioning of 
## the application specification and a mapping of the partitioned entities onto an 
## automatically defined heterogeneous multi-processor architecture, it is possible to proceed 
## with system implementation.
## --------------------------------------------------------------------------------------------

SCRIPT_VERSION=v1.0
SCRIPT_AUTHOR=Vittoriano Muttillo

functional_noinstr:         			##@Build Build Functional, Concurrency and Communication Project (No Instrumentation)
functional:         					##@Build Build Functional, Concurrency and Communication Project
load:         							##@Build Build Load and Energy Project
pam1:         							##@Build Build PAM1 Project
pam2:									##@Build Build PAM2 Project
timing_concom:							##@Build Build Timing, Concurrency and Communication Project
timing:									##@Build Build Timing Project
timing_save_csv:						##@Build Build Timing Project and Save Results into CSV report file

functional_noinstr_run:					##@Running Run Functional, Concurrency and Communication Project (No Instrumentation)
functional_run:							##@Running Run Functional, Concurrency and Communication Project
load_run:								##@Running Run Load Project
pam1_run:								##@Running Run PAM1 Project
pam2_run:								##@Running Run PAM2 Project
timing_concom_run:						##@Running Run Timing, Concurrency and Communication Project
timing_run:								##@Running Run Timing Project
timing_save_csv_run:					##@Running Run Timing Project and Save Results into CSV report file

functional_noinstr_clean:              	##@Cleaning Remove all output and interemediate objects
functional_clean:              			##@Cleaning Remove all output and interemediate objects
load_clean:              				##@Cleaning Remove all output and interemediate objects
pam1_clean:              				##@Cleaning Remove all output and interemediate objects
pam2_clean:              				##@Cleaning Remove all output and interemediate objects
timing_concom_clean:              		##@Cleaning Remove all output and interemediate objects
timing_clean:              				##@Cleaning Remove all output and interemediate objects
timing_save_csv_clean:					##@Cleaning Remove all output and interemediate objects
clean:              					##@Cleaning Remove all output and interemediate objects

HELP_FUN = \
	%help; while(<>){push@{$$help{$$2//'options'}},[$$1,$$3] \
	if/^([\w-_]+)\s*:.*\#\#(?:@(\w+))?\s(.*)$$/}; \
	print"$$_:\n", map"  $$_->[0]".(" "x(39-length($$_->[0])))."$$_->[1]\n",\
	@{$$help{$$_}},"\n" for keys %help; \

help: ##@Miscellaneous Show this help
	@echo ""
	@sed -ne '/@sed/!s/## //p' $(MAKEFILE_LIST)
	@echo ""	
	@echo "Usage: make [target] ...\n"
	@perl -e '$(HELP_FUN)' $(MAKEFILE_LIST)
	@echo "Written by $(SCRIPT_AUTHOR), version $(SCRIPT_VERSION)"
	@echo "Please report any bug or error to the author." 
	@echo ""
