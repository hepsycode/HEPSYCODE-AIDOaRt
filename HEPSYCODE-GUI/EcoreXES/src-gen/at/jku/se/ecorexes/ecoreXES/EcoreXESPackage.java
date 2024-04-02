/**
 */
package at.jku.se.ecorexes.ecoreXES;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EEnum;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each operation of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESFactory
 * @model kind="package"
 * @generated
 */
public interface EcoreXESPackage extends EPackage {
	/**
	 * The package name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNAME = "ecoreXES";

	/**
	 * The package namespace URI.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_URI = "http://www.example.org/ecoreXES";

	/**
	 * The package namespace name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_PREFIX = "ecoreXES";

	/**
	 * The singleton instance of the package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	EcoreXESPackage eINSTANCE = at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl.init();

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl <em>Event</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EventImpl
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getEvent()
	 * @generated
	 */
	int EVENT = 0;

	/**
	 * The feature id for the '<em><b>Set</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT__SET = 0;

	/**
	 * The feature id for the '<em><b>Timestamp</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT__TIMESTAMP = 1;

	/**
	 * The feature id for the '<em><b>Fature And Class</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT__FATURE_AND_CLASS = 2;

	/**
	 * The feature id for the '<em><b>Id</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT__ID = 3;

	/**
	 * The feature id for the '<em><b>Referencevalue</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT__REFERENCEVALUE = 4;

	/**
	 * The feature id for the '<em><b>Data Value</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT__DATA_VALUE = 5;

	/**
	 * The feature id for the '<em><b>Event Type</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT__EVENT_TYPE = 6;

	/**
	 * The number of structural features of the '<em>Event</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT_FEATURE_COUNT = 7;

	/**
	 * The number of operations of the '<em>Event</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int EVENT_OPERATION_COUNT = 0;

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.impl.LogImpl <em>Log</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.impl.LogImpl
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getLog()
	 * @generated
	 */
	int LOG = 1;

	/**
	 * The feature id for the '<em><b>Resource</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LOG__RESOURCE = 0;

	/**
	 * The feature id for the '<em><b>Event</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LOG__EVENT = 1;

	/**
	 * The feature id for the '<em><b>Attributes</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LOG__ATTRIBUTES = 2;

	/**
	 * The number of structural features of the '<em>Log</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LOG_FEATURE_COUNT = 3;

	/**
	 * The number of operations of the '<em>Log</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LOG_OPERATION_COUNT = 0;

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.impl.AttributesImpl <em>Attributes</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.impl.AttributesImpl
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getAttributes()
	 * @generated
	 */
	int ATTRIBUTES = 2;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ATTRIBUTES__NAME = 0;

	/**
	 * The number of structural features of the '<em>Attributes</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ATTRIBUTES_FEATURE_COUNT = 1;

	/**
	 * The number of operations of the '<em>Attributes</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ATTRIBUTES_OPERATION_COUNT = 0;

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.impl.FeatureAndClassImpl <em>Feature And Class</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.impl.FeatureAndClassImpl
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getFeatureAndClass()
	 * @generated
	 */
	int FEATURE_AND_CLASS = 3;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE_AND_CLASS__NAME = ATTRIBUTES__NAME;

	/**
	 * The feature id for the '<em><b>Class</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE_AND_CLASS__CLASS = ATTRIBUTES_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Feature</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE_AND_CLASS__FEATURE = ATTRIBUTES_FEATURE_COUNT + 1;

	/**
	 * The number of structural features of the '<em>Feature And Class</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE_AND_CLASS_FEATURE_COUNT = ATTRIBUTES_FEATURE_COUNT + 2;

	/**
	 * The number of operations of the '<em>Feature And Class</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE_AND_CLASS_OPERATION_COUNT = ATTRIBUTES_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.EventType <em>Event Type</em>}' enum.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.EventType
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getEventType()
	 * @generated
	 */
	int EVENT_TYPE = 8;

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.impl.FeatureImpl <em>Feature</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.impl.FeatureImpl
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getFeature()
	 * @generated
	 */
	int FEATURE = 4;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE__NAME = ATTRIBUTES__NAME;

