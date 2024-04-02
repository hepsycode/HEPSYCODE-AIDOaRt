/**
 */
package org.univaq.hepsy;

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
 * @see org.univaq.hepsy.HepsyFactory
 * @model kind="package"
 * @generated
 */
public interface HepsyPackage extends EPackage {
	/**
	 * The package name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNAME = "hepsy";

	/**
	 * The package namespace URI.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_URI = "org.univaq.hepsy";

	/**
	 * The package namespace name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_PREFIX = "hml";

	/**
	 * The singleton instance of the package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	HepsyPackage eINSTANCE = org.univaq.hepsy.impl.HepsyPackageImpl.init();

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.NamedElementImpl <em>Named Element</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.NamedElementImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getNamedElement()
	 * @generated
	 */
	int NAMED_ELEMENT = 3;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NAMED_ELEMENT__NAME = 0;

	/**
	 * The number of structural features of the '<em>Named Element</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NAMED_ELEMENT_FEATURE_COUNT = 1;

	/**
	 * The number of operations of the '<em>Named Element</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NAMED_ELEMENT_OPERATION_COUNT = 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.BehaviorSpecificationImpl <em>Behavior Specification</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.BehaviorSpecificationImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getBehaviorSpecification()
	 * @generated
	 */
	int BEHAVIOR_SPECIFICATION = 0;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BEHAVIOR_SPECIFICATION__NAME = NAMED_ELEMENT__NAME;

	/**
	 * The feature id for the '<em><b>Nodes</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BEHAVIOR_SPECIFICATION__NODES = NAMED_ELEMENT_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Behavior Specification</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BEHAVIOR_SPECIFICATION_FEATURE_COUNT = NAMED_ELEMENT_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>Behavior Specification</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BEHAVIOR_SPECIFICATION_OPERATION_COUNT = NAMED_ELEMENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.NodeImpl <em>Node</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.NodeImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getNode()
	 * @generated
	 */
	int NODE = 1;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NODE__NAME = NAMED_ELEMENT__NAME;

	/**
	 * The feature id for the '<em><b>NChannels</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NODE__NCHANNELS = NAMED_ELEMENT_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Ports</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NODE__PORTS = NAMED_ELEMENT_FEATURE_COUNT + 1;

	/**
	 * The number of structural features of the '<em>Node</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NODE_FEATURE_COUNT = NAMED_ELEMENT_FEATURE_COUNT + 2;

	/**
	 * The number of operations of the '<em>Node</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NODE_OPERATION_COUNT = NAMED_ELEMENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.ChannelImpl <em>Channel</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.ChannelImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getChannel()
	 * @generated
	 */
	int CHANNEL = 2;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__NAME = NAMED_ELEMENT__NAME;

	/**
	 * The feature id for the '<em><b>NFrom</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__NFROM = NAMED_ELEMENT_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>NTo</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__NTO = NAMED_ELEMENT_FEATURE_COUNT + 1;

	/**
	 * The feature id for the '<em><b>PFrom</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__PFROM = NAMED_ELEMENT_FEATURE_COUNT + 2;

	/**
	 * The feature id for the '<em><b>PTo</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__PTO = NAMED_ELEMENT_FEATURE_COUNT + 3;

	/**
	 * The feature id for the '<em><b>Queue Size</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__QUEUE_SIZE = NAMED_ELEMENT_FEATURE_COUNT + 4;

	/**
	 * The feature id for the '<em><b>Timeout</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__TIMEOUT = NAMED_ELEMENT_FEATURE_COUNT + 5;

	/**
	 * The feature id for the '<em><b>Rendez Vous</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__RENDEZ_VOUS = NAMED_ELEMENT_FEATURE_COUNT + 6;

	/**
	 * The feature id for the '<em><b>Direction</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__DIRECTION = NAMED_ELEMENT_FEATURE_COUNT + 7;

	/**
	 * The feature id for the '<em><b>Message</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL__MESSAGE = NAMED_ELEMENT_FEATURE_COUNT + 8;

	/**
	 * The number of structural features of the '<em>Channel</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL_FEATURE_COUNT = NAMED_ELEMENT_FEATURE_COUNT + 9;

	/**
	 * The number of operations of the '<em>Channel</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CHANNEL_OPERATION_COUNT = NAMED_ELEMENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.StructuredNodeImpl <em>Structured Node</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.StructuredNodeImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getStructuredNode()
	 * @generated
	 */
	int STRUCTURED_NODE = 4;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRUCTURED_NODE__NAME = NODE__NAME;

