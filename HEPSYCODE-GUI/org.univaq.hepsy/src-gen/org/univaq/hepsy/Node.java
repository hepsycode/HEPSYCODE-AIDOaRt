/**
 */
package org.univaq.hepsy;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Node</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.Node#getNChannels <em>NChannels</em>}</li>
 *   <li>{@link org.univaq.hepsy.Node#getPorts <em>Ports</em>}</li>
 * </ul>
 *
 * @see org.univaq.hepsy.HepsyPackage#getNode()
 * @model abstract="true"
 * @generated
 */
public interface Node extends NamedElement {
	/**
	 * Returns the value of the '<em><b>NChannels</b></em>' containment reference list.
	 * The list contents are of type {@link org.univaq.hepsy.Channel}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>NChannels</em>' containment reference list.
	 * @see org.univaq.hepsy.HepsyPackage#getNode_NChannels()
	 * @model containment="true"
	 * @generated
	 */
	EList<Channel> getNChannels();

	/**
	 * Returns the value of the '<em><b>Ports</b></em>' containment reference list.
	 * The list contents are of type {@link org.univaq.hepsy.Port}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Ports</em>' containment reference list.
	 * @see org.univaq.hepsy.HepsyPackage#getNode_Ports()
	 * @model containment="true"
	 * @generated
	 */
	EList<Port> getPorts();

} // Node