	/**
	 * The number of structural features of the '<em>Feature</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE_FEATURE_COUNT = ATTRIBUTES_FEATURE_COUNT + 0;

	/**
	 * The number of operations of the '<em>Feature</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE_OPERATION_COUNT = ATTRIBUTES_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.impl.JavaClassImpl <em>Java Class</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.impl.JavaClassImpl
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getJavaClass()
	 * @generated
	 */
	int JAVA_CLASS = 5;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int JAVA_CLASS__NAME = ATTRIBUTES__NAME;

	/**
	 * The number of structural features of the '<em>Java Class</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int JAVA_CLASS_FEATURE_COUNT = ATTRIBUTES_FEATURE_COUNT + 0;

	/**
	 * The number of operations of the '<em>Java Class</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int JAVA_CLASS_OPERATION_COUNT = ATTRIBUTES_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.impl.IDImpl <em>ID</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.impl.IDImpl
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getID()
	 * @generated
	 */
	int ID = 6;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ID__NAME = ATTRIBUTES__NAME;

	/**
	 * The number of structural features of the '<em>ID</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ID_FEATURE_COUNT = ATTRIBUTES_FEATURE_COUNT + 0;

	/**
	 * The number of operations of the '<em>ID</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ID_OPERATION_COUNT = ATTRIBUTES_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link at.jku.se.ecorexes.ecoreXES.impl.ReferenceValueImpl <em>Reference Value</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see at.jku.se.ecorexes.ecoreXES.impl.ReferenceValueImpl
	 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getReferenceValue()
	 * @generated
	 */
	int REFERENCE_VALUE = 7;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int REFERENCE_VALUE__NAME = ATTRIBUTES__NAME;

	/**
	 * The number of structural features of the '<em>Reference Value</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int REFERENCE_VALUE_FEATURE_COUNT = ATTRIBUTES_FEATURE_COUNT + 0;

	/**
	 * The number of operations of the '<em>Reference Value</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int REFERENCE_VALUE_OPERATION_COUNT = ATTRIBUTES_OPERATION_COUNT + 0;

	/**
	 * Returns the meta object for class '{@link at.jku.se.ecorexes.ecoreXES.Event <em>Event</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Event</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Event
	 * @generated
	 */
	EClass getEvent();

	/**
	 * Returns the meta object for the attribute '{@link at.jku.se.ecorexes.ecoreXES.Event#isSet <em>Set</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Set</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Event#isSet()
	 * @see #getEvent()
	 * @generated
	 */
	EAttribute getEvent_Set();

	/**
	 * Returns the meta object for the attribute '{@link at.jku.se.ecorexes.ecoreXES.Event#getTimestamp <em>Timestamp</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Timestamp</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Event#getTimestamp()
	 * @see #getEvent()
	 * @generated
	 */
	EAttribute getEvent_Timestamp();

	/**
	 * Returns the meta object for the reference '{@link at.jku.se.ecorexes.ecoreXES.Event#getFatureAndClass <em>Fature And Class</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Fature And Class</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Event#getFatureAndClass()
	 * @see #getEvent()
	 * @generated
	 */
	EReference getEvent_FatureAndClass();

	/**
	 * Returns the meta object for the reference '{@link at.jku.se.ecorexes.ecoreXES.Event#getId <em>Id</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Id</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Event#getId()
	 * @see #getEvent()
	 * @generated
	 */
	EReference getEvent_Id();

	/**
	 * Returns the meta object for the reference '{@link at.jku.se.ecorexes.ecoreXES.Event#getReferencevalue <em>Referencevalue</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Referencevalue</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Event#getReferencevalue()
	 * @see #getEvent()
	 * @generated
	 */
	EReference getEvent_Referencevalue();

	/**
	 * Returns the meta object for the attribute '{@link at.jku.se.ecorexes.ecoreXES.Event#getDataValue <em>Data Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Data Value</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Event#getDataValue()
	 * @see #getEvent()
	 * @generated
	 */
	EAttribute getEvent_DataValue();

	/**
	 * Returns the meta object for the attribute '{@link at.jku.se.ecorexes.ecoreXES.Event#getEventType <em>Event Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Event Type</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Event#getEventType()
	 * @see #getEvent()
	 * @generated
	 */
	EAttribute getEvent_EventType();

