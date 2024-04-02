/**
 */
package org.univaq.hepsy;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Stuctured Node</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.StucturedNode#getProcesses <em>Processes</em>}</li>
 * </ul>
 *
 * @see org.univaq.hepsy.HepsyPackage#getStucturedNode()
 * @model
 * @generated
 */
public interface StucturedNode extends Node {

	/**
	 * Returns the value of the '<em><b>Processes</b></em>' containment reference list.
	 * The list contents are of type {@link org.univaq.hepsy.Process}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Processes</em>' containment reference list.
	 * @see org.univaq.hepsy.HepsyPackage#getStucturedNode_Processes()
	 * @model containment="true"
	 * @generated
	 */
	EList<org.univaq.hepsy.Process> getProcesses();
} // StucturedNode
