package transformationTest

class XGenerator {

	// main process C++ issues
	def static startWhile(){
		'''
		
		//implementation
			while(1){
				
		// content
		'''
	}

	def static endWhile(){
		'''
		    	}
		    }
		    //END
		'''
	}
	
	// datatype

	def static startDatatype(){
		'''
		#ifndef __DATATYPE__
		#define __DATATYPE__
		
		#include <systemc.h>
		
		'''
	}
	
	def static startSingleDatatype(String payload){
		'''
		struct «payload»
		{
		
		'''
	}
	
	def static contentSingleDatatype(String type, String typeName){
		'''
			«typeName»<8> «type»;
		'''
	}
	
	def static endSingleDatatype(){
		'''
		
		};
		
		'''
	}
	
	def static endDatatype(){
		'''
		#endif
		'''	
	}

	// Stimulus.cpp
	
	def static startStimulusCpp(){
		'''
		#include <systemc.h>
		#include "stim_gen.h"
		
		void stim_gen::main()
		{
			// init CODE
			unsigned int i=1;
		'''
	}
	

	def static initStimulusCpp(String payload){
		'''
		
			«payload» «payload»_var;
		'''
	}
	
	def static contentStimulusCpp(String port, String payload){
		'''		
		
			wait(1, SC_MS);
			«port»->write(«payload»_var);
			cout << "Stimulus-"<<i<<": \t" << "\t at time \t" << sc_time_stamp() << endl;	
														
		'''
	}
	
	def static endStimulusCpp(){
		'''
		// Check for stop
				if(i >= 10) return;
				else i++;
		'''
	}
	
	// stimulus.h
	
	def static startStimulusH(){
		'''
		#ifndef __STIMGEN__
		#define __STIMGEN__
		
		#include <systemc.h>
		#include "sc_csp_channel_ifs.h"
		#include "sc_csp_channel.h"
		#include "datatype.h"
		
		SC_MODULE(stim_gen)
		{
		'''
	}
	
	def static initStimulusH(String port, String payload){
		'''
		
		    sc_port < sc_csp_channel_out_if < «payload» > > «port»;
		    
		'''
	}
	
	def static endStimulusH(){
		'''
				SC_CTOR(stim_gen)
				{
					SC_THREAD(main);
				}  
			
				void main();
			};
			
			#endif
		'''
	}
	
	// display.cpp
	def static startDisplayCpp(){
		'''
		#include <systemc.h>
		#include "display.h"
		
		void display::main()
		{
			int i = 1;
		'''
	}
	
	def static initDisplayCpp(String payload){
		'''
		
			«payload» «payload»_var;
		'''
	}
	
	def static startWhileDisplay(){
		'''
		
		//implementation
			while(i <= 10)
			{
		'''
	}
	
	def static contentDisplayCpp(String port, String payload){
		'''
		
				«payload»_var = «port»->read();
				cout << "Display-" << i << "\t at time \t" << sc_time_stamp().to_seconds() << endl;										
		'''
	}
	
	def static endDisplayCpp(){
		'''
					i++;
				}
				sc_stop();
			}
		'''
	}
	
	// display.h
	def static startDisplayH(){
		'''
		#ifndef __DISPLAY__
		#define __DISPLAY__
		
		#include <systemc.h>
		#include "sc_csp_channel_ifs.h"
		#include "sc_csp_channel.h"
		#include "datatype.h"
		
		
		SC_MODULE(display)
		{
		'''
	}
	
	def static initDisplayH(String port, String payload){
		'''
		
		    sc_port < sc_csp_channel_in_if < «payload» > > «port»;
		    
		'''
	}
	
	def static endDisplayH(){
		'''
			SC_CTOR(display)
		    {
		      SC_THREAD(main);
		    }
		
		    void main();
		};
		
		#endif

		'''
	}
	
	// Processes
	def static startProcess(String processName){
		'''
		#include <systemc.h>
		#include "mainsystem.h"
		#include <math.h>
		
		void mainsystem::«processName»_main()
		{
			// datatype for channels
		'''
	}
	
	def static initProcess(String payload){
		'''
		
			«payload» «payload»_var;
		'''
	}
	
	def static contentProcessRead(String channel, String payload){
		'''
		
				«payload»_var = «channel»->read();
		'''
	}
	
	def static contentProcessWrite(String channel, String payload){
		'''
		
				«channel»->write(«payload»_var);
			
		'''
	}
	
	// mainsystem
	
	def static startMainsystem(){
		'''
		#ifndef __MYSYSTEM__
		#define __MYSYSTEM__
		
		#include "sc_csp_channel_ifs.h"
		#include "sc_csp_channel.h"
		#include "datatype.h"
		
		SC_MODULE(mainsystem)
		{
			
		'''
	}
	
	def static initMainsystem()
	{
		'''
		// Ports for testbench connections
		'''
	}
	
