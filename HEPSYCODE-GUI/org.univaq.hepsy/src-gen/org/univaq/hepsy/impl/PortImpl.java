/**
 */
package org.univaq.hepsy.impl;

import java.util.Collection;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;
import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;

import org.univaq.hepsy.Channel;
import org.univaq.hepsy.HepsyPackage;
import org.univaq.hepsy.Port;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Port</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.impl.PortImpl#getPChannels <em>PChannels</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.PortImpl#getPortExtension <em>Port Extension</em>}</li>
 * </ul>
 *
 * @generated
 */
public class PortImpl extends NamedElementImpl implements Port {
	/**
	 * The cached value of the '{@link #getPChannels() <em>PChannels</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getPChannels()
	 * @generated
	 * @ordered
	 */
	protected EList<Channel> pChannels;

	/**
	 * The cached value of the '{@link #getPortExtension() <em>Port Extension</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getPortExtension()
	 * @generated
	 * @ordered
	 */
	protected org.univaq.hepsy.Process portExtension;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected PortImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return HepsyPackage.Literals.PORT;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Channel> getPChannels() {
		if (pChannels == null) {
			pChannels = new EObjectContainmentEList<Channel>(Channel.class, this, HepsyPackage.PORT__PCHANNELS);
		}
		return pChannels;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public org.univaq.hepsy.Process getPortExtension() {
		if (portExtension != null && portExtension.eIsProxy()) {
			InternalEObject oldPortExtension = (InternalEObject) portExtension;
			portExtension = (org.univaq.hepsy.Process) eResolveProxy(oldPortExtension);
			if (portExtension != oldPortExtension) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, HepsyPackage.PORT__PORT_EXTENSION,
							oldPortExtension, portExtension));
			}
		}
		return portExtension;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public org.univaq.hepsy.Process basicGetPortExtension() {
		return portExtension;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setPortExtension(org.univaq.hepsy.Process newPortExtension) {
		org.univaq.hepsy.Process oldPortExtension = portExtension;
		portExtension = newPortExtension;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.PORT__PORT_EXTENSION, oldPortExtension,
					portExtension));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseRemove(InternalEObject otherEnd, int featureID, NotificationChain msgs) {
		switch (featureID) {
		case HepsyPackage.PORT__PCHANNELS:
			return ((InternalEList<?>) getPChannels()).basicRemove(otherEnd, msgs);
		}
		return super.eInverseRemove(otherEnd, featureID, msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
		case HepsyPackage.PORT__PCHANNELS:
			return getPChannels();
		case HepsyPackage.PORT__PORT_EXTENSION:
			if (resolve)
				return getPortExtension();
			return basicGetPortExtension();
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
		case HepsyPackage.PORT__PCHANNELS:
			getPChannels().clear();
			getPChannels().addAll((Collection<? extends Channel>) newValue);
			return;
		case HepsyPackage.PORT__PORT_EXTENSION:
			setPortExtension((org.univaq.hepsy.Process) newValue);
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
		case HepsyPackage.PORT__PCHANNELS:
			getPChannels().clear();
			return;
		case HepsyPackage.PORT__PORT_EXTENSION:
			setPortExtension((org.univaq.hepsy.Process) null);
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
		case HepsyPackage.PORT__PCHANNELS:
			return pChannels != null && !pChannels.isEmpty();
		case HepsyPackage.PORT__PORT_EXTENSION:
			return portExtension != null;
		}
		return super.eIsSet(featureID);
	}

} //PortImpl
