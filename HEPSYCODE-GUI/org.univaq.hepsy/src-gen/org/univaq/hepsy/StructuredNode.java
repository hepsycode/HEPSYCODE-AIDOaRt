/**
 */
package org.univaq.hepsy;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Structured Node</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.StructuredNode#getProcesses <em>Processes</em>}</li>
 * </ul>
 *
 * @see org.univaq.hepsy.HepsyPackage#getStructuredNode()
 * @model
 * @generated
 */
public interface StructuredNode extends Node {
	/**
	 * Returns the value of the '<em><b>Processes</b></em>' containment reference list.
	 * The list contents are of type {@link org.univaq.hepsy.Process}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Processes</em>' containment reference list.
	 * @see org.univaq.hepsy.HepsyPackage#getStructuredNode_Processes()
	 * @model containment="true"
	 * @generated
	 */
	EList<org.univaq.hepsy.Process> getProcesses();

} // StructuredNode
