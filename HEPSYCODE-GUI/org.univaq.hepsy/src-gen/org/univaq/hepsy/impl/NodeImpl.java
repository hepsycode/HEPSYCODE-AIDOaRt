/**
 */
package org.univaq.hepsy.impl;

import java.util.Collection;

import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;

import org.univaq.hepsy.Channel;
import org.univaq.hepsy.HepsyPackage;
import org.univaq.hepsy.Node;
import org.univaq.hepsy.Port;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Node</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.impl.NodeImpl#getNChannels <em>NChannels</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.NodeImpl#getPorts <em>Ports</em>}</li>
 * </ul>
 *
 * @generated
 */
public abstract class NodeImpl extends NamedElementImpl implements Node {
	/**
	 * The cached value of the '{@link #getNChannels() <em>NChannels</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getNChannels()
	 * @generated
	 * @ordered
	 */
	protected EList<Channel> nChannels;

	/**
	 * The cached value of the '{@link #getPorts() <em>Ports</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getPorts()
	 * @generated
	 * @ordered
	 */
	protected EList<Port> ports;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected NodeImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return HepsyPackage.Literals.NODE;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Channel> getNChannels() {
		if (nChannels == null) {
			nChannels = new EObjectContainmentEList<Channel>(Channel.class, this, HepsyPackage.NODE__NCHANNELS);
		}
		return nChannels;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Port> getPorts() {
		if (ports == null) {
			ports = new EObjectContainmentEList<Port>(Port.class, this, HepsyPackage.NODE__PORTS);
		}
		return ports;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseRemove(InternalEObject otherEnd, int featureID, NotificationChain msgs) {
		switch (featureID) {
		case HepsyPackage.NODE__NCHANNELS:
			return ((InternalEList<?>) getNChannels()).basicRemove(otherEnd, msgs);
		case HepsyPackage.NODE__PORTS:
			return ((InternalEList<?>) getPorts()).basicRemove(otherEnd, msgs);
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
		case HepsyPackage.NODE__NCHANNELS:
			return getNChannels();
		case HepsyPackage.NODE__PORTS:
			return getPorts();
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
		case HepsyPackage.NODE__NCHANNELS:
			getNChannels().clear();
			getNChannels().addAll((Collection<? extends Channel>) newValue);
			return;
		case HepsyPackage.NODE__PORTS:
			getPorts().clear();
			getPorts().addAll((Collection<? extends Port>) newValue);
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
		case HepsyPackage.NODE__NCHANNELS:
			getNChannels().clear();
			return;
		case HepsyPackage.NODE__PORTS:
			getPorts().clear();
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
		case HepsyPackage.NODE__NCHANNELS:
			return nChannels != null && !nChannels.isEmpty();
		case HepsyPackage.NODE__PORTS:
			return ports != null && !ports.isEmpty();
		}
		return super.eIsSet(featureID);
	}

} //NodeImpl
