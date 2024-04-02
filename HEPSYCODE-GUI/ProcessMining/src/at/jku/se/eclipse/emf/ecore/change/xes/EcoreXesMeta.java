package at.jku.se.eclipse.emf.ecore.change.xes;

import java.util.HashMap;
import java.util.Map;

import at.jku.se.ecorexes.ecoreXES.EventType;
import at.jku.se.ecorexes.ecoreXES.Feature;
import at.jku.se.ecorexes.ecoreXES.FeatureAndClass;
import at.jku.se.ecorexes.ecoreXES.ID;
import at.jku.se.ecorexes.ecoreXES.JavaClass;
import at.jku.se.ecorexes.ecoreXES.ReferenceValue;

public class EcoreXesMeta {
	Map<String, JavaClass> javaClassMap = new HashMap<>();
	Map<String, Feature> featureMap = new HashMap<String, Feature>();
	Map<String, FeatureAndClass> eventTypeMap = new HashMap<>();
	Map<String, ID> iDMap = new HashMap<>();
	Map<String, ReferenceValue> referenceValueMap = new HashMap<>();
}