	def static initMainsystemStim(String port, String payload)
	{
		'''
		sc_port< sc_csp_channel_in_if< «payload» > > «port»;
			
		'''
	}
	
	def static initMainsystemDis(String port, String payload)
	{
		'''
		sc_port< sc_csp_channel_out_if< «payload» > > «port»;
		
		'''
	}
	
	def static initMainsystemProcess(String ProcessName){
		'''
		
		// Process «ProcessName»
		void «ProcessName»_main();
		'''
	}
	
	def static initMainsystemChannel(String ChannelName, String payload){
		'''
		
		// channel «ChannelName»
		sc_csp_channel< «payload» > *«ChannelName»;
		'''
	}
	
	def static initMainsystemSC_CTOR(){
		'''
		
		//mainsystem impl.
		SC_CTOR(mainsystem)
		{
		'''
	}
	
	def static initMainsystemSC_CTOR_Channel(String channelName, String payload, int id, int writer, int reader){
		'''
		«channelName» = new sc_csp_channel< «payload» >(«id»,«writer»,«reader»);
		
		'''
	}
	
	def static initMainsystemSC_CTOR_Process(String ProcessName){
		'''
		SC_THREAD(«ProcessName»_main);
		'''
	}
	
	def static endMainsystemSC_CTOR(){
		'''
		
			}
		};	
		#endif
		'''
	}
	
	// main
	
	def static startMain(){
		'''
		#include <systemc.h>
		#include "sc_csp_channel_ifs.h"
		#include "sc_csp_channel.h"
		#include "datatype.h"
		#include "stim_gen.h"
		#include "mainsystem.h"
		#include "display.h"
		#include <string.h>
		
		/////////////////////////////////////////////////////////////////////////////////////////
		// Testbench
		/////////////////////////////////////////////////////////////////////////////////////////
		
		int sc_main (int, char *[])
		{
		
		// Channels for the connection to the main system
		
		'''
	}
	
	def static initChannel(String ChannelName, String payload){
		'''
		sc_csp_channel< «payload» >   «ChannelName»;		
		'''
	}

	def static testbench_system_Main(){
		'''
		
		// Instantiation and connection of testbench and system
		
		stim_gen mystimgen("mystimgen");
		mainsystem mysystem("mysystem");
		display mydisplay("mydisplay");
		
		'''
	}	
	
	def static stim_gen_Main(String channel, String port){
		'''
		mystimgen.«port»(«channel»); 
		
		'''
	}	
	
	def static mainsystem_Main(String channel, String port){
		'''
		mysystem.«port»(«channel»);
		'''
	}	
	
	def static display_Main(String channel, String port){
		'''
		
		mydisplay.«port»(«channel»); 
		'''
	}	
	
	def static endMain(){
		'''
		
		sc_start();
		// system("pause");
		return 0;
		}
		'''
	}	
	
	// Application.xml
	
	def static startApplicationXMLProcesses(){
		'''
		<?xml version="1.0" encoding="UTF-8"?>
		<instancesPS>
		'''
	}
	
	def static processApplicationXML(String ProcessName, int id, int priority, int criticality){
		'''
			<process>
					<name>«ProcessName»</name>
					<id>«id»</id>
					<priority>«priority»</priority>
					<criticality>«criticality»</criticality>
			</process>
		'''
	}
	
	def static endApplicationXMLProcesses(){
		'''
		</instancesPS>
		<instancesLL>
		'''
	}
	
	def static displayApplicationXML(String DisplayName, int id){
		'''
			<process>
					<name>display</name>
					<id>«id»</id>
			</process>
		'''
	}
	
	def static stimulusApplicationXML(String StimulusName, int id){
		'''
			<process>
					<name>stimulus</name>
					<id>«id»</id>
			</process>
		'''
	}
	
	def static initMainChannel(String ChannelName, String payload, int id, int writer, int reader){
		'''
		sc_csp_channel< «payload» >   «ChannelName»(«id»,«writer»,«reader»);		
		'''
	}


	def static nodeApplicationXML(String NodeName, int id){
		'''
			<node>
					<name>«NodeName»</name>
					<id>«id»</id>
			</node>
		'''
	}
	def static channelApplicationXML(String channelName, int id, int width){
		'''
			<logical_link>
					<name>«channelName»</name>
					<id>«id»</id>
					<width>«width»</width>
			</logical_link>
		'''
	}
	
	
	def static channelApplicationXML(String channelName, int id, int w_id, int r_id, int width){
		'''
			<logical_link>
					<name>«channelName»</name>
					<id>«id»</id>
					<w_id>«w_id»</w_id>
					<r_id>«r_id»</r_id>
					<width>«width»</width>
			</logical_link>
		'''
	}
	
	def static endApplicationXML(){
		'''
		</instancesLL>
		'''
	}	
	
}         