	/**
	 * The feature id for the '<em><b>NChannels</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRUCTURED_NODE__NCHANNELS = NODE__NCHANNELS;

	/**
	 * The feature id for the '<em><b>Ports</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRUCTURED_NODE__PORTS = NODE__PORTS;

	/**
	 * The feature id for the '<em><b>Processes</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRUCTURED_NODE__PROCESSES = NODE_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Structured Node</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRUCTURED_NODE_FEATURE_COUNT = NODE_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>Structured Node</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRUCTURED_NODE_OPERATION_COUNT = NODE_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.PortImpl <em>Port</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.PortImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getPort()
	 * @generated
	 */
	int PORT = 5;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PORT__NAME = NAMED_ELEMENT__NAME;

	/**
	 * The feature id for the '<em><b>PChannels</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PORT__PCHANNELS = NAMED_ELEMENT_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Port Extension</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PORT__PORT_EXTENSION = NAMED_ELEMENT_FEATURE_COUNT + 1;

	/**
	 * The number of structural features of the '<em>Port</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PORT_FEATURE_COUNT = NAMED_ELEMENT_FEATURE_COUNT + 2;

	/**
	 * The number of operations of the '<em>Port</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PORT_OPERATION_COUNT = NAMED_ELEMENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.ProcessImpl <em>Process</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.ProcessImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getProcess()
	 * @generated
	 */
	int PROCESS = 6;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROCESS__NAME = NODE__NAME;

	/**
	 * The feature id for the '<em><b>NChannels</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROCESS__NCHANNELS = NODE__NCHANNELS;

	/**
	 * The feature id for the '<em><b>Ports</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROCESS__PORTS = NODE__PORTS;

	/**
	 * The feature id for the '<em><b>Process Extension</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROCESS__PROCESS_EXTENSION = NODE_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Priority</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROCESS__PRIORITY = NODE_FEATURE_COUNT + 1;

	/**
	 * The feature id for the '<em><b>Criticality</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROCESS__CRITICALITY = NODE_FEATURE_COUNT + 2;

	/**
	 * The number of structural features of the '<em>Process</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROCESS_FEATURE_COUNT = NODE_FEATURE_COUNT + 3;

	/**
	 * The number of operations of the '<em>Process</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROCESS_OPERATION_COUNT = NODE_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.DisplayImpl <em>Display</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.DisplayImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getDisplay()
	 * @generated
	 */
	int DISPLAY = 7;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DISPLAY__NAME = NODE__NAME;

	/**
	 * The feature id for the '<em><b>NChannels</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DISPLAY__NCHANNELS = NODE__NCHANNELS;

	/**
	 * The feature id for the '<em><b>Ports</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DISPLAY__PORTS = NODE__PORTS;

	/**
	 * The number of structural features of the '<em>Display</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DISPLAY_FEATURE_COUNT = NODE_FEATURE_COUNT + 0;

	/**
	 * The number of operations of the '<em>Display</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DISPLAY_OPERATION_COUNT = NODE_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.StimulusImpl <em>Stimulus</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.StimulusImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getStimulus()
	 * @generated
	 */
	int STIMULUS = 8;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STIMULUS__NAME = NODE__NAME;

	/**
	 * The feature id for the '<em><b>NChannels</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STIMULUS__NCHANNELS = NODE__NCHANNELS;

	/**
	 * The feature id for the '<em><b>Ports</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STIMULUS__PORTS = NODE__PORTS;

	/**
	 * The number of structural features of the '<em>Stimulus</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STIMULUS_FEATURE_COUNT = NODE_FEATURE_COUNT + 0;

	/**
	 * The number of operations of the '<em>Stimulus</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STIMULUS_OPERATION_COUNT = NODE_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.MessageImpl <em>Message</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.MessageImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getMessage()
	 * @generated
	 */
	int MESSAGE = 9;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MESSAGE__NAME = NAMED_ELEMENT__NAME;

