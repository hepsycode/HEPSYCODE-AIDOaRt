package at.jku.se.eclipse.emf.ecore.sirius;

import org.deckfour.xes.extension.std.XConceptExtension;
import org.deckfour.xes.extension.std.XTimeExtension;
import org.deckfour.xes.factory.XFactory;
import org.deckfour.xes.factory.XFactoryBufferedImpl;
import org.deckfour.xes.model.XAttributeList;
import org.deckfour.xes.model.XAttributeMap;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.gmf.runtime.emf.core.util.EMFCoreUtil;

public class Util {
	
	private static XFactory factory = new XFactoryBufferedImpl();
	private static XConceptExtension conceptExt = XConceptExtension.instance();
	private static XTimeExtension timeExt = XTimeExtension.instance();
	private static final String[] eventTypeNames = new String[] {
			"CREATE",
			"SET",
			"UNSET",
			"ADD",
			"REMOVE",
			"ADD_MANY",
			"REMOVE_MANY",
			"MOVE",
			"REMOVING_ADAPTER",
			"RESOLVE"
	};
	
	public static String getQualifiedName(EObject eObject) {
		String qualifiedName;
		try {
			qualifiedName = EMFCoreUtil.getQualifiedName(eObject, true);
		} catch (java.util.MissingResourceException e) {
			qualifiedName = eObject.toString();
		}
		return qualifiedName;
	}

	public static void addObjectSpecs(XAttributeMap attrs, Object obj, String name) {
		if (obj instanceof EObject) {
			addEObjectSpecs(attrs, (EObject) obj, name);
		} else {
			addPrimitiveSpecs(attrs, obj, name);
		}
	}

	public static void addEObjectSpecs(XAttributeMap attrs, EObject eObject, String name) {
		attrs.put(name + "_object_name", factory.createAttributeLiteral(name + "_object_name", getQualifiedName(eObject), null));
		attrs.put(name + "_class_name", factory.createAttributeLiteral(name + "_class_name", eObject.eClass().getName(), null));
		attrs.put(name + "_class_full_name", factory.createAttributeLiteral(name + "_class_full_name", eObject.getClass().getCanonicalName(), null));
	}

	public static void addPrimitiveSpecs(XAttributeMap attrs, Object obj, String name) {
		String toString = obj.toString();
		if(toString.isBlank()) {
			toString = "null";
		}
		attrs.put(name + "_object_name", factory.createAttributeLiteral(name + "_object_name", toString, null));
		attrs.put(name + "_class_name", factory.createAttributeLiteral(name + "_class_name", obj.getClass().getName(), null));
		attrs.put(name + "_class_full_name", factory.createAttributeLiteral(name + "_class_full_name", obj.getClass().getCanonicalName(), null));
	}
	
	public static void addObjectSpecs(XAttributeList list, Object obj, String name) {
		if (obj instanceof EObject) {
			addEObjectSpecs(list, (EObject) obj, name);
		} else {
			addPrimitiveSpecs(list, obj, name);
		}
	}

	public static void addEObjectSpecs(XAttributeList list, EObject eObject, String name) {
		list.addToCollection(factory.createAttributeLiteral(name + "_object_name", getQualifiedName(eObject), null));
		list.addToCollection(factory.createAttributeLiteral(name + "_class_name", eObject.eClass().getName(), null));
	}

	public static void addPrimitiveSpecs(XAttributeList list, Object obj, String name) {
		String toString = obj.toString();
		if(toString.isBlank()) {
			toString = "null";
		}
		list.addToCollection(factory.createAttributeLiteral(name + "_object_name", toString, null));
		list.addToCollection(factory.createAttributeLiteral(name + "_class_name", obj.getClass().getName(), null));
	}

	public static XFactory getFactory() {
		return factory;
	}

	public static XConceptExtension getConceptExt() {
		return conceptExt;
	}

	public static XTimeExtension getTimeExt() {
		return timeExt;
	}
	
	public static String getEventType(int type) {
		return eventTypeNames[type];
	}
	
}