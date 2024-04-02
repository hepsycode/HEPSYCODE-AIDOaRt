/**
 */
package org.univaq.hepsy;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Channel</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.Channel#getNFrom <em>NFrom</em>}</li>
 *   <li>{@link org.univaq.hepsy.Channel#getNTo <em>NTo</em>}</li>
 *   <li>{@link org.univaq.hepsy.Channel#getPFrom <em>PFrom</em>}</li>
 *   <li>{@link org.univaq.hepsy.Channel#getPTo <em>PTo</em>}</li>
 *   <li>{@link org.univaq.hepsy.Channel#getQueueSize <em>Queue Size</em>}</li>
 *   <li>{@link org.univaq.hepsy.Channel#getTimeout <em>Timeout</em>}</li>
 *   <li>{@link org.univaq.hepsy.Channel#isRendezVous <em>Rendez Vous</em>}</li>
 *   <li>{@link org.univaq.hepsy.Channel#getDirection <em>Direction</em>}</li>
 *   <li>{@link org.univaq.hepsy.Channel#getMessage <em>Message</em>}</li>
 * </ul>
 *
 * @see org.univaq.hepsy.HepsyPackage#getChannel()
 * @model
 * @generated
 */
public interface Channel extends NamedElement {
	/**
	 * Returns the value of the '<em><b>NFrom</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>NFrom</em>' reference.
	 * @see #setNFrom(Node)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_NFrom()
	 * @model required="true"
	 * @generated
	 */
	Node getNFrom();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#getNFrom <em>NFrom</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>NFrom</em>' reference.
	 * @see #getNFrom()
	 * @generated
	 */
	void setNFrom(Node value);

	/**
	 * Returns the value of the '<em><b>NTo</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>NTo</em>' reference.
	 * @see #setNTo(Node)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_NTo()
	 * @model required="true"
	 * @generated
	 */
	Node getNTo();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#getNTo <em>NTo</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>NTo</em>' reference.
	 * @see #getNTo()
	 * @generated
	 */
	void setNTo(Node value);

	/**
	 * Returns the value of the '<em><b>PFrom</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>PFrom</em>' reference.
	 * @see #setPFrom(Port)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_PFrom()
	 * @model required="true"
	 * @generated
	 */
	Port getPFrom();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#getPFrom <em>PFrom</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>PFrom</em>' reference.
	 * @see #getPFrom()
	 * @generated
	 */
	void setPFrom(Port value);

	/**
	 * Returns the value of the '<em><b>PTo</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>PTo</em>' reference.
	 * @see #setPTo(Port)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_PTo()
	 * @model required="true"
	 * @generated
	 */
	Port getPTo();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#getPTo <em>PTo</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>PTo</em>' reference.
	 * @see #getPTo()
	 * @generated
	 */
	void setPTo(Port value);

	/**
	 * Returns the value of the '<em><b>Queue Size</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Queue Size</em>' attribute.
	 * @see #setQueueSize(int)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_QueueSize()
	 * @model
	 * @generated
	 */
	int getQueueSize();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#getQueueSize <em>Queue Size</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Queue Size</em>' attribute.
	 * @see #getQueueSize()
	 * @generated
	 */
	void setQueueSize(int value);

	/**
	 * Returns the value of the '<em><b>Timeout</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Timeout</em>' attribute.
	 * @see #setTimeout(int)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_Timeout()
	 * @model
	 * @generated
	 */
	int getTimeout();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#getTimeout <em>Timeout</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Timeout</em>' attribute.
	 * @see #getTimeout()
	 * @generated
	 */
	void setTimeout(int value);

	/**
	 * Returns the value of the '<em><b>Rendez Vous</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Rendez Vous</em>' attribute.
	 * @see #setRendezVous(boolean)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_RendezVous()
	 * @model
	 * @generated
	 */
	boolean isRendezVous();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#isRendezVous <em>Rendez Vous</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Rendez Vous</em>' attribute.
	 * @see #isRendezVous()
	 * @generated
	 */
	void setRendezVous(boolean value);

	/**
	 * Returns the value of the '<em><b>Message</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Message</em>' containment reference.
	 * @see #setMessage(Message)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_Message()
	 * @model containment="true"
	 * @generated
	 */
	Message getMessage();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#getMessage <em>Message</em>}' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Message</em>' containment reference.
	 * @see #getMessage()
	 * @generated
	 */
	void setMessage(Message value);

	/**
	 * Returns the value of the '<em><b>Direction</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Direction</em>' attribute.
	 * @see #setDirection(String)
	 * @see org.univaq.hepsy.HepsyPackage#getChannel_Direction()
	 * @model
	 * @generated
	 */
	String getDirection();

	/**
	 * Sets the value of the '{@link org.univaq.hepsy.Channel#getDirection <em>Direction</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Direction</em>' attribute.
	 * @see #getDirection()
	 * @generated
	 */
	void setDirection(String value);

} // Channel
