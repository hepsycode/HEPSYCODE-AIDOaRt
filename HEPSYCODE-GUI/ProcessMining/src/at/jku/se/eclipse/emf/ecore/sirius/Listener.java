package at.jku.se.eclipse.emf.ecore.sirius;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Collections;
import org.deckfour.xes.model.XLog;
import org.deckfour.xes.model.XTrace;
import org.deckfour.xes.out.XesXmlSerializer;
import org.eclipse.emf.common.util.URI;
import at.jku.se.eclipse.emf.ecore.change.ChangeDescription;
import at.jku.se.eclipse.emf.ecore.change.util.ChangeRecorder;
import at.jku.se.ecorexes.ecoreXES.Log;

import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.util.EcoreUtil.Copier;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;
import org.eclipse.sirius.business.api.session.Session;

public class Listener {
	private XLog log;
	private XTrace trace;
	private Session session;
	ResourceSet resourceSet;
	private ChangeRecorder recorder;

	public Listener(Session session) {
		this.session = session;

		log = Util.getFactory().createLog();
		log.getExtensions().add(Util.getConceptExt());
		log.getExtensions().add(Util.getTimeExt());

		trace = Util.getFactory().createTrace();
		resourceSet = session.getTransactionalEditingDomain().getResourceSet();
		recorder = new ChangeRecorder();
		recorder.beginRecording(Collections.singleton(resourceSet));
	}

	public void serializeLog() {
		log.add(trace);
		XesXmlSerializer serializer = new XesXmlSerializer();
		DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH.mm");
		String formattedDateTime = LocalDateTime.now().format(formatter); // "2015-07-07 12.30"
		String sessionId = session.getID().replace("platform:/resource/", "");
		String formattedSessionId = sessionId.replace("/", "-");
		String name = formattedDateTime + " " + formattedSessionId;
		File file = new File(Activator.getPath() + "\\XES\\" + name + ".xes");
		saveEcore(Activator.getPath() + "\\Ecore\\" + name + ".xmi");
		ChangeDescription ch = saveXMI(Activator.getPath() + "\\ChangeModel\\" + name + ".xmi");
		log = recorder.getLog();
		System.out.println(file.getAbsolutePath());
		try {
			file.getParentFile().mkdirs();
			file.createNewFile();
			OutputStream out = new BufferedOutputStream(new FileOutputStream(file));
			// nested attributes : false
			serializer.serialize(log, out, false);
			out.flush();
			out.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public ChangeDescription saveXMI(String path) {
		ChangeDescription changeDescription = recorder.endRecording();
		recorder.dispose();
		ResourceSet resourceSet = new ResourceSetImpl();
		resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap().put("change", new XMIResourceFactoryImpl());
		URI uri = URI.createURI("file:/" + path);
		Resource resource = resourceSet.createResource(uri);
		Copier copier = new Copier();
		resource.getContents().add(copier.copy(changeDescription));
		copier.copyReferences();
		try {
			resource.save(null);
			System.out.println("saved to " + path);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return changeDescription;
	}
	
	public void saveEcore(String path) {
		Log ecorelog = recorder.ecoreLog;
		ResourceSet resourceSet = new ResourceSetImpl();
		resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap().put("ecorexes", new XMIResourceFactoryImpl());
		URI uri = URI.createURI("file:/" + path);
		Resource resource = resourceSet.createResource(uri);
		Copier copier = new Copier();
		resource.getContents().add(copier.copy(ecorelog));
		copier.copyReferences();
		try {
			resource.save(null);
			System.out.println("saved to " + path);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}