	/**
	 * Returns the meta object for class '{@link at.jku.se.ecorexes.ecoreXES.Log <em>Log</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Log</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Log
	 * @generated
	 */
	EClass getLog();

	/**
	 * Returns the meta object for the attribute '{@link at.jku.se.ecorexes.ecoreXES.Log#getResource <em>Resource</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Resource</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Log#getResource()
	 * @see #getLog()
	 * @generated
	 */
	EAttribute getLog_Resource();

	/**
	 * Returns the meta object for the containment reference list '{@link at.jku.se.ecorexes.ecoreXES.Log#getEvent <em>Event</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Event</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Log#getEvent()
	 * @see #getLog()
	 * @generated
	 */
	EReference getLog_Event();

	/**
	 * Returns the meta object for the containment reference list '{@link at.jku.se.ecorexes.ecoreXES.Log#getAttributes <em>Attributes</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Attributes</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Log#getAttributes()
	 * @see #getLog()
	 * @generated
	 */
	EReference getLog_Attributes();

	/**
	 * Returns the meta object for class '{@link at.jku.se.ecorexes.ecoreXES.Attributes <em>Attributes</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Attributes</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Attributes
	 * @generated
	 */
	EClass getAttributes();

	/**
	 * Returns the meta object for the attribute '{@link at.jku.se.ecorexes.ecoreXES.Attributes#getName <em>Name</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Name</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Attributes#getName()
	 * @see #getAttributes()
	 * @generated
	 */
	EAttribute getAttributes_Name();

	/**
	 * Returns the meta object for class '{@link at.jku.se.ecorexes.ecoreXES.FeatureAndClass <em>Feature And Class</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Feature And Class</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.FeatureAndClass
	 * @generated
	 */
	EClass getFeatureAndClass();

	/**
	 * Returns the meta object for the reference '{@link at.jku.se.ecorexes.ecoreXES.FeatureAndClass#getClass_ <em>Class</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Class</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.FeatureAndClass#getClass_()
	 * @see #getFeatureAndClass()
	 * @generated
	 */
	EReference getFeatureAndClass_Class();

	/**
	 * Returns the meta object for the reference '{@link at.jku.se.ecorexes.ecoreXES.FeatureAndClass#getFeature <em>Feature</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Feature</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.FeatureAndClass#getFeature()
	 * @see #getFeatureAndClass()
	 * @generated
	 */
	EReference getFeatureAndClass_Feature();

	/**
	 * Returns the meta object for enum '{@link at.jku.se.ecorexes.ecoreXES.EventType <em>Event Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for enum '<em>Event Type</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.EventType
	 * @generated
	 */
	EEnum getEventType();

	/**
	 * Returns the meta object for class '{@link at.jku.se.ecorexes.ecoreXES.Feature <em>Feature</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Feature</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.Feature
	 * @generated
	 */
	EClass getFeature();

	/**
	 * Returns the meta object for class '{@link at.jku.se.ecorexes.ecoreXES.JavaClass <em>Java Class</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Java Class</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.JavaClass
	 * @generated
	 */
	EClass getJavaClass();

	/**
	 * Returns the meta object for class '{@link at.jku.se.ecorexes.ecoreXES.ID <em>ID</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>ID</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.ID
	 * @generated
	 */
	EClass getID();

	/**
	 * Returns the meta object for class '{@link at.jku.se.ecorexes.ecoreXES.ReferenceValue <em>Reference Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Reference Value</em>'.
	 * @see at.jku.se.ecorexes.ecoreXES.ReferenceValue
	 * @generated
	 */
	EClass getReferenceValue();

	/**
	 * Returns the factory that creates the instances of the model.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the factory that creates the instances of the model.
	 * @generated
	 */
	EcoreXESFactory getEcoreXESFactory();

	/**
	 * <!-- begin-user-doc -->
	 * Defines literals for the meta objects that represent
	 * <ul>
	 *   <li>each class,</li>
	 *   <li>each feature of each class,</li>
	 *   <li>each operation of each class,</li>
	 *   <li>each enum,</li>
	 *   <li>and each data type</li>
	 * </ul>
	 * <!-- end-user-doc -->
	 * @generated
	 */
	interface Literals {
		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl <em>Event</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EventImpl
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getEvent()
		 * @generated
		 */
		EClass EVENT = eINSTANCE.getEvent();