	/**
	 * The feature id for the '<em><b>Entry</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MESSAGE__ENTRY = NAMED_ELEMENT_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Message</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MESSAGE_FEATURE_COUNT = NAMED_ELEMENT_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>Message</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MESSAGE_OPERATION_COUNT = NAMED_ELEMENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.impl.EntryImpl <em>Entry</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.impl.EntryImpl
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getEntry()
	 * @generated
	 */
	int ENTRY = 10;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTRY__NAME = NAMED_ELEMENT__NAME;

	/**
	 * The feature id for the '<em><b>Type</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTRY__TYPE = NAMED_ELEMENT_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Entry</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTRY_FEATURE_COUNT = NAMED_ELEMENT_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>Entry</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTRY_OPERATION_COUNT = NAMED_ELEMENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.DataType <em>Data Type</em>}' enum.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.DataType
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getDataType()
	 * @generated
	 */
	int DATA_TYPE = 11;

	/**
	 * The meta object id for the '{@link org.univaq.hepsy.Direction <em>Direction</em>}' enum.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.univaq.hepsy.Direction
	 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getDirection()
	 * @generated
	 */
	int DIRECTION = 12;

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.BehaviorSpecification <em>Behavior Specification</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Behavior Specification</em>'.
	 * @see org.univaq.hepsy.BehaviorSpecification
	 * @generated
	 */
	EClass getBehaviorSpecification();

	/**
	 * Returns the meta object for the containment reference list '{@link org.univaq.hepsy.BehaviorSpecification#getNodes <em>Nodes</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Nodes</em>'.
	 * @see org.univaq.hepsy.BehaviorSpecification#getNodes()
	 * @see #getBehaviorSpecification()
	 * @generated
	 */
	EReference getBehaviorSpecification_Nodes();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.Node <em>Node</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Node</em>'.
	 * @see org.univaq.hepsy.Node
	 * @generated
	 */
	EClass getNode();

	/**
	 * Returns the meta object for the containment reference list '{@link org.univaq.hepsy.Node#getNChannels <em>NChannels</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>NChannels</em>'.
	 * @see org.univaq.hepsy.Node#getNChannels()
	 * @see #getNode()
	 * @generated
	 */
	EReference getNode_NChannels();

	/**
	 * Returns the meta object for the containment reference list '{@link org.univaq.hepsy.Node#getPorts <em>Ports</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Ports</em>'.
	 * @see org.univaq.hepsy.Node#getPorts()
	 * @see #getNode()
	 * @generated
	 */
	EReference getNode_Ports();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.Channel <em>Channel</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Channel</em>'.
	 * @see org.univaq.hepsy.Channel
	 * @generated
	 */
	EClass getChannel();

	/**
	 * Returns the meta object for the reference '{@link org.univaq.hepsy.Channel#getNFrom <em>NFrom</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>NFrom</em>'.
	 * @see org.univaq.hepsy.Channel#getNFrom()
	 * @see #getChannel()
	 * @generated
	 */
	EReference getChannel_NFrom();

	/**
	 * Returns the meta object for the reference '{@link org.univaq.hepsy.Channel#getNTo <em>NTo</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>NTo</em>'.
	 * @see org.univaq.hepsy.Channel#getNTo()
	 * @see #getChannel()
	 * @generated
	 */
	EReference getChannel_NTo();

	/**
	 * Returns the meta object for the reference '{@link org.univaq.hepsy.Channel#getPFrom <em>PFrom</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>PFrom</em>'.
	 * @see org.univaq.hepsy.Channel#getPFrom()
	 * @see #getChannel()
	 * @generated
	 */
	EReference getChannel_PFrom();

	/**
	 * Returns the meta object for the reference '{@link org.univaq.hepsy.Channel#getPTo <em>PTo</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>PTo</em>'.
	 * @see org.univaq.hepsy.Channel#getPTo()
	 * @see #getChannel()
	 * @generated
	 */
	EReference getChannel_PTo();

