/**
 */
package org.univaq.hepsy;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Behavior Specification</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.BehaviorSpecification#getNodes <em>Nodes</em>}</li>
 * </ul>
 *
 * @see org.univaq.hepsy.HepsyPackage#getBehaviorSpecification()
 * @model
 * @generated
 */
public interface BehaviorSpecification extends NamedElement {
	/**
	 * Returns the value of the '<em><b>Nodes</b></em>' containment reference list.
	 * The list contents are of type {@link org.univaq.hepsy.Node}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Nodes</em>' containment reference list.
	 * @see org.univaq.hepsy.HepsyPackage#getBehaviorSpecification_Nodes()
	 * @model containment="true"
	 * @generated
	 */
	EList<Node> getNodes();

} // BehaviorSpecification
