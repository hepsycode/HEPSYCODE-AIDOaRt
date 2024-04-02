/**
 */
package at.jku.se.ecorexes.ecoreXES;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Log</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Log#getResource <em>Resource</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Log#getEvent <em>Event</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Log#getAttributes <em>Attributes</em>}</li>
 * </ul>
 *
 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getLog()
 * @model
 * @generated
 */
public interface Log extends EObject {
	/**
	 * Returns the value of the '<em><b>Resource</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Resource</em>' attribute.
	 * @see #setResource(String)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getLog_Resource()
	 * @model
	 * @generated
	 */
	String getResource();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.Log#getResource <em>Resource</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Resource</em>' attribute.
	 * @see #getResource()
	 * @generated
	 */
	void setResource(String value);

	/**
	 * Returns the value of the '<em><b>Event</b></em>' containment reference list.
	 * The list contents are of type {@link at.jku.se.ecorexes.ecoreXES.Event}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Event</em>' containment reference list.
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getLog_Event()
	 * @model containment="true"
	 * @generated
	 */
	EList<Event> getEvent();

	/**
	 * Returns the value of the '<em><b>Attributes</b></em>' containment reference list.
	 * The list contents are of type {@link at.jku.se.ecorexes.ecoreXES.Attributes}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Attributes</em>' containment reference list.
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getLog_Attributes()
	 * @model containment="true"
	 * @generated
	 */
	EList<Attributes> getAttributes();

} // Log