		/**
		 * The meta object literal for the '<em><b>Set</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute EVENT__SET = eINSTANCE.getEvent_Set();

		/**
		 * The meta object literal for the '<em><b>Timestamp</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute EVENT__TIMESTAMP = eINSTANCE.getEvent_Timestamp();

		/**
		 * The meta object literal for the '<em><b>Fature And Class</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference EVENT__FATURE_AND_CLASS = eINSTANCE.getEvent_FatureAndClass();

		/**
		 * The meta object literal for the '<em><b>Id</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference EVENT__ID = eINSTANCE.getEvent_Id();

		/**
		 * The meta object literal for the '<em><b>Referencevalue</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference EVENT__REFERENCEVALUE = eINSTANCE.getEvent_Referencevalue();

		/**
		 * The meta object literal for the '<em><b>Data Value</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute EVENT__DATA_VALUE = eINSTANCE.getEvent_DataValue();

		/**
		 * The meta object literal for the '<em><b>Event Type</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute EVENT__EVENT_TYPE = eINSTANCE.getEvent_EventType();

		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.impl.LogImpl <em>Log</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.impl.LogImpl
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getLog()
		 * @generated
		 */
		EClass LOG = eINSTANCE.getLog();

		/**
		 * The meta object literal for the '<em><b>Resource</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute LOG__RESOURCE = eINSTANCE.getLog_Resource();

		/**
		 * The meta object literal for the '<em><b>Event</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference LOG__EVENT = eINSTANCE.getLog_Event();

		/**
		 * The meta object literal for the '<em><b>Attributes</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference LOG__ATTRIBUTES = eINSTANCE.getLog_Attributes();

		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.impl.AttributesImpl <em>Attributes</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.impl.AttributesImpl
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getAttributes()
		 * @generated
		 */
		EClass ATTRIBUTES = eINSTANCE.getAttributes();

		/**
		 * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute ATTRIBUTES__NAME = eINSTANCE.getAttributes_Name();

		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.impl.FeatureAndClassImpl <em>Feature And Class</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.impl.FeatureAndClassImpl
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getFeatureAndClass()
		 * @generated
		 */
		EClass FEATURE_AND_CLASS = eINSTANCE.getFeatureAndClass();

		/**
		 * The meta object literal for the '<em><b>Class</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference FEATURE_AND_CLASS__CLASS = eINSTANCE.getFeatureAndClass_Class();

		/**
		 * The meta object literal for the '<em><b>Feature</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference FEATURE_AND_CLASS__FEATURE = eINSTANCE.getFeatureAndClass_Feature();

		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.EventType <em>Event Type</em>}' enum.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.EventType
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getEventType()
		 * @generated
		 */
		EEnum EVENT_TYPE = eINSTANCE.getEventType();

		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.impl.FeatureImpl <em>Feature</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.impl.FeatureImpl
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getFeature()
		 * @generated
		 */
		EClass FEATURE = eINSTANCE.getFeature();

		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.impl.JavaClassImpl <em>Java Class</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.impl.JavaClassImpl
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getJavaClass()
		 * @generated
		 */
		EClass JAVA_CLASS = eINSTANCE.getJavaClass();

		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.impl.IDImpl <em>ID</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.impl.IDImpl
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getID()
		 * @generated
		 */
		EClass ID = eINSTANCE.getID();

		/**
		 * The meta object literal for the '{@link at.jku.se.ecorexes.ecoreXES.impl.ReferenceValueImpl <em>Reference Value</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see at.jku.se.ecorexes.ecoreXES.impl.ReferenceValueImpl
		 * @see at.jku.se.ecorexes.ecoreXES.impl.EcoreXESPackageImpl#getReferenceValue()
		 * @generated
		 */
		EClass REFERENCE_VALUE = eINSTANCE.getReferenceValue();

	}

} //EcoreXESPackage
