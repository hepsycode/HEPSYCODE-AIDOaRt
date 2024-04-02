/**
 */
package at.jku.se.ecorexes.ecoreXES.impl;

import at.jku.se.ecorexes.ecoreXES.Attributes;
import at.jku.se.ecorexes.ecoreXES.EcoreXESFactory;
import at.jku.se.ecorexes.ecoreXES.EcoreXESPackage;
import at.jku.se.ecorexes.ecoreXES.Event;
import at.jku.se.ecorexes.ecoreXES.EventType;
import at.jku.se.ecorexes.ecoreXES.Feature;
import at.jku.se.ecorexes.ecoreXES.FeatureAndClass;
import at.jku.se.ecorexes.ecoreXES.JavaClass;
import at.jku.se.ecorexes.ecoreXES.Log;
import at.jku.se.ecorexes.ecoreXES.ReferenceValue;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EEnum;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

import org.eclipse.emf.ecore.impl.EPackageImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Package</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class EcoreXESPackageImpl extends EPackageImpl implements EcoreXESPackage {
	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EClass eventEClass = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EClass logEClass = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EClass attributesEClass = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EClass featureAndClassEClass = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EClass featureEClass = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EClass javaClassEClass = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EClass idEClass = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EClass referenceValueEClass = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EEnum eventTypeEEnum = null;

	/**
	 * Creates an instance of the model <b>Package</b>, registered with
	 * {@link org.eclipse.emf.ecore.EPackage.Registry EPackage.Registry} by the package
	 * package URI value.
	 * <p>Note: the correct way to create the package is via the static
	 * factory method {@link #init init()}, which also performs
	 * initialization of the package, or returns the registered package,
	 * if one already exists.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.eclipse.emf.ecore.EPackage.Registry
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#eNS_URI
	 * @see #init()
	 * @generated
	 */
	private EcoreXESPackageImpl() {
		super(eNS_URI, EcoreXESFactory.eINSTANCE);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private static boolean isInited = false;

	/**
	 * Creates, registers, and initializes the <b>Package</b> for this model, and for any others upon which it depends.
	 *
	 * <p>This method is used to initialize {@link EcoreXESPackage#eINSTANCE} when that field is accessed.
	 * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #eNS_URI
	 * @see #createPackageContents()
	 * @see #initializePackageContents()
	 * @generated
	 */
	public static EcoreXESPackage init() {
		if (isInited)
			return (EcoreXESPackage) EPackage.Registry.INSTANCE.getEPackage(EcoreXESPackage.eNS_URI);

		// Obtain or create and register package
		Object registeredEcoreXESPackage = EPackage.Registry.INSTANCE.get(eNS_URI);
		EcoreXESPackageImpl theEcoreXESPackage = registeredEcoreXESPackage instanceof EcoreXESPackageImpl
				? (EcoreXESPackageImpl) registeredEcoreXESPackage
				: new EcoreXESPackageImpl();

		isInited = true;

		// Create package meta-data objects
		theEcoreXESPackage.createPackageContents();

		// Initialize created meta-data
		theEcoreXESPackage.initializePackageContents();

		// Mark meta-data to indicate it can't be changed
		theEcoreXESPackage.freeze();

		// Update the registry and return the package
		EPackage.Registry.INSTANCE.put(EcoreXESPackage.eNS_URI, theEcoreXESPackage);
		return theEcoreXESPackage;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EClass getEvent() {
		return eventEClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EAttribute getEvent_Set() {
		return (EAttribute) eventEClass.getEStructuralFeatures().get(0);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EAttribute getEvent_Timestamp() {
		return (EAttribute) eventEClass.getEStructuralFeatures().get(1);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EReference getEvent_FatureAndClass() {
		return (EReference) eventEClass.getEStructuralFeatures().get(2);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EReference getEvent_Id() {
		return (EReference) eventEClass.getEStructuralFeatures().get(3);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EReference getEvent_Referencevalue() {
		return (EReference) eventEClass.getEStructuralFeatures().get(4);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EAttribute getEvent_DataValue() {
		return (EAttribute) eventEClass.getEStructuralFeatures().get(5);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EAttribute getEvent_EventType() {
		return (EAttribute) eventEClass.getEStructuralFeatures().get(6);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EClass getLog() {
		return logEClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EAttribute getLog_Resource() {
		return (EAttribute) logEClass.getEStructuralFeatures().get(0);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EReference getLog_Event() {
		return (EReference) logEClass.getEStructuralFeatures().get(1);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EReference getLog_Attributes() {
		return (EReference) logEClass.getEStructuralFeatures().get(2);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EClass getAttributes() {
		return attributesEClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EAttribute getAttributes_Name() {
		return (EAttribute) attributesEClass.getEStructuralFeatures().get(0);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EClass getFeatureAndClass() {
		return featureAndClassEClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EReference getFeatureAndClass_Class() {
		return (EReference) featureAndClassEClass.getEStructuralFeatures().get(0);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EReference getFeatureAndClass_Feature() {
		return (EReference) featureAndClassEClass.getEStructuralFeatures().get(1);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EEnum getEventType() {
		return eventTypeEEnum;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EClass getFeature() {
		return featureEClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EClass getJavaClass() {
		return javaClassEClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EClass getID() {
		return idEClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EClass getReferenceValue() {
		return referenceValueEClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EcoreXESFactory getEcoreXESFactory() {
		return (EcoreXESFactory) getEFactoryInstance();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private boolean isCreated = false;

	/**
	 * Creates the meta-model objects for the package.  This method is
	 * guarded to have no affect on any invocation but its first.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void createPackageContents() {
		if (isCreated)
			return;
		isCreated = true;

		// Create classes and their features
		eventEClass = createEClass(EVENT);
		createEAttribute(eventEClass, EVENT__SET);
		createEAttribute(eventEClass, EVENT__TIMESTAMP);
		createEReference(eventEClass, EVENT__FATURE_AND_CLASS);
		createEReference(eventEClass, EVENT__ID);
		createEReference(eventEClass, EVENT__REFERENCEVALUE);
		createEAttribute(eventEClass, EVENT__DATA_VALUE);
		createEAttribute(eventEClass, EVENT__EVENT_TYPE);

		logEClass = createEClass(LOG);
		createEAttribute(logEClass, LOG__RESOURCE);
		createEReference(logEClass, LOG__EVENT);
		createEReference(logEClass, LOG__ATTRIBUTES);

		attributesEClass = createEClass(ATTRIBUTES);
		createEAttribute(attributesEClass, ATTRIBUTES__NAME);

		featureAndClassEClass = createEClass(FEATURE_AND_CLASS);
		createEReference(featureAndClassEClass, FEATURE_AND_CLASS__CLASS);
		createEReference(featureAndClassEClass, FEATURE_AND_CLASS__FEATURE);

		featureEClass = createEClass(FEATURE);

		javaClassEClass = createEClass(JAVA_CLASS);

		idEClass = createEClass(ID);

		referenceValueEClass = createEClass(REFERENCE_VALUE);

		// Create enums
		eventTypeEEnum = createEEnum(EVENT_TYPE);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private boolean isInitialized = false;

	/**
	 * Complete the initialization of the package and its meta-model.  This
	 * method is guarded to have no affect on any invocation but its first.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void initializePackageContents() {
		if (isInitialized)
			return;
		isInitialized = true;

		// Initialize package
		setName(eNAME);
		setNsPrefix(eNS_PREFIX);
		setNsURI(eNS_URI);

		// Create type parameters

		// Set bounds for type parameters

		// Add supertypes to classes
		featureAndClassEClass.getESuperTypes().add(this.getAttributes());
		featureEClass.getESuperTypes().add(this.getAttributes());
		javaClassEClass.getESuperTypes().add(this.getAttributes());
		idEClass.getESuperTypes().add(this.getAttributes());
		referenceValueEClass.getESuperTypes().add(this.getAttributes());

		// Initialize classes, features, and operations; add parameters
		initEClass(eventEClass, Event.class, "Event", !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
		initEAttribute(getEvent_Set(), ecorePackage.getEBoolean(), "set", null, 0, 1, Event.class, !IS_TRANSIENT,
				!IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
		initEAttribute(getEvent_Timestamp(), ecorePackage.getEDate(), "timestamp", null, 0, 1, Event.class,
				!IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
		initEReference(getEvent_FatureAndClass(), this.getFeatureAndClass(), null, "fatureAndClass", null, 1, 1,
				Event.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
				!IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
		initEReference(getEvent_Id(), this.getID(), null, "id", null, 1, 1, Event.class, !IS_TRANSIENT, !IS_VOLATILE,
				IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
		initEReference(getEvent_Referencevalue(), this.getReferenceValue(), null, "referencevalue", null, 0, 1,
				Event.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
				!IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
		initEAttribute(getEvent_DataValue(), ecorePackage.getEString(), "dataValue", null, 0, 1, Event.class,
				!IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
		initEAttribute(getEvent_EventType(), this.getEventType(), "eventType", null, 0, 1, Event.class, !IS_TRANSIENT,
				!IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

		initEClass(logEClass, Log.class, "Log", !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
		initEAttribute(getLog_Resource(), ecorePackage.getEString(), "resource", null, 0, 1, Log.class, !IS_TRANSIENT,
				!IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
		initEReference(getLog_Event(), this.getEvent(), null, "event", null, 0, -1, Log.class, !IS_TRANSIENT,
				!IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
				IS_ORDERED);
		initEReference(getLog_Attributes(), this.getAttributes(), null, "attributes", null, 0, -1, Log.class,
				!IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES, !IS_UNSETTABLE,
				IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

		initEClass(attributesEClass, Attributes.class, "Attributes", IS_ABSTRACT, !IS_INTERFACE,
				IS_GENERATED_INSTANCE_CLASS);
		initEAttribute(getAttributes_Name(), ecorePackage.getEString(), "name", null, 0, 1, Attributes.class,
				!IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

		initEClass(featureAndClassEClass, FeatureAndClass.class, "FeatureAndClass", !IS_ABSTRACT, !IS_INTERFACE,
				IS_GENERATED_INSTANCE_CLASS);
		initEReference(getFeatureAndClass_Class(), this.getJavaClass(), null, "class", null, 1, 1,
				FeatureAndClass.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
				!IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
		initEReference(getFeatureAndClass_Feature(), this.getFeature(), null, "feature", null, 1, 1,
				FeatureAndClass.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
				!IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

		initEClass(featureEClass, Feature.class, "Feature", !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);

		initEClass(javaClassEClass, JavaClass.class, "JavaClass", !IS_ABSTRACT, !IS_INTERFACE,
				IS_GENERATED_INSTANCE_CLASS);

		initEClass(idEClass, at.jku.se.ecorexes.ecoreXES.ID.class, "ID", !IS_ABSTRACT, !IS_INTERFACE,
				IS_GENERATED_INSTANCE_CLASS);

		initEClass(referenceValueEClass, ReferenceValue.class, "ReferenceValue", !IS_ABSTRACT, !IS_INTERFACE,
				IS_GENERATED_INSTANCE_CLASS);

		// Initialize enums and add enum literals
		initEEnum(eventTypeEEnum, EventType.class, "EventType");
		addEEnumLiteral(eventTypeEEnum, EventType.SET);
		addEEnumLiteral(eventTypeEEnum, EventType.UNSET);
		addEEnumLiteral(eventTypeEEnum, EventType.ADD);
		addEEnumLiteral(eventTypeEEnum, EventType.REMOVE);
		addEEnumLiteral(eventTypeEEnum, EventType.ADD_MANY);
		addEEnumLiteral(eventTypeEEnum, EventType.REMOVE_MANY);
		addEEnumLiteral(eventTypeEEnum, EventType.MOVE);
		addEEnumLiteral(eventTypeEEnum, EventType.RESOLVE);

		// Create resource
		createResource(eNS_URI);
	}

} //EcoreXESPackageImpl