	/**
	 * Returns the meta object for the attribute '{@link org.univaq.hepsy.Channel#getQueueSize <em>Queue Size</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Queue Size</em>'.
	 * @see org.univaq.hepsy.Channel#getQueueSize()
	 * @see #getChannel()
	 * @generated
	 */
	EAttribute getChannel_QueueSize();

	/**
	 * Returns the meta object for the attribute '{@link org.univaq.hepsy.Channel#getTimeout <em>Timeout</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Timeout</em>'.
	 * @see org.univaq.hepsy.Channel#getTimeout()
	 * @see #getChannel()
	 * @generated
	 */
	EAttribute getChannel_Timeout();

	/**
	 * Returns the meta object for the attribute '{@link org.univaq.hepsy.Channel#isRendezVous <em>Rendez Vous</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Rendez Vous</em>'.
	 * @see org.univaq.hepsy.Channel#isRendezVous()
	 * @see #getChannel()
	 * @generated
	 */
	EAttribute getChannel_RendezVous();

	/**
	 * Returns the meta object for the containment reference '{@link org.univaq.hepsy.Channel#getMessage <em>Message</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference '<em>Message</em>'.
	 * @see org.univaq.hepsy.Channel#getMessage()
	 * @see #getChannel()
	 * @generated
	 */
	EReference getChannel_Message();

	/**
	 * Returns the meta object for the attribute '{@link org.univaq.hepsy.Channel#getDirection <em>Direction</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Direction</em>'.
	 * @see org.univaq.hepsy.Channel#getDirection()
	 * @see #getChannel()
	 * @generated
	 */
	EAttribute getChannel_Direction();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.NamedElement <em>Named Element</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Named Element</em>'.
	 * @see org.univaq.hepsy.NamedElement
	 * @generated
	 */
	EClass getNamedElement();

	/**
	 * Returns the meta object for the attribute '{@link org.univaq.hepsy.NamedElement#getName <em>Name</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Name</em>'.
	 * @see org.univaq.hepsy.NamedElement#getName()
	 * @see #getNamedElement()
	 * @generated
	 */
	EAttribute getNamedElement_Name();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.StructuredNode <em>Structured Node</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Structured Node</em>'.
	 * @see org.univaq.hepsy.StructuredNode
	 * @generated
	 */
	EClass getStructuredNode();

	/**
	 * Returns the meta object for the containment reference list '{@link org.univaq.hepsy.StructuredNode#getProcesses <em>Processes</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Processes</em>'.
	 * @see org.univaq.hepsy.StructuredNode#getProcesses()
	 * @see #getStructuredNode()
	 * @generated
	 */
	EReference getStructuredNode_Processes();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.Port <em>Port</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Port</em>'.
	 * @see org.univaq.hepsy.Port
	 * @generated
	 */
	EClass getPort();

	/**
	 * Returns the meta object for the containment reference list '{@link org.univaq.hepsy.Port#getPChannels <em>PChannels</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>PChannels</em>'.
	 * @see org.univaq.hepsy.Port#getPChannels()
	 * @see #getPort()
	 * @generated
	 */
	EReference getPort_PChannels();

	/**
	 * Returns the meta object for the reference '{@link org.univaq.hepsy.Port#getPortExtension <em>Port Extension</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Port Extension</em>'.
	 * @see org.univaq.hepsy.Port#getPortExtension()
	 * @see #getPort()
	 * @generated
	 */
	EReference getPort_PortExtension();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.Process <em>Process</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Process</em>'.
	 * @see org.univaq.hepsy.Process
	 * @generated
	 */
	EClass getProcess();

	/**
	 * Returns the meta object for the reference '{@link org.univaq.hepsy.Process#getProcessExtension <em>Process Extension</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Process Extension</em>'.
	 * @see org.univaq.hepsy.Process#getProcessExtension()
	 * @see #getProcess()
	 * @generated
	 */
	EReference getProcess_ProcessExtension();

