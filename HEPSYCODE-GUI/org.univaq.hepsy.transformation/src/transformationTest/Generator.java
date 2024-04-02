package transformationTest;

import java.io.File;
import java.util.Iterator;
import java.util.Map;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.filechooser.FileSystemView;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.URI;

import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;

import org.univaq.hepsy.*;
import org.univaq.hepsy.Process;

public class Generator {
	public Generator(){}
	
	public static void main(String[] args) 
	{
		// Initialize the model
        HepsyPackage.eINSTANCE.eClass();

        // Register the XMI resource factory for the .website extension
        Resource.Factory.Registry reg = Resource.Factory.Registry.INSTANCE;
        
        // Registers the extension "hepsy" in the extensions map 'm'
        Map<String, Object> m = reg.getExtensionToFactoryMap();
        m.put("hepsy", new XMIResourceFactoryImpl());

        // Instantiate a new collection of resources 
        ResourceSet resSet = new ResourceSetImpl();

        // It is needed to upload the file representing the model ".hepsy". It uses the class JFileChooser
        JFileChooser jfc = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
        jfc.setDialogTitle("Choose a directory to get your file: ");
        jfc.setAcceptAllFileFilterUsed(false);
        
        // Delimitates the choice only to ".hepsy" files
		FileNameExtensionFilter filter = new FileNameExtensionFilter("Hepsy", "hepsy");
		jfc.addChoosableFileFilter(filter);
		
		int returnValue = jfc.showOpenDialog(null);

		String path = null;
		
		if (returnValue == JFileChooser.APPROVE_OPTION) 
		{
			// Gets the absolute path of the file
			path = jfc.getSelectedFile().getAbsolutePath();
		} 
		else 
		{
			path = "/Users/";
		}
		
		System.out.printf(path + "\n");
                
        // Get the resource
        Resource resource = resSet.getResource(URI.createFileURI(path), true); //URI_LOCAL 
        
        /*
         * Get the first model element and cast it to the right type, in my
         * example everything is hierarchical and it is a leaf of the first node
         */
        BehaviorSpecification myHepsy = (BehaviorSpecification) resource.getContents().get(0);
        
        // Destination directory
        jfc = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
        jfc.setDialogTitle("Choose a directory to save your file: ");
        jfc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        
		returnValue = jfc.showSaveDialog(null);

		String pathDest = null;
		String pathDest1 = null;
		String pathDestXML = null;
		
		if (returnValue == JFileChooser.APPROVE_OPTION) 
		{
			pathDest1 = jfc.getSelectedFile().getAbsolutePath();
		}
		else 
		{
			pathDest1 = "/Users/";
		}
		
		File files1 = new File(pathDest1 + "/Functional/src/");
        if (!files1.exists()) 
        {
            if (files1.mkdirs()) 
            {
                System.out.println("Multiple directories have been created! \n");
            } 
            else 
            {
                System.out.println("Failed to create multiple directories! \n");
            }
        }
		
		pathDest = pathDest1 + "/Functional/src/";
        File file = new File(pathDest);
        for (File files: file.listFiles()) 
        {
        	if (!files.isDirectory())
        	{
        		files.delete();
        	}
        }
        
        File filesXML = new File(pathDest1 + "/XML/");
        if (!filesXML.exists()) 
        {
            if (filesXML.mkdirs()) 
            {
                System.out.println("Multiple directories have been created! \n");
            } 
            else 
            {
                System.out.println("Failed to create multiple directories! \n");
            }
        }
        
        pathDestXML = pathDest1 + "/XML/";
        File fileXML = new File(pathDest);
        for (File files: fileXML.listFiles()) 
        {
        	if (!files.isDirectory())
        	{
        		files.delete();
        	}
        }
        
        pathDest1 = pathDest1 + "/";
        
        CreateMakefile makeFiles = new CreateMakefile();
        CreateXML xmlF = new CreateXML();
		CreateSystemC sysCFiles = new CreateSystemC();
		
		// Create MakeFile and sh script
		makeFiles.createFiles(pathDest1);
		
		// Create XML
		xmlF.createXMLFiles(pathDestXML, myHepsy);
		sysCFiles.findLeafs(xmlF.getNodesList());
		
		// Create systemC Libraries
		sysCFiles.createLib(pathDest);  //PATH_SYSTEMC_PROJECT
		
		System.out.println(pathDest);
		
		sysCFiles.setHashId(xmlF.getHashId());
		EList<Process> prList = xmlF.getProcessesList();
		sysCFiles.setProcessesList(prList);
		sysCFiles.setChannelsList(xmlF.getChannelsList());
		// Create Main
		sysCFiles.createMain(pathDest, myHepsy);  //PATH_SYSTEMC_PROJECT
		sysCFiles.createMainsystem(pathDest, myHepsy);  //PATH_SYSTEMC_PROJECT
		sysCFiles.createDatatype(pathDest, myHepsy);  //PATH_SYSTEMC_PROJECT  
		sysCFiles.createStimGenCpp(pathDest);
		sysCFiles.createStimGenh(pathDest);
		sysCFiles.createDisplayCpp(pathDest);
		sysCFiles.createDisplayH(pathDest);
		for(Iterator<Process> pr = prList.iterator(); pr.hasNext(); )
		{
			Process item = pr.next();
			sysCFiles.createProcess(pathDest, item);
		}
	}

}
