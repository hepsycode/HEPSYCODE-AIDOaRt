/**
 */
package org.univaq.hepsy.impl;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.univaq.hepsy.Channel;
import org.univaq.hepsy.HepsyPackage;
import org.univaq.hepsy.Message;
import org.univaq.hepsy.Node;
import org.univaq.hepsy.Port;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Channel</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#getNFrom <em>NFrom</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#getNTo <em>NTo</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#getPFrom <em>PFrom</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#getPTo <em>PTo</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#getQueueSize <em>Queue Size</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#getTimeout <em>Timeout</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#isRendezVous <em>Rendez Vous</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#getDirection <em>Direction</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ChannelImpl#getMessage <em>Message</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ChannelImpl extends NamedElementImpl implements Channel {
	/**
	 * The cached value of the '{@link #getNFrom() <em>NFrom</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getNFrom()
	 * @generated
	 * @ordered
	 */
	protected Node nFrom;

	/**
	 * The cached value of the '{@link #getNTo() <em>NTo</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getNTo()
	 * @generated
	 * @ordered
	 */
	protected Node nTo;

	/**
	 * The cached value of the '{@link #getPFrom() <em>PFrom</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getPFrom()
	 * @generated
	 * @ordered
	 */
	protected Port pFrom;

	/**
	 * The cached value of the '{@link #getPTo() <em>PTo</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getPTo()
	 * @generated
	 * @ordered
	 */
	protected Port pTo;

	/**
	 * The default value of the '{@link #getQueueSize() <em>Queue Size</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getQueueSize()
	 * @generated
	 * @ordered
	 */
	protected static final int QUEUE_SIZE_EDEFAULT = 0;

	/**
	 * The cached value of the '{@link #getQueueSize() <em>Queue Size</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getQueueSize()
	 * @generated
	 * @ordered
	 */
	protected int queueSize = QUEUE_SIZE_EDEFAULT;

	/**
	 * The default value of the '{@link #getTimeout() <em>Timeout</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getTimeout()
	 * @generated
	 * @ordered
	 */
	protected static final int TIMEOUT_EDEFAULT = 0;

	/**
	 * The cached value of the '{@link #getTimeout() <em>Timeout</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getTimeout()
	 * @generated
	 * @ordered
	 */
	protected int timeout = TIMEOUT_EDEFAULT;

	/**
	 * The default value of the '{@link #isRendezVous() <em>Rendez Vous</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isRendezVous()
	 * @generated
	 * @ordered
	 */
	protected static final boolean RENDEZ_VOUS_EDEFAULT = false;

	/**
	 * The cached value of the '{@link #isRendezVous() <em>Rendez Vous</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isRendezVous()
	 * @generated
	 * @ordered
	 */
	protected boolean rendezVous = RENDEZ_VOUS_EDEFAULT;

	/**
	 * The default value of the '{@link #getDirection() <em>Direction</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getDirection()
	 * @generated
	 * @ordered
	 */
	protected static final String DIRECTION_EDEFAULT = null;

	/**
	 * The cached value of the '{@link #getDirection() <em>Direction</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getDirection()
	 * @generated
	 * @ordered
	 */
	protected String direction = DIRECTION_EDEFAULT;

	/**
	 * The cached value of the '{@link #getMessage() <em>Message</em>}' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getMessage()
	 * @generated
	 * @ordered
	 */
	protected Message message;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected ChannelImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return HepsyPackage.Literals.CHANNEL;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Node getNFrom() {
		if (nFrom != null && nFrom.eIsProxy()) {
			InternalEObject oldNFrom = (InternalEObject) nFrom;
			nFrom = (Node) eResolveProxy(oldNFrom);
			if (nFrom != oldNFrom) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, HepsyPackage.CHANNEL__NFROM, oldNFrom,
							nFrom));
			}
		}
		return nFrom;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Node basicGetNFrom() {
		return nFrom;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setNFrom(Node newNFrom) {
		Node oldNFrom = nFrom;
		nFrom = newNFrom;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__NFROM, oldNFrom, nFrom));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Node getNTo() {
		if (nTo != null && nTo.eIsProxy()) {
			InternalEObject oldNTo = (InternalEObject) nTo;
			nTo = (Node) eResolveProxy(oldNTo);
			if (nTo != oldNTo) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, HepsyPackage.CHANNEL__NTO, oldNTo, nTo));
			}
		}
		return nTo;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Node basicGetNTo() {
		return nTo;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setNTo(Node newNTo) {
		Node oldNTo = nTo;
		nTo = newNTo;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__NTO, oldNTo, nTo));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Port getPFrom() {
		if (pFrom != null && pFrom.eIsProxy()) {
			InternalEObject oldPFrom = (InternalEObject) pFrom;
			pFrom = (Port) eResolveProxy(oldPFrom);
			if (pFrom != oldPFrom) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, HepsyPackage.CHANNEL__PFROM, oldPFrom,
							pFrom));
			}
		}
		return pFrom;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Port basicGetPFrom() {
		return pFrom;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setPFrom(Port newPFrom) {
		Port oldPFrom = pFrom;
		pFrom = newPFrom;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__PFROM, oldPFrom, pFrom));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Port getPTo() {
		if (pTo != null && pTo.eIsProxy()) {
			InternalEObject oldPTo = (InternalEObject) pTo;
			pTo = (Port) eResolveProxy(oldPTo);
			if (pTo != oldPTo) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, HepsyPackage.CHANNEL__PTO, oldPTo, pTo));
			}
		}
		return pTo;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Port basicGetPTo() {
		return pTo;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setPTo(Port newPTo) {
		Port oldPTo = pTo;
		pTo = newPTo;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__PTO, oldPTo, pTo));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getQueueSize() {
		return queueSize;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setQueueSize(int newQueueSize) {
		int oldQueueSize = queueSize;
		queueSize = newQueueSize;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__QUEUE_SIZE, oldQueueSize,
					queueSize));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getTimeout() {
		return timeout;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setTimeout(int newTimeout) {
		int oldTimeout = timeout;
		timeout = newTimeout;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__TIMEOUT, oldTimeout, timeout));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isRendezVous() {
		return rendezVous;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setRendezVous(boolean newRendezVous) {
		boolean oldRendezVous = rendezVous;
		rendezVous = newRendezVous;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__RENDEZ_VOUS, oldRendezVous,
					rendezVous));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Message getMessage() {
		return message;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NotificationChain basicSetMessage(Message newMessage, NotificationChain msgs) {
		Message oldMessage = message;
		message = newMessage;
		if (eNotificationRequired()) {
			ENotificationImpl notification = new ENotificationImpl(this, Notification.SET,
					HepsyPackage.CHANNEL__MESSAGE, oldMessage, newMessage);
			if (msgs == null)
				msgs = notification;
			else
				msgs.add(notification);
		}
		return msgs;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setMessage(Message newMessage) {
		if (newMessage != message) {
			NotificationChain msgs = null;
			if (message != null)
				msgs = ((InternalEObject) message).eInverseRemove(this,
						EOPPOSITE_FEATURE_BASE - HepsyPackage.CHANNEL__MESSAGE, null, msgs);
			if (newMessage != null)
				msgs = ((InternalEObject) newMessage).eInverseAdd(this,
						EOPPOSITE_FEATURE_BASE - HepsyPackage.CHANNEL__MESSAGE, null, msgs);
			msgs = basicSetMessage(newMessage, msgs);
			if (msgs != null)
				msgs.dispatch();
		} else if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__MESSAGE, newMessage,
					newMessage));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseRemove(InternalEObject otherEnd, int featureID, NotificationChain msgs) {
		switch (featureID) {
		case HepsyPackage.CHANNEL__MESSAGE:
			return basicSetMessage(null, msgs);
		}
		return super.eInverseRemove(otherEnd, featureID, msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getDirection() {
		return direction;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setDirection(String newDirection) {
		String oldDirection = direction;
		direction = newDirection;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.CHANNEL__DIRECTION, oldDirection,
					direction));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
		case HepsyPackage.CHANNEL__NFROM:
			if (resolve)
				return getNFrom();
			return basicGetNFrom();
		case HepsyPackage.CHANNEL__NTO:
			if (resolve)
				return getNTo();
			return basicGetNTo();
		case HepsyPackage.CHANNEL__PFROM:
			if (resolve)
				return getPFrom();
			return basicGetPFrom();
		case HepsyPackage.CHANNEL__PTO:
			if (resolve)
				return getPTo();
			return basicGetPTo();
		case HepsyPackage.CHANNEL__QUEUE_SIZE:
			return getQueueSize();
		case HepsyPackage.CHANNEL__TIMEOUT:
			return getTimeout();
		case HepsyPackage.CHANNEL__RENDEZ_VOUS:
			return isRendezVous();
		case HepsyPackage.CHANNEL__DIRECTION:
			return getDirection();
		case HepsyPackage.CHANNEL__MESSAGE:
			return getMessage();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@SuppressWarnings("unchecked")
	@Override
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
		case HepsyPackage.CHANNEL__NFROM:
			setNFrom((Node) newValue);
			return;
		case HepsyPackage.CHANNEL__NTO:
			setNTo((Node) newValue);
			return;
		case HepsyPackage.CHANNEL__PFROM:
			setPFrom((Port) newValue);
			return;
		case HepsyPackage.CHANNEL__PTO:
			setPTo((Port) newValue);
			return;
		case HepsyPackage.CHANNEL__QUEUE_SIZE:
			setQueueSize((Integer) newValue);
			return;
		case HepsyPackage.CHANNEL__TIMEOUT:
			setTimeout((Integer) newValue);
			return;
		case HepsyPackage.CHANNEL__RENDEZ_VOUS:
			setRendezVous((Boolean) newValue);
			return;
		case HepsyPackage.CHANNEL__DIRECTION:
			setDirection((String) newValue);
			return;
		case HepsyPackage.CHANNEL__MESSAGE:
			setMessage((Message) newValue);
			return;
		}
		super.eSet(featureID, newValue);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eUnset(int featureID) {
		switch (featureID) {
		case HepsyPackage.CHANNEL__NFROM:
			setNFrom((Node) null);
			return;
		case HepsyPackage.CHANNEL__NTO:
			setNTo((Node) null);
			return;
		case HepsyPackage.CHANNEL__PFROM:
			setPFrom((Port) null);
			return;
		case HepsyPackage.CHANNEL__PTO:
			setPTo((Port) null);
			return;
		case HepsyPackage.CHANNEL__QUEUE_SIZE:
			setQueueSize(QUEUE_SIZE_EDEFAULT);
			return;
		case HepsyPackage.CHANNEL__TIMEOUT:
			setTimeout(TIMEOUT_EDEFAULT);
			return;
		case HepsyPackage.CHANNEL__RENDEZ_VOUS:
			setRendezVous(RENDEZ_VOUS_EDEFAULT);
			return;
		case HepsyPackage.CHANNEL__DIRECTION:
			setDirection(DIRECTION_EDEFAULT);
			return;
		case HepsyPackage.CHANNEL__MESSAGE:
			setMessage((Message) null);
			return;
		}
		super.eUnset(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public boolean eIsSet(int featureID) {
		switch (featureID) {
		case HepsyPackage.CHANNEL__NFROM:
			return nFrom != null;
		case HepsyPackage.CHANNEL__NTO:
			return nTo != null;
		case HepsyPackage.CHANNEL__PFROM:
			return pFrom != null;
		case HepsyPackage.CHANNEL__PTO:
			return pTo != null;
		case HepsyPackage.CHANNEL__QUEUE_SIZE:
			return queueSize != QUEUE_SIZE_EDEFAULT;
		case HepsyPackage.CHANNEL__TIMEOUT:
			return timeout != TIMEOUT_EDEFAULT;
		case HepsyPackage.CHANNEL__RENDEZ_VOUS:
			return rendezVous != RENDEZ_VOUS_EDEFAULT;
		case HepsyPackage.CHANNEL__DIRECTION:
			return DIRECTION_EDEFAULT == null ? direction != null : !DIRECTION_EDEFAULT.equals(direction);
		case HepsyPackage.CHANNEL__MESSAGE:
			return message != null;
		}
		return super.eIsSet(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString() {
		if (eIsProxy())
			return super.toString();

		StringBuilder result = new StringBuilder(super.toString());
		result.append(" (queueSize: ");
		result.append(queueSize);
		result.append(", timeout: ");
		result.append(timeout);
		result.append(", rendezVous: ");
		result.append(rendezVous);
		result.append(", direction: ");
		result.append(direction);
		result.append(')');
		return result.toString();
	}

} //ChannelImpl
