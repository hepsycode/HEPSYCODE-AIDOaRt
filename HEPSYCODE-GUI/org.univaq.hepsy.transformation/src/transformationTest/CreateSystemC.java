package transformationTest;

import java.io.*;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;

import org.univaq.hepsy.*;
import org.univaq.hepsy.Process;

public class CreateSystemC {
	
	Map<String, String> mapPorts = new HashMap<String, String>();
	private Display disp;
	private Stimulus stim;
	private EList<Port> dispPorts;
	private EList<Port> stimPorts;
	private EList<Process> processesList;
	private EList<Channel> channelsList;
	private Map<Integer, Integer> hashId;
	
	public CreateSystemC(){}
	
	public void createLib(String path){
		
		try {
			BufferedWriter sc_csp_channel_ifs = new BufferedWriter(new FileWriter(path + "sc_csp_channel_ifs.h"));
			sc_csp_channel_ifs.append(XGeneratorLib.createSC_CSP_Channel_IFS());
			sc_csp_channel_ifs.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			BufferedWriter sc_csp_channel = new BufferedWriter(new FileWriter(path + "sc_csp_channel.h"));
			sc_csp_channel.append(XGeneratorLib.createSC_CSP_Channel());
			sc_csp_channel.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
	}
	
	public void findLeafs(EList<Node> nodesList)
	{
		for(Iterator<Node> i = nodesList.iterator(); i.hasNext(); )
		{
			Node item = i.next();
			
			if(item.eClass().getName().equals("Display"))
				this.disp = (Display) item;
				
			if(item.eClass().getName().equals("Stimulus"))
				this.stim = (Stimulus) item;
		}
		
		this.dispPorts = this.disp.getPorts();
		this.stimPorts = this.stim.getPorts();
	}
	
	
	public void createMain(String path, BehaviorSpecification root)
	{

       //int countS = 0;
    	//int countD = 0;
    		
		try {
			BufferedWriter mainCpp = new BufferedWriter(new FileWriter(path + "main.cpp"));
			mainCpp.append(XGenerator.startMain());	
			
			/* TEMPORARY -- Only one stimulus or display */

			// Retrieves the ports 
			
			// Channels for the connection to the main system 
			for(Iterator<Port> z = stimPorts.iterator(); z.hasNext(); )
			{
				Port pTemp = z.next();
				EList<Channel> chList = pTemp.getPChannels();
				
				for(Iterator<Channel> k = chList.iterator(); k.hasNext();)
				{  
					Channel ch = k.next();
					Port pTo = ch.getPTo();
					Boolean pExst = (pTo != null) ? true : false;
					
					
					if(pExst)
					{
						Process proc = pTo.getPortExtension();
						mainCpp.append(XGenerator.initMainChannel(ch.getName(), ch.getMessage().getName(), 1, 1, hashId.get(proc.hashCode())));     		    		

					}
				}
			}
			
			//Display Ports 
			for(Iterator<Port> z = dispPorts.iterator(); z.hasNext(); )
			{
				Port pTemp = z.next();
				EList<Channel> chList = pTemp.getPChannels();
				
				for(Iterator<Channel> k = chList.iterator(); k.hasNext();)
				{  
					Channel ch = k.next();
					Port pTo = ch.getPTo();
					Boolean pExst = (pTo != null) ? true : false;
					
					for(Iterator<Process> pr = processesList.iterator(); pr.hasNext(); )
					{
						Process item = pr.next();
						Port pCheck = item.getProcessExtension();
						Boolean pExistance = (pCheck != null) ? true : false;
						
						if(pExistance && pCheck.hashCode() == pTo.hashCode())
							mainCpp.append(XGenerator.initMainChannel(ch.getName(), ch.getMessage().getName(), 0, hashId.get(item.hashCode()), 0));     		    		

							
					}					   		    		
				}
			}

	        mainCpp.append(XGenerator.testbench_system_Main());

	        // stimulus ports
			for(Iterator<Port> z = stimPorts.iterator(); z.hasNext(); )
			{
				Port pTemp = z.next();
				EList<Channel> chList = pTemp.getPChannels();
				
				for(Iterator<Channel> k = chList.iterator(); k.hasNext();)
				{  
					Channel ch = k.next();
					Port pFrom = ch.getPFrom();
					
					// String portNameSt = nFrom.getName() + countS++;
        			mainCpp.append(XGenerator.stim_gen_Main(ch.getName(), pFrom.getName()));
        			mainCpp.append(XGenerator.mainsystem_Main(ch.getName(), pFrom.getName()));	   		    		
				}
			}
			
			for(Iterator<Port> z = dispPorts.iterator(); z.hasNext(); )
			{
				Port pTemp = z.next();
				EList<Channel> chList = pTemp.getPChannels();
				
				for(Iterator<Channel> k = chList.iterator(); k.hasNext();)
				{  
					Channel ch = k.next();
					Port pFrom = ch.getPFrom();
					
					// String portNameDs = pFrom.getName() + countD++;
					mainCpp.append(XGenerator.mainsystem_Main(ch.getName(), pFrom.getName()));
    				mainCpp.append(XGenerator.display_Main(ch.getName(), pFrom.getName()));   		    		
				}
			}

			/* ------------------------------------------ */
			
			mainCpp.append(XGenerator.endMain());	
	        mainCpp.close();
	        
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void createMainsystem(String path, BehaviorSpecification root)
	{	
		try {
			
			BufferedWriter mainSys = new BufferedWriter(new FileWriter(path + "mainsystem.h"));
			mainSys.append(XGenerator.startMainsystem());	
			
			// Ports - Display
			for(Iterator<Port> i = dispPorts.iterator(); i.hasNext(); )
			{
				Port pTemp = i.next();
				EList<Channel> chList = pTemp.getPChannels();

				for(Iterator<Channel> k = chList.iterator(); k.hasNext();)
				{  
					Channel ch = k.next();
					mainSys.append(XGenerator.initMainsystemDis(pTemp.getName(), ch.getMessage().getName()));    		    			
				}
			}

			// Ports - Stimulus
			for(Iterator<Port> i = stimPorts.iterator(); i.hasNext(); )
			{
				Port pTemp = i.next();
				EList<Channel> chList = pTemp.getPChannels();

				for(Iterator<Channel> k = chList.iterator(); k.hasNext();)
				{  
					Channel ch = k.next();
					mainSys.append(XGenerator.initMainsystemStim(pTemp.getName(), ch.getMessage().getName()));    		    			
				}
			}
			
			// Iterates through processes
			for(Iterator<Process> i = processesList.iterator(); i.hasNext(); )
			{
				Process ptemp = i.next();
        		mainSys.append(XGenerator.initMainsystemProcess(ptemp.getName()));
			}

	        // Channels
			for(Iterator<Channel> i = channelsList.iterator(); i.hasNext(); )
			{
				Channel ch = i.next();
				System.out.println(ch.getName());
				if(ch.getPFrom() == null)
        			mainSys.append(XGenerator.initMainsystemChannel(ch.getName(), ch.getMessage().getName()));

			}
				        
        	mainSys.append(XGenerator.initMainsystemSC_CTOR());

        	// Channel Initialization
			for(Iterator<Channel> i = channelsList.iterator(); i.hasNext(); )
			{
				Channel ch = i.next();
				
				Process nFrom = (Process) ch.getNFrom();
				Process nTo = (Process) ch.getNTo();
				
				Boolean fromExistance = (nFrom != null) ? true  : false;
				Boolean toExistance = (nTo != null) ? true  : false;
				
				if(fromExistance && toExistance)
				{
					int nFromId = hashId.get(nFrom.hashCode());
					int nToId = hashId.get(nTo.hashCode());

        			mainSys.append(XGenerator.initMainsystemSC_CTOR_Channel(ch.getName(), ch.getMessage().getName(), nFromId, nFromId, nToId));

				}

			}
	        
	        for(Iterator<Process> i = processesList.iterator(); i.hasNext();)
	        {
	        	Process item = i.next();
	        	mainSys.append(XGenerator.initMainsystemSC_CTOR_Process(item.getName()));
	        }
	  
			mainSys.append(XGenerator.endMainsystemSC_CTOR());
			mainSys.close();
	        	      	
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public Display getDisp() {
		return disp;
	}

	public void setDisp(Display disp) {
		this.disp = disp;
	}

	public Stimulus getStim() {
		return stim;
	}

	public void setStim(Stimulus stim) {
		this.stim = stim;
	}

	public EList<Port> getDispPorts() {
		return dispPorts;
	}

	public void setDispPorts(EList<Port> dispPorts) {
		this.dispPorts = dispPorts;
	}

	public EList<Port> getStimPorts() {
		return stimPorts;
	}

	public void setStimPorts(EList<Port> stimPorts) {
		this.stimPorts = stimPorts;
	}

	public EList<Process> getProcessesList() {
		return processesList;
	}

	public void setProcessesList(EList<Process> processesList) {
		this.processesList = processesList;
	}

	public EList<Channel> getChannelsList() {
		return channelsList;
	}

	public void setChannelsList(EList<Channel> channelsList) {
		this.channelsList = channelsList;
	}
	
	public void createDatatype(String path, BehaviorSpecification myHepsy)
	{
		try {
			BufferedWriter datatype = new BufferedWriter(new FileWriter(path + "datatype.h"));
			datatype.append(XGenerator.startDatatype());
			
			for(Iterator<Channel> i = channelsList.iterator(); i.hasNext(); )
			{
				Channel ch = i.next();
				EList<Entry> entries = ch.getMessage().getEntry();
				
				if(entries != null && (!entries.isEmpty()))
				{
					datatype.append(XGenerator.startSingleDatatype(ch.getMessage().getName()));
					for(Iterator<Entry> en = entries.iterator(); en.hasNext(); )
					{
						Entry item = en.next();
		    			datatype.append(XGenerator.contentSingleDatatype(item.getName(), item.getType()));
					}
		    		datatype.append(XGenerator.endSingleDatatype());
				}
			}
			
	    	datatype.append(XGenerator.endDatatype());
	    	datatype.close();
		} 
		catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void createStimGenCpp(String path)
	{	
		try 
		{
			BufferedWriter stimulusCpp = new BufferedWriter(new FileWriter(path + "stim_gen.cpp"));
			
			stimulusCpp.append(XGenerator.startStimulusCpp());	
			
        	for(Iterator<Port> pt = stimPorts.iterator(); pt.hasNext(); )
        	{
				Port item = pt.next();
				EList<Channel> chList = item.getPChannels();
				for(Iterator<Channel> k = chList.iterator(); k.hasNext(); )
				{
					Channel ch = k.next();
	        		stimulusCpp.append(XGenerator.initStimulusCpp(ch.getMessage().getName()));
	        		
				}
        	}
        	stimulusCpp.append(XGenerator.startWhile());
        	
        	for(Iterator<Port> pt = stimPorts.iterator(); pt.hasNext(); )
        	{
				Port item = pt.next();
				EList<Channel> chList = item.getPChannels();
				for(Iterator<Channel> k = chList.iterator(); k.hasNext(); )
				{
					Channel ch = k.next();
	        		stimulusCpp.append(XGenerator.contentStimulusCpp(item.getName(), ch.getMessage().getName()));   		    		
				}
        	}
        	
        	stimulusCpp.append(XGenerator.endStimulusCpp());
			stimulusCpp.append(XGenerator.endWhile());
			stimulusCpp.close();
			
		} 
		catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	public void createStimGenh(String path){
		
		try {
			BufferedWriter stimulusH = new BufferedWriter(new FileWriter(path + "stim_gen.h"));
			
			stimulusH.append(XGenerator.startStimulusH());	
        		
        	for(Iterator<Port> pt = stimPorts.iterator(); pt.hasNext(); )
        	{
				Port item = pt.next();
				EList<Channel> chList = item.getPChannels();
				for(Iterator<Channel> k = chList.iterator(); k.hasNext(); )
				{
					Channel ch = k.next();
	        		stimulusH.append(XGenerator.initStimulusH(item.getName(), ch.getMessage().getName()));    		
				}
        	}
			
        	stimulusH.append(XGenerator.endStimulusH());
        	stimulusH.close();

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public void createDisplayCpp(String path){
		
		try 
		{
			BufferedWriter displayCpp = new BufferedWriter(new FileWriter(path + "display.cpp"));
			displayCpp.append(XGenerator.startDisplayCpp());	
	        
			for(Iterator<Port> pt = dispPorts.iterator(); pt.hasNext(); )
			{
				Port item = pt.next();
				EList<Channel> chList = item.getPChannels();
				for(Iterator<Channel> k = chList.iterator(); k.hasNext(); )
				{
					Channel ch = k.next();
					displayCpp.append(XGenerator.initDisplayCpp(ch.getMessage().getName()));				
				}

			}
        	
        	displayCpp.append(XGenerator.startWhileDisplay());

			for(Iterator<Port> pt = dispPorts.iterator(); pt.hasNext(); )
			{
				Port item = pt.next();
				EList<Channel> chList = item.getPChannels();
				for(Iterator<Channel> k = chList.iterator(); k.hasNext(); )
				{
					Channel ch = k.next();
					displayCpp.append(XGenerator.contentDisplayCpp(item.getName(), ch.getMessage().getName()));
				}

			}
			
        	displayCpp.append(XGenerator.endDisplayCpp());
        	displayCpp.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	

	public void createDisplayH(String path){
		
		try 
		{
			BufferedWriter displayH = new BufferedWriter(new FileWriter(path + "display.h"));
			displayH.append(XGenerator.startDisplayH());	
			
			for(Iterator<Port> pt = dispPorts.iterator(); pt.hasNext(); )
			{
				Port item = pt.next();
				EList<Channel> chList = item.getPChannels();
				for(Iterator<Channel> k = chList.iterator(); k.hasNext(); )
				{
					Channel ch = k.next();
        			displayH.append(XGenerator.initDisplayH(item.getName(), ch.getMessage().getName()));
				}

			}

        	displayH.append(XGenerator.endDisplayH());
        	displayH.close();
			
		} catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void createProcess(String path, Process processCSP)
	{				
		try 
		{
			BufferedWriter processCpp = new BufferedWriter(new FileWriter(path + processCSP.getName() + ".cpp"));
			processCpp.append(XGenerator.startProcess(processCSP.getName()));

        	Port px = processCSP.getProcessExtension();
        	Boolean procExstExistance = (px != null) ? true : false;

			for(Iterator<Channel> cn = channelsList.iterator(); cn.hasNext(); )
			{
				Channel ch = cn.next();
				Process nFrom = (Process) ch.getNFrom();
				Process nTo = (Process) ch.getNTo();
				Boolean fromExistance = (nFrom != null) ? true  : false;
				Boolean toExistance = (nTo != null) ? true  : false;
				
				Port sourcePort = ch.getPFrom();
				Port targetPort = ch.getPTo();
				
				Boolean sourcePortExistance = (sourcePort != null) ? true  : false;
				Boolean targetPortExistance = (targetPort != null) ? true  : false;

				
				if(fromExistance)
					if(nFrom.hashCode() == processCSP.hashCode())
						processCpp.append(XGenerator.initProcess(ch.getMessage().getName()));
				if(toExistance)
					if(nTo.hashCode() == processCSP.hashCode())
						processCpp.append(XGenerator.initProcess(ch.getMessage().getName()));
			
				// Port Extension
				if(targetPortExistance)
				{
					Process targetPortProc = (Process) targetPort.getPortExtension();
					Boolean proceExistance = (targetPortProc != null) ? true : false;
					
					if(proceExistance && targetPortProc.hashCode() == processCSP.hashCode())
						processCpp.append(XGenerator.initProcess(ch.getMessage().getName()));	
				}
				

				// Process Extension
				if(procExstExistance && targetPortExistance)
				{
					if(px.hashCode() == sourcePort.hashCode() || px.hashCode() == targetPort.hashCode())
						processCpp.append(XGenerator.initProcess(ch.getMessage().getName()));	

				}
					
				
			}
			
        	processCpp.append(XGenerator.startWhile());	
        	
			for(Iterator<Channel> cn = channelsList.iterator(); cn.hasNext(); )
			{
				Channel ch = cn.next();
				Process nFrom = (Process) ch.getNFrom();
				Process nTo = (Process) ch.getNTo();
				Boolean fromExistance = (nFrom != null) ? true  : false;
				Boolean toExistance = (nTo != null) ? true  : false;
				
				Port sourcePort = ch.getPFrom();
				Port targetPort = ch.getPTo();
				
				Boolean sourcePortExistance = (sourcePort != null) ? true  : false;
				Boolean targetPortExistance = (targetPort != null) ? true  : false;

				// Read 
				if(toExistance)
					if(nTo.hashCode() == processCSP.hashCode())
	        			processCpp.append(XGenerator.contentProcessRead(ch.getName(), ch.getMessage().getName()));
				

				// Port Extension
				if(targetPortExistance)
				{
					Process targetPortProc = (Process) targetPort.getPortExtension();
					Boolean proceExistance = (targetPortProc != null) ? true : false;
					
					if(proceExistance &&  sourcePortExistance && targetPortProc.hashCode() == processCSP.hashCode())
	        			processCpp.append(XGenerator.contentProcessRead(sourcePort.getName(), ch.getMessage().getName()));
				}
				
			}
						
			for(Iterator<Channel> cn = channelsList.iterator(); cn.hasNext(); )
			{
				Channel ch = cn.next();
				Process nFrom = (Process) ch.getNFrom();
				Process nTo = (Process) ch.getNTo();
				Boolean fromExistance = (nFrom != null) ? true  : false;
				Boolean toExistance = (nTo != null) ? true  : false;
				
				Port sourcePort = ch.getPFrom();
				Port targetPort = ch.getPTo();
				
				Boolean sourcePortExistance = (sourcePort != null) ? true  : false;
				Boolean targetPortExistance = (targetPort != null) ? true  : false;
				
				// Process Extension
				if(procExstExistance && targetPortExistance && sourcePortExistance)
				{
					if(px.hashCode() == sourcePort.hashCode())
    	    			processCpp.append(XGenerator.contentProcessWrite(sourcePort.getName(), ch.getMessage().getName())); 
					
					if(px.hashCode() == targetPort.hashCode())
    	    			processCpp.append(XGenerator.contentProcessWrite(sourcePort.getName(), ch.getMessage().getName())); 

				}			
				
				//Write
				if(fromExistance)
					if(nFrom.hashCode() == processCSP.hashCode())
    	    			processCpp.append(XGenerator.contentProcessWrite(ch.getName(), ch.getMessage().getName())); 
			}
			
        	processCpp.append(XGenerator.endWhile());	
        	processCpp.close();		
		} 
		catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public Map<Integer, Integer> getHashId() {
		return hashId;
	}

	public void setHashId(Map<Integer, Integer> hashId) {
		this.hashId = hashId;
	}
}