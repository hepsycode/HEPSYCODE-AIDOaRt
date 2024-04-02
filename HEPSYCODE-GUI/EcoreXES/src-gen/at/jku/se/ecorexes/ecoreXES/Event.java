/**
 */
package at.jku.se.ecorexes.ecoreXES;

import java.util.Date;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Event</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Event#isSet <em>Set</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Event#getTimestamp <em>Timestamp</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Event#getFatureAndClass <em>Fature And Class</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Event#getId <em>Id</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Event#getReferencevalue <em>Referencevalue</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Event#getDataValue <em>Data Value</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.Event#getEventType <em>Event Type</em>}</li>
 * </ul>
 *
 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEvent()
 * @model
 * @generated
 */
public interface Event extends EObject {
	/**
	 * Returns the value of the '<em><b>Set</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Set</em>' attribute.
	 * @see #setSet(boolean)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEvent_Set()
	 * @model
	 * @generated
	 */
	boolean isSet();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.Event#isSet <em>Set</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Set</em>' attribute.
	 * @see #isSet()
	 * @generated
	 */
	void setSet(boolean value);

	/**
	 * Returns the value of the '<em><b>Timestamp</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Timestamp</em>' attribute.
	 * @see #setTimestamp(Date)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEvent_Timestamp()
	 * @model
	 * @generated
	 */
	Date getTimestamp();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.Event#getTimestamp <em>Timestamp</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Timestamp</em>' attribute.
	 * @see #getTimestamp()
	 * @generated
	 */
	void setTimestamp(Date value);

	/**
	 * Returns the value of the '<em><b>Fature And Class</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Fature And Class</em>' reference.
	 * @see #setFatureAndClass(FeatureAndClass)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEvent_FatureAndClass()
	 * @model required="true"
	 * @generated
	 */
	FeatureAndClass getFatureAndClass();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.Event#getFatureAndClass <em>Fature And Class</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Fature And Class</em>' reference.
	 * @see #getFatureAndClass()
	 * @generated
	 */
	void setFatureAndClass(FeatureAndClass value);

	/**
	 * Returns the value of the '<em><b>Id</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Id</em>' reference.
	 * @see #setId(ID)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEvent_Id()
	 * @model required="true"
	 * @generated
	 */
	ID getId();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.Event#getId <em>Id</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Id</em>' reference.
	 * @see #getId()
	 * @generated
	 */
	void setId(ID value);

	/**
	 * Returns the value of the '<em><b>Referencevalue</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Referencevalue</em>' reference.
	 * @see #setReferencevalue(ReferenceValue)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEvent_Referencevalue()
	 * @model
	 * @generated
	 */
	ReferenceValue getReferencevalue();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.Event#getReferencevalue <em>Referencevalue</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Referencevalue</em>' reference.
	 * @see #getReferencevalue()
	 * @generated
	 */
	void setReferencevalue(ReferenceValue value);

	/**
	 * Returns the value of the '<em><b>Data Value</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Data Value</em>' attribute.
	 * @see #setDataValue(String)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEvent_DataValue()
	 * @model
	 * @generated
	 */
	String getDataValue();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.Event#getDataValue <em>Data Value</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Data Value</em>' attribute.
	 * @see #getDataValue()
	 * @generated
	 */
	void setDataValue(String value);

	/**
	 * Returns the value of the '<em><b>Event Type</b></em>' attribute.
	 * The literals are from the enumeration {@link at.jku.se.ecorexes.ecoreXES.EventType}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Event Type</em>' attribute.
	 * @see at.jku.se.ecorexes.ecoreXES.EventType
	 * @see #setEventType(EventType)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEvent_EventType()
	 * @model
	 * @generated
	 */
	EventType getEventType();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.Event#getEventType <em>Event Type</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Event Type</em>' attribute.
	 * @see at.jku.se.ecorexes.ecoreXES.EventType
	 * @see #getEventType()
	 * @generated
	 */
	void setEventType(EventType value);

} // Event
