/**
 */
package org.univaq.hepsy;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Message</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.Message#getEntry <em>Entry</em>}</li>
 * </ul>
 *
 * @see org.univaq.hepsy.HepsyPackage#getMessage()
 * @model
 * @generated
 */
public interface Message extends NamedElement {
	/**
	 * Returns the value of the '<em><b>Entry</b></em>' containment reference list.
	 * The list contents are of type {@link org.univaq.hepsy.Entry}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Entry</em>' containment reference list.
	 * @see org.univaq.hepsy.HepsyPackage#getMessage_Entry()
	 * @model containment="true"
	 * @generated
	 */
	EList<Entry> getEntry();

} // Message
