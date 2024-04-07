# HEPSYCODE-AIDOaRt
HEPSYCODE Modeling Methodology, Framework and tools for AIDOaRt European Project

<p align="center">
<img src="img/logo.png" width="400" height="236">
</p>

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Installation instructions

### OVERVIEW
HEPSYCODE (HW/SW CO-DEsign of HEterogeneous Parallel dedicated SYstems) is a prototypal tool to improve the design time of embedded applications. It is based on a System-Level methodology for HW/SW Co-Design of Heterogeneous Parallel Dedicated Systems. The whole framework drives the designer from an Electronic System-Level (ESL) behavioral model, with related NF requirements, including real-time and mixed-criticality ones, to the final HW/SW implementation, considering specific HW technologies, scheduling policies and Inter-Process Communication (IPC) mechanisms. The system behavior modeling language introduced in HEPSYCODE, named HML (HEPSY Modeling Language), is based on the Communicating Sequential Processes (CSP) Model of Computation (MoC). It allows modeling the behavior of the system as a network of processes communicating through unidirectional synchronous channels. By means of HML it is possible to specify the System Behavior Model (SBM), an executable model of the system behavior, a set of Non Functional Constraints (NFC) and a set of Reference Inputs (RI) to be used for simulation-based activities. Through the execution of different steps, including a system-level Design Space Exploration (DSE) approach that allows the related co-design methodology to suggest an HW/SW partitioning of the application specification and a mapping of the partitioned entities onto an automatically defined heterogeneous multi-processor architecture, it is possible to proceed with system implementation.

HEPSYCODE uses Eclipse MDE technologies, SystemC custom simulator implementation and an evolutionary genetic algorithm for partitioning activities, all integrated into an automatic framework that drive the designer from first input to final solution.

This repository contains the HEPSYCODE framework, which consists of a set of

- Reference libraries
- Scripts and makefiles
- Eclipse plugins 
- XML data exchange files
- SystemC files (part of the HEPSYM simulator)
- HW/SW Partitioning And Mapping (PAM) tool

### WEBSITE
www.HEPSYCODE.com
 
### DOWNLOAD
Official git repository: https://github.com/HEPSYCODE/HEPSYCODE-AIDOaRt
 
### INSTALLATION
 1. Download Eclipse Modelling Tool: [https://www.eclipse.org/downloads/eclipse-packages/](https://www.eclipse.org/downloads/packages/)
 2. Cloning HEPSYCODE from https://github.com/HEPSYCODE/HEPSYCODE-AIDOaRt
 3. Import in Eclipse HEPSYCODE projects present in the folder and run a separate Eclipse application to run and debug HEPSYCODE plug-in
 4. Install Systemc library (it is recommended version 2.3.3)
 5. Go to /home/.bashrc and insert the path of Systemc (folder lib-linux and include) the names of the variable must be SYSTEMCPATHLIB and SYSTEMCPATHINCLUDE for example:
    - export SYSTEMCPATHLIB=/usr/local/systemc-2.3.3/lib-linux64
    - export SYSTEMCPATHINCLUDE=/usr/local/systemc-2.3.3/include
    - Alternative: launch settings.sh script
 6. Try and enjoy the HEPSYCODE Tool!!!

### SYSTEM REQUIREMENTS
 - Linux OS or Windows;
 - SystemC Libraries version 2.3.3;
 - Eclipse Modelling Tools with the following plugins in place: 
   - Eclipse Sirius
   - Eclipse Xtext

### RELEASE NOTES
Latest Release: 2.0.0
 
### LICENSE
GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007 (see https://www.gnu.org/licenses/gpl-3.0.en.html)
 
### DEVELOPER RESOURCES
Source Repositories: https://github.com/HEPSYCODE/HEPSYCODE-AIDOaRt

- Clone: 
    - ssh: git@github.com:HEPSYCODE/HEPSYCODE-AIDOaRt.git
    - https: https://github.com/HEPSYCODE/HEPSYCODE-AIDOaRt.git
 
You can use the code from these repositories to experiment, test, build, and create patches, and issue pull requests (only by request).
 
### SUPPORT
We currently support:

 1. Email: 
    - Luigi Pomante, luigi.pomante@univaq.it
    - Vittoriano Muttillo, vittoriano.muttillo@graduate.univaq.it
    - Marco Santic, marco.santic@guest.univaq.it
    - (please take care to use \[HEPSYCODE SUPPORT\] as object
 2. Issues on bitbucket.org
 
## Getting Started Guidelines
You can find getting started guidelines in the docs folder or on the official HEPSYCODE website:: www.HEPSYCODE.com  

To get started with HEPSYCODE, you can:

 1. Clone this repository to your local machine.
 2. Import the plugin projects in the HEPSYCODE-GUI directory in Eclipse.
 3. Use the HEPSYCODE Sirius-based tool to create and edit your HEPSYCODE models.
 4. Generate code from your HEPSYCODE models using the HEPSYCODE M2M XText transformation code.
 5. Simulate your HEPSYCODE models using the HEPSYCODE HEPSIM2 simulator. Example are available in the HEPSYCODE-Workbench folder.

## Additional information
Research publications are available on http://www.HEPSYCODE.com/ and http://www.pomante.net/sito_gg/Publications.htm

If you use HEPSYCODE in your research, please cite:
```
@ARTICLE{MUTTILLO2023108803,
  title = {SystemC-based Co-Simulation/Analysis for System-Level Hardware/Software Co-Design},
  journal = {Computers and Electrical Engineering},
  volume = {110},
  pages = {108803},
  year = {2023},
  issn = {0045-7906},
  doi = {https://doi.org/10.1016/j.compeleceng.2023.108803},
  url = {https://www.sciencedirect.com/science/article/pii/S0045790623002276},
  author = {Vittoriano Muttillo and Luigi Pomante and Marco Santic and Giacomo Valente},
  keywords = {Electronic system-level design, HW/SW co-design, Embedded systems,
              Parallel systems, Heterogeneous systems},
  abstract = {Heterogeneous parallel devices are becoming increasingly common in the
              embedded systems field. This is primarily due to their ability to improve
              timing performance, while simultaneously reducing costs and energy.
              In this context, this study addresses the role of a hardware/software (HW/SW)
              co-simulation and analysis tool for embedded systems designed on heterogeneous
              parallel architectures. In particular, it presents an extended System C-based
              tool for functional and timing HW/SW co-simulation/analysis within a reference
              Electronic System-Level HW/SW co-design flow. The description of the main features
              of the tool, and the main design and integration issues represent the
              core of the paper. Furthermore, the paper presents two case studies that
              demonstrate the enhanced effectiveness and efficiency of the extended tool.
              This is achieved through reduced simulation. Thanks to all this, the paper
              contributes to fully motivate the industrial and research communities to
              adopt and further investigate system-level approaches.}
}
```
