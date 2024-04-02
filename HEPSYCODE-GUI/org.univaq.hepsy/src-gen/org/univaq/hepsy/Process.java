/**
 */
package org.univaq.hepsy;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Process</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.Process#getProcessExtension <em>Process Extension</em>}</li>
 *   <li>{@link org.univaq.hepsy.Process#getPriority <em>Priority</em>}</li>
 *   <li>{@link org.univaq.hepsy.Process#getCriticality <em>Criticality</em>}</li>
 * </ul>
 *
 * @see org.univaq.hepsy.HepsyPackage#getProcess()
 * @model
 * @generated
 */
public interface Process extends Node {

	/**
	 * Returns the value of the '<em><b>Process Extension</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Process Extension</em>' reference.
	 * @see #setProcessExtension(Port)
	 * @see org.univaq.hepsy.HepsyPackage#getProcess_ProcessExtension()
	 * @model
	 * @generated
	 */
	Port getProcessExtension();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Process#getProcessExtension <em>Process Extension</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Process Extension</em>' reference.
	 * @see #getProcessExtension()
	 * @generated
	 */
	void setProcessExtension(Port value);

	/**
	 * Returns the value of the '<em><b>Priority</b></em>' attribute.
	 * The default value is <code>"1"</code>.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Priority</em>' attribute.
	 * @see #setPriority(int)
	 * @see org.univaq.hepsy.HepsyPackage#getProcess_Priority()
	 * @model default="1"
	 * @generated
	 */
	int getPriority();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Process#getPriority <em>Priority</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Priority</em>' attribute.
	 * @see #getPriority()
	 * @generated
	 */
	void setPriority(int value);

	/**
	 * Returns the value of the '<em><b>Criticality</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Criticality</em>' attribute.
	 * @see #setCriticality(int)
	 * @see org.univaq.hepsy.HepsyPackage#getProcess_Criticality()
	 * @model
	 * @generated
	 */
	int getCriticality();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Process#getCriticality <em>Criticality</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Criticality</em>' attribute.
	 * @see #getCriticality()
	 * @generated
	 */
	void setCriticality(int value);
} // Process
