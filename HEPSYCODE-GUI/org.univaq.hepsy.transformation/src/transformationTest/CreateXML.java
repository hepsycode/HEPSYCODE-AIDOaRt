package transformationTest;

import java.io.*;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;
import org.univaq.hepsy.*;
import org.univaq.hepsy.Process;

public class CreateXML 
{
	private EList<Node> nodesList; 
	private EList<Channel> channelsList;
	private EList<Process> processesList;
	private Map<Integer, Integer> hashId;

	public CreateXML()
	{
		this.nodesList = new BasicEList<Node>();
		this.channelsList = new BasicEList<Channel>();
		this.processesList = new BasicEList<Process>();
		this.hashId = new HashMap<Integer, Integer>();
	}
	
	public EList<Node> getNodesList()	
	{
		return this.nodesList;
	}
	
	public EList<Channel> getChannelsList()
	{
		return this.channelsList;
	}
	
	public EList<Process> getProcessesList()
	{
		return this.processesList;
	}
	
	public EList<Channel> getConnectors(EList<Port> ports)
	{
		EList<Channel> channels = new BasicEList<Channel>();
		
		for(Iterator<Port> i = ports.iterator(); i.hasNext(); )
		{
			Port item = i.next();
			channels.addAll(item.getPChannels());
		}
		
		return channels;
	}
	
	public void createXMLFiles(String path, BehaviorSpecification root)
	{
		try 
		{
			// Stores the xml file in the application directory
			BufferedWriter xml = new BufferedWriter(new FileWriter(path + "application.xml"));
			xml.append(XGenerator.startApplicationXMLProcesses());
			
			Map<String,Integer> mapProcessId = new HashMap<String, Integer>();
			
			// The variable processList represents the list of the nodes defined in the model
			EList<Node> nodesList = root.getNodes();
			EList<Channel> channelsList = new BasicEList<Channel>();
			
			int count = 0;
			
			/* TEMPORARY -- Get first stimulus or display */
			for(Iterator<Node> i = nodesList.iterator(); i.hasNext(); )
			{
				Node item = i.next();
				
				if(item.eClass().getName().equals("Display"))
				{
					Display disp = (Display) item;
					xml.append(XGenerator.displayApplicationXML(disp.getName(), 0));
					channelsList.addAll(getConnectors(disp.getPorts()));
					count += 1;
				}
				
				if(item.eClass().getName().equals("Stimulus"))
				{
					Stimulus stim = (Stimulus) item;
					xml.append(XGenerator.stimulusApplicationXML(stim.getName(), 1));
					channelsList.addAll(getConnectors(stim.getPorts()));
					count += 1;
				}
				
				if(count == 2)
					break;
			}
			/* ------------------------------------------ */
		
			
			for(Iterator<Node> i = nodesList.iterator(); i.hasNext(); )
			{
				Node item = i.next();
				
				switch(item.eClass().getName())
				{
				/*
					case "Display":
						Display dtemp = (Display) item;
						xml.append(XGenerator.displayApplicationXML(dtemp.getName(), count++));
						// Adds the connectors that are connected to its ports
						channelsList.addAll(getConnectors(dtemp.getPorts()));		
						break;					
						
					case "Stimulus":
						Stimulus stemp = (Stimulus) item;
						xml.append(XGenerator.stimulusApplicationXML(stemp.getName(), count++));
						// Adds the connectors that are connected to its ports
						channelsList.addAll(getConnectors(stemp.getPorts()));
						break;		
				*/
						
					case "StructuredNode":
						StructuredNode ntemp = (StructuredNode) item;
						// Adds its nested processes to the processes list
						processesList.addAll(ntemp.getProcesses());
						// Adds its internal channels to the channels list
						channelsList.addAll(item.getNChannels());	
						// Adds the connectors that are connected to its ports
						channelsList.addAll(getConnectors(ntemp.getPorts()));						
						//xml.append(XGenerator.nodeApplicationXML(ntemp.getName(), count++));
						break;	
				}
			}
			
			// Iterates through processes
			for(Iterator<Process> i = processesList.iterator(); i.hasNext(); )
			{
				Process ptemp = i.next();
				xml.append(XGenerator.processApplicationXML(ptemp.getName(), count, ptemp.getPriority(), ptemp.getCriticality()));
				hashId.put(ptemp.hashCode(), count);
				count += 1;
			}
			
			xml.append(XGenerator.endApplicationXMLProcesses());
			
			// Iterates through channels 
		    for(Iterator<Channel> k = channelsList.iterator(); k.hasNext(); )
		    {
		    	Channel ch = k.next();
		    	xml.append(XGenerator.channelApplicationXML(ch.getName(), count++, ch.getQueueSize()));
				hashId.put(ch.hashCode(), count);
				count +=1;
		    }
			
			
			this.nodesList.addAll(nodesList);
			this.channelsList.addAll(channelsList);
	        
			xml.append(XGenerator.endApplicationXML());
			xml.close();
			
		} catch (IOException e) {
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