	/**
	 * Returns the meta object for the attribute '{@link org.univaq.hepsy.Process#getPriority <em>Priority</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Priority</em>'.
	 * @see org.univaq.hepsy.Process#getPriority()
	 * @see #getProcess()
	 * @generated
	 */
	EAttribute getProcess_Priority();

	/**
	 * Returns the meta object for the attribute '{@link org.univaq.hepsy.Process#getCriticality <em>Criticality</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Criticality</em>'.
	 * @see org.univaq.hepsy.Process#getCriticality()
	 * @see #getProcess()
	 * @generated
	 */
	EAttribute getProcess_Criticality();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.Display <em>Display</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Display</em>'.
	 * @see org.univaq.hepsy.Display
	 * @generated
	 */
	EClass getDisplay();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.Stimulus <em>Stimulus</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Stimulus</em>'.
	 * @see org.univaq.hepsy.Stimulus
	 * @generated
	 */
	EClass getStimulus();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.Message <em>Message</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Message</em>'.
	 * @see org.univaq.hepsy.Message
	 * @generated
	 */
	EClass getMessage();

	/**
	 * Returns the meta object for the containment reference list '{@link org.univaq.hepsy.Message#getEntry <em>Entry</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Entry</em>'.
	 * @see org.univaq.hepsy.Message#getEntry()
	 * @see #getMessage()
	 * @generated
	 */
	EReference getMessage_Entry();

	/**
	 * Returns the meta object for class '{@link org.univaq.hepsy.Entry <em>Entry</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Entry</em>'.
	 * @see org.univaq.hepsy.Entry
	 * @generated
	 */
	EClass getEntry();

	/**
	 * Returns the meta object for the attribute '{@link org.univaq.hepsy.Entry#getType <em>Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Type</em>'.
	 * @see org.univaq.hepsy.Entry#getType()
	 * @see #getEntry()
	 * @generated
	 */
	EAttribute getEntry_Type();

	/**
	 * Returns the meta object for enum '{@link org.univaq.hepsy.DataType <em>Data Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for enum '<em>Data Type</em>'.
	 * @see org.univaq.hepsy.DataType
	 * @generated
	 */
	EEnum getDataType();

	/**
	 * Returns the meta object for enum '{@link org.univaq.hepsy.Direction <em>Direction</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for enum '<em>Direction</em>'.
	 * @see org.univaq.hepsy.Direction
	 * @generated
	 */
	EEnum getDirection();

	/**
	 * Returns the factory that creates the instances of the model.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the factory that creates the instances of the model.
	 * @generated
	 */
	HepsyFactory getHepsyFactory();

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
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.BehaviorSpecificationImpl <em>Behavior Specification</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.BehaviorSpecificationImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getBehaviorSpecification()
		 * @generated
		 */
		EClass BEHAVIOR_SPECIFICATION = eINSTANCE.getBehaviorSpecification();

		/**
		 * The meta object literal for the '<em><b>Nodes</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference BEHAVIOR_SPECIFICATION__NODES = eINSTANCE.getBehaviorSpecification_Nodes();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.NodeImpl <em>Node</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.NodeImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getNode()
		 * @generated
		 */
		EClass NODE = eINSTANCE.getNode();

		/**
		 * The meta object literal for the '<em><b>NChannels</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference NODE__NCHANNELS = eINSTANCE.getNode_NChannels();

		/**
		 * The meta object literal for the '<em><b>Ports</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference NODE__PORTS = eINSTANCE.getNode_Ports();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.ChannelImpl <em>Channel</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.ChannelImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getChannel()
		 * @generated
		 */
		EClass CHANNEL = eINSTANCE.getChannel();

