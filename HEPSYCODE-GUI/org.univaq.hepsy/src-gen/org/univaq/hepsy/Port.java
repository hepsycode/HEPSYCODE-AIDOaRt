/**
 */
package org.univaq.hepsy;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Port</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.Port#getPChannels <em>PChannels</em>}</li>
 *   <li>{@link org.univaq.hepsy.Port#getPortExtension <em>Port Extension</em>}</li>
 * </ul>
 *
 * @see org.univaq.hepsy.HepsyPackage#getPort()
 * @model
 * @generated
 */
public interface Port extends NamedElement {
	/**
	 * Returns the value of the '<em><b>PChannels</b></em>' containment reference list.
	 * The list contents are of type {@link org.univaq.hepsy.Channel}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>PChannels</em>' containment reference list.
	 * @see org.univaq.hepsy.HepsyPackage#getPort_PChannels()
	 * @model containment="true"
	 * @generated
	 */
	EList<Channel> getPChannels();

	/**
	 * Returns the value of the '<em><b>Port Extension</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Port Extension</em>' reference.
	 * @see #setPortExtension(org.univaq.hepsy.Process)
	 * @see org.univaq.hepsy.HepsyPackage#getPort_PortExtension()
	 * @model
	 * @generated
	 */
	org.univaq.hepsy.Process getPortExtension();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Port#getPortExtension <em>Port Extension</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Port Extension</em>' reference.
	 * @see #getPortExtension()
	 * @generated
	 */
	void setPortExtension(org.univaq.hepsy.Process value);

} // Port
