package at.jku.se.eclipse.emf.ecore.change.xes;

import org.deckfour.xes.factory.XFactory;
import at.jku.se.eclipse.emf.ecore.change.ListChange;
import at.jku.se.eclipse.emf.ecore.change.ResourceChange;

public class ResourceListChangeToEvent extends ListChangeToEvent {

	public ResourceListChangeToEvent(ListChange listChange, ResourceChange resourceChange, XFactory factory) {
		super(listChange, factory);
		put("type", "resourceChange");
		putTime(resourceChange.getTimeStamp());
		String uri = resourceChange.getResourceURI();
		String kind = listChange.getKind().getName();
		put("uri", uri);
		String resource = resourceChange.getResource().getURI().fileExtension();
		put("resource", resource);
		putName(resource + ":" + kind);
	}

}
