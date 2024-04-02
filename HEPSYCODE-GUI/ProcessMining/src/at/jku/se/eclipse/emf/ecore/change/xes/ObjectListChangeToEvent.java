package at.jku.se.eclipse.emf.ecore.change.xes;

import org.eclipse.emf.common.notify.Notification;
import org.deckfour.xes.factory.XFactory;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.util.EcoreUtil;

import at.jku.se.eclipse.emf.ecore.change.FeatureChange;
import at.jku.se.eclipse.emf.ecore.change.ListChange;
import at.jku.se.ecorexes.ecoreXES.EventType;

public class ObjectListChangeToEvent extends ListChangeToEvent {

	public ObjectListChangeToEvent(ListChange listChange, EObject reference, FeatureChange featureChange,
			XFactory factory, Notification notification) {
		super(listChange, factory);
		put("type", "listChange");
		put("eventType", EventType.get(notification.getEventType()).toString());
		putTime(featureChange.getTimeStamp());
		String className = reference.eClass().getName();
		String javaClass = reference.eClass().getInstanceClassName();
		put("class", className);
		put("javaClass", javaClass);
		put("featureName", featureChange.getFeatureName());
		putName(className + ":" + featureChange.getFeatureName());
		put("set", featureChange.isSet());
		String dataValue = featureChange.getDataValue();
		if (dataValue != null) {
			if (dataValue.isEmpty()) {
				dataValue = "\"\"";
			}
			put("dataValue", featureChange.getDataValue());
		}
		if (featureChange.getReferenceValue() != null) {
			put("referenceValue", EcoreUtil.getURI(featureChange.getReferenceValue()).toString());
		}
		URI proxy = EcoreUtil.getURI(reference);
		put("proxy", proxy.toString());
		Resource resource = reference.eResource();
		if (resource != null) {
			URI uri = resource.getURI();
			put("resource", uri.fileExtension());
			String id = resource.getURIFragment(reference);
			put("id", id);
		}
	}

}