		/**
		 * The meta object literal for the '<em><b>NFrom</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference CHANNEL__NFROM = eINSTANCE.getChannel_NFrom();

		/**
		 * The meta object literal for the '<em><b>NTo</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference CHANNEL__NTO = eINSTANCE.getChannel_NTo();

		/**
		 * The meta object literal for the '<em><b>PFrom</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference CHANNEL__PFROM = eINSTANCE.getChannel_PFrom();

		/**
		 * The meta object literal for the '<em><b>PTo</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference CHANNEL__PTO = eINSTANCE.getChannel_PTo();

		/**
		 * The meta object literal for the '<em><b>Queue Size</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute CHANNEL__QUEUE_SIZE = eINSTANCE.getChannel_QueueSize();

		/**
		 * The meta object literal for the '<em><b>Timeout</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute CHANNEL__TIMEOUT = eINSTANCE.getChannel_Timeout();

		/**
		 * The meta object literal for the '<em><b>Rendez Vous</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute CHANNEL__RENDEZ_VOUS = eINSTANCE.getChannel_RendezVous();

		/**
		 * The meta object literal for the '<em><b>Message</b></em>' containment reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference CHANNEL__MESSAGE = eINSTANCE.getChannel_Message();

		/**
		 * The meta object literal for the '<em><b>Direction</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute CHANNEL__DIRECTION = eINSTANCE.getChannel_Direction();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.NamedElementImpl <em>Named Element</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.NamedElementImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getNamedElement()
		 * @generated
		 */
		EClass NAMED_ELEMENT = eINSTANCE.getNamedElement();

		/**
		 * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute NAMED_ELEMENT__NAME = eINSTANCE.getNamedElement_Name();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.StructuredNodeImpl <em>Structured Node</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.StructuredNodeImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getStructuredNode()
		 * @generated
		 */
		EClass STRUCTURED_NODE = eINSTANCE.getStructuredNode();

		/**
		 * The meta object literal for the '<em><b>Processes</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference STRUCTURED_NODE__PROCESSES = eINSTANCE.getStructuredNode_Processes();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.PortImpl <em>Port</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.PortImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getPort()
		 * @generated
		 */
		EClass PORT = eINSTANCE.getPort();

		/**
		 * The meta object literal for the '<em><b>PChannels</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PORT__PCHANNELS = eINSTANCE.getPort_PChannels();

		/**
		 * The meta object literal for the '<em><b>Port Extension</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PORT__PORT_EXTENSION = eINSTANCE.getPort_PortExtension();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.ProcessImpl <em>Process</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.ProcessImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getProcess()
		 * @generated
		 */
		EClass PROCESS = eINSTANCE.getProcess();

		/**
		 * The meta object literal for the '<em><b>Process Extension</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PROCESS__PROCESS_EXTENSION = eINSTANCE.getProcess_ProcessExtension();

		/**
		 * The meta object literal for the '<em><b>Priority</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute PROCESS__PRIORITY = eINSTANCE.getProcess_Priority();

		/**
		 * The meta object literal for the '<em><b>Criticality</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute PROCESS__CRITICALITY = eINSTANCE.getProcess_Criticality();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.DisplayImpl <em>Display</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.DisplayImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getDisplay()
		 * @generated
		 */
		EClass DISPLAY = eINSTANCE.getDisplay();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.StimulusImpl <em>Stimulus</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.StimulusImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getStimulus()
		 * @generated
		 */
		EClass STIMULUS = eINSTANCE.getStimulus();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.MessageImpl <em>Message</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.MessageImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getMessage()
		 * @generated
		 */
		EClass MESSAGE = eINSTANCE.getMessage();

		/**
		 * The meta object literal for the '<em><b>Entry</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MESSAGE__ENTRY = eINSTANCE.getMessage_Entry();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.impl.EntryImpl <em>Entry</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.impl.EntryImpl
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getEntry()
		 * @generated
		 */
		EClass ENTRY = eINSTANCE.getEntry();

		/**
		 * The meta object literal for the '<em><b>Type</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute ENTRY__TYPE = eINSTANCE.getEntry_Type();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.DataType <em>Data Type</em>}' enum.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.DataType
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getDataType()
		 * @generated
		 */
		EEnum DATA_TYPE = eINSTANCE.getDataType();

		/**
		 * The meta object literal for the '{@link org.univaq.hepsy.Direction <em>Direction</em>}' enum.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.univaq.hepsy.Direction
		 * @see org.univaq.hepsy.impl.HepsyPackageImpl#getDirection()
		 * @generated
		 */
		EEnum DIRECTION = eINSTANCE.getDirection();

	}

} //HepsyPackage
