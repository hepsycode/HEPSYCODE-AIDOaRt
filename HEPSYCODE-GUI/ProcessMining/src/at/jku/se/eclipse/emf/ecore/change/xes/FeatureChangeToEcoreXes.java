package at.jku.se.eclipse.emf.ecore.change.xes;

import java.util.Date;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.util.EcoreUtil;

import at.jku.se.eclipse.emf.ecore.change.FeatureChange;
import at.jku.se.ecorexes.ecoreXES.EcoreXESFactory;
import at.jku.se.ecorexes.ecoreXES.Event;
import at.jku.se.ecorexes.ecoreXES.EventType;
import at.jku.se.ecorexes.ecoreXES.Feature;
import at.jku.se.ecorexes.ecoreXES.FeatureAndClass;
import at.jku.se.ecorexes.ecoreXES.ID;
import at.jku.se.ecorexes.ecoreXES.JavaClass;
import at.jku.se.ecorexes.ecoreXES.Log;
import at.jku.se.ecorexes.ecoreXES.ReferenceValue;

public class FeatureChangeToEcoreXes {
	public static void addEvent(EObject reference, FeatureChange featureChange, Log log, EcoreXesMeta meta, Notification notification) {
		EcoreXESFactory f = EcoreXESFactory.eINSTANCE;
		Event event = f.createEvent();
		event.setEventType(EventType.get(notification.getEventType()));
		event.setTimestamp(new Date(featureChange.getTimeStamp()));
		event.setSet(featureChange.isSet());
		String javaClassName = reference.eClass().getInstanceClassName();
		JavaClass javaClass = meta.javaClassMap.get(javaClassName);
		if (javaClass == null) {
			javaClass = f.createJavaClass();
			javaClass.setName(javaClassName);
			meta.javaClassMap.put(javaClassName, javaClass);
			log.getAttributes().add(javaClass);
		}
		String featureName = featureChange.getFeatureName();
		Feature feature = meta.featureMap.get(featureName);
		if (feature == null) {
			feature = f.createFeature();
			feature.setName(featureName);
			meta.featureMap.put(featureName, feature);
			log.getAttributes().add(feature);
		}
		String eventTypeName = reference.eClass().getName() + ":" + featureName;
		FeatureAndClass featureAndClass = meta.eventTypeMap.get(eventTypeName);
		if (featureAndClass == null) {
			featureAndClass = f.createFeatureAndClass();
			featureAndClass.setClass(javaClass);
			featureAndClass.setFeature(feature);
			featureAndClass.setName(eventTypeName);
			meta.eventTypeMap.put(eventTypeName, featureAndClass);
			log.getAttributes().add(featureAndClass);
		}
		event.setFatureAndClass(featureAndClass);
		String dataValue = featureChange.getDataValue();
		if (dataValue != null && !dataValue.isEmpty()) {
			event.setDataValue(dataValue);
		}
		if (featureChange.getReferenceValue() != null) {
			String referenceValueName = EcoreUtil.getURI(featureChange.getReferenceValue()).toString();
			ReferenceValue referenceValue = meta.referenceValueMap.get(referenceValueName);
			if(referenceValue == null) {
				referenceValue = f.createReferenceValue();
				referenceValue.setName(referenceValueName);
				meta.referenceValueMap.put(referenceValueName, referenceValue);
				log.getAttributes().add(referenceValue);
			}
			event.setReferencevalue(referenceValue);
		}
		Resource resource = reference.eResource();
		if (resource != null) {
			URI uri = resource.getURI();
			if(log.getResource() == null) {
				log.setResource(uri.fileExtension());
			}
			String idName = resource.getURIFragment(reference);
			ID id = meta.iDMap.get(idName);
			if(id == null) {
				id = f.createID();
				id.setName(idName);
				meta.iDMap.put(idName, id);
				log.getAttributes().add(id);
			}
			event.setId(id);
		}
		log.getEvent().add(event);
	}

}
